#ifndef MTEST_H_INCLUDED
#define MTEST_H_INCLUDED

#define TESTMAX 10

struct ExpectInt
{
    int expected;
    int actual;
    char* name;
};

struct ExpectFloat
{
    double expected;
    double actual;
    double error;
    char* name;
};

typedef int (* testFunc)(void* exp);

struct TestTable
{
    void* exp;
    testFunc func;
};

extern struct TestTable table[TESTMAX];

void addToTable(void* exp, testFunc func);

int runIntEq(void* e);
int runFloatEq(void* e);


#define EXPECT_INT_EQ(EXPECTED, ACTUAL) \
struct ExpectInt exp_##EXPECTED; \
exp_##EXPECTED.name = #EXPECTED; \
exp_##EXPECTED.expected = EXPECTED; \
exp_##EXPECTED.actual = ACTUAL; \
do \
{ \
    addToTable(&exp_##EXPECTED, runIntEq);\
} while(0)

#define EXPECT_FLOAT_EQ(EXPECTED, ACTUAL, ERROR) \
struct ExpectFloat exp_##EXPECTED; \
exp_##EXPECTED.name = #EXPECTED; \
exp_##EXPECTED.expected = EXPECTED; \
exp_##EXPECTED.actual = ACTUAL; \
do \
{ \
    addToTable(&exp_##EXPECTED, runFloatEq);\
} while(0)


#define RUNTEST \
do \
{ \
    int i = 0; \
    for (i = 0; i < TESTMAX && table[i].exp != NULL; i++) \
        table[i].func(table[i].exp);\
} while(0)


#endif // MTEST_H_INCLUDED
