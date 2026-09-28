#include "../includes/basic.h"
#include "../includes/stack.h"

int main()
{
    SetUpLog();


    WORK_RES statusCode = OK;

    stack_t stk1 = {};

    size_t capacity = 3;
    if ((statusCode = GetStackCapacity(&capacity)) != OK) {
        return  $err("ERROR WHILE GETTING CAPACITY FROM USER", statusCode);
    }

    if ((statusCode = STACK_CTOR(&stk1, capacity)) != OK) {
        return  $err("ERROR WHILE CONSTRUCTING STACK", statusCode);
    }

    if ((statusCode = StackPush(&stk1, 'a')) != OK) {
        return $err("ERROR WHILE TRYING TO PUSH", statusCode);
    }
    if ((statusCode = StackPush(&stk1, 'b')) != OK) {
        return $err("ERROR WHILE TRYING TO PUSH", statusCode);
    }
    if ((statusCode = StackPush(&stk1, 'c')) != OK) {
        return $err("ERROR WHILE TRYING TO PUSH", statusCode);
    }

    StackDump(&stk1);
    
    if ((statusCode = StackPush(&stk1, 's')) != OK) {
        return $err("ERROR WHILE TRYING TO PUSH", statusCode);
    }

    StackDump(&stk1);

    stackDataType Elem = 0;

    if ((statusCode = StackPop(&stk1, &Elem)) != OK) {
        return $err("ERROR WHILE TRYING TO Pop", statusCode);
    }

    $dbl(Elem);

    StackDump(&stk1);

    if ((statusCode = StackDtor(&stk1)) != OK) {
        return $err("ERROR WHILE DESTRUCTING STACK", statusCode);
    }
    
    return 0;
}