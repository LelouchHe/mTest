#include "mTestSuite.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "mTestCase.h"

#define TRUE 1
#define FALSE 0

struct TestSuite
{
    struct TestCase* tcHead;
    struct TestCase* tcTail;
    struct TestCase* curCase;
    struct TestSuite* next;
    int num;
    const char* suiteName;

    void (* beforeHead)();
    void (* afterHead)();
};


static void ts_s_addToSuite(struct TestSuite* pTs, struct TestCase* pTc)
{
    if (pTs->tcHead == NULL)
    {
        pTs->tcHead = pTs->tcTail = pTc;
    }
    else
    {
        tc_setNextCase(pTs->tcTail, pTc);
    }
    pTs->num++;
    pTs->curCase = pTc;
    pTs->tcTail = pTc;
}


struct TestSuite* ts_malloc(const char* suiteName)
{
    struct TestSuite* pTs = (struct TestSuite*)malloc(sizeof (*pTs));
    pTs->tcHead = pTs->tcTail = pTs->curCase = NULL;
    pTs->next = NULL;
    pTs->num = 0;
    pTs->suiteName = suiteName;
    pTs->beforeHead = pTs->afterHead = NULL;
    return pTs;
};



void ts_free(struct TestSuite* pTs)
{
    struct TestCase* pTc;
    while (pTs->tcHead != NULL)
    {
        pTc = tc_getNextCase(pTs->tcHead);
        tc_free(pTs->tcHead);
        pTs->tcHead = pTc;
    }
    free(pTs);
    pTs = NULL;
}

void ts_addToSuite(struct TestSuite* pTs, const char* caseName, void (* func)(struct TestResultList*))
{
    struct TestCase* pTc = tc_malloc(caseName);
    tc_addExpFunc(pTc, func);
    ts_s_addToSuite(pTs, pTc);
}

int ts_run(struct TestSuite* pTs)
{
    struct TestCase* pTc;
    for (pTc = pTs->tcHead; pTc != NULL; pTc = tc_getNextCase(pTc))
    {
        if (tc_run(pTc) == TRUE)
            break;
    }

    if (pTc == NULL)
        return FALSE;
    else
        return TRUE;
}

void ts_merge(struct TestSuite* pTo, struct TestSuite* pFrom)
{
    struct TestCase* pTc = pFrom->tcHead;
    while (pFrom->tcHead != NULL)
    {
        pTc = tc_getNextCase(pFrom->tcHead);
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



struct TestSuite* ts_getNextSuite(struct TestSuite* pTs)
{
    return pTs->next;
}

void ts_setNextSuite(struct TestSuite* pTs, struct TestSuite* pNext)
{
    pTs->next = pNext;
}
