#ifndef MTEST_H_INCLUDED
#define MTEST_H_INCLUDED

#define TESTMAX 10

#define TRUE 1
#define FALSE 0

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


#define EXPECT_EQ(EXPECTED, ACTUAL) \
struct Expect exp_##EXPECTED; \
exp_##EXPECTED.name = #EXPECTED; \
exp_##EXPECTED.expected = EXPECTED; \
exp_##EXPECTED.actual = ACTUAL; \
 \
int run_##EXPECTED(struct Expect* e) \
{ \
    if (e->expected == e->actual) \
    { \
        printf("Expectation %s : PASS\n\n", e->name); \
        return TRUE; \
    } \
    else \
    { \
        printf("Expectation %s : FAIL\nExpected = %d\nActual = %d\n\n", e->name, e->expected, e->actual); \
        return FALSE; \
    } \
} \
 \
addToTable(&exp_##EXPECTED, run_##EXPECTED);


#define RUNTEST \
do \
{ \
    int i = 0; \
    for (i = 0; i < TESTMAX && table[i].exp != NULL; i++) \
        table[i].func(table[i].exp);\
} while(0)



#undef TRUE
#undef FALSE

#endif // MTEST_H_INCLUDED
