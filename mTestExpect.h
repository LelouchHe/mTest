#ifndef MTESTEXPECT_H_INCLUDED
#define MTESTEXPECT_H_INCLUDED


int runIntEq(void* e);
struct ExpectInt
{
    int expected;
    int actual;
    const char* caseName;
};

int runFloatEq(void* e);
struct ExpectFloat
{
    double expected;
    double actual;
    double error;
    const char* caseName;
};

#endif // MTESTEXPECT_H_INCLUDED
