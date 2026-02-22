#pragma once
#include "ArrayEror.h"
#include "TypeInfo.h"

void* string_clone(const void* elem, ArrayErrors* error);
void string_free(void* elem,ArrayErrors* error);
void string_print(const void* elem, ArrayErrors* error);
TypeInfo* GetStringTypeInfo();
void FreeStringTypeInfo();
