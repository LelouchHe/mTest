#ifndef MTESTPRINTER_H_INCLUDED
#define MTESTPRINTER_H_INCLUDED

struct TestResult;
struct TestResultList;

enum TP_ColorMode
{
    WITH_COLOR, NO_COLOR
};

enum TP_TimeMode
{
    WITH_TIME, NO_TIME
};

enum TP_OutputMode
{
    STD_OUTPUT, FILE_OUTPUT
};

enum TP_PrintState
{
    ALL, SUITE, CASE
};


void tp_init(enum TP_ColorMode color, enum TP_TimeMode time, const char* fileName);
struct TestPrinter* tp_getPrinter();
void tp_free();

void tp_printTitle(enum TP_PrintState state, const char* title);
void tp_printTime(struct TestResultList* pTrl);
void tp_printStatics();

void tp_printResult(struct TestResult* pTr, int i);




#endif // MTESTPRINTER_H_INCLUDED
