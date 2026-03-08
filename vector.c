#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// Начальная вместимость
#define INITIAL_CAPACITY 4

Vector* vector_create(FieldInfo* type_info) {
    if (type_info == NULL) return NULL;
    
    Vector* vec = (Vector*)malloc(sizeof(Vector));
    if (vec == NULL) return NULL;
      
    vec->type_info = type_info;
    vec->size = 0;
    vec->capacity = INITIAL_CAPACITY;
    
    vec->data = malloc(type_info->element_size * vec->capacity);
    if (vec->data == NULL) {
        free(vec);
        return NULL;
    }
    
    return vec;
}

void vector_free(Vector* vec) {
    if (vec == NULL) return;
    
    // Освобождаем элементы, если нужно
    if (vec->type_info->free != NULL) {
        for (size_t i = 0; i < vec->size; i++) {
            void* elem = (char*)vec->data + i * vec->type_info->element_size;
            vec->type_info->free(elem);
        }
    }
    
    free(vec->data);
    free(vec);
}

int vector_push_back(Vector* vec, const void* element) {
    if (vec == NULL || element == NULL) return -1;
    
    // Проверяем, нужно ли расширять массив
    if (vec->size >= vec->capacity) {
        size_t new_capacity = vec->capacity * 2;
        void* new_data = realloc(vec->data, 
                                 vec->type_info->element_size * new_capacity);
        if (new_data == NULL) return -1;
        
        vec->data = new_data;
        vec->capacity = new_capacity;
    }
    
    // Копируем элемент
    void* dest = (char*)vec->data + vec->size * vec->type_info->element_size;
    vec->type_info->copy(dest, element);
    
    vec->size++;
    return 0;
}

void* vector_get(const Vector* vec, size_t index) {
    if (vec == NULL || index >= vec->size) return NULL;
    
    return (char*)vec->data + index * vec->type_info->element_size;
}

int vector_set(Vector* vec, size_t index, const void* element) {
    if (vec == NULL || element == NULL || index >= vec->size) return -1;
    
    void* dest = (char*)vec->data + index * vec->type_info->element_size;
    
    // Освобождаем старый элемент, если нужно
    if (vec->type_info->free != NULL) {
        vec->type_info->free(dest);
    }
    
    vec->type_info->copy(dest, element);
    return 0;
}

size_t vector_size(const Vector* vec) {
    return vec == NULL ? 0 : vec->size;
}

bool vector_empty(const Vector* vec) {
    return vec == NULL || vec->size == 0;
}

void vector_print(const Vector* vec) {
    if (vec == NULL) {
        printf("NULL\n");
        return;
    }
    
    printf("[");
    for (size_t i = 0; i < vec->size; i++) {
        void* elem = (char*)vec->data + i * vec->type_info->element_size;
        vec->type_info->print(elem);
        if (i < vec->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

bool vector_types_compatible(const Vector* a, const Vector* b) {
    if (a == NULL || b == NULL) return false;
    
    // Проверяем, что это один и тот же тип (сравниваем указатели на FieldInfo)
    return a->type_info == b->type_info;
}

Vector* vector_add(const Vector* a, const Vector* b) {
    // Проверка на NULL
    if (a == NULL || b == NULL) {
        printf("Ошибка: NULL вектор\n");
        return NULL;
    }
    
    // Проверка совместимости типов
    if (!vector_types_compatible(a, b)) {
        printf("Ошибка: векторы разных типов\n");
        return NULL;
    }
    
    // Проверка размеров
    if (a->size != b->size) {
        printf("Ошибка: векторы разного размера\n");
        return NULL;
    }
    
    // Создаем новый вектор
    Vector* result = vector_create(a->type_info);
    if (result == NULL) return NULL;
    
    // Временный буфер для результата сложения
    char* temp = (char*)malloc(a->type_info->element_size);

    // Складываем поэлементно
    for (size_t i = 0; i < a->size; i++) {
        void* elem_a = (char*)a->data + i * a->type_info->element_size;
        void* elem_b = (char*)b->data + i * b->type_info->element_size;
        
        a->type_info->add(temp, elem_a, elem_b);
        
        if (vector_push_back(result, temp) != 0) {
            vector_free(result);
            return NULL;
        }
    }
    
    free(temp);
    return result;
}

void* vector_dot(const Vector* a, const Vector* b) {
    // Проверка на NULL
    if (a == NULL || b == NULL) {
        printf("Ошибка: NULL аргумент\n");
        return NULL;
    }
    
    // Проверка совместимости типов
    if (!vector_types_compatible(a, b)) {
        printf("Ошибка: векторы разных типов\n");
        return NULL;
    }
    
    // Проверка размеров
    if (a->size != b->size) {
        printf("Ошибка: векторы разного размера\n");
        return NULL;
    }
    
    if (a->size == 0) {
        printf("Ошибка: пустые векторы\n");
        return NULL;
    }
    
    void* result = malloc(a->type_info->element_size);// выделение памяти под результат
    if (result == NULL) return NULL;
    // Вычисляем скалярное произведение
    // Начинаем с первого произведения
    void* elem_a = (char*)a->data;
    void* elem_b = (char*)b->data;
    
    char* temp = (char*)malloc(a->type_info->element_size);
    a->type_info->multiply(temp, elem_a, elem_b);
    a->type_info->copy(result, temp);
    
    // Добавляем остальные произведения
    for (size_t i = 1; i < a->size; i++) {
        elem_a = (char*)a->data + i * a->type_info->element_size;
        elem_b = (char*)b->data + i * b->type_info->element_size;
        
        a->type_info->multiply(temp, elem_a, elem_b);
        a->type_info->add(result, result, temp);
    }
    
    return result;
}

void vector_clear(Vector* vec) {
    if (vec == NULL) return;
    
    // Освобождаем элементы, если нужно
    if (vec->type_info->free != NULL) {
        for (size_t i = 0; i < vec->size; i++) {
            void* elem = (char*)vec->data + i * vec->type_info->element_size;
            vec->type_info->free(elem);
        }
    }
    
    vec->size = 0;
}