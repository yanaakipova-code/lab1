#pragma once
#include "DynamicArray.h"
#include "StringType.h"
#include "FuncType.h"
#include "IntType.h"

void clear_input();
void print_error(const char* context);
void print_menu();

void create_string_array();
void create_func_array();

void add_element();
void show_array();
void show_info();

void do_map();
void do_where();
void do_reduce();
void do_concatenation();

void* string_to_upper_wrapper(const void* elem, ArrayErrors* error);
void* string_to_lower_wrapper(const void* elem, ArrayErrors* error);
int string_length_4_wrapper(const void* elem, ArrayErrors* error);
int string_contains_y_wrapper(const void* elem, ArrayErrors* error);
void* string_concat_op_wrapper(const void* a, const void* b, ArrayErrors* error);

void* func_apply_to_arg_wrapper(const void* elem, ArrayErrors* error);
void* func_apply_to_8_wrapper(const void* elem, ArrayErrors* error);
int func_even_wrapper(const void* elem, ArrayErrors* error);
int func_greater_than_10_wrapper(const void* elem, ArrayErrors* error);
void* func_compose_op_wrapper(const void* a, const void* b, ArrayErrors* error);

char* string_to_upper(const char* elem, ArrayErrors* error);
char* string_to_lower(const char* elem, ArrayErrors* error);
int string_length_4(const char* elem, ArrayErrors* error);
int string_contains_y(const char* elem, ArrayErrors* error);
char* string_concat_op(const char* a, const char* b, ArrayErrors* error);

int* func_apply_to_arg(IntFunc f, int arg, ArrayErrors* error);
int* func_apply_to_8(IntFunc f, ArrayErrors* error);
int func_even(IntFunc f, ArrayErrors* error);
int func_greater_than_10(IntFunc f, ArrayErrors* error);
IntFunc func_compose(IntFunc f, IntFunc g, ArrayErrors* error);