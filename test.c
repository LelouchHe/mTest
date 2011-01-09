#include <stdio.h>
#include <stdlib.h>

//to be tested, usually in another file
/*
int add(int a, int b)
{
    return a + b;
}

double sub(double a, double b)
{
    return a - b;
}
*/

#include "mTest.h"
#include "mUtil.h"


struct TestTable* table;

TEST_BEG

BEFORE_CASE(Suite, Case1)
{
    int i = 0;
    STORE(i);
}

AFTER_CASE(Suite, Case1)
{
    printf("leave my sweet suite");
}

TEST("Suite", "Case1");
{
    EXPECT_INT_EQ(5, 5);
}

TEST("Suite", "Case2");
{
    EXPECT_INT_EQ(4, 5);
}

TEST_END

int main()
{
    INITTEST();

    RUNTEST();
    return 0;
}

