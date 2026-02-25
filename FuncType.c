#include "FuncType.h"

static TypeInfo* FUNC_TYPE_INFO = NULL;

typedef int (*IntFunc)(int);

static TypeInfo* FUNC_TYPE_INFO = NULL;

int inc(int x) {
    return x + 1;
}

int dec(int x) {
    return x - 1;
}

int square(int x) {
    return x * x;
}

const IntFunc AVAILABLE_FUNCTIONS[] = {inc, dec, square};
const char* FUNCTION_NAMES[] = {"inc (+1)", "dec (-1)", "square (x*x)"};
const int FUNCTION_COUNT = 3;

static void* func_clone(const void* elem, ArrayErrors* error){
    if (elem == NULL){
        if (error)*error = NULL_POINTER;
        return NULL;
    }
    if (error)*error = ARRAY_OK;
    return (void*)elem;
}

static void func_free(void* elem, ArrayErrors* error) {
    if (error) *error = ARRAY_OK;
}

static void func_print(const void* elem, ArrayErrors* error) {
    if (elem == NULL) {
        if (error) *error = NULL_POINTER;
        return;
    }
    IntFunc f = (IntFunc)elem;
    unsigned int found = 0;
    
    for (int i = 0; i < FUNCTION_COUNT; i++) {
        if (AVAILABLE_FUNCTIONS[i] == f) {
            printf("%s", FUNCTION_NAMES[i]);
            found = 1;
            break;
        }
    }
    if (found == 0) {
        printf("%p", f);
    }
    
    if (error) *error = ARRAY_OK;
}

void* func_apply_to_5(const void* elem, void* context, ArrayErrors* error) {
    if (elem == NULL) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    
    IntFunc f = (IntFunc)elem;
    int* result = malloc(sizeof(int));
    if (!result) {
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }
    
    *result = f(5); // Применяем функцию к 5
    // Здесь нужен TypeInfo для int, но пока сделаем так
    
    if (error) *error = ARRAY_OK;
    return result;
}

// Предикат для where: отбирает функции, которые возвращают > 10 при x=5
int func_greater_than_10(const void* elem, void* context, ArrayErrors* error) {
    if (elem == NULL) {
        if (error) *error = NULL_POINTER;
        return 0;
    }
    
    IntFunc f = (IntFunc)elem;
    int result = f(5);
    
    if (error) *error = ARRAY_OK;
    return result > 10;
}

// Бинарная операция для reduce: композиция функций
void* func_compose(const void* a, const void* b, void* context, ArrayErrors* error) {
    if (!a || !b) {
        if (error) *error = NULL_POINTER;
        return NULL;
    }
    
    // Это упрощенная реализация - в реальности нужно создавать новую функцию
    // Но для демо вернем указатель на b
    if (error) *error = ARRAY_OK;
    return (void*)b;
}

TypeInfo* GetFuncTypeInfo() {
    if (FUNC_TYPE_INFO == NULL) {
        FUNC_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        FUNC_TYPE_INFO->kind = TYPE_FUNC;
        FUNC_TYPE_INFO->clone = func_clone;
        FUNC_TYPE_INFO->free = func_free;
        FUNC_TYPE_INFO->print = func_print;
    }
    return FUNC_TYPE_INFO;
}


void FreeFuncTypeInfo() {
    if (FUNC_TYPE_INFO != NULL) {
        free(FUNC_TYPE_INFO);
        FUNC_TYPE_INFO = NULL;
    }
}