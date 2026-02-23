#pragma once
#include "ArrayEror.h"
#include "TypeInfo.h"

typedef int (*IntFunc)(int);

int inc(int x);
int dec(int x);
int square(int x);

static void* func_clone(const void* elem, ArrayErrors* error);
static void func_free(void* elem, ArrayErrors* error);
static void func_print(const void* elem, ArrayErrors* error);

TypeInfo* GetFuncTypeInfo();
void FreeFuncTypeInfo();