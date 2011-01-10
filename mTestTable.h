#ifndef MTESTTABLE_H_INCLUDED
#define MTESTTABLE_H_INCLUDED

struct TestCase;
struct TestSuite;
struct TestTable;

struct TestTable* tt_getTable();
void tt_free();
void tt_addToTable(const char* suiteName, const char* caseName, void (*func)());
void tt_run();

void tt_addToCase(struct TestTable* pTt, void* exp, int(* func)(void*));
struct TestCase* tt_getCurCase(struct TestTable* pTt);


#endif // MTEST_H_INCLUDED
