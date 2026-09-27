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

    size_t capacity = 3; //TODO: function to get from user

    if ((statusCode = STACK_CTOR(&stk1, capacity)) != OK) {
        return  $err("ERROR WHILE CONSTRUCTING STACK", statusCode);
    }

    // if ((statusCode = StackPush(&stk1, 1)) != OK) {
    //     return $err("ERROR WHILE TRYING TO PUSH", statusCode);
    // }
    // if ((statusCode = StackPush(&stk1, 2)) != OK) {
    //     return $err("ERROR WHILE TRYING TO PUSH", statusCode);
    // }
    // if ((statusCode = StackPush(&stk1, 3)) != OK) {
    //     return $err("ERROR WHILE TRYING TO PUSH", statusCode);
    // }

    // StackDump(&stk1);
    
    // if ((statusCode = StackPush(&stk1, 4)) != OK) {
    //     return $err("ERROR WHILE TRYING TO PUSH", statusCode);
    // }

    StackDump(&stk1);

    double Elem = 0;

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