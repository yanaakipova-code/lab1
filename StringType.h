#pragma once
#include "ArrayEror.h"
#include "TypeInfo.h"

void* string_clone(const void* elem, AllErrors* error);
void string_free(void* elem,AllErrors* error);
char* string_to_string(const void* elem, AllErrors* error);

static size_t get_element_size();
TypeInfo* get_string_type_info();

