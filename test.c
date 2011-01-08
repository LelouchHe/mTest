#include "mTest.h"
#include <stdio.h>

#define TESTMAX 10

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
    EXPECT_INT_EQ(5, add(1, 4));
    EXPECT_FLOAT_EQ(2, sub(3, 1), 0.001);

    RUNTEST;
    return 0;
}

