#include <stdio.h>
#include <stdlib.h>

#include "mTest.h"

#define TRUE 1
#define FALSE 0

int add(int a, int b)
{
    return a + b;
}

double sub(double a, double b)
{
    return a - b;
}


int main()
{
    struct TestTable* table;

    INITTEST();

    TEST(Suite, CaseFuck)
    {
        EXPECT_INT_EQ(5, add(1, 4));
        EXPECT_INT_EQ(5, 5);
        EXPECT_FLOAT_EQ(2, sub(3, 1), 0.001);
    }

    TEST(Suite, Case)
    {
        EXPECT_INT_EQ(5, add(1, 4));
        EXPECT_INT_EQ(5, 5);
        EXPECT_FLOAT_EQ(2, sub(3, 1), 0.001);
    }

    TEST(Suite, CaseFuck)
    {
        EXPECT_INT_EQ(4, add(1, 4));
        EXPECT_INT_EQ(2, 5);
        EXPECT_FLOAT_EQ(2, sub(3, 1), 0.001);
    }

    RUNTEST();
    return 0;
}

