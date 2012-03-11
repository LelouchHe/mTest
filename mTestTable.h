#ifndef MTESTTABLE_H_INCLUDED
#define MTESTTABLE_H_INCLUDED

struct TestResultList;
struct TestTable;
struct TestContext;

struct TestTable* tt_getTable();
void tt_free();
void tt_addToTable(const char* suiteName, const char* caseName, void (*func)(struct TestResultList*, struct TestContext*));

void tt_run();
void tt_print();

void tt_getSuiteStatus(int* suiteNum, int* suitePassNum);
void tt_getCaseStatus(int* caseNum, int* casePassNum);

void tt_addBeforeAll(void (* func)());
void tt_addBeforeSuite(const char* suiteName, void (* func)());
void tt_addBeforeCase(const char* suiteName, const char* caseName, void (* func)());

void tt_addAfterAll(void (* func)());
void tt_addAfterSuite(const char* suiteName, void (* func)());
void tt_addAfterCase(const char* suiteName, const char* caseName, void (* func)());

#endif // MTEST_H_INCLUDED
