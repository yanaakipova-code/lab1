#include <test.h>

TEST(create_array_string){
    puts("ТЕСТ 1.1");
    puts("---Создание массива строк---");
    AllErrors errors;

    DinamicArray* arr = create_array(get_string_type_info(), &errors);

    assert(errors == ARRAY_OK);
    assert(arr != NULL);
    assert(arr->size == 0);
    assert(arr->capacity == 4);
    
    destroy_array(arr, &errors);
}

TEST(test_create_array_func){ 
    puts("ТЕСТ 1.2");
    puts("---Создание массива функций---");
    AllErrors errors;

    DinamicArray* arr = create_array(get_func_type_info(), &errors);

    assert(errors == ARRAY_OK);
    assert(arr != NULL);
    assert(arr->size == 0);
    assert(arr->capacity == 4);
    
    destroy_array(arr, &errors);
}

TEST(test_create_array){
    puts("ТЕСТ 1.3");
    puts("---Пограничное значение функции создания массива---");
    AllErrors errors;

    DinamicArray* arr = create_array(NULL, &errors);

    assert(errors == NULL_POINTER);
    assert(arr == NULL);
}

TEST(test_destroy_array_ok){
    puts("ТЕСТ 2.1");
    puts("---Разрушение массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_func_type_info(), &errors);

    destroy_array(arr, &errors);

    assert(errors == ARRAY_OK);
}

TEST(test_destroy_array_fl){
    puts("ТЕСТ 2.2");
    puts("---Разрушение массива c NULL---");
    AllErrors errors;

    destroy_array(NULL, &errors);

    assert(errors == NULL_POINTER);
}

TEST(test_append){
    puts("ТЕСТ 3.1");
    puts("---добавление элемента в массив---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    const char* elem = "y";
    unsigned int old_size = arr->size;

    append(arr, elem, &errors);

    assert(errors == ARRAY_OK);
    assert(arr->size == old_size + 1);
    
    destroy_array(arr, &errors);
}

TEST(test_increasing_size){
    puts("ТЕСТ 3.2");
    puts("---Увеличение емкости массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    const char* elem = "y";
    unsigned int start_capacity = arr->capacity;

    for (unsigned int i = 0; i < start_capacity; i++){
        append(arr, elem, &errors);
    }
    assert(arr->size == start_capacity);
    assert(arr->size == arr->capacity);

    append(arr, elem, &errors);

    assert(errors == ARRAY_OK);
    assert(arr->capacity == start_capacity * 2);
    
    destroy_array(arr, &errors);
}

TEST(test_increasing_size_fl){
    puts("ТЕСТ 3.3");
    puts("---Увеличение ёмкости массива с NULL---");
    AllErrors errors;
    
    increasing_size(NULL, &errors);

    assert(errors == NULL_POINTER); 
}

TEST(test_append_fl){
    puts("ТЕСТ 3.4");
    puts("---Добавление элемента с NULL---");
    const char* elem = "y";
    AllErrors errors;

    append(NULL, elem, &errors);

    assert(errors == NULL_POINTER);
}

TEST(get_by_valid_index){
    puts("ТЕСТ 4.1");
    puts("---Получение элемента по индексу---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "h", &errors);
    append(arr, "e", &errors);
    append(arr, "l", &errors);
    append(arr, "l", &errors);
    append(arr, "o", &errors);
    
    char* element = (char*)get(arr, 2, &errors);

    assert(errors == ARRAY_OK);
    assert(strcmp(element, "l") == 0);
    
    destroy_array(arr, &errors);
}

TEST(get_by_index_negative){
    puts("ТЕСТ 4.2");
    puts("---Отрицательный индекс массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "h", &errors);
    append(arr, "e", &errors);
    append(arr, "l", &errors);
    append(arr, "l", &errors);
    append(arr, "o", &errors);

    char* element = (char*)get(arr, -1, &errors);

    assert(errors == INDEX_OUT);
    assert(element == NULL);
    
    destroy_array(arr, &errors);
}

TEST(get_by_index_out_bounds){
    puts("ТЕСТ 4.3");
    puts("---Индекс вне диапазона---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "h", &errors);
    append(arr, "e", &errors);
    append(arr, "l", &errors);
    append(arr, "l", &errors);
    append(arr, "o", &errors);

    char* element = (char*)get(arr, 5, &errors);

    assert(errors == INDEX_OUT);
    assert(element == NULL);
    
    destroy_array(arr, &errors);
}

TEST(get_by_empty_array){
    puts("ТЕСТ 4.4");
    puts("---Индекс пустого массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);

    char* element = (char*)get(arr, 0, &errors);
    
    assert(errors == INDEX_OUT);
    assert(element == NULL);
    
    destroy_array(arr, &errors);
}

TEST(test_get_size){
    puts("ТЕСТ 5.1");
    puts("---Получение размера массива---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "h", &errors);
    append(arr, "e", &errors);
    append(arr, "l", &errors);

    int size = get_size(arr, &errors);

    assert(errors == ARRAY_OK);
    assert(size == 3);
    
    destroy_array(arr, &errors);
}

TEST(test_get_size_empty_array){
    puts("ТЕСТ 5.2");
    puts("---Получение размера массива с нулевой длиной---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);

    int size = get_size(arr, &errors);

    assert(errors == ARRAY_OK);
    assert(size == 0);
    
    destroy_array(arr, &errors);
}
  
TEST(test_get_size_null_array){
    puts("ТЕСТ 5.3");
    puts("---Получение размера массива с NULL---");
    AllErrors errors;

    int size = get_size(NULL, &errors);

    assert(errors == NULL_POINTER);
    assert(size == -1);
}

TEST(test_array_to_string){
    puts("ТЕСТ 6.1");
    puts("---Преобразование массива в строку---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_string_type_info(), &errors);
    append(arr, "hello", &errors);
    append(arr, "world", &errors);
    append(arr, "!", &errors);

    char* str = array_to_string(arr, &errors);

    assert(errors == ARRAY_OK);
    assert(str != NULL);
    assert(strcmp(str, "[\"hello\", \"world\", \"!\"]") == 0);
    
    free(str);
    destroy_array(arr, &errors);
}

TEST(test_array_to_string_empty_array){
    puts("ТЕСТ 6.2");
    puts("---Преобразование пустого массива в строку---");
    AllErrors errors;
    DinamicArray* empty_arr = create_array(get_string_type_info(), &errors);

    char* str = array_to_string(empty_arr, &errors);

    assert(errors == ARRAY_OK);
    assert(str != NULL);
    assert(strcmp(str, "[]") == 0);

    free(str);
    destroy_array(empty_arr, &errors);
}

TEST(test_array_to_string_null){
    puts("ТЕСТ 6.3");
    puts("---Преобразование массива в строку с NULL указателем---");
    AllErrors errors;

    char* str = array_to_string(NULL, &errors);

    assert(errors == NULL_POINTER);
    assert(str == NULL);
}

TEST(array_to_string_int){
    puts("ТЕСТ 6.4");
    puts("---Преобразование массива чисел в строку---");
    AllErrors errors;
    DinamicArray* arr = create_array(get_int_type_info(), &errors);
    int a = 10, b = 20, c = 30;
    append(arr, &a, &errors);
    append(arr, &b, &errors);
    append(arr, &c, &errors);

    char* str = array_to_string(arr, &errors);

    assert(errors == ARRAY_OK);
    assert(str != NULL);
    assert(strcmp(str, "[10, 20, 30]") == 0);
    
    free(str);
    destroy_array(arr, &errors);
}