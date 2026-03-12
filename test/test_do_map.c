#include "test.h"

extern DinamicArray* current_array;
extern int current_arg;

TEST(do_map_no_array) {
    puts("ТЕСТ 22.1");
    puts("---do_map: массив не создан---");
    AllErrors last_error;
    current_array = NULL;
    
    do_map();
    
    assert(TEST_OK); 
}

TEST(do_map_string_to_upper) {
    puts("ТЕСТ 22.2");
    puts("---do_map: преобразование строк в верхний регистр---");
    AllErrors last_error;
    current_array = create_array(get_string_type_info(), &last_error);
    append(current_array, "hello", &last_error);
    append(current_array, "world", &last_error);
    append(current_array, "test", &last_error);
    
    DinamicArray* result = map(current_array, string_to_upper, 
                               get_string_type_info(), &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 3);
    char* val0 = (char*)get(result, 0, &last_error);
    char* val1 = (char*)get(result, 1, &last_error);
    char* val2 = (char*)get(result, 2, &last_error);
    assert(strcmp(val0, "HELLO") == 0);
    assert(strcmp(val1, "WORLD") == 0);
    assert(strcmp(val2, "TEST") == 0);
    
    destroy_array(result, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_map_string_to_lower) {
    puts("ТЕСТ 22.3");
    puts("---do_map: преобразование строк в нижний регистр---");
    AllErrors last_error;
    current_array = create_array(get_string_type_info(), &last_error);
    append(current_array, "HELLO", &last_error);
    append(current_array, "WORLD", &last_error);
    append(current_array, "TEST", &last_error);
    
    DinamicArray* result = map(current_array, string_to_lower, 
                               get_string_type_info(), &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 3);
    char* val0 = (char*)get(result, 0, &last_error);
    char* val1 = (char*)get(result, 1, &last_error);
    char* val2 = (char*)get(result, 2, &last_error);
    assert(strcmp(val0, "hello") == 0);
    assert(strcmp(val1, "world") == 0);
    assert(strcmp(val2, "test") == 0);
    
    destroy_array(result, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_map_func_to_8) {
    puts("ТЕСТ 22.4");
    puts("---do_map: применение функций к числу 8---");
    AllErrors last_error;
    current_array = create_array(get_func_type_info(), &last_error);
    append(current_array, inc, &last_error);
    append(current_array, dec, &last_error);
    append(current_array, square, &last_error);
    
    DinamicArray* result = map(current_array, func_apply_to_8, 
                               get_int_type_info(), &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 3);
    int* val0 = (int*)get(result, 0, &last_error);
    int* val1 = (int*)get(result, 1, &last_error);
    int* val2 = (int*)get(result, 2, &last_error);
    assert(*val0 == 9);
    assert(*val1 == 7); 
    assert(*val2 == 64);
    
    destroy_array(result, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_map_func_to_arg) {
    puts("ТЕСТ 22.5");
    puts("---do_map: применение функций к аргументу---");
    AllErrors last_error;
    current_arg = 10;
    current_array = create_array(get_func_type_info(), &last_error);
    append(current_array, inc, &last_error);
    append(current_array, dec, &last_error);
    append(current_array, square, &last_error);
    
    DinamicArray* result = map(current_array, func_apply_to_arg, 
                               get_int_type_info(), &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 3);
    int* val0 = (int*)get(result, 0, &last_error);
    int* val1 = (int*)get(result, 1, &last_error);
    int* val2 = (int*)get(result, 2, &last_error);
    assert(*val0 == 11);
    assert(*val1 == 9); 
    assert(*val2 == 100);
    
    destroy_array(result, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_map_empty_array) {
    puts("ТЕСТ 22.6");
    puts("---do_map: пустой массив---");
    AllErrors last_error;
    current_array = create_array(get_string_type_info(), &last_error);
    
    DinamicArray* result = map(current_array, string_to_upper, 
                               get_string_type_info(), &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 0);
    
    destroy_array(result, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

// ================ ТЕСТЫ ДЛЯ do_where ================

TEST(do_where_no_array) {
    puts("ТЕСТ 22.7");
    puts("---do_where: массив не создан---");
    
    AllErrors last_error;
    current_array = NULL;
    
    do_where();
    
    assert(1);
}

TEST(do_where_string_length_gt_4) {
    puts("ТЕСТ 22.8");
    puts("---do_where: фильтрация строк длиной больше 4---");
    
    AllErrors last_error;
    
    current_array = create_array(get_string_type_info(), &last_error);
    append(current_array, "cat", &last_error);       // длина 3
    append(current_array, "elephant", &last_error);  // длина 7
    append(current_array, "dog", &last_error);       // длина 3
    append(current_array, "butterfly", &last_error); // длина 9
    append(current_array, "fox", &last_error);       // длина 3
    
    DinamicArray* result = where(current_array, string_length_4, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 2);  // elephant, butterfly
    
    char* val0 = (char*)get(result, 0, &last_error);
    char* val1 = (char*)get(result, 1, &last_error);
    
    assert(strcmp(val0, "elephant") == 0);
    assert(strcmp(val1, "butterfly") == 0);
    
    destroy_array(result, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_where_string_contains_y) {
    puts("ТЕСТ 22.9");
    puts("---do_where: фильтрация строк содержащих 'y'---");
    
    AllErrors last_error;
    
    current_array = create_array(get_string_type_info(), &last_error);
    append(current_array, "sky", &last_error);      // содержит y
    append(current_array, "cat", &last_error);      // не содержит
    append(current_array, "yellow", &last_error);   // содержит y
    append(current_array, "dog", &last_error);      // не содержит
    append(current_array, "yacht", &last_error);    // содержит y
    
    DinamicArray* result = where(current_array, string_contains_y, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 3);  // sky, yellow, yacht
    
    char* val0 = (char*)get(result, 0, &last_error);
    char* val1 = (char*)get(result, 1, &last_error);
    char* val2 = (char*)get(result, 2, &last_error);
    
    assert(strcmp(val0, "sky") == 0);
    assert(strcmp(val1, "yellow") == 0);
    assert(strcmp(val2, "yacht") == 0);
    
    destroy_array(result, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_where_func_even) {
    puts("ТЕСТ 22.10");
    puts("---do_where: фильтрация функций с четным f(7)---");
    
    AllErrors last_error;
    
    current_array = create_array(get_func_type_info(), &last_error);
    append(current_array, inc, &last_error);    // inc(7)=8 (четное)
    append(current_array, dec, &last_error);    // dec(7)=6 (четное)
    append(current_array, square, &last_error); // square(7)=49 (нечетное)
    
    DinamicArray* result = where(current_array, func_even, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 2);  // inc и dec
    
    IntFunc f0 = (IntFunc)get(result, 0, &last_error);
    IntFunc f1 = (IntFunc)get(result, 1, &last_error);
    
    assert(f0(5) == 6);  // inc(5) = 6
    assert(f1(5) == 4);  // dec(5) = 4
    
    destroy_array(result, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_where_func_greater_than_10) {
    puts("ТЕСТ 22.11");
    puts("---do_where: фильтрация функций с f(7) > 10---");
    
    AllErrors last_error;
    
    current_array = create_array(get_func_type_info(), &last_error);
    append(current_array, inc, &last_error);    // inc(7)=8 (<10)
    append(current_array, dec, &last_error);    // dec(7)=6 (<10)
    append(current_array, square, &last_error); // square(7)=49 (>10)
    
    DinamicArray* result = where(current_array, func_greater_than_10, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 1);  // только square
    
    IntFunc f0 = (IntFunc)get(result, 0, &last_error);
    assert(f0(5) == 25);  // square(5) = 25
    
    destroy_array(result, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_where_empty_result) {
    puts("ТЕСТ 22.12");
    puts("---do_where: пустой результат фильтрации---");
    
    AllErrors last_error;
    
    current_array = create_array(get_string_type_info(), &last_error);
    append(current_array, "cat", &last_error);
    append(current_array, "dog", &last_error);
    append(current_array, "fox", &last_error);
    
    // Нет строк длиной > 4
    DinamicArray* result = where(current_array, string_length_4, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 0);
    
    char* str = array_to_string(result, &last_error);
    assert(strcmp(str, "[]") == 0);
    free(str);
    
    destroy_array(result, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_where_empty_array) {
    puts("ТЕСТ 22.13");
    puts("---do_where: пустой массив---");
    
    AllErrors last_error;
    
    current_array = create_array(get_string_type_info(), &last_error);
    
    DinamicArray* result = where(current_array, string_length_4, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 0);
    
    destroy_array(result, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

// ================ ТЕСТЫ ДЛЯ do_reduce ================

TEST(do_reduce_no_array) {
    puts("ТЕСТ 22.14");
    puts("---do_reduce: массив не создан---");
    
    AllErrors last_error;
    current_array = NULL;
    
    do_reduce();
    
    assert(1);
}

TEST(do_reduce_empty_array) {
    puts("ТЕСТ 22.15");
    puts("---do_reduce: пустой массив---");
    
    AllErrors last_error;
    
    current_array = create_array(get_string_type_info(), &last_error);
    
    do_reduce();  // Должна вывести "Массив пуст"
    
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_reduce_string_concat) {
    puts("ТЕСТ 22.16");
    puts("---do_reduce: конкатенация строк---");
    
    AllErrors last_error;
    
    current_array = create_array(get_string_type_info(), &last_error);
    append(current_array, "Hello", &last_error);
    append(current_array, " ", &last_error);
    append(current_array, "World", &last_error);
    append(current_array, "!", &last_error);
    
    char* init = "";
    char* result = (char*)reduce(current_array, string_concat_op, init, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(strcmp(result, "Hello World!") == 0);
    
    free(result);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_reduce_string_concat_single) {
    puts("ТЕСТ 22.17");
    puts("---do_reduce: конкатенация одного элемента---");
    
    AllErrors last_error;
    
    current_array = create_array(get_string_type_info(), &last_error);
    append(current_array, "Hello", &last_error);
    
    char* init = "";
    char* result = (char*)reduce(current_array, string_concat_op, init, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(strcmp(result, "Hello") == 0);
    
    free(result);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_reduce_func_compose) {
    puts("ТЕСТ 22.18");
    puts("---do_reduce: композиция функций---");
    
    AllErrors last_error;
    
    current_array = create_array(get_func_type_info(), &last_error);
    append(current_array, inc, &last_error);
    append(current_array, square, &last_error);
    
    void* init = get(current_array, 0, &last_error);
    void* result = reduce(current_array, func_compose, init, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    
    IntFunc composed = (IntFunc)result;
    // Композиция: сначала inc, потом square: square(inc(5)) = square(6) = 36
    assert(composed(5) == 36);
    
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_reduce_func_compose_three) {
    puts("ТЕСТ 22.19");
    puts("---do_reduce: композиция трех функций---");
    
    AllErrors last_error;
    
    current_array = create_array(get_func_type_info(), &last_error);
    append(current_array, inc, &last_error);
    append(current_array, square, &last_error);
    append(current_array, dec, &last_error);
    
    void* init = get(current_array, 0, &last_error);
    void* result = reduce(current_array, func_compose, init, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    
    IntFunc composed = (IntFunc)result;
    // Композиция: inc -> square -> dec
    // dec(square(inc(5))) = dec(square(6)) = dec(36) = 35
    assert(composed(5) == 35);
    
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

// ================ ТЕСТЫ ДЛЯ do_concatenation ================

TEST(do_concatenation_no_array) {
    puts("ТЕСТ 22.20");
    puts("---do_concatenation: массив не создан---");
    
    AllErrors last_error;
    current_array = NULL;
    
    do_concatenation();
    
    assert(1);
}

TEST(do_concatenation_string_arrays) {
    puts("ТЕСТ 22.21");
    puts("---do_concatenation: конкатенация строковых массивов---");
    
    AllErrors last_error;
    
    current_array = create_array(get_string_type_info(), &last_error);
    append(current_array, "Hello", &last_error);
    append(current_array, " ", &last_error);
    
    // Создаем второй массив вручную
    DinamicArray* second = create_array(get_string_type_info(), &last_error);
    append(second, "World", &last_error);
    append(second, "!", &last_error);
    
    DinamicArray* result = concatenation(current_array, second, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 4);
    
    char* val0 = (char*)get(result, 0, &last_error);
    char* val1 = (char*)get(result, 1, &last_error);
    char* val2 = (char*)get(result, 2, &last_error);
    char* val3 = (char*)get(result, 3, &last_error);
    
    assert(strcmp(val0, "Hello") == 0);
    assert(strcmp(val1, " ") == 0);
    assert(strcmp(val2, "World") == 0);
    assert(strcmp(val3, "!") == 0);
    
    destroy_array(result, &last_error);
    destroy_array(second, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_concatenation_func_arrays) {
    puts("ТЕСТ 22.22");
    puts("---do_concatenation: конкатенация массивов функций---");
    
    AllErrors last_error;
    
    current_array = create_array(get_func_type_info(), &last_error);
    append(current_array, inc, &last_error);
    append(current_array, dec, &last_error);
    
    DinamicArray* second = create_array(get_func_type_info(), &last_error);
    append(second, square, &last_error);
    
    DinamicArray* result = concatenation(current_array, second, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 3);
    
    IntFunc f0 = (IntFunc)get(result, 0, &last_error);
    IntFunc f1 = (IntFunc)get(result, 1, &last_error);
    IntFunc f2 = (IntFunc)get(result, 2, &last_error);
    
    assert(f0(5) == 6);  // inc
    assert(f1(5) == 4);  // dec
    assert(f2(5) == 25); // square
    
    destroy_array(result, &last_error);
    destroy_array(second, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_concatenation_empty_first) {
    puts("ТЕСТ 22.23");
    puts("---do_concatenation: пустой первый массив---");
    
    AllErrors last_error;
    
    current_array = create_array(get_string_type_info(), &last_error);
    
    DinamicArray* second = create_array(get_string_type_info(), &last_error);
    append(second, "test", &last_error);
    
    DinamicArray* result = concatenation(current_array, second, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 1);
    
    char* val = (char*)get(result, 0, &last_error);
    assert(strcmp(val, "test") == 0);
    
    destroy_array(result, &last_error);
    destroy_array(second, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_concatenation_empty_second) {
    puts("ТЕСТ 22.24");
    puts("---do_concatenation: пустой второй массив---");
    
    AllErrors last_error;
    
    current_array = create_array(get_string_type_info(), &last_error);
    append(current_array, "test", &last_error);
    
    DinamicArray* second = create_array(get_string_type_info(), &last_error);
    
    DinamicArray* result = concatenation(current_array, second, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 1);
    
    char* val = (char*)get(result, 0, &last_error);
    assert(strcmp(val, "test") == 0);
    
    destroy_array(result, &last_error);
    destroy_array(second, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_concatenation_both_empty) {
    puts("ТЕСТ 22.25");
    puts("---do_concatenation: оба массива пустые---");
    
    AllErrors last_error;
    
    current_array = create_array(get_string_type_info(), &last_error);
    DinamicArray* second = create_array(get_string_type_info(), &last_error);
    
    DinamicArray* result = concatenation(current_array, second, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 0);
    
    char* str = array_to_string(result, &last_error);
    assert(strcmp(str, "[]") == 0);
    free(str);
    
    destroy_array(result, &last_error);
    destroy_array(second, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_concatenation_different_types) {
    puts("ТЕСТ 22.26");
    puts("---do_concatenation: массивы разных типов---");
    
    AllErrors last_error;
    
    current_array = create_array(get_string_type_info(), &last_error);
    DinamicArray* second = create_array(get_func_type_info(), &last_error);
    
    DinamicArray* result = concatenation(current_array, second, &last_error);
    
    assert(result == NULL);
    assert(last_error == DIFFERENT_TYPE);
    
    destroy_array(current_array, &last_error);
    destroy_array(second, &last_error);
    current_array = NULL;
}

#ifdef RUN_ALONE
    TEST_ENTRY_POINT
#endif