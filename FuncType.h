#pragma once
#include "ArrayEror.h"
#include "TypeInfo.h"

typedef int (*IntFunc)(int);

void* func_clone(const void* elem, AllErrors* error);
void func_free(void* elem, AllErrors* error);
char* func_to_string(const void* elem, AllErrors* error);
static size_t get_element_size();
TypeInfo* get_func_type_info();