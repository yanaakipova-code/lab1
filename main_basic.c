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
    puts("5. MAP - применить преобразование");
    puts("6. WHERE - фильтрация");
    puts("7. REDUCE - свертка");
    puts("8. CONCAT - конкатенация");
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

void* func_apply_to_8_wrapper(const void* elem, void* ctx, ArrayErrors* error){
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
    
    *result = f(8);
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


void do_map() {
    if (!current_array) {
        puts("Массив не создан");
        return;
    }
    
    switch (current_array->type->kind){
        case TYPE_STRING: {
            puts("Выберите преобразование:");
            puts("1. toUpperCase");
            puts("2. toLowerCase");
            printf("Ваш выбор: ");
            
            unsigned int choice;
            scanf("%u", &choice);
            clear_input();

            void* (*transform)(const void*, void*, ArrayErrors*) = NULL;
            
            switch (choice) {
                case 1: transform = string_to_upper; break;
                case 2: transform = string_to_lower; break;
                default: puts("Неверный выбор"); return;
            }
            
            DinamicArray* result = map(current_array, transform, NULL,
                                       GetStringTypeInfo(), &last_error);
            if (result){
                puts("Результат map:");
                print_array(result, &last_error);
                destroy_array(result, &last_error);
            } else print_error("map");
            break;
        }
        
        case TYPE_FUNC: {
            puts("Выберите аргумент:");
            puts("1. Применить к 8");
            puts("2. Применить к введенному числу");
            printf("Ваш выбор: ");
            
            unsigned int choice;
            scanf("%u", &choice);
            clear_input();
            
            void* (*transform)(const void*, void*, ArrayErrors*) = NULL;
            void* context = NULL;
            int arg;
            
            if (choice == 1) {
                transform = func_apply_to_8_wrapper;
            } else if (choice == 2) {
                printf("Введите число: ");
                scanf("%d", &arg);
                clear_input();
                transform = func_apply_to_arg_wrapper;
                context = &arg;
            } else {
                puts("Неверный выбор");
                return;
            }
            
            DinamicArray* result = map(current_array, transform, context,
                                       GetIntTypeInfo(), &last_error);
            if (result) {
                puts("Результаты применения функций:");
                print_array(result, &last_error);
                destroy_array(result, &last_error);
            } else print_error("map");
            break;
        }
    }
}

void do_where(){
    if (!current_array){
        puts("Массив не создан");
        return;
    }
    
    switch (current_array->type->kind){
        case TYPE_STRING: {
            puts("Выберите условие:");
            puts("1. Длина > 4");
            puts("2. Содержит букву 'y'");
            printf("Ваш выбор: ");
            
            unsigned int choice;
            scanf("%u", &choice);
            clear_input();
            
            int (*predicate)(const void*, void*, ArrayErrors*) = NULL;
            
            switch (choice) {
                case 1: predicate = string_length_4; break;
                case 2: predicate = string_contains_y; break;
                default: puts("Неверный выбор"); return;
            }
            
            DinamicArray* result = where(current_array, predicate, NULL, &last_error);
            if (result) {
                printf("Результат where: ");
                if (get_size(result, &last_error) > 0){
                    print_array(result, &last_error);
                }else puts("пусто");
                destroy_array(result, &last_error);
            } else print_error("where");
            break;
        }
        
        case TYPE_FUNC: {
            puts("Выберите условие:");
            puts("1. f(7) > 10");
            puts("2. f(7) - четное");
            printf("Ваш выбор: ");
            
            unsigned int choice;
            scanf("%u", &choice);
            clear_input();
            
            int (*predicate)(const void*, void*, ArrayErrors*) = NULL;
            
            switch (choice) {
                case 1: predicate = func_greater_than_10_wrapper; break;
                case 2: predicate = func_even_wrapper; break;
                default: puts("Неверный выбор"); return;
            }
            
            DinamicArray* result = where(current_array, predicate, NULL, &last_error);
            if (result) {
                printf("Результат where: ");
                if (get_size(result, &last_error) > 0) {
                    print_array(result, &last_error);
                    printf("\n");
                } else puts("пусто");
                destroy_array(result, &last_error);
            } else print_error("where");
            break;
        }
    }
}

void do_reduce() {
    if (!current_array){
        puts("Массив не создан");
        return;
    }
    
    if (get_size(current_array, &last_error) == 0){
        puts("Массив пуст");
        return;
    }
    
    switch (current_array->type->kind){
        case TYPE_STRING:{
            puts("Выберите операцию:");
            puts("1. Конкатенация строк");
            printf("Ваш выбор: ");
            
            unsigned int choice;
            scanf("%u", &choice);
            clear_input();
            
            if (choice != 1) {
                puts("Неверный выбор");
                return;
            }
            
            void* init = "";
            void* result = reduce(current_array, string_concat_op, NULL, init, &last_error);
            
            if (result) {
                printf("Результат reduce: ");
                current_array->type->print(result, &last_error);
                printf("\n");
                current_array->type->free(result, &last_error);
            } else print_error("reduce");
            break;
        }
        
        case TYPE_FUNC:{
            puts("Выберите операцию:");
            puts("1. Композиция функций");
            printf("Ваш выбор: ");
            
            unsigned int choice;
            scanf("%u", &choice);
            clear_input();

            if (choice != 1) {
                puts("Неверный выбор");
                return;
            }
            
            void* init = get(current_array, 0, &last_error);
            void* result = reduce(current_array, func_compose_op, NULL, init, &last_error);
            
            if (result){
                printf("Результат reduce: композиция функций\n");
            } else print_error("reduce");
            break;
        }
    }
}

void do_concatenation(){
    if (!current_array) {
        puts("Сначала создайте первый массив");
        return;
    }
    
    DinamicArray* second_array = NULL;
    
    if (current_array->type->kind == TYPE_STRING){
        second_array = create_array(GetStringTypeInfo(), &last_error);
        if (last_error == ARRAY_OK) {
            append(second_array, "extra", &last_error);
            append(second_array, "data", &last_error);
            puts("Создан второй массив: [\"extra\", \"data\"]");
        }
    } else {
        second_array = create_array(GetFuncTypeInfo(), &last_error);
        if (last_error == ARRAY_OK) {
            append(second_array, inc, &last_error);
            append(second_array, square, &last_error);
            puts("Создан второй массив: [inc, square]");
        }
    }

    if (!second_array){
        print_error("create second array");
        return;
    }
    
    DinamicArray* result = concatenation(current_array, second_array, &last_error);
    
    if (result){
        puts("Результат конкатенации:");
        print_array(result, &last_error);
        destroy_array(result, &last_error);
    } else print_error("concatenation");
    
    destroy_array(second_array, &last_error);
}