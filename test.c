#include "mTest.h"
#include <stdio.h>

#define TESTMAX 10

#define TRUE 1
#define FALSE 0

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

