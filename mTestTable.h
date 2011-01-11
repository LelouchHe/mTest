#ifndef MTESTTABLE_H_INCLUDED
#define MTESTTABLE_H_INCLUDED

struct TestResultList;
struct TestTable;

struct TestTable* tt_getTable();
void tt_free();
void tt_addToTable(const char* suiteName, const char* caseName, void (*func)(struct TestResultList*));

void tt_run();
void tt_print();

void tt_getSuiteStatus(int* suiteNum, int* suitePassNum);
void tt_getCaseStatus(int* caseNum, int* casePassNum);



#endif // MTEST_H_INCLUDED
