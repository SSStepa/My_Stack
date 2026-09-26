#include "../includes/basic.h"

void InfoPrintfInt(int var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%d%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}

void InfoPrintfStr(const char *var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%s%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}

void InfoPrintfC(char var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%c%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}

void InfoPrintfLlu(size_t var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%llu%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}


void InfoPrintfDouble(double var, const char *varName, const char *file, int line)
{
    fprintf(stderr, YEL "%s, %d:%s %s = <%s%lg%s>\n", file, line, COLOR_RESET, varName, CYN, var, COLOR_RESET);
}

WORK_RES ErrorPrintf(const char *errMess, int line, const char *file, WORK_RES ErrCode)
{
    FILE *fileLog = fopen(LOG_FILE, "a");

    #ifdef LOUD
    fprintf(stderr, CYN "%s, %d:%s %s:%d %s%s\n" COLOR_RESET, file, line, COLOR_RESET, TO_STR(ErrCode), ErrCode, RED, errMess);
    #endif

    fprintf(fileLog, "%s, %d: %s:%d %s\n\n", file, line, TO_STR(ErrCode), ErrCode, errMess);

    fclose(fileLog);
    return ErrCode;
}

WORK_RES SetUpLog()
{
    FILE *fileLog = fopen(LOG_FILE, "a");
    if (fileLog == NULL) return $err("PROBLEM WITH LOG FILE", FILEERR);

    fwrite("-------------------------------------------------------------------------------\n", 1, 80, fileLog);
    fwrite("                                   NEW TRY                                     \n", 1, 80, fileLog);
    fwrite("-------------------------------------------------------------------------------\n", 1, 80, fileLog);
    
    fclose(fileLog);
    return OK;
}

