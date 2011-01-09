#include "mUtil.h"

#include <stdlib.h>

#include "mTestTable.h"
#include "mTestSuite.h"
#include "mTestCase.h"
#include "mTestExpect.h"

extern struct TestTable* table;
extern void init();

void TEST(const char* suiteName, const char* caseName)
{
    struct TestSuite* pTs = ts_malloc(suiteName);
    struct TestCase* pTc = tc_malloc(caseName);
    ts_addToSuite(pTs, pTc);
    tt_addToTable(table, pTs);
}

void EXPECT_INT_EQ(const int expected, const int actual)
{
    struct ExpectInt* exp = (struct ExpectInt*)malloc(sizeof (*exp));
    exp->expected = expected;
    exp->actual = actual;
    exp->caseName = tt_getCurCase(table)->caseName;
    tt_addToCase(table, exp, runIntEq);
}
void EXPECT_FLOAT_EQ(const double expected, const double actual, const double error)
{
    struct ExpectFloat* exp = (struct ExpectFloat*)malloc(sizeof (*exp));
    exp->expected = expected;
    exp->actual = actual;
    exp->error = error;
    exp->caseName = tt_getCurCase(table)->caseName;
    tt_addToCase(table, exp, runFloatEq);
}

void INITTEST()
{
    table = tt_malloc();
    init();
}
void RUNTEST()
{
    tt_run(table);
    tt_free(table);
}
