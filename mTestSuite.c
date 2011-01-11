#include "mTestSuite.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "mTestCase.h"
#include "mTestPrinter.h"
#include "mTestContext.h"

#define TRUE 1
#define FALSE 0

#define PASS 1
#define FAIL 0
#define ERROR -1

struct TestSuite
{
    struct TestCase* tcHead;
    struct TestCase* tcTail;
    struct TestCase* curCase;
    struct TestSuite* next;
    int num;
    int passNum;
    int runState;
    const char* suiteName;

    void (* before)();
    void (* after)();
};


static void ts_s_addToSuite(struct TestSuite* pTs, struct TestCase* pTc)
{
    if (pTs->tcHead == NULL)
    {
        pTs->tcHead = pTc;
    }
    else
    {
        tc_setNextCase(pTc, pTs->tcHead);
        pTs->tcHead = pTc;
    }
    pTs->num++;
    pTs->curCase = pTc;
}


struct TestSuite* ts_malloc(const char* suiteName)
{
    struct TestSuite* pTs = (struct TestSuite*)malloc(sizeof (*pTs));
    pTs->tcHead = pTs->curCase = NULL;
    pTs->next = NULL;
    pTs->num = 0;
    pTs->suiteName = suiteName;
    pTs->before = pTs->after = NULL;
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

void ts_addToSuite(struct TestSuite* pTs, const char* caseName, void (* func)(struct TestResultList*, struct TestContext*))
{
    struct TestCase* pTc = tc_malloc(caseName);
    tc_addExpFunc(pTc, func);
    ts_s_addToSuite(pTs, pTc);
}

int ts_run(struct TestSuite* pTs, struct TestContext* pTct)
{
    struct TestCase* pTc;
    int result = PASS;
    pTs->runState = FAIL;

    if (pTs->before != NULL)
        pTs->before();
    for (pTc = pTs->tcHead; pTc != NULL; pTc = tc_getNextCase(pTc))
    {
        pTct->pTc = pTc;
        result = tc_run(pTc, pTct);
        if (result == PASS)
            pTs->passNum++;
        else if (result == ERROR)
        {
            pTs->runState = ERROR;
            break;
        }
    }
    if (pTs->after != NULL)
        pTs->after();

    if (result != ERROR && pTs->num == pTs->passNum)
        pTs->runState = PASS;
    return result;
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

int ts_print(struct TestSuite* pTs)
{
    struct TestCase* pTc;
    int result = FALSE;

    tp_printTitle(SUITE, pTs->suiteName);
    for (pTc = pTs->tcHead; pTc != NULL; pTc = tc_getNextCase(pTc))
    {
        if ((result = tc_print(pTc)) == TRUE)
            break;
    }
    return result;
}

void ts_getCaseStatus(struct TestSuite* pTs, int* caseNum, int* casePassNum)
{
    *caseNum = pTs->num;
    *casePassNum = pTs->passNum;
}

int ts_isSuiteName(struct TestSuite* pTs, const char* suiteName)
{
    return !strcmp(pTs->suiteName, suiteName);
}

void ts_addBeforeSuite(struct TestSuite* pTs, void (*func)())
{
    pTs->before = func;
}

void ts_addAfterSuite(struct TestSuite* pTs, void (*func)())
{
    pTs->after = func;
}
