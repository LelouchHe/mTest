#include "mTestExpect.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

#include "mTestResult.h"

#define TRUE 1
#define FALSE 0

#define BUFMAX 1024



struct TestResult* runCase(struct Expect* pExp, void (* cmp)(struct Expect*, struct TestResult*), int fatal, int user, ...)
{
    struct TestResult* pTr = tr_malloc();
    cmp(pExp, pTr);
    if (fatal == TRUE)
        pTr->fatal = TRUE;
    else
        pTr->fatal = FALSE;

    if (user == TRUE)
    {
        char buf[1024];
        va_list arg;
        int len;
        char* fmt;
        va_start(arg, user);
        fmt = va_arg(arg, char*);
        len = vsprintf(buf, fmt, arg);
        buf[len] = '\0';
        tr_setMsg(pTr, buf, len);
    }
    else
        pTr->msg = NULL;

    return pTr;
}

/*
int runCase(struct Expect* pExp, int (* cmp)(struct Expect*), void (* output)(struct Expect*, int, va_list), int fatal, int user, ...)
{
    int pass = cmp(pExp);
    if (pass == TRUE)
    {
        HANDLE outputHandle;
        WORD oldColor;
        beforePrint(COLOR_GREEN, &outputHandle, &oldColor);
        printf("\n+----------PASS----------+\n");
        afterPrint(outputHandle, oldColor);
        return TRUE;
    }
    else if (fatal == TRUE)
        abort();
    else
    {
        va_list args;
        va_start(args, user);
        output(pExp, user, args);
        va_end(args);
        return FALSE;
    }
}
*/

void cmpIntEq(struct Expect* pExp, struct TestResult* pTr)
{
    int expected = *(int *)pExp->expected;
    int actual = *(int *)pExp->actual;

    tr_setVal(pTr, &expected, &actual, INTEGER, sizeof (int));
    pTr->pass = (expected == actual);
}

/*
void outputInt(struct Expect* pExp, int user, va_list param)
{
    HANDLE outputHandle;
    WORD oldColor;
    beforePrint(COLOR_RED, &outputHandle, &oldColor);

    int expected = *(int *)pExp->expected;
    int actual = *(int *)pExp->actual;

    printf("\n+----------FAIL----------+\n");
    printf(" Expected\t:\t%d\n", expected);
    printf(" Actual\t\t:\t%d\n", actual);
    if (user == TRUE)
    {
        printf(" User's Info\t: ");
        char* fmt = va_arg(param, char*);
        vprintf(fmt, param);

    }
    afterPrint(outputHandle, oldColor);
}


int cmpFloatEq(struct Expect* pExp)
{
    double expected = *(double *)pExp->expected;
    double actual = *(double *)pExp->actual;
    double error = *(double *)pExp->extra;
    return fabs(expected - actual) <= error;
}

void outputFloat(struct Expect* pExp, int output, va_list param)
{
    double expected = *(double *)pExp->expected;
    double actual = *(double *)pExp->actual;
    printf("----FAIL----\n");
    printf("Expected\t:%g\n", expected);
    printf("Actual\t:\t%g\n", actual);
    if (output == TRUE)
    {
        printf(" ");
        char* fmt = va_arg(param, char*);
        vprintf(fmt, param);
    }
}
*/
