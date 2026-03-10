#pragma once
#include "ArrayEror.h"
#include <stdio.h>
typedef struct {
    size_t (*elem_size)(); 
    void (*free)(void *, AllErrors*);
    void* (*clone)(const void *,  AllErrors*);
    char* (*to_string)(const void*, AllErrors*);
} TypeInfo;