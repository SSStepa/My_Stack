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
        assert(MyName);
    )

    if (capacity == 0) {
        $ERR_START();
        return $ERR("CAN'T CREATE STACK WITH 0 CAPACITY", WRIN);
    }

    if (stk -> capacity != 0 || stk -> data != 0 || stk -> size != 0) {
        $ERR_START();
        return $ERR("INCORRECT STACK TO INITIALIZE", WRIN);
    }

    stk -> capacity = capacity;
    stk -> data = (stackDataType *) calloc(capacity DEBUGGER(+2), sizeof(stackDataType));
    if (stk -> data == NULL) {
        $ERR_START();
        return $ERR("NOT ENOUGH MEMORY TO CREATE STACK", NOMEM);
    }

    DEBUGGER(
        stk -> canaryData = stk -> data;
        stk -> data++;
        *(stk -> canaryData) = STACK_CANARY_FIRST;
        *(stk -> data + stk -> capacity) = STACK_CANARY_SECOND;

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
        DEBUGGER(
            ErrInfo errInfo = {};
            ERR_INIT(errInfo, statusCode, "INCORRECT STACK AFTER CREATION");
            StackDump(stk, errInfo);
        )
        
        return $ERR("WRONG DATA IN STACK", statusCode);
    }

    return OK;
}

WORK_RES StackPush(stack_t *stk, stackDataType Elem) 
{
    assert(stk);

    WORK_RES statusCode = OK;

    if ((statusCode = StackIsValid(*stk)) != OK) {
        return $ERR("NOT VALID STACK GOT BY FUNCTION", statusCode);
    }

    if (stk -> capacity == stk -> size) {
        if ((statusCode = ResizeUp(stk)) != OK)
            return statusCode;
    }

    (stk -> data)[(stk -> size)++] = Elem;

    if ((statusCode = StackIsValid(*stk)) != OK) {
        DEBUGGER(
            ErrInfo errInfo = {};
            ERR_INIT(errInfo, statusCode, "UNVALID STACK WHILE PUSHING");
            StackDump(stk, errInfo);
        )
        return $ERR("NOT VALID STACK AFTER PUSH", statusCode);
    }

    return OK;
}

WORK_RES ResizeUp(stack_t *stk)
{
    assert(stk);
    
    stk -> capacity *= 2;
    
    stackDataType *temp = (stackDataType *) realloc(DEBUGGER(--)(stk -> data), (stk -> capacity DEBUGGER(+2))*sizeof(stackDataType));
    if (temp == NULL) {
        DEBUGGER(
            ErrInfo errInfo = {};
            ERR_INIT(errInfo, NOMEM, "NOT ENOUGH MEMORY");
            StackDump(stk, errInfo);
        )
        return $ERR("NOT ENOUGH MEMORY", NOMEM);
    }
    stk -> data = temp;

    DEBUGGER(
        stk -> canaryData = (stk -> data)++;
        *(stk -> canaryData) = STACK_CANARY_FIRST;
        *(stk -> data + stk -> capacity) = STACK_CANARY_SECOND;

        for (size_t ind = stk -> size; ind < stk -> capacity; ind++) {
            (stk -> data)[ind] = STACK_EL_POISON;
        }
    )
    return OK;

}

WORK_RES StackPop(stack_t *stk, stackDataType *elem)
{
    assert(stk);

    WORK_RES statusCode = OK;

    if ((statusCode = StackIsValid(*stk)) != OK) {
        DEBUGGER(
        ErrInfo errInfo = {};
        ERR_INIT(errInfo, statusCode, "INCORRECT STACK WHILE TRYING TO POP");

        StackDump(stk, errInfo);
        )
        return $ERR("NOT VALID STACK GOT BY FUNCTION", statusCode);
    }
    
    if (stk -> size == 0) {
        DEBUGGER(
            ErrInfo errInfo = {};
            ERR_INIT(errInfo, STACK_UNDERFLOW, "POP FROM STACK WITH 0 SIZE");
            StackDump(stk, errInfo);
        )
        return $ERR("CAN'T GET ELEMENT FROM STACK WITHOUT ELEMENTS", STACK_UNDERFLOW);
    }

    if ((stk ->capacity)/4 > stk -> size) {
        if ((statusCode = ResizeDown(stk)) != OK) {
            return statusCode;
        }
    }

    *elem = (stk -> data)[--(stk -> size)];
    DEBUGGER(
    (stk -> data)[(stk -> size)] = STACK_EL_POISON;
    )

    if ((statusCode = StackIsValid(*stk)) != OK) {
        DEBUGGER(
            ErrInfo errInfo = {};
            ERR_INIT(errInfo, statusCode, "INCORRECT STACK WHILE TRYING TO POP");
            StackDump(stk, errInfo);
        )
        return $ERR("NOT VALID STACK AFTER POP", statusCode);
    }

    return OK;
}

WORK_RES ResizeDown(stack_t *stk)
{
    assert(stk);

    stk -> capacity = stk -> size;
    
    stackDataType *temp = (stackDataType *) realloc(DEBUGGER(--)(stk -> data), (stk -> capacity DEBUGGER(+2))*sizeof(stackDataType));
    if (temp == NULL) {
        DEBUGGER(
            ErrInfo errInfo = {};
            ERR_INIT(errInfo, NOMEM, "PROBLEM WHILE TRYING TO REALLOC TO SMALLER SIZE");
            StackDump(stk, errInfo);
        )
        return $ERR("PROBLEM WHILE TRYING TO REALLOC TO SMALLER SIZE", NOMEM);
    }
    stk -> data = temp;

    DEBUGGER(
        stk -> canaryData = (stk -> data)++;
        *(stk -> canaryData) = STACK_CANARY_FIRST;
        *(stk -> data + stk -> capacity) = STACK_CANARY_SECOND;
    )

    return OK;
}

WORK_RES StackDtor(stack_t *stk)
{
    WORK_RES statusCode = OK;
    if ((statusCode = StackIsValid(*stk)) != OK) {
        DEBUGGER(
           ErrInfo errInfo = {};
            ERR_INIT(errInfo, WRIN, "INCORRECT STACK TO DELETE");
            StackDump(stk, errInfo);
        )
        return $ERR("WRONG DATA IN STACK", statusCode);
    }

    free(DEBUGGER(--)(stk -> data));
    stk -> data = 0;
    stk -> capacity = 0;
    stk -> size = 0;
    DEBUGGER(
        stk -> canaryData = 0;
    )

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
        $ERR_START();
        return $ERR("STACK DATA PTR IS 0", STACK_DATA);
    }

    if (stk.capacity == 0) {
        $ERR_START();
        return $ERR("STACK CAPACITY IS 0", STACK_CAP);
    }

    if (stk.size > stk.capacity) {
        $ERR_START();
        return $ERR("STACK SIZE OF BIGGER THAN CAPACITY", STACK_OVERFLOW);
    }

    DEBUGGER(
    if (*stk.canaryData != STACK_CANARY_FIRST) {
        $ERR_START();
        return $ERR("FIRST CANARY IS KILLED", STACK_CANARY_RIP);
    }
    if (*(stk.data + stk.capacity) != STACK_CANARY_SECOND) {
        $ERR_START();
        return $ERR("SECOND CANARY IS KILLED", STACK_CANARY_RIP);
    }
    )
    return OK;
}

WORK_RES StackDump(stack_t *stk, ErrInfo errInfo)
{
    DEBUGGER(
    assert(stk != NULL);

    FILE *logFile = fopen(LOG_FILE, "a");

    if (logFile == NULL) {
        $ERR("CAN'T OPEN LOG FILE", FILEERR);
    } else {

        fprintf(logFile, "\nBEGIN OF DUMP\n\n");
        fprintf(logFile, "%s %s\n", __DATE__, __TIME__);
        fflush(logFile);

        fprintf(logFile, "Dump was called in %s %s:%d with error code %d because of %s\n", 
            errInfo.fileCreationName,
            errInfo.creationFunctionName,
            errInfo.creationLineName,
            errInfo.err,
            errInfo.ErrorText
        );

        if (errInfo.err == STACK_DATA) return OK;

        fprintf(logFile, "\nHi there! I'm %s[%p] and I was created in %s %s:%d\n", 
            &(stk -> MyName)[1], // to skip &
            stk, 
            stk -> fileCreationName, 
            stk -> creationFunctionName, 
            stk -> creationLineName
        );

        fprintf(logFile, "capacity = <%llu> \nsize = <%llu>\n\n", stk -> capacity, stk -> size);
        fprintf(logFile, "data is on [%p]\n", stk -> data);

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

        if (errInfo.err == STACK_CANARY_RIP) {
            fprintf(logFile, "Expected canary is: ");
            fprintf(logFile, FILL_FOR_PRINTF " and " FILL_FOR_PRINTF, STACK_CANARY_FIRST, STACK_CANARY_SECOND);
            fprintf(logFile, "\nAnd got: ");
            fprintf(logFile, FILL_FOR_PRINTF " and " FILL_FOR_PRINTF "\n", *(stk -> canaryData), *(stk -> data + stk -> capacity));
        }

        fprintf(logFile, "%s %s\n", __DATE__, __TIME__);
        fprintf(logFile, "\nEND OF DUMP\n\n");
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