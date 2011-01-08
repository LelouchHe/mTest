#include "mTest.h"
#include <stdio.h>

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

int run_eq(struct Expect* e)
{
    if (e->expected == e->actual)
    {
        printf("Expectation %s : PASS\n\n", e->name);
        return TRUE;
    }
    else
    {
        printf("Expectation %s : FAIL\nExpected = %d\nActual = %d\n\n", e->name, e->expected, e->actual);
        return FALSE;
    }
}


