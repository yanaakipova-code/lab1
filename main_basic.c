#include "main_basic.h"

void clear_input(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_menu(){
    puts("---------- ЧТО МОЖЕТ МОЯ ПРОГРАММА ---------- ");
    puts("1. Создать массив (строки)");
    puts("2. Создать массив (функции)");
    puts("3. Добавить элемент");
    puts("4. Показать массив");
    puts("5. Информация");
    puts("6. MAP");
    puts("7. WHERE");
    puts("8. REDUCE");
    puts("9. CONCAT");
    puts("0. Выход");
    printf("Ваш выбор: ");
}

void* to_upper(const void* elem, void* ctx, ArrayErrors* error){
    const char* str = (const char*)elem;
    char* result = malloc(strlen(str) + 1);
    if (!result){ 
        *error = MEMORY_ALLOCATION_FAILED; 
        return NULL; 
    }
    for (size_t i = 0; i < strlen(str); i++){
        result[i] = toupper(str[i]);
    }
    result[strlen(str)] = '\0';
    (void)ctx;
    return result;
}
void* to_lower(const void* elem, void* ctx, ArrayErrors* error){
    const char* str = (const char*)elem;
    char* result = malloc(strlen(str) + 1);
    if (!result){ 
        *error = MEMORY_ALLOCATION_FAILED; 
        return NULL; 
    }
    for (size_t i = 0; i < strlen(str); i++){
        result[i] = tolower(str[i]);
    }
    result[strlen(str)] = '\0';
    (void)ctx;
    return result;
}

int longer_than_3(const void* elem, void* ctx, ArrayErrors* error){
    (void)ctx; 
    (void)error;
    return strlen((const char*)elem) > 3;
}
int contains_a(const void* elem, void* ctx, ArrayErrors* error){
    (void)ctx; 
    (void)error;
    return strchr((const char*)elem, 'a') != NULL;
}

void* concat_strings(const void* a, const void* b, void* ctx, ArrayErrors* error) {
    (void)ctx;
    const char* s1 = (const char*)a;
    const char* s2 = (const char*)b;
    char* result = malloc(strlen(s1) + strlen(s2) + 1);
    if (!result){ 
        *error = MEMORY_ALLOCATION_FAILED; 
        return NULL;
    }
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

