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