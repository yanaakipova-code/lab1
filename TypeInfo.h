#pragma once
#include "ArrayEror.h"
#include <stdio.h>

typedef enum {
    TYPE_UNKNOWN,
    TYPE_STRING,
    TYPE_FUNC,
    TYPE_INT,
    TYPE_FUNC_RESULT
} TypeKind;

typedef struct {
    TypeKind kind;
    void (*free)(void *, ArrayErrors*);
    void* (*clone)(const void *,  ArrayErrors*);
    void (*print)(const void*,  ArrayErrors*);
} TypeInfo;