#include "../includes/basic.h"
#include "../includes/stack.h"
void Break(stack_t *stk) {
    stk->size++;
}

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

    if ((statusCode = STACK_PUSH(&stk1, 32)) != OK) {
        $ERR("ERROR WHILE TRYING TO PUSH\n", statusCode);
        $ERR_END();
        return statusCode;
    }

    if ((statusCode = STACK_PUSH(&stk1, 'b')) != OK) {
        $ERR("ERROR WHILE TRYING TO PUSH\n", statusCode);
        $ERR_END();
        return statusCode;
    }

    if ((statusCode = STACK_PUSH(&stk1, 'c')) != OK) {
        $ERR("ERROR WHILE TRYING TO PUSH\n", statusCode);
        $ERR_END();
        return statusCode;
    }
    if ((statusCode = STACK_PUSH(&stk1, 'c')) != OK) {
        $ERR("ERROR WHILE TRYING TO PUSH\n", statusCode);
        $ERR_END();
        return statusCode;
    }
    if ((statusCode = STACK_PUSH(&stk1, 'c')) != OK) {
        $ERR("ERROR WHILE TRYING TO PUSH\n", statusCode);
        $ERR_END();
        return statusCode;
    }

    if ((statusCode = STACK_PUSH(&stk1, 's')) != OK) {
        $ERR("ERROR WHILE TRYING TO PUSH\n", statusCode);
        $ERR_END();
        return statusCode;
    }

    stackDataType Elem = 0;

    if ((statusCode = STACK_POP(&stk1, &Elem)) != OK) {
        $ERR("ERROR WHILE TRYING TO POP\n", statusCode);
        $ERR_END();
        return statusCode;
    }
//------------------------------------------------------------------------------------------------

    if ((statusCode = STACK_POP(&stk1, &Elem)) != OK) {
        $ERR("ERROR WHILE TRYING TO POP\n", statusCode);
        $ERR_END();
        return statusCode;
    }

    Break(&stk1);

    if ((statusCode = STACK_POP(&stk1, &Elem)) != OK) {
        $ERR("ERROR WHILE TRYING TO POP\n", statusCode);
        $ERR_END();
        return statusCode;
    }
    
    if ((statusCode = StackDtor(&stk1)) != OK) {
        $ERR("ERROR WHILE DESTRUCTING STACK\n", statusCode);
        $ERR_END();
        return statusCode;
    }
    
    EndLog();
    
    return 0;
}