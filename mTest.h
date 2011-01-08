#ifndef MTEST_H_INCLUDED
#define MTEST_H_INCLUDED

#define TESTMAX 10

int runIntEq(void* e);
struct ExpectInt
{
    int expected;
    int actual;
};

int runFloatEq(void* e);
struct ExpectFloat
{
    double expected;
    double actual;
    double error;
};

typedef int (* testFunc)(void* exp);


struct Expect
{
    struct Expect* next;
    testFunc func;
    void* exp;
};

struct TestCase
{
    struct Expect* expHead;
    struct TestCase* next;
    int num;
    const char* suiteName;
    const char* caseName;
};

struct TestTable
{
    struct TestCase* tcHead;
    struct TestCase* curCase;
    int num;
};

#define TEST(SUITE, CASE) \
do \
{ \
    struct TestCase* pTc = (struct TestCase*)malloc(sizeof (*pTc)); \
    pTc->expHead = NULL; \
    pTc->num = 0; \
    pTc->suiteName = #SUITE; \
    pTc->caseName = #CASE; \
    addToTable(pTc); \
} while (0);

#define EXPECT_INT_EQ(EXPECTED, ACTUAL) \
do \
{ \
    struct ExpectInt* exp = (struct ExpectInt*)malloc(sizeof (*exp)); \
    exp->expected = EXPECTED; \
    exp->actual = ACTUAL; \
    addToCase(exp, runIntEq);\
} while(0)

#define EXPECT_FLOAT_EQ(EXPECTED, ACTUAL, ERROR) \
do \
{ \
    struct ExpectFloat* exp = (struct ExpectFloat*)malloc(sizeof (*exp)); \
    exp->expected = EXPECTED; \
    exp->actual = ACTUAL; \
    exp->error = ERROR; \
    addToCase(exp, runFloatEq);\
} while(0)



#define INITTEST() \
do \
{ \
    table = (struct TestTable*)malloc(sizeof (*table)); \
    table->tcHead = NULL; \
    table->curCase = NULL; \
    table->num = 0; \
} while (0)


#define RUNTEST() \
do \
{ \
    struct TestCase* pCase; \
    struct Expect* pExp; \
    for (table->curCase = table->tcHead; table->curCase != NULL; table->curCase = table->curCase->next) \
    { \
        pCase = table->curCase; \
        for (pExp = pCase->expHead; pExp != NULL; pExp = pExp->next) \
            pExp->func(pExp->exp); \
    } \
    \
    for (pCase = table->tcHead; pCase != NULL; ) \
    { \
        for (pExp = pCase->expHead; pExp != NULL; ) \
        { \
            pExp = pCase->expHead->next; \
            free(pCase->expHead); \
            pCase->expHead = pExp; \
        } \
        pCase = table->tcHead->next; \
        free(table->tcHead); \
        table->tcHead = pCase; \
    } \
    free(table); \
} while(0)


#endif // MTEST_H_INCLUDED
