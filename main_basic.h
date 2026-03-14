#pragma once
#include "DynamicArray.h"
#include "StringType.h"
#include "FuncType.h"
#include "IntType.h"

void clear_input();
void print_error(const char* context);

void create_string_array();
void create_func_array();

void add_element();
void show_array();
void show_info();

void do_map();
void do_where();
void do_reduce();
void do_concatenation();

void string_to_upper(const void* src, void* dst, AllErrors* error);
void string_to_lower(const void* src, void* dst, AllErrors* error);
int string_length_4(const void* elem, AllErrors* error);
int string_contains_y(const void* elem, AllErrors* error);
void* string_concat_op(const void* a, const void* b, AllErrors* error);

void func_apply_to_arg(const void* src, void* dst, AllErrors* error);
int func_even(const void* a, AllErrors* error);
int func_greater_than_10(const void * a, AllErrors* error);
void * func_compose(const void* a, const void* b, AllErrors* error);