#include "mTestTable.h"

#include <stdlib.h>

#include "mTestSuite.h"
#include "mTestPrinter.h"

#define TRUE 1
#define FALSE 0

#define PASS 1
#define FAIL 0
#define ERROR -1


struct TestTable
{
    struct TestSuite* tsHead;
    struct TestSuite* tsTail;
    struct TestSuite* curSuite;
    int num;
    int passNum;
    int runState;

    void (* beforeHead)();
    void (* afterHead)();
};

static struct TestTable* table;

static struct TestTable* tt_s_malloc()
{
    struct TestTable* pTt = (struct TestTable*)malloc(sizeof (*pTt));
    pTt->tsHead = pTt->curSuite = NULL;
    pTt->num = pTt->passNum = 0;

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
            tt_getTable()->tsHead  = pTs;
        else
        {
            ts_setNextSuite(pTs, tt_getTable()->tsHead);
            tt_getTable()->tsHead = pTs;
        }
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
    int result = PASS;
    tt_getTable()->runState = FAIL;
    for (pTs = tt_getTable()->tsHead; pTs != NULL; pTs = ts_getNextSuite(pTs))
    {
        result = ts_run(pTs);
        if (result == PASS)
            tt_getTable()->passNum++;
        if (result == ERROR)
        {
            tt_getTable()->runState = ERROR;
            break;
        }
    }
    if (result != ERROR && tt_getTable()->num == tt_getTable()->passNum)
        tt_getTable()->runState = PASS;
}

void tt_print()
{
    tp_printTitle(ALL, "this is test");
    struct TestSuite* pTs;
    for (pTs = tt_getTable()->tsHead; pTs != NULL; pTs = ts_getNextSuite(pTs))
    {
        if (ts_print(pTs) == TRUE)
            break;
    }
    tp_printStatics();
}

void tt_getSuiteStatus(int* suiteNum, int* suitePassNum)
{
    *suiteNum = tt_getTable()->num;
    *suitePassNum = tt_getTable()->passNum;
}
void tt_getCaseStatus(int* caseNum, int* casePassNum)
{
    struct TestSuite* pTs;
    *caseNum = *casePassNum = 0;
    for (pTs = tt_getTable()->tsHead; pTs != NULL; pTs = ts_getNextSuite(pTs))
    {
        int num, passNum;
        ts_getCaseStatus(pTs, &num, &passNum);
        *caseNum += num;
        *casePassNum += passNum;
    }
}

