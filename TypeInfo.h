#pragma once
#include "ArrayEror.h"
#include <stdio.h>
typedef struct {
    size_t (*elem_size)(); 
    void (*free)(void *, ArrayErrors*);
    void* (*clone)(const void *,  ArrayErrors*);
    char* (*to_string)(const void*, ArrayErrors*);
} TypeInfo;