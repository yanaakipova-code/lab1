#include "main_basic.h" 
#include "DynamicArray.h"
#include "DynamicArray.c"
#include "StringType.h"
#include "FuncType.h"
#include "IntType.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void print_test_res(const char * test_name, unsigned int condition){
    if (condition){
        printf("тест функции %s прошел успешно", test_name);
    }else printf("тест функции %s провален", test_name);
}

void test_create_array_string(){
    puts("ТЕСТ 1");
    puts("---Создание массива строк---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    assert(errors == ARRAY_OK);
    assert(arr != NULL);
    assert(arr->size == ZERO_SIZE);
    assert(arr->capacity == INITIAL_CAPACITY);

    print_test_res(test_create_array_string, 1);
}

void test_create_array_func(){ 
    puts("ТЕСТ 2");
    puts("---Создание массива функций---");
    AllErrors errors;
   
    DinamicArray* arr = create_array(get_func_type_info(), &errors);
    assert(errors == ARRAY_OK);
    assert(arr != NULL);
    assert(arr->size == ZERO_SIZE);
    assert(arr->capacity == INITIAL_CAPACITY);

    print_test_res(test_create_array_func, 1);
}

void test_create_array(){
    puts("ТЕСТ 2");
    puts("---Пограничное значение функции создания массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(NULL, &errors);
    assert(errors == NULL_POINTER);

    print_test_res(test_create_array, 1);
}

void test_destroy_array_ok(){
    puts("ТЕСТ 3");
    puts("---Разрушение массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_func_type_info(), &errors);
    destroy_array(arr, &errors);
    assert(errors == ARRAY_OK);

    print_test_res(test_destroy_array_ok, 1);
}

void test_destroy_array_fl(){
    puts("ТЕСТ 4");
    puts("---Разрушение массива c NULL---");
    AllErrors errors;
    destroy_array(NULL, &errors);
    assert(errors == NULL_POINTER);

    print_test_res(test_destroy_array_fl, 1);
}

void test_increasing_size(){
    puts("ТЕСТ 5");
    puts("---Увеличение/Добавление элемента ёмкости массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    const char elem ="y";
    unsigned int start_capacity = arr->capacity;
    for (unsigned int i = 0; i < start_capacity; i++){
        append(arr, elem, &errors);
        assert(errors == ARRAY_OK);
    }
    assert(arr->size == start_capacity);
    assert(arr->size == arr->capacity);

    append(arr, elem, &errors);
    assert(errors == ARRAY_OK);
    assert(arr->capacity == start_capacity * RISING_AT_TWO);

    print_test_res(test_increasing_size, 1);
}

void test_increasing_size_fl(){
    puts("ТЕСТ 6");
    puts("---Увеличение ёмкости массива с NULL---");
    AllErrors errors;
    increasing_size(NULL,&errors);

    print_test_res(test_increasing_size_fl, 1);
}

void test_append_fl(){
    puts("ТЕСТ 7");
    puts("---Добавление элемента с NULL---");
    const char elem ="y";
    AllErrors errors;
    append(NULL,elem, &errors);
    assert(errors == NULL_POINTER);
    print_test_res(test_append_fl, 1);
}

void test_get(){
    puts("ТЕСТ 8");
    puts("---Получение элемента по индексу---")
}
