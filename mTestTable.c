#include "mTestTable.h"

#include <stdlib.h>

#include "mTestSuite.h"

struct TestTable
{
    struct TestSuite* tsHead;
    struct TestSuite* curSuite;
    int num;

    void (* beforeHead)();
    void (* afterHead)();
};

static struct TestTable* table;

static struct TestTable* tt_s_malloc()
{
    struct TestTable* pTt = (struct TestTable*)malloc(sizeof (*pTt));
    pTt->tsHead = pTt->curSuite = NULL;
    pTt->num = 0;
    return pTt;
}

static void tt_s_addToTable(struct TestSuite* pTs)
{
    struct TestSuite* pTSuite;
    for (pTSuite = tt_getTable()->tsHead; pTSuite != NULL && !ts_isSameSuite(pTSuite, pTs); pTSuite = pTSuite->next)
        ;
    if (pTSuite == NULL)
    {
        pTs->next = tt_getTable()->tsHead;
        tt_getTable()->tsHead = pTs;
        tt_getTable()->num++;
        tt_getTable()->curSuite = pTs;
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
        pTs = table->tsHead->next;
        ts_free(table->tsHead);
        table->tsHead = pTs;
    }
    free(table);
    table = NULL;
}

void tt_addToTable(const char* suiteName, const char* caseName, void (*func)())
{
    struct TestSuite* pTs = ts_malloc(suiteName);
    ts_addToSuite(pTs, caseName, func);
    tt_s_addToTable(pTs);
}




void tt_run()
{
    struct TestSuite* pTs;
    for (pTs = tt_getTable()->tsHead; pTs != NULL; pTs = pTs->next)
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


void tt_addExpFunc(void (*func)())
{
    ts_addExpFunc(tt_getTable()->curSuite, func);
}

