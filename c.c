// Для строк - преобразование в верхний регистр
void string_to_upper_map(const void* src, void* dst, ArrayErrors* error) {
    const char* str = (const char*)src;
    if (!str) {
        if (error) *error = NULL_POINTER;
        return;
    }
    
    char* result = (char*)malloc(strlen(str) + 1);
    if (!result) {
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return;
    }
    
    for (size_t i = 0; i <= strlen(str); i++) {
        result[i] = toupper(str[i]);
    }
    
    // Сохраняем указатель на результат в dst
    *(char**)dst = result;
    
    if (error) *error = ARRAY_OK;
}

// Для строк - преобразование в нижний регистр
void string_to_lower_map(const void* src, void* dst, ArrayErrors* error) {
    const char* str = (const char*)src;
    if (!str) {
        if (error) *error = NULL_POINTER;
        return;
    }
    
    char* result = (char*)malloc(strlen(str) + 1);
    if (!result) {
        if (error) *error = MEMORY_ALLOCATION_FAILED;
        return;
    }
    
    for (size_t i = 0; i <= strlen(str); i++) {
        result[i] = tolower(str[i]);
    }
    
    *(char**)dst = result;
    
    if (error) *error = ARRAY_OK;
}

// Для функций - применение к 8
void func_apply_to_8_map(const void* src, void* dst, ArrayErrors* error) {
    IntFunc f = (IntFunc)src;
    if (!f) {
        if (error) *error = NULL_POINTER;
        return;
    }
    
    int result = f(8);
    
    // Сохраняем значение (не указатель) в dst
    *(int*)dst = result;
    
    if (error) *error = ARRAY_OK;
}

// Для функций - применение к аргументу
void func_apply_to_arg_map(const void* src, void* dst, ArrayErrors* error) {
    IntFunc f = (IntFunc)src;
    if (!f) {
        if (error) *error = NULL_POINTER;
        return;
    }
    
    extern int current_arg;
    int result = f(current_arg);
    
    *(int*)dst = result;
    
    if (error) *error = ARRAY_OK;
}