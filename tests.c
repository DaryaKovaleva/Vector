#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "vector.h"

// ==================== Тесты для вектора целых чисел ====================

void test_int_vector_create(void) {
    printf("Тест создания вектора целых чисел... ");
    
    Vector* v = vector_create(get_int_field_info());
    assert(v != NULL);                      // вектор должен создаться
    assert(vector_size(v) == 0);             // новый вектор пуст
    assert(vector_empty(v));                  // должен быть пустым
    assert(v->type_info == get_int_field_info()); // тип должен совпадать
    
    vector_free(v);
    printf("OK\n");
}

void test_int_vector_push_back_get(void) {
    printf("Тест добавления и получения элементов (int)... ");
    
    Vector* v = vector_create(get_int_field_info());
    int values[] = {10, 20, 30, 40, 50};
    
    // Добавляем элементы и проверяем размер
    for (int i = 0; i < 5; i++) {
        int result = vector_push_back(v, &values[i]);
        assert(result == 0);                 // успешное добавление
        assert((int)vector_size(v) == i + 1);      // размер увеличился
    }
    
    // Проверяем значения
    for (int i = 0; i < 5; i++) {
        int* elem = (int*)vector_get(v, i);
        assert(elem != NULL);                 // указатель не NULL
        assert(*elem == values[i]);            // значение совпадает
    }
    
    // Проверка выхода за границы
    assert(vector_get(v, 5) == NULL);          // индекс >= size → NULL
    assert(vector_get(v, 100) == NULL);        // большой индекс → NULL
    
    vector_free(v);
    printf("OK\n");
}

void test_int_vector_set(void) {
    printf("Тест замены элементов (int)... ");
    
    Vector* v = vector_create(get_int_field_info());
    int values[] = {10, 20, 30};
    
    for (int i = 0; i < 3; i++) {
        vector_push_back(v, &values[i]);
    }
    
    // Замена существующего элемента
    int new_val = 99;
    int result = vector_set(v, 1, &new_val);
    assert(result == 0);                       // успешная замена
    
    int* elem = (int*)vector_get(v, 1);
    assert(*elem == 99);                        // значение изменилось
    
    // Замена с неверным индексом
    result = vector_set(v, 5, &new_val);
    assert(result == -1);                        // должна быть ошибка
    
    // Замена с NULL параметрами
    result = vector_set(NULL, 0, &new_val);
    assert(result == -1);                        // ошибка
    
    result = vector_set(v, 0, NULL);
    assert(result == -1);                        // ошибка
    
    vector_free(v);
    printf("OK\n");
}

void test_int_vector_add(void) {
    printf("Тест векторного сложения (int)... ");
    
    Vector* v1 = vector_create(get_int_field_info());
    Vector* v2 = vector_create(get_int_field_info());
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {5, 4, 3, 2, 1};
    
    for (int i = 0; i < 5; i++) {
        vector_push_back(v1, &a[i]);
        vector_push_back(v2, &b[i]);
    }
    
    Vector* result = vector_add(v1, v2);
    assert(result != NULL);                      // сложение успешно
    
    // Проверка результата: [6, 6, 6, 6, 6]
    for (int i = 0; i < 5; i++) {
        int* val = (int*)vector_get(result, i);
        assert(*val == 6);
    }
    
    vector_free(result);
    vector_free(v1);
    vector_free(v2);
    printf("OK\n");
}

void test_int_vector_add_time(int n, FILE *fout) {
    printf("Время выполнения векторного сложения (int, %d элементов)... ", n);
    clock_t cbegin, cend;
    double time;
    
    Vector* v1 = vector_create(get_int_field_info());
    Vector* v2 = vector_create(get_int_field_info());
    int a;

    for (int i = 0; i < n; i++) {
        a = i%10;
        vector_push_back(v1, &a);
        vector_push_back(v2, &a);
    }
    
    cbegin = clock();
    Vector* result = vector_add(v1, v2);
    cend = clock();
    time = (double)(cend - cbegin)/CLOCKS_PER_SEC;
    printf("%lfсек\n", time);
    fprintf(fout, "%d,%lf\n", n, time);
    
    vector_free(result);
    vector_free(v1);
    vector_free(v2);
    printf("OK\n");
}

void test_int_vector_dot(void) {
    printf("Тест скалярного произведения (int)... ");
    
    Vector* v1 = vector_create(get_int_field_info());
    Vector* v2 = vector_create(get_int_field_info());
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {5, 4, 3, 2, 1};
    
    for (int i = 0; i < 5; i++) {
        vector_push_back(v1, &a[i]);
        vector_push_back(v2, &b[i]);
    }
    
    int* result = (int*)vector_dot(v1, v2);
    assert(result != NULL);
    
    // 1*5 + 2*4 + 3*3 + 4*2 + 5*1 = 5+8+9+8+5 = 35
    assert(*result == 35);
    free(result);                 
    
    vector_free(v1);
    vector_free(v2);
    printf("OK\n");
}

void test_int_vector_clear(void) {
    printf("Тест очистки вектора (int)... ");
    
    Vector* v = vector_create(get_int_field_info());
    int val = 42;
    
    vector_push_back(v, &val);
    vector_push_back(v, &val);
    assert(vector_size(v) == 2);
    
    vector_clear(v);
    assert(vector_size(v) == 0);                  // размер стал 0
    assert(vector_empty(v));                        // вектор пуст
    
    // После очистки можно снова добавлять
    vector_push_back(v, &val);
    assert(vector_size(v) == 1);
    
    vector_free(v);
    printf("OK\n");
}

// ==================== Тесты для вектора вещественных чисел ====================

void test_float_vector_create(void) {
    printf("Тест создания вектора вещественных чисел... ");
    
    Vector* v = vector_create(get_float_field_info());
    assert(v != NULL);
    assert(vector_size(v) == 0);
    assert(vector_empty(v));
    assert(v->type_info == get_float_field_info());
    
    vector_free(v);
    printf("OK\n");
}

void test_float_vector_push_back_get(void) {
    printf("Тест добавления и получения элементов (float)... ");
    
    Vector* v = vector_create(get_float_field_info());
    float values[] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    
    for (int i = 0; i < 5; i++) {
        int result = vector_push_back(v, &values[i]);
        assert(result == 0);
        assert((int)vector_size(v) == i + 1);
    }
    
    for (int i = 0; i < 5; i++) {
        float* elem = (float*)vector_get(v, i);
        assert(elem != NULL);
        // Сравнение float с учётом погрешности
        assert(fabs(*elem - values[i]) < EPS);
    }
    
    vector_free(v);
    printf("OK\n");
}

void test_float_vector_add(void) {
    printf("Тест векторного сложения (float)... ");
    
    Vector* v1 = vector_create(get_float_field_info());
    Vector* v2 = vector_create(get_float_field_info());
    float a[] = {1.1f, 2.2f, 3.3f};
    float b[] = {3.3f, 2.2f, 1.1f};
    
    for (int i = 0; i < 3; i++) {
        vector_push_back(v1, &a[i]);
        vector_push_back(v2, &b[i]);
    }
    
    Vector* result = vector_add(v1, v2);
    assert(result != NULL);
    
    // Проверка: [4.4, 4.4, 4.4]
    for (int i = 0; i < 3; i++) {
        float* val = (float*)vector_get(result, i);
        assert(fabs(*val - 4.4f) < EPS);
    }
    
    vector_free(result);
    vector_free(v1);
    vector_free(v2);
    printf("OK\n");
}

void test_float_vector_dot(void) {
    printf("Тест скалярного произведения (float)... ");
    
    Vector* v1 = vector_create(get_float_field_info());
    Vector* v2 = vector_create(get_float_field_info());
    float a[] = {1.0f, 2.0f, 3.0f};
    float b[] = {4.0f, 5.0f, 6.0f};
    
    for (int i = 0; i < 3; i++) {
        vector_push_back(v1, &a[i]);
        vector_push_back(v2, &b[i]);
    }
    
    float* result = (float*)vector_dot(v1, v2);
    assert(result != NULL);
    // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    assert(fabs(*result - 32.0f) < EPS);
    free(result);
    
    vector_free(v1);
    vector_free(v2);
    printf("OK\n");
}

// ==================== Тесты на ошибки и граничные случаи ====================

void test_error_cases(void) {
    printf("Тест обработки ошибок...\n");
    
    // Тест 1: операции с NULL
    printf("  Проверка операций с NULL... ");
    assert(vector_push_back(NULL, NULL) == -1);
    assert(vector_get(NULL, 0) == NULL);
    assert(vector_set(NULL, 0, NULL) == -1);
    assert(vector_size(NULL) == 0);
    assert(vector_empty(NULL) == true);
    assert(vector_add(NULL, NULL) == NULL);
    assert(vector_dot(NULL, NULL) == NULL);
    // vector_free(NULL) не должна падать (проверяем визуально, если упадёт - тест не пройдёт)
    vector_free(NULL);
    printf("OK\n");
    
    // Тест 2: создание вектора с NULL type_info
    printf("  Проверка vector_create(NULL)... ");
    assert(vector_create(NULL) == NULL);
    printf("OK\n");
    
    // Тест 3: несовместимые типы
    printf("  Проверка несовместимых типов... ");
    Vector* v_int = vector_create(get_int_field_info());
    Vector* v_float = vector_create(get_float_field_info());
    int x = 42;
    float y = 3.14f;
    vector_push_back(v_int, &x);
    vector_push_back(v_float, &y);
    
    assert(vector_add(v_int, v_float) == NULL);   // сложение разных типов
    assert(vector_dot(v_int, v_float) == NULL); // скалярное разных типов
    
    vector_free(v_int);
    vector_free(v_float);
    printf("OK\n");
    
    // Тест 4: разные размеры
    printf("  Проверка разных размеров... ");
    Vector* v1 = vector_create(get_int_field_info());
    Vector* v2 = vector_create(get_int_field_info());
    int val1 = 1, val2 = 2;
    vector_push_back(v1, &val1);
    vector_push_back(v1, &val2);
    vector_push_back(v2, &val1);
    
    assert(vector_add(v1, v2) == NULL);    // размеры 2 и 1
    assert(vector_dot(v1, v2) == NULL); // размеры 2 и 1
    
    vector_free(v1);
    vector_free(v2);
    printf("OK\n");
    
    // Тест 5: пустые векторы
    printf("  Проверка пустых векторов... ");
    Vector* v_empty = vector_create(get_int_field_info());
    
    assert(vector_dot(v_empty, v_empty) == NULL); // скалярное пустых
    
    vector_free(v_empty);
    printf("OK\n");
}

// ==================== Запуск всех тестов ====================

void run_all_tests(void) {
    printf("\n========================================\n");
    printf("    ЗАПУСК МОДУЛЬНЫХ ТЕСТОВ\n");
    printf("========================================\n\n");
    
    // Тесты для целых чисел
    printf("--- Тесты для целых чисел ---\n");
    test_int_vector_create();
    test_int_vector_push_back_get();
    test_int_vector_set();
    test_int_vector_add();
    test_int_vector_dot();
    test_int_vector_clear();
    
    printf("\n--- Тесты для вещественных чисел ---\n");
    test_float_vector_create();
    test_float_vector_push_back_get();
    test_float_vector_add();
    test_float_vector_dot();
    
    printf("\n--- Тесты граничных случаев ---\n");
    test_error_cases();

    printf("\n--- Тесты времени ---\n");
    FILE *fout;
    if (!(fout = fopen("time_test.csv","w"))){
        printf("Ошибка открытия файла для теста времени\n");
    }
    else{
        for (int i = 10000; i <= 1000000; i+=10000){
            test_int_vector_add_time(i, fout);
        }
        fclose(fout);
    }
    
    printf("\n========================================\n");
    printf("    ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!\n");
    printf("========================================\n\n");
}