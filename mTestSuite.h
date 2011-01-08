#ifndef MTESTSUITE_H_INCLUDED
#define MTESTSUITE_H_INCLUDED

struct TestCase;

struct TestSuite
{
    struct TestCase* tcHead;
    struct TestCase* curCase;
    struct TestSuite* next;
    const char* suiteName;
    int num;
};

struct TestSuite* ts_malloc(const char* suiteName);
void ts_free(struct TestSuite* pTs);
void ts_addToSuite(struct TestSuite* pTs, struct TestCase* pTc);
void ts_run(struct TestSuite* pTs);

void ts_merge(struct TestSuite* pTo, struct TestSuite* pFrom);

int ts_isSameSuite(struct TestSuite* pA, struct TestSuite* pB);

void ts_addToCase(struct TestSuite* pTs, void* exp, int(*func)(void*));

struct TestCase* ts_getCurCase(struct TestSuite* pTs);

#endif // MTESTSUITE_H_INCLUDED
