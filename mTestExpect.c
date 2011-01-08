#include "mTestExpect.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

//�������ط������,����ǻ���,����Ŀǰ��û�е���һ��
//��ϣ���Ȱ�TestSuite�㶨
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
