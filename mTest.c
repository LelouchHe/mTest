#include "mTest.h"
#include <stdio.h>

#define TESTMAX 10

struct TestTable table[TESTMAX];

void addToTable(void* exp, testFunc func)
{
    int i;
    for (i = 0; i < TESTMAX; i++)
    {
        if (table[i].exp != NULL)
        {
            table[i].exp = exp;
            table[i].func = func;
        }
    }
    if (i == TESTMAX)
        printf("TestTable is full\n");
    else
        printf("TestTable is set up\n");
}
