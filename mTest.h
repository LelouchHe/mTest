#ifndef MTEST_H_INCLUDED
#define MTEST_H_INCLUDED

#define TESTMAX 10

struct Expect
{
    int expected;
    int actual;
    char* name;
};

typedef int (* testFunc)(struct Expect* exp);

struct TestTable
{
    void* exp;
    testFunc func;
};

extern struct TestTable table[TESTMAX];

void addToTable(void* exp, testFunc func);

int run_eq(struct Expect* e);


#define EXPECT_EQ(EXPECTED, ACTUAL) \
struct Expect exp_##EXPECTED; \
exp_##EXPECTED.name = #EXPECTED; \
exp_##EXPECTED.expected = EXPECTED; \
exp_##EXPECTED.actual = ACTUAL; \
do \
{ \
    addToTable(&exp_##EXPECTED, run_eq);\
} while(0)


#define RUNTEST \
do \
{ \
    int i = 0; \
    for (i = 0; i < TESTMAX && table[i].exp != NULL; i++) \
        table[i].func(table[i].exp);\
} while(0)


#endif // MTEST_H_INCLUDED
