#include "mTest.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

extern struct TestTable* table;

void addToTable(struct TestCase* pTc)
{
    pTc->next = table->tcHead;
    table->tcHead = pTc;
    table->num++;
    table->curCase = pTc;
}

void addToCase(void* exp, testFunc func)
{
    struct Expect* pExp = (struct Expect*)malloc(sizeof (*pExp));
    pExp->exp = exp;
    pExp->func = func;
    pExp->next = table->curCase->expHead;
    table->curCase->expHead = pExp;
    table->curCase->num++;
}

int runIntEq(void* e)
{
    struct ExpectInt* exp = (struct ExpectInt*)e;
    if (exp->expected == exp->actual)
    {
        printf("Expectation %s : PASS\n\n", table->curCase->caseName);
        return TRUE;
    }
    else
    {
        printf("Expectation %s : FAIL\nExpected = %d\nActual = %d\n\n", table->curCase->caseName, exp->expected, exp->actual);
        return FALSE;
    }
}

int runFloatEq(void* e)
{
    struct ExpectFloat* exp = (struct ExpectFloat*)e;
    if (fabs(exp->expected - exp->actual) <= exp->error)
    {
        printf("Expectation %s : PASS\n\n", table->curCase->caseName);
        return TRUE;
    }
    else
    {
        printf("Expectation %s : FAIL\nExpected = %f\nActual = %f\n\n", table->curCase->caseName, exp->expected, exp->actual);
        return FALSE;
    }
}


