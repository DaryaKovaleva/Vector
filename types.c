#include <stdio.h>
#include "types.h"

//Целые числа:

static FieldInfo* int_field_info = NULL;

FieldInfo* get_int_field_info(void) {
    if (int_field_info == NULL) { //Проверка нужно ли создавать новый объект
        int_field_info = (FieldInfo*)malloc(sizeof(FieldInfo)); //Память размером со структуру
        int_field_info->element_size = sizeof(int);
        int_field_info->copy = int_copy;
        int_field_info->free = NULL;  
        int_field_info->print = int_print;
        int_field_info->compare = int_compare;
        int_field_info->add = int_add;
        int_field_info->multiply = int_multiply;
    }
    return int_field_info;
}

void* int_copy(void* dest, const void* src) {
    if (dest == NULL || src == NULL) return NULL;
    *(int*)dest = *(const int*)src;
    return dest;
}

void int_print(const void* elem) {
    if (elem == NULL) return;
    printf("%d", *(const int*)elem);
}

int int_compare(const void* a, const void* b) {
    if (a == NULL || b == NULL) return 0;
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

void* int_add(void* result, const void* a, const void* b) {
    if (result == NULL || a == NULL || b == NULL) return NULL;
    *(int*)result = *(const int*)a + *(const int*)b;
    return result;
}

void* int_multiply(void* result, const void* a, const void* b) {
    if (result == NULL || a == NULL || b == NULL) return NULL;
    *(int*)result = *(const int*)a * *(const int*)b;
    return result;
}

//Вещественные числа:

static FieldInfo* float_field_info = NULL;

FieldInfo* get_float_field_info(void) {
    if (float_field_info == NULL) {
        float_field_info = (FieldInfo*)malloc(sizeof(FieldInfo));
        float_field_info->element_size = sizeof(float);
        float_field_info->copy = float_copy;
        float_field_info->free = NULL;  
        float_field_info->print = float_print;
        float_field_info->compare = float_compare;
        float_field_info->add = float_add;
        float_field_info->multiply = float_multiply;
    }
    return float_field_info;
}

void* float_copy(void* dest, const void* src) {
    if (dest == NULL || src == NULL) return NULL;
    *(float*)dest = *(const float*)src;
    return dest;
}

void float_print(const void* elem) {
    if (elem == NULL) return;
    printf("%.2f", *(const float*)elem);
}

int float_compare(const void* a, const void* b) {
    if (a == NULL || b == NULL) return 0;
    float fa = *(const float*)a;
    float fb = *(const float*)b;
    if (fa < fb - 0.00001) return -1;
    if (fa > fb + 0.00001) return 1;
    return 0;
}

void* float_add(void* result, const void* a, const void* b) {
    if (result == NULL || a == NULL || b == NULL) return NULL;
    *(float*)result = *(const float*)a + *(const float*)b;
    return result;
}

void* float_multiply(void* result, const void* a, const void* b) {
    if (result == NULL || a == NULL || b == NULL) return NULL;
    *(float*)result = *(const float*)a * *(const float*)b;
    return result;
}