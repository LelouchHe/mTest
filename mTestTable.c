#include "mTestTable.h"

#include <stdlib.h>

#include "mTestSuite.h"


struct TestTable* tt_malloc()
{
    struct TestTable* pTt = (struct TestTable*)malloc(sizeof (*pTt));
    pTt->tsHead = pTt->curSuite = NULL;
    pTt->num = 0;
    return pTt;
};


void tt_free(struct TestTable* pTt)
{
    struct TestSuite* pTs;
    while (pTt->tsHead != NULL)
    {
        pTs = pTt->tsHead->next;
        ts_free(pTt->tsHead);
        pTt->tsHead = pTs;
    }
    free(pTt);
    pTt = NULL;
}


void tt_addToTable(struct TestTable* pTt, struct TestSuite* pTs)
{
    struct TestSuite* pTSuite;
    for (pTSuite = pTt->tsHead; pTSuite != NULL && !ts_isSameSuite(pTSuite, pTs); pTSuite = pTSuite->next)
        ;
    if (pTSuite == NULL)
    {
        pTs->next = pTt->tsHead;
        pTt->tsHead = pTs;
        pTt->num++;
        pTt->curSuite = pTs;
    }
    else
    {
        ts_merge(pTSuite, pTs);
        pTs = NULL;
        pTt->curSuite = pTSuite;
    }
}


void tt_run(struct TestTable* pTt)
{
    struct TestSuite* pTs;
    for (pTs = pTt->tsHead; pTs != NULL; pTs = pTs->next)
        ts_run(pTs);
}

void tt_addToCase(struct TestTable* pTt, void* exp, int(* func)(void*))
{
    ts_addToCase(pTt->curSuite, exp, func);
}

struct TestCase* tt_getCurCase(struct TestTable* pTt)
{
    return ts_getCurCase(pTt->curSuite);
}

