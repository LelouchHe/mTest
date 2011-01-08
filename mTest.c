#include "mTest.h"
#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

extern struct TestTable* table;

void addToTable(void* exp, testFunc func)
{
    if (table->cur < table->num)
    {
        table->items[table->cur].exp = exp;
        table->items[table->cur].func = func;
        table->cur++;
    }
    else
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


