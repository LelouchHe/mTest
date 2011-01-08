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
void addToTable(struct TestCase* pTc);
void addToCase(void* exp, testFunc func);

int main()
{

    INITTEST();

    TEST(Suite, CaseFuck)
    {
        EXPECT_INT_EQ(5, add(1, 4));
        EXPECT_INT_EQ(5, 5);
        EXPECT_FLOAT_EQ(2, sub(3, 1), 0.001);
    }

    RUNTEST();
    return 0;
}

