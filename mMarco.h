#ifndef MMARCO_H_INCLUDED
#define MMARCO_H_INCLUDED

//绝对不允许重名

/*
#define TEST(SUITE, CASE) \
do \
{ \
    struct TestSuite* pTs = ts_malloc(#SUITE); \
    struct TestCase* pTc = tc_malloc(#CASE); \
    ts_addToSuite(pTs, pTc); \
    tt_addToTable(table, pTs); \
} while (0);
*/

#define TEST(SUITE, CASE) \
void test_##SUITE##_##CASE(); \
static void init_##SUITE##_##CASE() __attribute__((constructor)); \
static void init_##SUITE##_##CASE() \
{ \
    tt_addToTable(#SUITE, #CASE, test_##SUITE##_##CASE); \
} \
void test_##SUITE##_##CASE()

/*
#define EXPECT_INT_EQ(EXPECTED, ACTUAL) \
do \
{ \
    struct ExpectInt* exp = (struct ExpectInt*)malloc(sizeof (*exp)); \
    exp->expected = EXPECTED; \
    exp->actual = ACTUAL; \
    exp->caseName = tt_getCurCase(table)->caseName; \
    tt_addToCase(table, exp, runIntEq);\
} while(0)

#define EXPECT_FLOAT_EQ(EXPECTED, ACTUAL, ERROR) \
do \
{ \
    struct ExpectFloat* exp = (struct ExpectFloat*)malloc(sizeof (*exp)); \
    exp->expected = EXPECTED; \
    exp->actual = ACTUAL; \
    exp->error = ERROR; \
    exp->caseName = tt_getCurCase(table)->caseName; \
    tt_addToCase(table, exp, runFloatEq);\
} while(0)
*/

#define EXPECT_INT_EQ(EXPECTED, ACTUAL) \
do \
{ \
    if (EXPECTED != ACTUAL) \
        printf("FAIL\n"); \
    else \
        printf("PASS\n"); \
} while(0)


#define INITTEST() \
do \
{ \
} while (0)


#define RUNTEST() \
do \
{ \
    tt_run(); \
    tt_free(); \
} while(0)



#endif // MMARCO_H_INCLUDED
