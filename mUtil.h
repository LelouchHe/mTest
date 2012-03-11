#ifndef MUTIL_H_INCLUDED
#define MUTIL_H_INCLUDED

void TEST(const char* suiteName, const char* caseName);
void EXPECT_INT_EQ(const int expected, const int actual);
void EXPECT_FLOAT_EQ(const double expected, const double actual, const double error);

void INITTEST();
void RUNTEST();

#endif // MUTIL_H_INCLUDED
