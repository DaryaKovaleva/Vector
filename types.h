#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <stdbool.h>

// Структура для описания типа данных
typedef struct FieldInfo {
    size_t element_size;           // Размер элемента
    void* (*copy)(void* dest, const void* src);  // Копирование элемента
    void (*free)(void* elem);       // Освобождение элемента (если нужно)
    void (*print)(const void* elem); // Вывод элемента
    int (*compare)(const void* a, const void* b); // Сравнение элементов
    void* (*add)(void* result, const void* a, const void* b); // Сложение
    void* (*multiply)(void* result, const void* a, const void* b); // Умножение
} FieldInfo;

// Получение описателя для целых чисел
FieldInfo* get_int_field_info(void);

// Получение описателя для вещественных чисел
FieldInfo* get_float_field_info(void);

// Функции для работы с целыми числами
void* int_copy(void* dest, const void* src);
void int_print(const void* elem);
int int_compare(const void* a, const void* b);
void* int_add(void* result, const void* a, const void* b);
void* int_multiply(void* result, const void* a, const void* b);

// Функции для работы с вещественными числами
void* float_copy(void* dest, const void* src);
void float_print(const void* elem);
int float_compare(const void* a, const void* b);
void* float_add(void* result, const void* a, const void* b);
void* float_multiply(void* result, const void* a, const void* b);

#endif