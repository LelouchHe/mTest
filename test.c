#include "mTest.h"
#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a + b;
}

int main()
{
    EXPECT_EQ(5, add(1, 4));
    EXPECT_EQ(1, add(1, 3));

    RUNTEST;
    return 0;
}

