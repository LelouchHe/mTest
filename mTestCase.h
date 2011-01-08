#ifndef MTESTCASE_H_INCLUDED
#define MTESTCASE_H_INCLUDED

struct Expect;

struct TestCase
{
    struct Expect* expHead;
    struct TestCase* next;
    int num;
    const char* caseName;
};

struct TestCase* tc_malloc(const char* caseName);
void tc_free(struct TestCase* pTc);
void tc_addToCase(struct TestCase* pTc, void* exp, int (* func)(void*));
void tc_run(struct TestCase* pTc);

//pFrom与pTo重名,所以把pFrom合并到pTo中
void tc_merge(struct TestCase* pTo, struct TestCase* pFrom);

int tc_isSameCase(struct TestCase* pTo, struct TestCase* pFrom);


#endif // MTESTCASE_H_INCLUDED
