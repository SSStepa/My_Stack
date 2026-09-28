#include "../includes/stack.h"



WORK_RES StackCtor(
        stack_t *stk, size_t capacity 
        DEBUGGER(, const char *MyName, const char *fileCreationName, int creationLineName, const  char *creationFunctionName)
)
{
    assert(stk != NULL);

    DEBUGGER(
        assert(fileCreationName);
        assert(creationFunctionName);
    )

    if (capacity == 0) {
        return $err("CAN'T CREATE STACK WITH 0 CAPACITY", WRIN);
    }
    if (stk -> capacity != 0 || stk -> data != 0 || stk -> size != 0) {
        DEBUGGER(StackDump(stk);)
        return $err("INCORRECT STACK TO INITIALIZE", WRIN);
    }

    stk -> capacity = capacity;
    stk -> data = (stackDataType *) calloc(capacity, sizeof(stackDataType));

    DEBUGGER(
        stk -> MyName = MyName;
        stk -> fileCreationName = fileCreationName;
        stk -> creationLineName = creationLineName;
        stk -> creationFunctionName = creationFunctionName;

        for (size_t ind = 0; ind < capacity; ind++) {
            (stk -> data)[ind] = STACK_EL_POISON;
        }
    )

    WORK_RES statusCode = OK;
    if ((statusCode = StackIsValid(*stk)) != OK) {
        return $err("WRONG DATA IN STACK", statusCode);
    }

    return OK;
}

WORK_RES StackPush(stack_t *stk, stackDataType Elem) 
{
    assert(stk);

    WORK_RES statusCode = OK;

    if ((statusCode = StackIsValid(*stk)) != OK) {
        return $err("NOT VALID STACK GOT BY FUNCTION", statusCode);
    }

    if (stk -> capacity == stk -> size) {
        stk -> capacity *= 2;
        stackDataType *temp = (stackDataType *) realloc(stk -> data, (stk -> capacity)*sizeof(stackDataType));
        if (temp == NULL) {
            return $err("NOT ENOUGH MEMORY", NOMEM);
            DEBUGGER(StackDump(stk);)
        }
        stk -> data = temp;

        DEBUGGER(
            for (size_t ind = stk -> size; ind < stk -> capacity; ind++) {
                (stk -> data)[ind] = STACK_EL_POISON;
            }
        )
    }

    (stk -> data)[(stk -> size)++] = Elem;


    if ((statusCode = StackIsValid(*stk)) != OK) {
        return $err("NOT VALID STACK AFTER PUSH", statusCode);
    }

    return OK;
}

WORK_RES StackPop(stack_t *stk, stackDataType *elem)
{
    assert(stk);

    WORK_RES statusCode = OK;

    if ((statusCode = StackIsValid(*stk)) != OK) {
        return $err("NOT VALID STACK GOT BY FUNCTION", statusCode);
    }
    
    if (stk -> size == 0)
        return $err("CAN'T GET ELEMENT FROM STACK WITHOUT ELEMENTS", STACK_UNDERFLOW);

    if ((stk ->capacity)/4 > stk -> size) {
        stk -> capacity = stk -> size;
        stackDataType *temp = (stackDataType *) realloc(stk -> data, (stk -> capacity)*sizeof(stackDataType));
        if (temp == NULL) {
            return $err("NOT ENOUGH MEMORY", NOMEM);
            DEBUGGER(StackDump(stk);)
        }
        stk -> data = temp;
        
    }

    *elem = (stk -> data)[--(stk -> size)];
    DEBUGGER(
    (stk -> data)[(stk -> size)] = STACK_EL_POISON;
    )

    if ((statusCode = StackIsValid(*stk)) != OK) {
        return $err("NOT VALID STACK AFTER POP", statusCode);
    }

    return OK;
}

WORK_RES StackDtor(stack_t *stk)
{
    WORK_RES statusCode = OK;
    if ((statusCode = StackIsValid(*stk)) != OK) {
        return $err("WRONG DATA IN STACK", statusCode);
    }

    free(stk -> data);
    stk -> data = 0;
    stk -> capacity = 0;
    stk -> size = 0;

    return OK;
}

WORK_RES GetStackCapacity(size_t *capacity)
{
    assert(capacity);
    printf("Hi. What capacity of the stack do you need: ");
    if (scanf("%llu", capacity) == 1)
        return OK;
    else
        return WRIN;

}

WORK_RES StackIsValid(stack_t stk)
{
    if (stk.data == 0) {
        return $err("STACK DATA PTR IS 0", STACK_DATA);
    }
    if (stk.capacity == 0) {
        return $err("STACK CAPACITY IS 0", STACK_CAP);
    }
    if (stk.size > stk.capacity) {
        return $err("STACK SIZE OF BIGGER THAN CAPACITY", STACK_OVERFLOW);
    }

    return OK;
}

WORK_RES StackDump(stack_t *stk)
{
    DEBUGGER(
    assert(stk != NULL);
    WORK_RES statusCode = OK;

    FILE *logFile = fopen(LOG_FILE, "a");

    if (logFile == NULL) {
        $err("CAN'T OPEN LOG FILE", FILEERR);
    } else {

        if ((statusCode = StackIsValid(*stk)) != OK) {
            return $err("WRONG DATA IN STACK", statusCode);
        }

        fprintf(logFile, "Hi there! I'm %s[%p] and I was created in %s %s:%d\n", 
            &(stk -> MyName)[1], // to skip &
            stk, 
            stk -> fileCreationName, 
            stk -> creationFunctionName, 
            stk -> creationLineName
        );

        for (size_t ind = 0; ind < stk -> capacity; ind++) {
            if (IsZero((stk -> data)[ind] - STACK_EL_POISON) || isnan((stk -> data)[ind])) {
                fprintf(logFile, "* [%llu]", ind);
                fprintf(logFile, FILL_FOR_PRINTF, (stk -> data)[ind]);
                fprintf(logFile, "POISON\n");

            } else {
                fprintf(logFile, "  [%llu]", ind);
                fprintf(logFile, FILL_FOR_PRINTF, (stk -> data)[ind]);
                fprintf(logFile, "\n");
            }
        }
        fprintf(logFile, "capacity is <%llu> and size if <%llu>\n\n", stk -> capacity, stk -> size);
    }

    fclose(logFile);

    #ifdef LOUD

    printf("Hi there! I'm %s[%s%p%s] and I was created in %s %s:%d\n", 
        (stk -> MyName),
        YEL,
        stk, 
        COLOR_RESET,
        stk -> fileCreationName, 
        stk -> creationFunctionName, 
        stk -> creationLineName
    );

    for (size_t ind = 0; ind < stk -> capacity; ind++) {
        if ((stk -> data)[ind] == STACK_EL_POISON) {
            printf("* [%s%llu%s] <%s" , CYN, ind, COLOR_RESET, GRN);
            printf(FILL_FOR_PRINTF, (stk -> data)[ind]);
            printf("%s> POISON\n", COLOR_RESET);
        } else {
            printf("  [%s%llu%s] <%s" , CYN, ind, COLOR_RESET, GRN);
            printf(FILL_FOR_PRINTF , (stk -> data)[ind]);
            printf("%s>\n", COLOR_RESET);
        }
    }
    printf("capacity is <%s%llu%s> and size if <%s%llu%s>\n\n", GRN, stk -> capacity, COLOR_RESET, GRN, stk -> size, COLOR_RESET);

    #endif
    )

    return OK;
}