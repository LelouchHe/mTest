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
void test_##SUITE##_##CASE(struct TestResultList* pTr); \
static void init_##SUITE##_##CASE() __attribute__((constructor)); \
static void init_##SUITE##_##CASE() \
{ \
    tt_addToTable(#SUITE, #CASE, test_##SUITE##_##CASE); \
} \
void test_##SUITE##_##CASE(struct TestResultList* pTrl)

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


#define EXPECT_INT_EQ(EXPECTED, ACTUAL) \
do \
{ \
    if (EXPECTED != ACTUAL) \
        printf("FAIL\n"); \
    else \
        printf("PASS\n"); \
} while(0)
*/

#define MAKE_INT_TEST(EXPECTED, ACTUAL, ...) \
int expected = EXPECTED; \
int actual = ACTUAL; \
struct Expect expt; \
expt.expected = &expected; \
expt.actual = &actual; \
int user = 1; \
if (!strcmp(#__VA_ARGS__, "")) \
    user = 0; \

#define EXPECT_INT_EQ(EXPECTED, ACTUAL, ...) \
do \
{ \
    MAKE_INT_TEST(EXPECTED, ACTUAL, ##__VA_ARGS__)\
    struct TestResult* pTr = runCase(&expt, cmpIntEq, 0, user, ##__VA_ARGS__); \
    trl_add(pTrl, pTr); \
} while(0)

#define ASSERT_INT_EQ(EXPECTED, ACTUAL, ...) \
do \
{ \
    MAKE_INT_TEST(EXPECTED, ACTUAL, ##__VA_ARGS__)\
    struct TestResult* pTr = runCase(&expt, cmpIntEq, 1, user, ##__VA_ARGS__); \
    trl_add(pTrl, pTr); \
} while(0)

#define MAKE_FLOAT_TEST(EXPECTED, ACTUAL, ERROR, ...) \
double expected = EXPECTED; \
double actual = ACTUAL; \
double error = ERROR; \
struct Expect expt; \
expt.expected = &expected; \
expt.actual = &actual; \
expt.extra = &error; \
int user = 1; \
if (!strcmp(#__VA_ARGS__, "")) \
    user = 0; \

#define EXPECT_FLOAT_EQ(EXPECTED, ACTUAL, ERROR, ...) \
do \
{ \
    MAKE_FLOAT_TEST(EXPECTED, ACTUAL, ERROR, ##__VA_ARGS__) \
    struct TestResult* pTr = runCase(&expt, cmpFloatEq, 0, user, ##__VA_ARGS__); \
    trl_add(pTrl, pTr); \
} while (0)

#define ASSERT_FLOAT_EQ(EXPECTED, ACTUAL, ERROR, ...) \
do \
{ \
    MAKE_FLOAT_TEST(EXPECTED, ACTUAL, ERROR, ##__VA_ARGS__) \
    struct TestResult* pTr = runCase(&expt, cmpFloatEq, 1, user, ##__VA_ARGS__); \
    trl_add(pTrl, pTr); \
} while (0)

#define MAKE_STR_TEST(EXPECTED, ACTUAL, ...) \
char* expected = EXPECTED; \
char* actual = ACTUAL; \
struct Expect expt; \
expt.expected = expected; \
expt.actual = actual; \
int user = 1; \
if (!strcmp(#__VA_ARGS__, "")) \
    user = 0; \

#define EXPECT_STR_EQ(EXPECTED, ACTUAL, ...) \
do \
{ \
    MAKE_STR_TEST(EXPECTED, ACTUAL, ##__VA_ARGS__)\
    struct TestResult* pTr = runCase(&expt, cmpStrEq, 0, user, ##__VA_ARGS__); \
    trl_add(pTrl, pTr); \
} while(0)

#define ASSERT_STR_EQ(EXPECTED, ACTUAL, ...) \
do \
{ \
    MAKE_STR_TEST(EXPECTED, ACTUAL, ##__VA_ARGS__)\
    struct TestResult* pTr = runCase(&expt, cmpStrEq, 1, user, ##__VA_ARGS__); \
    trl_add(pTrl, pTr); \
} while(0)


#define INITTEST() \
do \
{ \
} while (0)


#define RUNTEST() \
do \
{ \
    tt_run(); \
    tt_print(); \
    tt_free(); \
} while(0)



#endif // MMARCO_H_INCLUDED
