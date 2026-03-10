#pragma once

typedef enum{
    ARRAY_OK = 0,

    MEMORY_ALLOCATION_FAILED = 101,
    NULL_POINTER = 202,

    INDEX_OUT= 303,

    DIFFERENT_TYPE = 505,

    ACTION_UNDEFINED = 606,

} AllErrors;