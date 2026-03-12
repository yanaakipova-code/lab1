#include <test.h>

extern DinamicArray* current_array;
extern int current_arg;

TEST(do_reduce_no_array) {
    puts("ТЕСТ 24.1");
    puts("---do_reduce: массив не создан---");
    
    AllErrors last_error;
    current_array = NULL;
    
    do_reduce();
    
    assert(TEST_OK);
}

TEST(do_reduce_empty_array) {
    puts("ТЕСТ 24.2");
    puts("---do_reduce: пустой массив---");
    AllErrors last_error;
    current_array = create_array(get_string_type_info(), &last_error);
    
    do_reduce();
    
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_reduce_string_concat) {
    puts("ТЕСТ 24.3");
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
    puts("ТЕСТ 24.4");
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
    puts("ТЕСТ 24.5");
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
    assert(composed(5) == 36);
    
    destroy_array(current_array, &last_error);
    current_array = NULL;
}

TEST(do_reduce_func_compose_three) {
    puts("ТЕСТ 24.6");
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
    assert(composed(5) == 35);
    
    destroy_array(current_array, &last_error);
    current_array = NULL;
}