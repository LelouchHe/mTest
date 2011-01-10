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


TEST(Suite1, Case1)
{
    EXPECT_INT_EQ(5, 5);
}


TEST(Suite2, Case2)
{
    EXPECT_INT_EQ(4, 5);
}


int main()
{
    INITTEST();

    RUNTEST();
    return 0;
}

