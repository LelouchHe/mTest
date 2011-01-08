#include "mTest.h"
#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define EXPECT_EQ(EXPECTED, ACTUAL)
struct Expect_##EXPECTED
{
    int expected;
    int actual;
    char* name;
};

struct Expect_##EXPECTED_##ACTUAL* e = malloc(sizeof (e));
e->name = #EXPECTED;
e->expected = EXPECTED;
e->actual = ACTUAL;

int run(struct Expect_##EXPECTED* e)
{
    if (e->expected == e->actual)
    {
        printf("Expectation %s : PASS", e->name);
        return TRUE;
    else
    {
        printf("Expectation %s : FAIL\nExpected = %d\nActual = %d\b", e->name, e->expected, e->actual);
        return FALSE;
    }
}
