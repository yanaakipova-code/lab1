#pragma once
#include "TypeInfo.h"
#include "ArrayEror.h"

void* int_clone(const void* elem, ArrayErrors* error);
void int_free(void* elem, ArrayErrors* error);
char* int_to_string(const void* elem, ArrayErrors* error);
static size_t get_element_size();
TypeInfo* get_int_type_info();