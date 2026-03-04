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

void* string_to_upper(const void* elem, void* ctx, ArrayErrors* error);
void* string_to_lower(const void* elem, void* ctx, ArrayErrors* error);

int string_length_4(const void* elem, void* ctx, ArrayErrors* error);
int string_contains_y(const void* elem, void* ctx, ArrayErrors* error);

void* string_concat_op(const void* a, const void* b, void* ctx, ArrayErrors* error);



void* func_apply_to_arg_wrapper(const void* elem, void* ctx, ArrayErrors* error);
void* func_apply_to_8_wrapper(const void* elem, void* ctx, ArrayErrors* error);

int func_even_wrapper(const void* elem, void* ctx, ArrayErrors* error);
int func_greater_than_10_wrapper(const void* elem, void* ctx, ArrayErrors* error);


void* func_compose_op(const void* a, const void* b, void* ctx, ArrayErrors* error);

