#include <stdio.h>
#include <stdlib.h>

//to be tested, usually in another file
int add(int a, int b)
{
    return a + b;
}

double sub(double a, double b)
{
    return a - b;
}

#include "mTest.h"

struct TestTable* table;

TEST_BEG

TEST("Suite", "Case")
{
    EXPECT_INT_EQ(5, add(1, 4));
    EXPECT_INT_EQ(5, 5);
    EXPECT_FLOAT_EQ(2, sub(3, 1), 0.001);
}

TEST("Suite", "CaseFuck")
{
    int a = add(1, 4);
    EXPECT_INT_EQ(4, a);
    EXPECT_INT_EQ(2, 5);
    EXPECT_FLOAT_EQ(2, sub(3, 1), 0.001);
}

TEST_END

int main()
{
    INITTEST();

    RUNTEST();
    return 0;
}

