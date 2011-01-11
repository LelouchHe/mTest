//to be tested, usually in another file

int add(int a, int b)
{
    return a + b;
}

double sub(double a, double b)
{
    return a - b;
}

char* str()
{
    return "Lelouch";
}


#include "mTest.h"


TEST(Suite1, Case1)
{
    int a = 1, b = 3, c = 5;
    EXPECT_INT_EQ(c, add(a, b), "%d + %d != %d\n", a, b, c);
}

TEST(Suite1, Case2)
{
    EXPECT_FLOAT_EQ(1.0, 2.0, 0.1, "hello, world");
}

TEST(Suite2, Case1)
{
    EXPECT_STR_EQ(str(), "lelouch", "All Hail Lelouch");
}


int main()
{
    RUNTEST();
    return 0;
}

