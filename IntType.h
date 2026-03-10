#pragma once
#include "TypeInfo.h"
#include "ArrayEror.h"

void* int_clone(const void* elem, AllErrors* error);
void int_free(void* elem, AllErrors* error);
char* int_to_string(const void* elem, AllErrors* error);
static size_t get_element_size();
TypeInfo* get_int_type_info();