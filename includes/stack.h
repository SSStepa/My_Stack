#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "basic.h"

#ifdef ON_DBG
#define DEBUGGER(...) __VA_ARGS__
#else
#define DEBUGGER(...)
#endif

#define STACK_CTOR(stk, capacity) StackCtor(stk, capacity \
    DEBUGGER(         \
        ,TO_STR(stk), \
        __FILE__,     \
        __LINE__,     \
        __FUNCTION__  \
    ) \
)

DEBUGGER(
const double STACK_EL_POISON = 1.0; // TODO: nan initialization
const int BUFF_DUMP_SIZE = 100;
)

struct stack_t {
    double *data;
    size_t size;
    size_t capacity;

    DEBUGGER(
    const char *MyName;
    const char *fileCreationName;
    int   creationLineName;
    const char *creationFunctionName;
    )
};

WORK_RES StackCtor(
        stack_t *stk, size_t capacity 
        DEBUGGER(,const char *Myname, const char *fileCreationName, int creationLineName, const  char *creationFunctionName)
    );
WORK_RES StackDtor(stack_t *stk);

WORK_RES StackIsValid(stack_t stk);

WORK_RES StackDump(stack_t *stk);



#endif
