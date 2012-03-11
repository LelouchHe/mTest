#ifndef MTESTEXPECT_H_INCLUDED
#define MTESTEXPECT_H_INCLUDED

struct TestResult;

struct Expect
{
    void* expected;
    void* actual;
    void* extra;
};

struct TestResult* runCase(struct Expect* pExp, void (* cmp)(struct Expect*, struct TestResult*), int fatal, int user, ...);

void cmpIntEq(struct Expect* pExp, struct TestResult* pTr);

void cmpFloatEq(struct Expect* pExp, struct TestResult* pTr);

void cmpStrEq(struct Expect* pExp, struct TestResult* pTr);

#endif // MTESTEXPECT_H_INCLUDED
