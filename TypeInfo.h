#pragma once
#include "ArrayEror.h"
#include <stdio.h>

typedef struct {
    void (*free)(void *, ArrayErrors*);
    void* (*clone)(const void *,  ArrayErrors*);
    void (*print)(const void*,  ArrayErrors*);
} TypeInfo;