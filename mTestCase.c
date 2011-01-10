#include "mTestCase.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef int (* testFunc)(void* exp);

struct Expect
{
    struct Expect* next;
    testFunc func;
    void* exp;
};

struct TestCase* tc_malloc(const char* caseName)
{
    struct TestCase* pTc = (struct TestCase*)malloc(sizeof (*pTc));
    assert(pTc != NULL);
    pTc->expHead = NULL;
    pTc->next = NULL;
    pTc->num = 0;
    pTc->caseName = caseName;
    return pTc;
}


void tc_free(struct TestCase* pTc)
{
    struct Expect* pExp;
    while (pTc->expHead != NULL)
    {
        pExp = pTc->expHead->next;
        free(pTc->expHead);
        pTc->expHead = pExp;
    }
    free(pTc);
    pTc = NULL;
}


void tc_addToCase(struct TestCase* pTc, void* exp, testFunc func)
{
    struct Expect* pExp = (struct Expect*)malloc(sizeof (*pExp));
    pExp->exp = exp;
    pExp->func = func;
    pExp->next = pTc->expHead;
    pTc->expHead = pExp;
    pTc->num++;
}

void tc_run(struct TestCase* pTc)
{
/*
    struct Expect* pExp = pTc->expHead;
    while (pExp != NULL)
    {
        pExp->func(pExp->exp);
        pExp = pExp->next;
    }
*/
    pTc->func();
}

void tc_merge(struct TestCase* pTo, struct TestCase* pFrom)
{
    struct Expect* pExp = pFrom->expHead;
    while (pExp != NULL && pExp->next != NULL)
        pExp = pExp->next;

    if (pExp == NULL)
        tc_free(pFrom);
    else
    {
        pExp->next = pTo->expHead;
        pTo->expHead = pFrom->expHead;
        pTo->num += pFrom->num;
        free(pFrom);
        pFrom = NULL;
    }
}

int tc_isSameCase(struct TestCase* pA, struct TestCase* pB)
{
    return !strcmp(pA->caseName, pB->caseName);
}

void tc_addExpFunc(struct TestCase* pTc, void (* func)())
{
    pTc->func = func;
}
