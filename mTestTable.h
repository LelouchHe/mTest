#ifndef MTESTTABLE_H_INCLUDED
#define MTESTTABLE_H_INCLUDED

struct TestCase;
struct TestSuite;

struct TestTable
{
    struct TestSuite* tsHead;
    struct TestSuite* curSuite;
    int num;
    void(* initHead)();
    int iniNum;
};

struct TestTable* tt_malloc();
void tt_free(struct TestTable* pTt);
void tt_addToTable(struct TestTable* pTt, struct TestSuite* pTs);
void tt_run(struct TestTable* pTt);

void tt_addToCase(struct TestTable* pTt, void* exp, int(* func)(void*));
struct TestCase* tt_getCurCase(struct TestTable* pTt);

#endif // MTEST_H_INCLUDED
