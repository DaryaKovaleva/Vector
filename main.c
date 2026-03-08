#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "vector.h"
#include "tests.h"

void print_menu() {
    printf("\n====================================\n");
    printf("    ПОЛИМОРФНЫЙ ВЕКТОР\n");
    printf("====================================\n");
    printf("1. Создать вектор целых чисел\n");
    printf("2. Создать вектор вещественных чисел\n");
    printf("3. Добавить элемент\n");
    printf("4. Вывести вектор\n");
    printf("5. Векторное сложение\n");
    printf("6. Скалярное произведение\n");
    printf("7. Очистить вектор\n");
    printf("8. Запустить тесты\n");
    printf("0. Выход\n");
    printf("Выберите действие: ");
}

void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Vector* current_vector = NULL;
    Vector* second_vector = NULL;
    int choice;
    int type_choice = 0;

    setlocale (LC_CTYPE, "ru_RU.UTF-8");
    
    while (1) {
        print_menu();
        scanf("%d", &choice);
        clear_input();
        
        switch (choice) {
            case 1: // Создать вектор целых чисел
                if (current_vector != NULL) {
                    vector_free(current_vector);
                }
                current_vector = vector_create(get_int_field_info());
                type_choice = 1;
                printf("Создан пустой вектор целых чисел\n");
                break;
                
            case 2: // Создать вектор вещественных чисел
                if (current_vector != NULL) {
                    vector_free(current_vector);
                }
                current_vector = vector_create(get_float_field_info());
                type_choice = 2;
                printf("Создан пустой вектор вещественных чисел\n");
                break;
                
            case 3: // Добавить элемент
                if (current_vector == NULL) {
                    printf("Сначала создайте вектор!\n");
                    break;
                }
                
                if (type_choice == 1) {
                    int val;
                    printf("Введите целое число: ");
                    scanf("%d", &val);
                    clear_input();
                    if (vector_push_back(current_vector, &val) == 0) {
                        printf("Элемент добавлен\n");
                    } else {
                        printf("Ошибка при добавлении элемента\n");
                    }
                } else if (type_choice == 2) {
                    float val;
                    printf("Введите вещественное число: ");
                    scanf("%f", &val);
                    clear_input();
                    if (vector_push_back(current_vector, &val) == 0) {
                        printf("Элемент добавлен\n");
                    } else {
                        printf("Ошибка при добавлении элемента\n");
                    }
                }
                break;
                
            case 4: // Вывести вектор
                if (current_vector == NULL) {
                    printf("Вектор не создан\n");
                } else {
                    printf("Текущий вектор: ");
                    vector_print(current_vector);
                }
                break;
                
            case 5: // Векторное сложение
                if (current_vector == NULL) {
                    printf("Сначала создайте первый вектор!\n");
                    break;
                }
                
                // Создаем второй вектор того же типа
                if (type_choice == 1) {
                    second_vector = vector_create(get_int_field_info());
                    printf("Введите 5 целых чисел для второго вектора:\n");
                    for (int i = 0; i < 5; i++) {
                        int val;
                        printf("Элемент %d: ", i+1);
                        scanf("%d", &val);
                        clear_input();
                        vector_push_back(second_vector, &val);
                    }
                } else {
                    second_vector = vector_create(get_float_field_info());
                    printf("Введите 5 вещественных чисел для второго вектора:\n");
                    for (int i = 0; i < 5; i++) {
                        float val;
                        printf("Элемент %d: ", i+1);
                        scanf("%f", &val);
                        clear_input();
                        vector_push_back(second_vector, &val);
                    }
                }
                
                printf("Второй вектор: ");
                vector_print(second_vector);
                
                Vector* result = vector_add(current_vector, second_vector);
                if (result != NULL) {
                    printf("Результат сложения: ");
                    vector_print(result);
                    vector_free(result);
                }
                
                vector_free(second_vector);
                break;
                
            case 6: // Скалярное произведение
                if (current_vector == NULL) {
                    printf("Сначала создайте первый вектор!\n");
                    break;
                }
                
                // Создаем второй вектор того же типа
                if (type_choice == 1) {
                    second_vector = vector_create(get_int_field_info());
                    printf("Введите 5 целых чисел для второго вектора:\n");
                    for (int i = 0; i < 5; i++) {
                        int val;
                        printf("Элемент %d: ", i+1);
                        scanf("%d", &val);
                        clear_input();
                        vector_push_back(second_vector, &val);
                    }
                    
                    int* result = (int*)vector_dot(current_vector, second_vector);
                    if (result != NULL) {
                        printf("Скалярное произведение = %d\n", *result);
                        free(result);  
                    }
                } else {
                    second_vector = vector_create(get_float_field_info());
                    printf("Введите 5 вещественных чисел для второго вектора:\n");
                    for (int i = 0; i < 5; i++) {
                        float val;
                        printf("Элемент %d: ", i+1);
                        scanf("%f", &val);
                        clear_input();
                        vector_push_back(second_vector, &val);
                    }
                    
                    float* result = (float*)vector_dot(current_vector, second_vector);
                    if (result != NULL) {
                        printf("Скалярное произведение = %.2f\n", *result);
                        free(result);
                    }
                }
                
                vector_free(second_vector);
                break;
                
            case 7: // Очистить вектор
                if (current_vector != NULL) {
                    vector_clear(current_vector);
                    printf("Вектор очищен\n");
                } else {
                    printf("Вектор не создан\n");
                }
                break;
                
            case 8: // Запустить тесты
                run_all_tests();
                break;
                
            case 0: // Выход
                if (current_vector != NULL) {
                    vector_free(current_vector);
                }
                printf("Программа завершена\n");
                return 0;
                
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
    
    return 0;
}