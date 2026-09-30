#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "basic.h"

#ifdef DEBUGGER
#define ON_DBG(...) __VA_ARGS__
#else
#define ON_DBG(...)
#endif

#define STACK_CTOR(stk, capacity) StackCtor(stk, capacity \
    ON_DBG(         \
        ,TO_STR(stk), \
        __FILE__,     \
        __LINE__,     \
        __FUNCTION__  \
    ) \
)

typedef char stackDataType;
#define FILL_FOR_PRINTF "%c"

ON_DBG(
const stackDataType STACK_EL_POISON = 0;
const stackDataType STACK_CANARY_FIRST = 'S';
const stackDataType STACK_CANARY_SECOND = 'U';
const int BUFF_DUMP_SIZE = 100;

const unsigned long long STACK_STRUCT_LEFT_CANARY = 0xC0FFEEE;
const unsigned long long STACK_STRUCT_RIGHT_CANARY = 0xC0FFFFE;

)


struct stack_t {
    ON_DBG(unsigned long long leftCanary;)

    stackDataType *data;
    size_t size;
    size_t capacity;

    ON_DBG(
    const char *MyName;
    const char *fileCreationName;
    int   creationLineName;
    const char *creationFunctionName;
    stackDataType *canaryData;
    )

    ON_DBG(unsigned long long rightCanary;)
};

WORK_RES StackCtor(
        stack_t *stk, size_t capacity 
        ON_DBG(,const char *Myname, const char *fileCreationName, int creationLineName, const  char *creationFunctionName)
    );
WORK_RES StackDtor(stack_t *stk);

WORK_RES StackPush(stack_t *stk, stackDataType Elem);
WORK_RES ResizeUp(stack_t *stk);

WORK_RES StackPop(stack_t *stk, stackDataType *elem);
WORK_RES ResizeDown(stack_t *stk);

WORK_RES GetStackCapacity(size_t *capacity);

WORK_RES StackIsValid(stack_t stk);

WORK_RES StackDump(stack_t *stk, ErrInfo errInfo);

#endif  
