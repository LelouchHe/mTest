#include "mTestExpect.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

//这两个地方的输出,最后是会变的,但是目前还没有到那一步
//我希望先把TestSuite搞定
int runIntEq(void* e)
{
    struct ExpectInt* exp = (struct ExpectInt*)e;
    if (exp->expected == exp->actual)
    {
        printf("Expectation %s : PASS\n\n", exp->caseName);
        return TRUE;
    }
    else
    {
        printf("Expectation %s : FAIL\nExpected = %d\nActual = %d\n\n", exp->caseName, exp->expected, exp->actual);
        return FALSE;
    }
}

int runFloatEq(void* e)
{
    struct ExpectFloat* exp = (struct ExpectFloat*)e;
    if (fabs(exp->expected - exp->actual) <= exp->error)
    {
        printf("Expectation %s : PASS\n\n", exp->caseName);
        return TRUE;
    }
    else
    {
        printf("Expectation %s : FAIL\nExpected = %f\nActual = %f\n\n", exp->caseName, exp->expected, exp->actual);
        return FALSE;
    }
}
