#include "main_basic.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

DinamicArray* current_array = NULL;
ArrayErrors last_error;

void clear_input(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void print_error(const char* context){
    printf("Ошибка в %s: ", context);
    switch (last_error){
        case ARRAY_OK: printf("нет ошибки"); break;
        case MEMORY_ALLOCATION_FAILED: printf("не удалось выделить память"); break;
        case NULL_POINTER: printf("нулевой указатель"); break;
        case INDEX_OUT: printf("индекс вне диапазона"); break;
        case DIFFERENT_TYPE: printf("несовместимые типы"); break;
        default: printf("неизвестная ошибка (%d)", last_error);
    }
}

void print_menu(){
    printf("-------------------------------------------------\n");
    puts("1. Создать массив (строки)");  
    puts("2. Создать массив (функции)");
    puts("3. Добавить элемент");
    puts("4. Показать массив");
    puts("5. Информация o массиве");
    puts("6. MAP - применить преобразование");
    puts("7. WHERE - фильтрация");
    puts("8. REDUCE - свертка");
    puts("9. CONCAT - конкатенация");
    puts("0. Выход");
    printf("Ваш выбор: ");
}

void create_string_array(){
    if (current_array){
        destroy_array(current_array, &last_error);
    }
    
    current_array = create_array(GetStringTypeInfo(), &last_error);
    if (last_error == ARRAY_OK){
        puts("Массив строк создан");
        append(current_array, "hello", &last_error);
        append(current_array, "world", &last_error);
        append(current_array, "this", &last_error);
        append(current_array, "is", &last_error);
        append(current_array, "a", &last_error);
        append(current_array, "test", &last_error);
        append(current_array, "programming", &last_error);
        puts("Добавлены тестовые строки");
    } else{
        print_error("create_string_array");
    }
}

void create_func_array(){
    if (current_array){
        destroy_array(current_array, &last_error);
    }
    
    current_array = create_array(GetFuncTypeInfo(), &last_error);
    if (last_error == ARRAY_OK){
        puts("Массив функций создан");
        append(current_array, inc, &last_error);
        append(current_array, dec, &last_error);
        append(current_array, square, &last_error);
        puts("Добавлены тестовые функции");
    } else{
        print_error("create_func_array");
    }
}

void add_element() {
    if (!current_array) {
        puts("Сначала создайте массив");
        return;
    }
    
    switch (current_array->type->kind){
        case TYPE_STRING:{
            char buffer[256];
            printf("Введите строку: ");
            clear_input();
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            
            if (strlen(buffer) == 0) {
                puts("Строка не может быть пустой");
                return;
            }
            
            append(current_array, buffer, &last_error);
            if (last_error == ARRAY_OK) {
                printf("Строка \"%s\" добавлена\n", buffer);
            } else{
                print_error("add_element");
            }
            break;
        }
        
        case TYPE_FUNC: {
            puts("Выберите функцию:");
            puts("1. inc (+1)");
            puts("2. dec (-1)");
            puts("3. square (x*x)");
            printf("Ваш выбор: ");
            
            unsigned int choice;
            scanf("%u", &choice);
            clear_input();
            
            void* func = NULL;
            const char* name = NULL;
            
            switch (choice){
                case 1: func = inc; name = "inc"; break;
                case 2: func = dec; name = "dec"; break;
                case 3: func = square; name = "square"; break;
                default:
                    puts("Неверный выбор");
                    return;
            }
            
            append(current_array, func, &last_error);
            if (last_error == ARRAY_OK){
                printf("Функция %s добавлена\n", name);
            } else {
                print_error("add_element");
            }
            break;
        }
        
        default:
            puts("Неподдерживаемый тип");
    }
}

void show_array(){
    if (!current_array){
        puts("Массив не создан");
        return;
    }
    
    puts("Текущий массив:");
    print_array(current_array, &last_error);
}


void* string_to_upper(const void* elem, void* ctx, ArrayErrors* error){
    (void)ctx;
    if (!elem){
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    
    const char* str = (const char*)elem;
    char* result = (char*)malloc(strlen(str) + 1);
    if (!result){
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    
    for (unsigned int i = 0; i <= strlen(str); i++){
        result[i] = toupper(str[i]);
    }
    
    if (error) *error = ARRAY_OK;
    return result;
}

void* string_to_lower(const void* elem, void* ctx, ArrayErrors* error) {
    (void)ctx;
    if (!elem) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    
    const char* str = (const char*)elem;
    char* result = (char*)malloc(strlen(str) + 1);
    if (!result) {
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    
    for (unsigned int i = 0; i <= strlen(str); i++) {
        result[i] = tolower(str[i]);
    }
    
    if (error) *error = ARRAY_OK;
    return result;
}

int string_length_4(const void* elem, void* ctx, ArrayErrors* error) {
    (void)ctx;
    if (!elem){
        if (error) *error = NULL_POINTER;
        return 0;
    }
    
    const char* str = (const char*)elem;
    if (error) *error = ARRAY_OK;
    return strlen(str) > 4;
}

int string_contains_y(const void* elem, void* ctx, ArrayErrors* error) {
    (void)ctx;
    if (!elem) {
        if (error) *error = NULL_POINTER;
        return 0;
    }
    
    const char* str = (const char*)elem;
    if (error) *error = ARRAY_OK;
    return strchr(str, 'y') != NULL || strchr(str, 'Y') != NULL;
}

void* string_concat_op(const void* a, const void* b, void* ctx, ArrayErrors* error){
    (void)ctx;
    if (!a || !b){
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    
    const char* s1 = (const char*)a;
    const char* s2 = (const char*)b;
    
    char* result = (char*)malloc(strlen(s1) + strlen(s2) + 1);
    if (!result){
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    
    strcpy(result, s1);
    strcat(result, s2);
    
    if (error) *error = ARRAY_OK;
    return result;
}


void* func_apply_to_arg_wrapper(const void* elem, void* ctx, ArrayErrors* error){
    if (!elem || !ctx){
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    
    IntFunc f = (IntFunc)elem;
    int arg = *(int*)ctx;
    int* result = (int*)malloc(sizeof(int));
    if (!result){
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    
    *result = f(arg);
    if (error) *error = ARRAY_OK;
    return result;
}

int func_even_wrapper(const void* elem, void* ctx, ArrayErrors* error){
    (void)ctx;
    if (!elem){
        if (error) *error = NULL_POINTER;
        return 0;
    }
    
    IntFunc f = (IntFunc)elem;
    if (error) *error = ARRAY_OK;
    return f(7) % 2 == 0;
}

void* func_apply_to_5_wrapper(const void* elem, void* ctx, ArrayErrors* error){
    (void)ctx;
    if (!elem){
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    
    IntFunc f = (IntFunc)elem;
    int* result = (int*)malloc(sizeof(int));
    if (!result){
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    
    *result = f(5);
    if (error) *error = ARRAY_OK;
    return result;
}

int func_greater_than_10_wrapper(const void* elem, void* ctx, ArrayErrors* error){
    (void)ctx;
    if (!elem){
        if (error) *error = NULL_POINTER;
        return 0;
    }
    
    IntFunc f = (IntFunc)elem;
    if (error) *error = ARRAY_OK;
    return f(7) > 10;
}

void* func_compose_op(const void* a, const void* b, void* ctx, ArrayErrors* error){
    (void)ctx;
    if (!a || !b){
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    
    if (error) *error = ARRAY_OK;
    return (void*)b;
}