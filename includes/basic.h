/**
 * @file basic.h
 * @brief structs, consts and funcs i use daily.
 */
#ifndef BASIC_H
#define BASIC_H

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

/**
 * @brief Work of function available results.
 */
enum WORK_RES {
    OK = 0, // all good
    WRIN = 1, // function got bad args
    NOMEM = 2, // not enough memory
    FILEERR = 4, // no file to open.

    STACK_DATA = 11, // wrong data format
    STACK_CAP = 12, // zero capacity
    STACK_OVERFLOW = 13  // size > capacity
};

/**
 * @brief struct to store info about string: length and pointer to first element
 * str - pointer to the first element of the string
 * len - length of the string (with no \0)
 */
struct String {
    char *str;
    size_t len;
};


//------------------------------------------------------------- COLORS ------------------------------------------------------------------------
/**
 * Basic colors
 */
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define COLOR_RESET "\e[0m"

//----------------------------------------------------- PRINTING VARS AND ERRORS ------------------------------------------------------------------------


#define TO_STR(str) #str

const char * const LOG_FILE = "log.txt";

void InfoPrintfInt      (int var, const char *varName, const char *file, int line);
void InfoPrintfStr      (const char *var, const char *varName, const char *file, int line);
void InfoPrintfC        (char var, const char *varName, const char *file, int line);
void InfoPrintfDouble   (double var, const char *varName, const char *file, int line);
void InfoPrintfLlu      (size_t var, const char *varName, const char *file, int line);
WORK_RES SetUpLog();

WORK_RES ErrorPrintf(const char *errMess, int line, const char *file, WORK_RES ErrCode);

#define $int(Variable) InfoPrintfInt(Variable, TO_STR(Variable), __FILE__, __LINE__)
#define $str(Variable) InfoPrintfStr(Variable, TO_STR(Variable), __FILE__, __LINE__)
#define $c(Variable) InfoPrintfC(Variable, TO_STR(Variable), __FILE__, __LINE__)
#define $dbl(Variable) InfoPrintfDouble(Variable, TO_STR(Variable), __FILE__, __LINE__)
#define $llu(Variable) InfoPrintfLlu(Variable, TO_STR(Variable), __FILE__, __LINE__)
#define $err(ErrorMessage, ErrCode) ErrorPrintf(ErrorMessage, __LINE__, __FILE__, ErrCode)

#endif
