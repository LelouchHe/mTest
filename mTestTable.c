#include "mTestTable.h"

#include <stdlib.h>

#include "mTestSuite.h"

#define TRUE 1
#define FALSE 0

struct TestTable
{
    struct TestSuite* tsHead;
    struct TestSuite* tsTail;
    struct TestSuite* curSuite;
    int num;

    void (* beforeHead)();
    void (* afterHead)();
};

static struct TestTable* table;

static struct TestTable* tt_s_malloc()
{
    struct TestTable* pTt = (struct TestTable*)malloc(sizeof (*pTt));
    pTt->tsHead = pTt->tsTail = pTt->curSuite = NULL;
    pTt->num = 0;

    pTt->beforeHead = pTt->afterHead = NULL;
    return pTt;
}

static void tt_s_addToTable(struct TestSuite* pTs)
{
    struct TestSuite* pTSuite;
    for (pTSuite = tt_getTable()->tsHead; pTSuite != NULL && !ts_isSameSuite(pTSuite, pTs); pTSuite = ts_getNextSuite(pTSuite))
        ;
    if (pTSuite == NULL)
    {
        if (tt_getTable()->tsHead == NULL)
            tt_getTable()->tsHead = tt_getTable()->tsTail = pTs;
        else
        {
            ts_setNextSuite(tt_getTable()->tsTail, pTs);
        }
        tt_getTable()->num++;
        tt_getTable()->curSuite = pTs;
        tt_getTable()->tsTail = pTs;
    }
    else
    {
        ts_merge(pTSuite, pTs);
        pTs = NULL;
        tt_getTable()->curSuite = pTSuite;
    }
}

struct TestTable* tt_getTable()
{
    if (table == NULL)
        table = tt_s_malloc();
    return table;
}

void tt_free()
{
    if (table == NULL)
        return;
    struct TestSuite* pTs;
    while (table->tsHead != NULL)
    {
        pTs = ts_getNextSuite(table->tsHead);
        ts_free(table->tsHead);
        table->tsHead = pTs;
    }
    free(table);
    table = NULL;
}

void tt_addToTable(const char* suiteName, const char* caseName, void (*func)(struct TestResultList*))
{
    struct TestSuite* pTs = ts_malloc(suiteName);
    ts_addToSuite(pTs, caseName, func);
    tt_s_addToTable(pTs);
}


void tt_run()
{
    struct TestSuite* pTs;
    for (pTs = tt_getTable()->tsHead; pTs != NULL; pTs = ts_getNextSuite(pTs))
    {
        if (ts_run(pTs) == TRUE)
            break;
    }
}

