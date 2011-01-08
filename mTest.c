#include "mTest.h"
#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

struct TestTable table[TESTMAX];

void addToTable(void* exp, testFunc func)
{
    int i;
    for (i = 0; i < TESTMAX; i++)
    {
        if (table[i].exp == NULL)
        {
            table[i].exp = exp;
            table[i].func = func;
            break;
        }
    }
    if (i == TESTMAX)
        printf("TestTable is full\n");
}

int runIntEq(void* e)
{
    struct ExpectInt* exp = (struct ExpectInt*)e;
    if (exp->expected == exp->actual)
    {
        printf("Expectation %s : PASS\n\n", exp->name);
        return TRUE;
    }
    else
    {
        printf("Expectation %s : FAIL\nExpected = %d\nActual = %d\n\n", exp->name, exp->expected, exp->actual);
        return FALSE;
    }
}

int runFloatEq(void* e)
{
    struct ExpectFloat* exp = (struct ExpectFloat*)e;
    if (fabs(exp->expected - exp->actual) <= exp->error)
    {
        printf("Expectation %s : PASS\n\n", exp->name);
        return TRUE;
    }
    else
    {
        printf("Expectation %s : FAIL\nExpected = %f\nActual = %f\n\n", exp->name, exp->expected, exp->actual);
        return FALSE;
    }
}


