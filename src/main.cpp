#include "../includes/basic.h"
#include "../includes/stack.h"

// DONE: Ctor
// DONE: Dtor
// TODO: Push
// TODO: POP
// DONE: IsValid
// DONE: Dump;
// TODO: IsZero;
int main()
{
    SetUpLog();


    WORK_RES statusCode = OK;

    stack_t stk1 = {};

    size_t capacity = 10; //TODO: function to get from user

    if ((statusCode = STACK_CTOR(&stk1, capacity)) != OK) {
        $err("ERROR WHILE CONSTRUCTING STACK", statusCode);
        return statusCode;
    }

    return 0;
}