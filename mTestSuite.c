#include "mTestSuite.h"

#include <stdlib.h>
#include <string.h>

#include "mTestCase.h"


static void ts_s_addToSuite(struct TestSuite* pTs, struct TestCase* pTc)
{
    struct TestCase* pTCase;
    for (pTCase = pTs->tcHead; pTCase != NULL && !tc_isSameCase(pTCase, pTc); pTCase = pTCase->next)
        ;
    if (pTCase == NULL)
    {
        pTc->next = pTs->tcHead;
        pTs->tcHead = pTc;
        pTs->num++;
        pTs->curCase = pTc;
    }
    else
    {
        tc_merge(pTCase, pTc);
        pTc = NULL;
        pTs->curCase = pTCase;
    }
}


struct TestSuite* ts_malloc(const char* suiteName)
{
    struct TestSuite* pTs = (struct TestSuite*)malloc(sizeof (*pTs));
    pTs->tcHead = NULL;
    pTs->next = NULL;
    pTs->num = 0;
    pTs->suiteName = suiteName;
    return pTs;
};



void ts_free(struct TestSuite* pTs)
{
    struct TestCase* pTc;
    while (pTs->tcHead != NULL)
    {
        pTc = pTs->tcHead->next;
        tc_free(pTs->tcHead);
        pTs->tcHead = pTc;
    }
    free(pTs);
    pTs = NULL;
}

void ts_addToSuite(struct TestSuite* pTs, const char* caseName, void (* func)())
{
    struct TestCase* pTc = tc_malloc(caseName);
    tc_addExpFunc(pTc, func);
    ts_s_addToSuite(pTs, pTc);
}

void ts_run(struct TestSuite* pTs)
{
    struct TestCase* pTc;
    for (pTc = pTs->tcHead; pTc != NULL; pTc = pTc->next)
        tc_run(pTc);
}

void ts_merge(struct TestSuite* pTo, struct TestSuite* pFrom)
{
    struct TestCase* pTc = pFrom->tcHead;
    while (pFrom->tcHead != NULL)
    {
        pTc = pFrom->tcHead->next;
        ts_s_addToSuite(pTo, pFrom->tcHead);
        pFrom->tcHead = pTc;
    }
    free(pFrom);
    pFrom = NULL;
}

int ts_isSameSuite(struct TestSuite* pA, struct TestSuite* pB)
{
    return !strcmp(pA->suiteName, pB->suiteName);
}

void ts_addToCase(struct TestSuite* pTs, void* exp, int(*func)(void*))
{
    tc_addToCase(pTs->curCase, exp, func);
}

struct TestCase* ts_getCurCase(struct TestSuite* pTs)
{
    return pTs->curCase;
}

void ts_addExpFunc(struct TestSuite* pTs, void (* func)())
{
    pTs->curCase->func = func;
}
