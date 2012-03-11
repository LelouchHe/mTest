#include "mTestCase.h"

#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "mTestResult.h"
#include "mTestPrinter.h"

#define TRUE 1
#define FALSE 0


struct TestCase
{
    struct TestCase* next;
    int num;
    const char* caseName;

    void (* func)(struct TestResultList* pTrl, struct TestContext*);
    struct TestResultList* pTrl;

    void (* before)();
    void (* after)();
};


struct TestCase* tc_malloc(const char* caseName)
{
    struct TestCase* pTc = (struct TestCase*)malloc(sizeof (*pTc));
    assert(pTc != NULL);
    pTc->next = NULL;
    pTc->num = 0;
    pTc->caseName = caseName;

    pTc->func = NULL;
    pTc->pTrl = trl_malloc();

    pTc->before = NULL;
    pTc->after = NULL;
    return pTc;
}


void tc_free(struct TestCase* pTc)
{
    trl_free(pTc->pTrl);
    free(pTc);
    pTc = NULL;
}

int tc_run(struct TestCase* pTc, struct TestContext* pTct)
{
    pTc->pTrl->time = clock();
    pTc->func(pTc->pTrl, pTct);
    pTc->pTrl->time = clock() - pTc->pTrl->time;
    return tc_runState(pTc);
}

void tc_addExpFunc(struct TestCase* pTc, void (* func)(struct TestResultList*, struct TestContext*))
{
    pTc->func = func;
}

struct TestCase* tc_getNextCase(struct TestCase* pTc)
{
    return pTc->next;
}
void tc_setNextCase(struct TestCase* pTc, struct TestCase* pNext)
{
    pTc->next = pNext;
}

struct TestResultList* tc_getResultList(struct TestCase* pTc)
{
    return pTc->pTrl;
}

int tc_print(struct TestCase* pTc)
{
    struct TestResult* pTr;
    int result = FALSE;
    int i;

    tp_printTitle(CASE, pTc->caseName);
    for (pTr = pTc->pTrl->trHead, i = 0; pTr != NULL; pTr = pTr->next, i++)
    {
        tp_printResult(pTr, i);
        if ((result = tr_isFatal(pTr)) == TRUE)
            break;
    }
    tp_printTime(pTc->pTrl);
    return result;
}

int tc_runState(struct TestCase* pTc)
{
    return pTc->pTrl->runState;
}
