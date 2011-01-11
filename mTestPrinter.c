#include "mTestPrinter.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "mTestResult.h"
#include "mTestTable.h"

#define TRUE 1
#define FALSE 0

enum TP_Color
{
    COLOR_DEFAULT,
    COLOR_RED,
    COLOR_GREEN,
};

struct TP_Statics
{
    int suiteNum;
    int caseNum;
    int suitePassNum;
    int casePassNum;
};

struct TestPrinter
{
    FILE* output;
    enum TP_ColorMode colorMode;
    enum TP_TimeMode timeMode;
    void (*printTitle)(enum TP_PrintState state, const char* title);
    void (*printTime)(struct TestResultList* pTrl);
    void (*printStatics)();
    void (*printPass)(struct TestResult* pTr, int i);
    void (*printFail)(struct TestResult* pTr, int i);
    void (*printError)(struct TestResult* pTr, int i);
};

static struct TestPrinter* printer;

void tp_s_stdPrintTitle(enum TP_PrintState state, const char* title)
{
    switch (state)
    {
    case ALL:
        printf("\n[\tIN\t] Test  : %s\n", title);
        break;

    case SUITE:
        printf("\n[\tIN\t] Suite : %s\n", title);
        break;

    case CASE:
        printf("[\tRUN\t] Case  : %s\n", title);
        break;

    default:
        assert(0);
        break;
    }
}

void tp_s_printUserInfo(struct TestResult* pTr)
{
    if (pTr->msg != NULL)
        printf("\tMsg\t = %s\n", pTr->msg);
}

void tp_s_stdPrintPass(struct TestResult* pTr, int i)
{
    printf("[\tPASS\t] Expect(%d) OK\n", i + 1);
}

void tp_s_printResult(struct TestResult* pTr)
{
    switch (pTr->paramType)
    {
    case INTEGER_TYPE:
        printf("\tExpected = %d\n", *(int *)pTr->expected);
        printf("\tActual   = %d\n", *(int *)pTr->actual);
        break;

    case FLOAT_TYPE:
        printf("\tExpected = %g\n", *(double *)pTr->expected);
        printf("\tActual   = %g\n", *(double *)pTr->actual);
        break;

    case STRING_TYPE:
        printf("\tExpected = %s\n", (char *)pTr->expected);
        printf("\tActual   = %s\n", (char *)pTr->actual);
        break;

    default:
        assert(0);
        break;
    }
}

void tp_s_stdPrintFail(struct TestResult* pTr, int i)
{
    printf("[\tFAIL\t] Expect(%d) Fail\n", i + 1);
    tp_s_printResult(pTr);
    tp_s_printUserInfo(pTr);
}

void tp_s_stdPrintError(struct TestResult* pTr, int i)
{
    printf("[\tERROR\t] Assert(%d) Fail\n", i + 1);
    tp_s_printResult(pTr);
    tp_s_printUserInfo(pTr);
}

void tp_s_getStatics(struct TP_Statics* pStat)
{
    tt_getSuiteStatus(&pStat->suiteNum, &pStat->suitePassNum);
    tt_getCaseStatus(&pStat->caseNum, &pStat->casePassNum);
}

void tp_s_stdPrintStatics()
{
    struct TP_Statics stat;
    tp_s_getStatics(&stat);
    printf("\n\tTotal\tPass\n");
    printf("Suite:\t%d\t%d\n", stat.suiteNum, stat.suitePassNum);
    printf("Case :\t%d\t%d\n", stat.caseNum, stat.casePassNum);
}

void tp_s_stdPrintTime(struct TestResultList* pTrl)
{
    printf("\n\n\tTime\t = %ld ms(with %d expect(s))\n\n", pTrl->time, pTrl->num);
}


static struct TestPrinter* tp_s_malloc(enum TP_ColorMode color, enum TP_TimeMode time, const char* fileName)
{
    assert(!((fileName != NULL) && (color == WITH_COLOR)));

    struct TestPrinter* pTp = (struct TestPrinter*)malloc(sizeof (*pTp));
    pTp->colorMode = color;
    pTp->timeMode = time;
    if (fileName == NULL)
    {
        pTp->output = stdout;
        pTp->printTitle = tp_s_stdPrintTitle;
        pTp->printStatics = tp_s_stdPrintStatics;
        pTp->printPass = tp_s_stdPrintPass;
        pTp->printFail = tp_s_stdPrintFail;
        pTp->printError = tp_s_stdPrintError;
        pTp->printTime = tp_s_stdPrintTime;
    }
/*
    else
    {
        pTp->output = fopen(fileName, "w");
        pTp->printTitle = tp_s_filePrintTitle;
        pTp->printStatics = tp_s_filePrintStatics;
        pTp->printPass = tp_s_filePrintPass;
        pTp->printFail = tp_s_filePrintFail;
        pTp->printError = tp_s_filePrintError;
        pTp->printTime = tp_s_filePrintTime;
    }
*/
    return pTp;
}

void tp_init(enum TP_ColorMode color, enum TP_TimeMode time, const char* fileName)
{
    assert(printer == NULL);

    printer = tp_s_malloc(color, time, fileName);
}

struct TestPrinter* tp_getPrinter()
{
    if (printer == NULL)
        printer = tp_s_malloc(WITH_COLOR, WITH_TIME, NULL);
    return printer;
}

void tp_printTitle(enum TP_PrintState state, const char* title)
{
    tp_getPrinter()->printTitle(state, title);
}

void tp_printTime(struct TestResultList* pTrl)
{
    if (printer->timeMode == WITH_TIME)
    {
        tp_getPrinter()->printTime(pTrl);
    }
}

void tp_printStatics()
{
    tp_getPrinter()->printStatics();
}

void tp_printResult(struct TestResult* pTr, int i)
{
    if (pTr->pass == TRUE)
        tp_getPrinter()->printPass(pTr, i);
    else if (pTr->fatal == TRUE)
        tp_getPrinter()->printError(pTr, i);
    else
        tp_getPrinter()->printFail(pTr, i);
}

/*
enum mColor
{
    COLOR_RED = FOREGROUND_RED,
    COLOR_GREEN = FOREGROUND_GREEN,
    COLOR_BLUE = FOREGROUND_BLUE,
    COLOR_INTENSE = FOREGROUND_INTENSITY
};

static void beforePrint(enum mColor color, HANDLE* outputHandle, WORD* pOldColor)
{
    *outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(*outputHandle, &buffer_info);
    *pOldColor = buffer_info.wAttributes;

    SetConsoleTextAttribute(*outputHandle, color | COLOR_INTENSE);
}

static void afterPrint(HANDLE outputHandle, WORD oldColor)
{
    SetConsoleTextAttribute(outputHandle, oldColor);
}
*/
