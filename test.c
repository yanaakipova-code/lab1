#include "main_basic.h"
#include "ArrayEror.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_create_arrays();
void test_string_operations();
void test_func_operations();
void test_map_string();
void test_map_func();
void test_where_string();
void test_where_func();
void test_reduce_string();
void test_reduce_func();
void test_concatenation();
void test_error_handling();

int string_equal(const char* s1, const char* s2) {
    return strcmp(s1, s2) == 0;
}

void print_all_test(){
    puts("--------------------запуск всех тестов-------------------------");
    test_create_arrays();
    test_string_operations();
    test_func_operations();
    test_map_string();
    test_map_func();
    test_where_string();
    test_where_func();
    test_reduce_string();
    test_reduce_func();
    test_concatenation();
    test_error_handling();
    puts("--------------------все тесты пройдены--------------------------");
}

void test_creater_arrays(){
    puts("тест первый: создание массива");
    ArrayErrors last_error; 
    DinamicArray* array = create_array(GetStringTypeInfo(), &last_error);
    assert(last_error == ARRAY_OK);
    assert(array != NULL);
    assert(array->type->kind == TYPE_STRING);
    assert(array->size == 0);
    assert(array->capacity == 4);
    destroy_array(array, &last_error);

    DinamicArray* array= create_array(GetFuncTypeInfo(), &last_error);
    assert(last_error == ARRAY_OK);
    assert(array != NULL);
    assert(array->type->kind == TYPE_FUNC);
    destroy_array(array, &last_error);

    puts("create_array работает корректно");
}

void test_string_operations(){
    ArrayErrors last_error; 
    puts("тест второй: функции для работы co строками");

    const char* str1 = "hello";
    char* upper =(char*)string_to_upper(str1, NULL, &last_error);
    assert(last_error==ARRAY_OK);
    ssert(string_equal(upper, "HELLO"));
    free(upper);

    const char* str2 = "HELLO";
    char* lower = (char*)string_to_lower(str2, NULL, &last_error);
    assert(last_error == ARRAY_OK);
    assert(string_equal(lower, "hello"));

    unsigned int len_f_str = string_length_4("hello", NULL, last_error);
    assert(last_error == ARRAY_OK);
    assert (len_f_str == 1);

    unsigned int len_t_str = "hel";
    assert(last_error==ARRAY_OK);
    assert(len_t_str == 0);

    int contains_result = string_contains_y("yana", NULL, &last_error);
    assert(last_error == ARRAY_OK);
    assert(contains_result == 1);

    contains_result = string_contains_y("Hello", NULL, &last_error);
    assert(last_error == ARRAY_OK);
    assert(contains_result == 0);

    char* concat = (char*)string_concat_op("hello", "world", NULL, &last_error);
    assert(last_error == ARRAY_OK);
    assert(string_equal(concat, "helloworld"));
    free(concat);

    puts("функции для работы co строками работают корректно");
}

void test_func_operations(){
    puts("тест три: тесты для работы с функциями ");
    
    ArrayErrors last_error;
    int* res1 = (int*)func_apply_to_8_wrapper(inc, NULL, &last_error);
    assert(last_error == ARRAY_OK);
    assert(*res1 == 9);
    free(res1);
    
    int* res2 = (int*)func_apply_to_8_wrapper(square, NULL, &last_error);
    assert(last_error == ARRAY_OK);
    assert(*res2 == 64);
    free(res2);
    
    int arg = 10;
    int* res3 = (int*)func_apply_to_arg_wrapper(inc, &arg, &last_error);
    assert(last_error == ARRAY_OK);
    assert(*res3 == 11);
    free(res3);

    int even_result = func_even_wrapper(inc, NULL, &last_error);
    assert(last_error == ARRAY_OK);
    assert(even_result == 1);
    
    even_result = func_even_wrapper(square, NULL, &last_error);
    assert(last_error == ARRAY_OK);
    assert(even_result == 0);
    
    int greater_result = func_greater_than_10_wrapper(square, NULL, &last_error);
    assert(last_error == ARRAY_OK);
    assert(greater_result == 1);
    
    greater_result = func_greater_than_10_wrapper(dec, NULL, &last_error);
    assert(last_error == ARRAY_OK);
    assert(greater_result == 0);
    
    puts("функции для работы с функциями работают корректно работают корректно");
}

void test_map_string() {
    puts("тест четыре: map для строк");

    ArrayErrors* last_error;
    DinamicArray* array= create_array(GetStringTypeInfo(), &last_error);
    append(array, "hello", &last_error);
    append(array, "world", &last_error);

    DinamicArray* result = map(array, string_to_upper, NULL,
                               GetStringTypeInfo(), &last_error);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 2);
    
    char* elem = (char*)get(result, 0, &last_error);
    assert(string_equal(elem, "HELLO"));
    elem = (char*)get(result, 1, &last_error);
    assert(string_equal(elem, "WORLD"));
    
    destroy_array(result, &last_error);
    destroy_array(array, &last_error);
    array = NULL;
    
    puts("map для строк работает корректно");
}

void test_map_func() {
    puts("тест пять: map для работы с  функциями");
    
    ArrayErrors last_error;
    DinamicArray* array = create_array(GetFuncTypeInfo(), &last_error);
    append(array, inc, &last_error);
    append(array, square, &last_error);
    
    DinamicArray* result = map(array, func_apply_to_8_wrapper, NULL,
                               GetIntTypeInfo(), &last_error);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 2);
    
    int* val = (int*)get(result, 0, &last_error);
    assert(*val == 9);
    val = (int*)get(result, 1, &last_error);
    assert(*val == 64);
    
    destroy_array(result, &last_error);
    
    unsigned int arg = 5;
    result = map(array, func_apply_to_arg_wrapper, &arg,
                 GetIntTypeInfo(), &last_error);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 2);
    
    val = (int*)get(result, 0, &last_error);
    assert(*val == 6);
    val = (int*)get(result, 1, &last_error);
    assert(*val == 25);
    
    destroy_array(result, &last_error);
    destroy_array(array, &last_error);
    array = NULL;
    
    puts("map для функций работает корректно");
}

void test_where_string() {
    puts("тест шесть: where для строк");
    
    ArrayErrors last_error; 
    DinamicArray* array = create_array(GetStringTypeInfo(), &last_error);
    append(array, "hello", &last_error);
    append(array, "word", &last_error);
    append(array, "!", &last_error);
    append(array, "Iyana", &last_error);
    
    DinamicArray* result = where(array, string_length_4, NULL, &last_error);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 2);
    
    char* elem = (char*)get(result, 0, &last_error);
    assert(string_equal(elem, "hello"));
    elem = (char*)get(result, 1, &last_error);
    assert(string_equal(elem, "word"));
    destroy_array(result, &last_error);
    
    result = where(array, string_contains_y, NULL, &last_error);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 1);
    
    elem = (char*)get(result, 0, &last_error);
    assert(string_equal(elem, "Iyana"));
    
    destroy_array(result, &last_error);
    destroy_array(array, &last_error);
    array = NULL;
    
    puts("where для строк работает корректно");
}

void test_where_func() {
    puts("тест семь: where для функций");

    ArrayErrors last_error;
    DinamicArray* array = create_array(GetFuncTypeInfo(), &last_error);
    append(array, inc, &last_error);
    append(array, dec, &last_error);
    append(array, square, &last_error);

    DinamicArray* result = where(array, func_greater_than_10_wrapper, NULL, &last_error);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 1);
    
    void* func = get(result, 0, &last_error);
    unsigned int test_val = ((IntFunc)func)(7);
    assert(test_val == 49);
    destroy_array(result, &last_error);

    result = where(array, func_even_wrapper, NULL, &last_error);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 2);
    
    destroy_array(result, &last_error);
    destroy_array(array, &last_error);
    array = NULL;
    
    puts("where для функций работает корректно");
}