#include <test.h>

TEST(reduce_string_concat) {
    puts("ТЕСТ 9.1");
    puts("---reduce: конкатенация строк---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors); 
    append(arr, "Hello", &errors);
    append(arr, " ", &errors);
    append(arr, "World", &errors);
    append(arr, "!", &errors);
    char* init = "";
    
    char* result = (char*)reduce(arr, string_concat_op, init, &errors);

    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(strcmp(result, "Hello World!") == 0);
}

TEST(reduce_func_compose) {
    puts("ТЕСТ 9.2");
    puts("---reduce: композиция функций---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_func_type_info(), &errors);
    append(arr, inc, &errors);
    append(arr, square, &errors);
    void* init = get(arr, 0, &errors);

    void* result = reduce(arr, func_compose, init, &errors);

    assert(errors == ARRAY_OK);
    assert(result != NULL);
    IntFunc composed = (IntFunc)result;
    assert(composed(5) == 36);
    
    destroy_array(arr, &errors);
}

TEST(reduce_single_element) {
    puts("ТЕСТ 9.3");
    puts("---reduce: массив с одним элементом---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "Hello", &errors);
    char* init = "";

    char* result = (char*)reduce(arr, string_concat_op, init, &errors);

    assert(errors == ARRAY_OK);
    assert(result != NULL);
    assert(strcmp(result, "Hello") == 0);
   
    free(result);
    destroy_array(arr, &errors);
} 

TEST(reduce_null_array) {
    puts("ТЕСТ 9.4");
    puts("---reduce: проверка с NULL массивом---");
    AllErrors errors;
    char* init = "";
    
    void* result = reduce(NULL, string_concat_op, init, &errors);
    
    assert(errors == NULL_POINTER);
    assert(result == NULL);
}

TEST(reduce_null_binop) {
    puts("ТЕСТ 9.5");
    puts("---reduce: проверка с NULL binop функцией---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    assert(errors == ARRAY_OK);
    char* init = "";
    
    void* result = reduce(arr, NULL, init, &errors);
    
    assert(errors == NULL_POINTER);
    assert(result == NULL);
}

TEST(reduce_null_init) {
    puts("ТЕСТ 9.6");
    puts("---reduce: проверка с NULL init значением---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    assert(errors == ARRAY_OK);
    
    void* result = reduce(arr, string_concat_op, NULL, &errors);
    
    assert(errors == NULL_POINTER);
    assert(result == NULL);
}