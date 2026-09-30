#include "../includes/basic.h"
#include "../includes/stack.h"

void CheckFailBySize(size_t *num) {
    *num = 4;
}

// TODO: canary in resize
// TODO: normal printf for canary
// TODO: hash
// TODO: push pop on dbg get line and info
int main()
{
    SetUpLog();

    WORK_RES statusCode = OK;

    stack_t stk1 = {};

    size_t capacity = 0;
    if ((statusCode = GetStackCapacity(&capacity)) != OK) {
        $ERR("ERROR WHILE GETTING CAPACITY FROM USER\n", statusCode);
        $ERR_END();
        return statusCode;
    }

    if ((statusCode = STACK_CTOR(&stk1, capacity)) != OK) {
        $ERR("ERROR WHILE CONSTRUCTING STACK\n", statusCode);
        $ERR_END();
        return statusCode;
    }

    if ((statusCode = StackPush(&stk1, 'a')) != OK) {
        $ERR("ERROR WHILE TRYING TO PUSH\n", statusCode);
        $ERR_END();
        return statusCode;
    }

    if ((statusCode = StackPush(&stk1, 'b')) != OK) {
        $ERR("ERROR WHILE TRYING TO PUSH\n", statusCode);
        $ERR_END();
        return statusCode;
    }

    if ((statusCode = StackPush(&stk1, 'c')) != OK) {
        $ERR("ERROR WHILE TRYING TO PUSH\n", statusCode);
        $ERR_END();
        return statusCode;
    }
    if ((statusCode = StackPush(&stk1, 'c')) != OK) {
        $ERR("ERROR WHILE TRYING TO PUSH\n", statusCode);
        $ERR_END();
        return statusCode;
    }
    if ((statusCode = StackPush(&stk1, 'c')) != OK) {
        $ERR("ERROR WHILE TRYING TO PUSH\n", statusCode);
        $ERR_END();
        return statusCode;
    }

    if ((statusCode = StackPush(&stk1, 's')) != OK) {
        $ERR("ERROR WHILE TRYING TO PUSH\n", statusCode);
        $ERR_END();
        return statusCode;
    }

    stackDataType Elem = 0;

    if ((statusCode = StackPop(&stk1, &Elem)) != OK) {
        $ERR("ERROR WHILE TRYING TO POP\n", statusCode);
        $ERR_END();
        return statusCode;
    }

    // CheckFailBySize(&(stk1.capacity));
    // *stk1.canaryData = 'L';
    *(int *) &stk1 = 0;
    // stk1.data = 0;
    if ((statusCode = StackPop(&stk1, &Elem)) != OK) {
        $ERR("ERROR WHILE TRYING TO POP\n", statusCode);
        $ERR_END();
    }
    
    if ((statusCode = StackPop(&stk1, &Elem)) != OK) {
        $ERR("ERROR WHILE TRYING TO POP\n", statusCode);
        $ERR_END();
        return statusCode;
    }
    
    if ((statusCode = StackDtor(&stk1)) != OK) {
        $ERR("ERROR WHILE DESTRUCTING STACK\n", statusCode);
        $ERR_END();
        return statusCode;
    }
    
    return 0;
}