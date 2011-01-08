#ifndef MTEST_H_INCLUDED
#define MTEST_H_INCLUDED


int runIntEq(void* e);
struct ExpectInt
{
    int expected;
    int actual;
    char* name;
};

int runFloatEq(void* e);
struct ExpectFloat
{
    double expected;
    double actual;
    double error;
    char* name;
};

typedef int (* testFunc)(void* exp);

struct Item
{
    void* exp;
    testFunc func;
};

struct TestTable
{
    struct Item* items;
    int num;
    int cur;
};


void addToTable(void* exp, testFunc func);


#define EXPECT_INT_EQ(EXPECTED, ACTUAL) \
struct ExpectInt exp_##EXPECTED; \
exp_##EXPECTED.name = "IntEq "#EXPECTED; \
exp_##EXPECTED.expected = EXPECTED; \
exp_##EXPECTED.actual = ACTUAL; \
do \
{ \
    addToTable(&exp_##EXPECTED, runIntEq);\
} while(0)

#define EXPECT_FLOAT_EQ(EXPECTED, ACTUAL, ERROR) \
struct ExpectFloat exp_##EXPECTED; \
exp_##EXPECTED.name = "FloatEq "#EXPECTED; \
exp_##EXPECTED.expected = EXPECTED; \
exp_##EXPECTED.actual = ACTUAL; \
do \
{ \
    addToTable(&exp_##EXPECTED, runFloatEq);\
} while(0)


#define INITTEST() \
do \
{ \
    table = (struct TestTable*)malloc(sizeof (struct TestTable)); \
    table->cur = 0; \
    table->num = 20; \
    table->items = (struct Item*)malloc(sizeof (struct Item) * table->num); \
} while (0)


#define RUNTEST() \
do \
{ \
    int i = 0; \
    for (i = 0; i < table->cur; i++) \
        table->items[i].func(table->items[i].exp); \
    free(table->items); \
    free(table); \
} while(0)


#endif // MTEST_H_INCLUDED
