#include "mTestResult.h"

#include <stdlib.h>
#include <mem.h>

#define TRUE 1
#define FALSE 0

static void tr_s_free(struct TestResult* pTr)
{
    free(pTr->expected);
    free(pTr->actual);
    free(pTr->msg);
}

struct TestResultList* trl_malloc()
{
    struct TestResultList* pTrl = (struct TestResultList*)malloc(sizeof (*pTrl));
    pTrl->trHead = pTrl->trTail = NULL;
    pTrl->num = 0;
    pTrl->time = 0;
    return pTrl;
}

void trl_add(struct TestResultList* pTrl, struct TestResult* pTr)
{
    if (pTrl->trHead == NULL)
        pTrl->trHead = pTrl->trTail = pTr;
    else
    {
        pTrl->trTail->next = pTr;
    }
    pTrl->num++;
    pTrl->trTail = pTr;
}
void trl_free(struct TestResultList* pTrl)
{
    struct TestResult* pTr;
    while (pTrl->trHead != NULL)
    {
        pTr = pTrl->trHead->next;
        tr_s_free(pTrl->trHead);
        free(pTrl->trHead);
        pTrl->trHead = pTr;
    }
    free(pTrl);
    pTrl = NULL;
}

int trl_isFatal(struct TestResultList* pTrl)
{
    struct TestResult* pTr;
    for (pTr = pTrl->trHead; pTr != NULL; pTr = pTr->next)
    {
        if (pTr->pass == FALSE && pTr->fatal == TRUE)
            break;
    }
    if (pTr == NULL)
        return FALSE;
    else
        return TRUE;
}

struct TestResult* tr_malloc()
{
    struct TestResult* pTr = (struct TestResult*)malloc(sizeof(*pTr));
    pTr->actual = pTr->expected = NULL;
    pTr->msg = NULL;
    pTr->next = NULL;
    return pTr;
}

void tr_setVal(struct TestResult* pTr, void* expected, void* actual, enum TR_ParamType type, size_t size)
{
    pTr->paramType = type;
    pTr->expected = malloc(size);
    pTr->actual = malloc(size);

    memcpy(pTr->expected, expected, size);
    memcpy(pTr->actual, actual, size);
}

void tr_setMsg(struct TestResult* pTr, char* msg, size_t len)
{
    pTr->msg = (char*)malloc(len + 1);
    memcpy(pTr->msg, msg, len + 1);
}
