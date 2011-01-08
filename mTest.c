#include "mTest.h"
#include <stdio.h>


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
}
