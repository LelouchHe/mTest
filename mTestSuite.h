#ifndef MTESTSUITE_H_INCLUDED
#define MTESTSUITE_H_INCLUDED

struct TestResultList;
struct TestSuite;

struct TestSuite* ts_malloc(const char* suiteName);
void ts_free(struct TestSuite* pTs);
void ts_addToSuite(struct TestSuite* pTs, const char* caseName, void (* func)(struct TestResultList*));
int ts_run(struct TestSuite* pTs);
void ts_merge(struct TestSuite* pTo, struct TestSuite* pFrom);
int ts_isSameSuite(struct TestSuite* pA, struct TestSuite* pB);


struct TestSuite* ts_getNextSuite(struct TestSuite* pTs);
void ts_setNextSuite(struct TestSuite* pTs, struct TestSuite* pNext);

#endif // MTESTSUITE_H_INCLUDED
