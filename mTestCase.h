#ifndef MTESTCASE_H_INCLUDED
#define MTESTCASE_H_INCLUDED

enum TR_RunState;
struct TestCase;
struct TestResultList;

struct TestCase* tc_malloc(const char* caseName);
void tc_free(struct TestCase* pTc);

int tc_run(struct TestCase* pTc);


void tc_addExpFunc(struct TestCase* pTc, void (* func)(struct TestResultList*));

struct TestCase* tc_getNextCase(struct TestCase* pTc);
void tc_setNextCase(struct TestCase* pTc, struct TestCase* pNext);

struct TestResultList* tc_getResultList(struct TestCase* pTc);

int tc_print(struct TestCase* pTc);

int tc_runState(struct TestCase* pTc);

#endif // MTESTCASE_H_INCLUDED
