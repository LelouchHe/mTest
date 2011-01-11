#ifndef MTESTRESULT_H_INCLUDED
#define MTESTRESULT_H_INCLUDED

#include <time.h>

enum TR_ParamType
{
    INTEGER, DOUBLE, STRING
};

struct TestResult
{
    struct TestResult* next;

    int pass;
    enum TR_ParamType paramType;
    void* expected;
    void* actual;

    int fatal;
    char* msg;
};

struct TestResultList
{
    struct TestResult* trHead;
    struct TestResult* trTail;
    int num;
    clock_t time;
};

struct TestResultList* trl_malloc();
void trl_add(struct TestResultList* pTrl, struct TestResult* pTr);
void trl_free(struct TestResultList* pTrl);

int trl_isFatal(struct TestResultList* pTrl);

struct TestResult* tr_malloc();

void tr_setVal(struct TestResult* pTr, void* expected, void* actual, enum TR_ParamType type, size_t size);
void tr_setMsg(struct TestResult* pTr, char* msg, size_t len);

#endif // MTESTRESULT_H_INCLUDED
