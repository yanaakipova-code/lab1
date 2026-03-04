#pragma once
#include "TypeInfo.h"
#include "ArrayEror.h"

TypeInfo* GetIntTypeInfo();
void FreeIntTypeInfo();

void* int_clone(const void* elem, ArrayErrors* error);
void int_free(void* elem, ArrayErrors* error);
char* int_to_string(const void* elem, ArrayErrors* error);
