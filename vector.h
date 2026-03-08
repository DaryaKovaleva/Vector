#ifndef VECTOR_H
#define VECTOR_H

#include "types.h"

#define EPS 0.0001f

// Структура вектора
typedef struct Vector {
    FieldInfo* type_info;    // Информация о типе элементов
    void* data;              // Данные вектора
    size_t size;             // Текущий размер
    size_t capacity;         // Вместимость
} Vector;

// Создание нового вектора
Vector* vector_create(FieldInfo* type_info);

// Удаление вектора
void vector_free(Vector* vec);

// Добавление элемента в конец
int vector_push_back(Vector* vec, const void* element);

// Получение элемента по индексу
void* vector_get(const Vector* vec, size_t index);

// Установка элемента по индексу
int vector_set(Vector* vec, size_t index, const void* element);

// Получение размера вектора
size_t vector_size(const Vector* vec);

// Проверка, пуст ли вектор
bool vector_empty(const Vector* vec);

// Вывод вектора
void vector_print(const Vector* vec);

// Векторное сложение: result = a + b
Vector* vector_add(const Vector* a, const Vector* b);

// Скалярное произведение: result = a · b
void* vector_dot(const Vector* a, const Vector* b);

// Проверка совместимости типов
bool vector_types_compatible(const Vector* a, const Vector* b);

// Очистка вектора
void vector_clear(Vector* vec);

#endif