#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "N.h"
#include "context.h"

void clear_screen();

typedef struct {
    int id;
    const char* name;
    const char* russian_name;
    const char* description;
    int num_operands;
} Operation;

static Operation nat_operations[] = {
    {1, "COM_NN_D", "Сравнение", "2-первое больше, 0-равны, 1-второе больше", 2},
    {2, "NZER_N_B", "Проверка на ноль", "да - не ноль, нет - ноль", 1},
    {3, "ADD_1N_N", "Добавление 1", "Прибавляет единицу к числу", 1},
    {4, "ADD_NN_N", "Сложение", "Сумма двух чисел", 2},
    {5, "SUB_NN_N", "Вычитание", "Разность (первое >= второе)", 2},
    {6, "MUL_ND_N", "Умножение на цифру", "Произведение числа на цифру 0-9", 1},
    {7, "MUL_Nk_N", "Умножение на 10^k", "Сдвиг на k позиций влево", 1},
    {8, "MUL_NN_N", "Умножение", "Произведение двух чисел", 2},
    {9, "SUB_NDN_N", "Вычитание с умножением", "a - b*цифра (результат >= 0)", 2},
    {10, "DIV_NN_N", "Неполное частное", "Целая часть от деления", 2},
    {11, "MOD_NN_N", "Остаток от деления", "Остаток от деления", 2},
    {12, "GCF_NN_N", "НОД", "Наибольший общий делитель", 2},
    {13, "LCM_NN_N", "НОК", "Наименьшее общее кратное", 2},
    {0, NULL, NULL, NULL, 0}
};

void handle_natural_operations(Context* ctx) {
    int running = 1;
    
    while (running) {
        clear_screen();
        printf("╔══════════════════════════════════════════════╗\n");
        printf("║    ОПЕРАЦИИ С НАТУРАЛЬНЫМИ ЧИСЛАМИ           ║\n");
        printf("╚══════════════════════════════════════════════╝\n\n");
        
        // Показываем доступные числа
        printf("ДОСТУПНЫЕ ЧИСЛА:\n");
        if (ctx->has_natural1) {
            printf("  Число 1: %s\n", ctx->natural1);
        } else {
            printf("  Число 1: не введено\n");
        }
        if (ctx->has_natural2) {
            printf("  Число 2: %s\n", ctx->natural2);
        } else {
            printf("  Число 2: не введено\n");
        }
        
        printf("\n┌────────── ДОСТУПНЫЕ ОПЕРАЦИИ ──────────┐\n");
        for (int i = 0; nat_operations[i].id != 0; i++) {
            printf("│ %2d. %-20s %-30s │\n", 
                   nat_operations[i].id,
                   nat_operations[i].russian_name,
                   nat_operations[i].description);
        }
        printf("│  0. Вернуться в главное меню             │\n");
        printf("└──────────────────────────────────────────┘\n");
        
        printf("\nВыберите операцию: ");
        
        int choice;
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        
        if (choice == 0) {
            running = 0;
            continue;
        }
        
        // Ищем операцию
        Operation* op = NULL;
        for (int i = 0; nat_operations[i].id != 0; i++) {
            if (nat_operations[i].id == choice) {
                op = &nat_operations[i];
                break;
            }
        }
        
        if (!op) {
            printf("\nНеверная операция!\n");
            printf("Нажмите Enter...");
            while (getchar() != '\n');
            continue;
        }
        
        // Проверяем наличие операндов
        if (op->num_operands >= 1 && !ctx->has_natural1) {
            printf("\nСначала введите число 1 в главном меню!\n");
            printf("Нажмите Enter...");
            while (getchar() != '\n');
            continue;
        }
        if (op->num_operands >= 2 && !ctx->has_natural2) {
            printf("\nНужны два числа! Введите число 2 в главном меню.\n");
            printf("Нажмите Enter...");
            while (getchar() != '\n');
            continue;
        }
        
        printf("\n═══ %s ═══\n", op->russian_name);
        
        char* result_str = NULL;
        int int_result = 0;
        
        switch (choice) {
            case 1:
                int_result = COM_NN_D(ctx->natural1, ctx->natural2);
                printf("Сравнение %s и %s: %d\n", 
                       ctx->natural1, ctx->natural2, int_result);
                if (int_result == 2) printf("→ Первое больше\n");
                else if (int_result == 0) printf("→ Числа равны\n");
                else printf("→ Второе больше\n");
                break;
                
            case 2:
                printf("%s — это %s\n", ctx->natural1, 
                       NZER_N_B(ctx->natural1));
                break;
                
            case 3:
                result_str = ADD_1N_N(ctx->natural1);
                printf("%s + 1 = %s\n", ctx->natural1, result_str);
                break;
                
            case 4: // ADD_NN_N
                result_str = ADD_NN_N(ctx->natural1, ctx->natural2);
                printf("%s + %s = %s\n", 
                       ctx->natural1, ctx->natural2, result_str);
                break;
                
            case 5:
                if (COM_NN_D(ctx->natural1, ctx->natural2) == 1) {
                    printf("Первое число должно быть >= второго!\n");
                    break;
                }
                result_str = SUB_NN_N(ctx->natural1, ctx->natural2);
                printf("%s - %s = %s\n", 
                       ctx->natural1, ctx->natural2, result_str);
                break;
                
            case 6:
                printf("Введите цифру (0-9): ");
                char digit;
                scanf("%c", &digit);
                while (getchar() != '\n');
                
                if (digit < '0' || digit > '9') {
                    printf("Это не цифра!\n");
                    break;
                }
                result_str = MUL_ND_N(ctx->natural1, digit);
                printf("%s × %c = %s\n", ctx->natural1, digit, result_str);
                break;
                
            case 7:
                printf("Введите степень k: ");
                char k_str[32];
                scanf("%s", k_str);
                while (getchar() != '\n');
                
                result_str = MUL_Nk_N(ctx->natural1, k_str);
                printf("%s × 10^%s = %s\n", 
                       ctx->natural1, k_str, result_str);
                break;
                
            case 8:
                result_str = MUL_NN_N(ctx->natural1, ctx->natural2);
                printf("%s × %s = %s\n", 
                       ctx->natural1, ctx->natural2, result_str);
                break;
                
            case 9:
                printf("Введите цифру (0-9): ");
                scanf("%c", &digit);
                while (getchar() != '\n');
                
                if (digit < '0' || digit > '9') {
                    printf("Это не цифра!\n");
                    break;
                }
                result_str = SUB_NDN_N(ctx->natural1, ctx->natural2, digit);
                if (result_str) {
                    printf("%s - %s×%c = %s\n", 
                           ctx->natural1, ctx->natural2, digit, result_str);
                }
                break;
                
            case 10:
                if (strcmp(ctx->natural2, "0") == 0) {
                    printf("Деление на ноль!\n");
                    break;
                }
                result_str = DIV_NN_N(ctx->natural1, ctx->natural2);
                printf("%s / %s = %s\n", 
                       ctx->natural1, ctx->natural2, result_str);
                break;
                
            case 11:
                if (strcmp(ctx->natural2, "0") == 0) {
                    printf("Деление на ноль!\n");
                    break;
                }
                result_str = MOD_NN_N(ctx->natural1, ctx->natural2);
                printf("%s mod %s = %s\n", 
                       ctx->natural1, ctx->natural2, result_str);
                break;
                
            case 12:
                result_str = GCF_NN_N(ctx->natural1, ctx->natural2);
                printf("НОД(%s, %s) = %s\n", 
                       ctx->natural1, ctx->natural2, result_str);
                break;
                
            case 13:
                result_str = LCM_NN_N(ctx->natural1, ctx->natural2);
                printf("НОК(%s, %s) = %s\n", 
                       ctx->natural1, ctx->natural2, result_str);
                break;
        }
        
        if (result_str) free(result_str);
        
        printf("\nНажмите Enter для продолжения...");
        while (getchar() != '\n');
    }
}