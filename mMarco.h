#ifndef MMARCO_H_INCLUDED
#define MMARCO_H_INCLUDED

//ÿ��TEST���ֱض���һ��case,���ǲ�һ����suite,suite�ĳ�����Ҫ�ж�����������������,���ϲ����
//�ض���case���Բ���������,����suite����ô?

//case�����Ѿ����Դ�����..������..��suite��...


#define TEST_BEG \
void init() \
{

#define TEST_END \
}

#define TEST(SUITE, CASE) \
do \
{ \
    struct TestSuite* pTs = ts_malloc(#SUITE); \
    struct TestCase* pTc = tc_malloc(#CASE); \
    ts_addToSuite(pTs, pTc); \
    tt_addToTable(table, pTs); \
} while (0);


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



#define INITTEST() \
do \
{ \
    table = tt_malloc(); \
    init(); \
} while (0)


#define RUNTEST() \
do \
{ \
    tt_run(table); \
    tt_free(table); \
} while(0)


#endif // MMARCO_H_INCLUDED
