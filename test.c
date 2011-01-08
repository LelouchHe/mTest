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

struct TestTable* table;

int main()
{
    INITTEST();

    EXPECT_INT_EQ(5, add(1, 4));
    EXPECT_FLOAT_EQ(2, sub(3, 1), 0.001);

    RUNTEST();
    return 0;
}

