#include <test.h>

extern DinamicArray* current_array;
extern int current_arg;

TEST(do_concatenation_no_array) {
    puts("ТЕСТ 25.1");
    puts("---do_concatenation: массив не создан---");
    
    AllErrors last_error;
    current_array = NULL;
    
    do_concatenation();
    
    assert(TEST_OK);
}

TEST(do_concatenation_string_arrays) {
    puts("ТЕСТ 25.2");
    puts("---do_concatenation: конкатенация строковых массивов---");
    AllErrors last_error;
    current_array = create_array(get_string_type_info(), &last_error);
    append(current_array, "Hello", &last_error);
    append(current_array, " ", &last_error);
    
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
    puts("ТЕСТ 25.3");
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
    assert(f0(5) == 6); 
    assert(f1(5) == 4);
    assert(f2(5) == 25);
    
    destroy_array(result, &last_error);
    destroy_array(second, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_concatenation_empty_first) {
    puts("ТЕСТ 26.4");
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
    puts("ТЕСТ 26.5");
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
    puts("ТЕСТ 26.6");
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
    puts("ТЕСТ 26.7");
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