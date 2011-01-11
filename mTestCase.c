#include "mTestCase.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "mTestResult.h"


struct TestCase
{
    struct TestCase* next;
    int num;
    const char* caseName;

    void (* func)(struct TestResultList* pTrl);
    struct TestResultList* pTrl;

    void (* beforeHead)();
    void (* afterHead)();


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

    pTc->beforeHead = NULL;
    pTc->afterHead = NULL;
    return pTc;
}


void tc_free(struct TestCase* pTc)
{
    trl_free(pTc->pTrl);
    free(pTc);
    pTc = NULL;
}

int tc_run(struct TestCase* pTc)
{
    pTc->pTrl->time = clock();
    pTc->func(pTc->pTrl);
    pTc->pTrl->time = clock() - pTc->pTrl->time;
    return trl_isFatal(pTc->pTrl);
}

void tc_addExpFunc(struct TestCase* pTc, void (* func)(struct TestResultList*))
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
};
