#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    EXPECT_INT_EQ(4, 5, "this is %s, %d\n", "what", 2);
    EXPECT_INT_EQ(4, 4);
}


int main()
{


    RUNTEST();
    return 0;
}

