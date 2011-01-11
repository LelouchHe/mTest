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

char* str()
{
    return "Lelouch";
}
*/

#include "mTest.h"

#include <stdio.h>

BEFORE_ALL()
{
    printf("it is the first time\n");
}

AFTER_ALL()
{
    printf("it is the last time\n");
}

BEFORE_SUITE(Suite1)
{
    printf("it is just before Suite1\n");
}

TEST(Suite1, Case1)
{
    printf("it is in the middle\n");
    EXPECT_INT_EQ(0, 0);
}


int main()
{
    RUNTEST();
    return 0;
}

