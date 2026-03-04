#pragma once
#include "ArrayEror.h"
#include "TypeInfo.h"

typedef int (*IntFunc)(int);

int inc(int x);
int dec(int x);
int square(int x);

void* func_clone(const void* elem, ArrayErrors* error);
void func_free(void* elem, ArrayErrors* error);
char* func_to_string(const void* elem, ArrayErrors* error);

TypeInfo* GetFuncTypeInfo();
void FreeFuncTypeInfo();