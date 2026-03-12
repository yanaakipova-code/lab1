#include <test.h>

extern DinamicArray* current_array;
extern int current_arg;

TEST(do_where_no_array) {
    puts("ТЕСТ 23.1");
    puts("---do_where: массив не создан---");
    
    current_array = NULL;
    
    do_where();
    
    assert(1 == 1);
}

TEST(do_where_string_length_gt_4) {
    puts("ТЕСТ 23.2");
    puts("---do_where: фильтрация строк длиной больше 4---");
    AllErrors last_error;
    
    current_array = create_array(get_string_type_info(), &last_error);
    append(current_array, "cat", &last_error);
    append(current_array, "elephant", &last_error);
    append(current_array, "dog", &last_error);
    append(current_array, "butterfly", &last_error);
    append(current_array, "fox", &last_error);
    
    DinamicArray* result = where(current_array, string_length_4, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 2);
    
    char* val0 = (char*)get(result, 0, &last_error);
    char* val1 = (char*)get(result, 1, &last_error);
    
    assert(strcmp(val0, "elephant") == 0);
    assert(strcmp(val1, "butterfly") == 0);
    
    destroy_array(result, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_where_string_contains_y) {
    puts("ТЕСТ 23.3");
    puts("---do_where: фильтрация строк содержащих 'y'---");
    AllErrors last_error;
    
    current_array = create_array(get_string_type_info(), &last_error);
    append(current_array, "sky", &last_error);
    append(current_array, "cat", &last_error); 
    append(current_array, "yellow", &last_error);   
    append(current_array, "dog", &last_error);
    append(current_array, "yacht", &last_error);
    
    DinamicArray* result = where(current_array, string_contains_y, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 3);
    
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
    puts("ТЕСТ 23.4");
    puts("---do_where: фильтрация функций с четным f(7)---");
    AllErrors last_error;
    
    current_array = create_array(get_func_type_info(), &last_error);
    append(current_array, inc, &last_error);
    append(current_array, dec, &last_error);
    append(current_array, square, &last_error); 
    
    DinamicArray* result = where(current_array, func_even, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 2);
    
    IntFunc f0 = (IntFunc)get(result, 0, &last_error);
    IntFunc f1 = (IntFunc)get(result, 1, &last_error);
    
    assert(f0(5) == 6);
    assert(f1(5) == 4);
    
    destroy_array(result, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_where_func_greater_than_10) {
    puts("ТЕСТ 23.5");
    puts("---do_where: фильтрация функций с f(7) > 10---");
    AllErrors last_error;
    
    current_array = create_array(get_func_type_info(), &last_error);
    append(current_array, inc, &last_error);
    append(current_array, dec, &last_error);
    append(current_array, square, &last_error);

    DinamicArray* result = where(current_array, func_greater_than_10, &last_error);
    
    assert(result != NULL);
    assert(last_error == ARRAY_OK);
    assert(get_size(result, &last_error) == 1);
    
    IntFunc f0 = (IntFunc)get(result, 0, &last_error);
    assert(f0(5) == 25);
    
    destroy_array(result, &last_error);
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_where_empty_result) {
    puts("ТЕСТ 23.6");
    puts("---do_where: пустой результат фильтрации---");
    AllErrors last_error;
    
    current_array = create_array(get_string_type_info(), &last_error);
    append(current_array, "cat", &last_error);
    append(current_array, "dog", &last_error);
    append(current_array, "fox", &last_error);
    
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
    puts("ТЕСТ 23.7");
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