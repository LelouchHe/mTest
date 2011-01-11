#ifndef MTESTSUITE_H_INCLUDED
#define MTESTSUITE_H_INCLUDED

struct TestResultList;
struct TestSuite;
struct TestContext;

struct TestSuite* ts_malloc(const char* suiteName);
void ts_free(struct TestSuite* pTs);
void ts_addToSuite(struct TestSuite* pTs, const char* caseName, void (* func)(struct TestResultList*, struct TestContext*));
int ts_run(struct TestSuite* pTs, struct TestContext* pTct);
void ts_merge(struct TestSuite* pTo, struct TestSuite* pFrom);

int ts_isSameSuite(struct TestSuite* pA, struct TestSuite* pB);

struct TestSuite* ts_getNextSuite(struct TestSuite* pTs);
void ts_setNextSuite(struct TestSuite* pTs, struct TestSuite* pNext);

int ts_print();

void ts_getCaseStatus(struct TestSuite* pTs, int* caseNum, int* casePassNum);

int ts_isSuiteName(struct TestSuite* pTs, const char* suiteName);
void ts_addBeforeSuite(struct TestSuite* pTs, void (*func)());
void ts_addAfterSuite(struct TestSuite* pTs, void (*func)());

#endif // MTESTSUITE_H_INCLUDED
