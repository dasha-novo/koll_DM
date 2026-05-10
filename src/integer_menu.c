#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Z.h"
#include "N.h"
#include "context.h"

void clear_screen();

typedef struct {
    int id;
    const char* name;
    const char* russian_name;
    const char* description;
    int num_operands;
} IntOperation;


static IntOperation int_operations[] = {
    {1, "ABS_Z_N", "Модуль числа", "Абсолютная величина (натуральное число)", 1},
    {2, "POZ_Z_D", "Знак числа", "2-положительное, 0-ноль, -1-отрицательное", 1},
    {3, "MUL_ZM_Z", "Смена знака", "Умножение на -1", 1},
    {4, "TRANS_N_Z", "Нат.→Целое", "Преобразование натурального в целое", 1},
    {5, "TRANS_Z_N", "Целое→Нат.", "Преобразование неотрицательного целого в натуральное", 1},
    {6, "ADD_ZZ_Z", "Сложение", "Сумма двух целых чисел", 2},
    {7, "SUB_ZZ_Z", "Вычитание", "Разность двух целых чисел", 2},
    {8, "MUL_ZZ_Z", "Умножение", "Произведение двух целых чисел", 2},
    {9, "DIV_ZZ_Z", "Частное", "Неполное частное от деления", 2},
    {10, "MOD_ZZ_Z", "Остаток", "Остаток от деления", 2},
    {0, NULL, NULL, NULL, 0}
};

void handle_integer_operations(Context* ctx) {
    int running = 1;
    
    while (running) {
        clear_screen();
        printf("╔══════════════════════════════════════════════╗\n");
        printf("║       ОПЕРАЦИИ С ЦЕЛЫМИ ЧИСЛАМИ              ║\n");
        printf("╚══════════════════════════════════════════════╝\n\n");
        
        printf("ДОСТУПНЫЕ ЧИСЛА:\n");
        if (ctx->has_integer1) {
            printf("  Число 1: %s\n", ctx->integer1);
        } else {
            printf("  Число 1: не введено\n");
        }
        if (ctx->has_integer2) {
            printf("  Число 2: %s\n", ctx->integer2);
        } else {
            printf("  Число 2: не введено\n");
        }
        
        printf("\n┌────────── ДОСТУПНЫЕ ОПЕРАЦИИ ──────────┐\n");
        for (int i = 0; int_operations[i].id != 0; i++) {
            printf("│ %2d. %-25s %-20s │\n", 
                   int_operations[i].id,
                   int_operations[i].russian_name,
                   int_operations[i].description);
        }
        printf("│  0. Вернуться в главное меню              │\n");
        printf("└───────────────────────────────────────────┘\n");
        
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
        
        IntOperation* op = NULL;
        for (int i = 0; int_operations[i].id != 0; i++) {
            if (int_operations[i].id == choice) {
                op = &int_operations[i];
                break;
            }
        }
        
        if (!op) {
            printf("\nНеверная операция!\n");
            printf("Нажмите Enter...");
            while (getchar() != '\n');
            continue;
        }
        
        if (op->num_operands >= 1 && !ctx->has_integer1) {
            printf("\nСначала введите целое число 1 в главном меню!\n");
            printf("Нажмите Enter...");
            while (getchar() != '\n');
            continue;
        }
        if (op->num_operands >= 2 && !ctx->has_integer2) {
            printf("\nНужны два целых числа! Введите число 2 в главном меню.\n");
            printf("Нажмите Enter...");
            while (getchar() != '\n');
            continue;
        }
        
        printf("\n═══ %s ═══\n", op->russian_name);
        
        char* result_str = NULL;
        int int_result = 0;
        
        switch (choice) {
            case 1: // ABS_Z_N
                result_str = ABS_Z_N(ctx->integer1);
                printf("|%s| = %s\n", ctx->integer1, result_str);
                break;
                
            case 2: // POZ_Z_D
                int_result = POZ_Z_D(ctx->integer1);
                printf("Знак числа %s: ", ctx->integer1);
                if (int_result == 1) printf("положительное\n");
                else if (int_result == 0) printf("ноль\n");
                else printf("отрицательное\n");
                printf("(код: %d)\n", int_result);
                break;
                
            case 3: // MUL_ZM_Z
                result_str = MUL_ZM_Z(ctx->integer1);
                printf("-(%s) = %s\n", ctx->integer1, result_str);
                break;
                
            case 4: // TRANS_N_Z
                if (!ctx->has_natural1) {
                    printf("Нужно натуральное число! Введите его в главном меню.\n");
                    break;
                }
                result_str = ctx->natural1;
                printf("Натуральное %s как целое: %s\n", ctx->natural1, result_str);
                result_str = NULL;
                break;
                
            case 5: // TRANS_Z_N
                if (ctx->integer1[0] == '-') {
                    printf("Нельзя преобразовать отрицательное число в натуральное!\n");
                    break;
                }
                result_str = TRANS_Z_N(ctx->integer1);
                if (result_str) {
                    printf("Целое %s как натуральное: %s\n", ctx->integer1, result_str);
                } else {
                    printf("Ошибка преобразования!\n");
                }
                break;
                
            case 6: // ADD_ZZ_Z
                result_str = ADD_ZZ_Z(ctx->integer1, ctx->integer2);
                printf("%s + %s = %s\n", 
                       ctx->integer1, ctx->integer2, result_str);
                break;
                
            case 7: // SUB_ZZ_Z
                result_str = SUB_ZZ_Z(ctx->integer1, ctx->integer2);
                printf("%s - %s = %s\n", 
                       ctx->integer1, ctx->integer2, result_str);
                break;
                
            case 8: // MUL_ZZ_Z
                result_str = MUL_ZZ_Z(ctx->integer1, ctx->integer2);
                printf("%s × %s = %s\n", 
                       ctx->integer1, ctx->integer2, result_str);
                break;
                
            case 9: // DIV_ZZ_Z
                if (strcmp(ctx->integer2, "0") == 0 || 
                    (ctx->integer2[0] == '-' && ctx->integer2[1] == '0' && ctx->integer2[2] == '\0')) {
                    printf("Деление на ноль!\n");
                    break;
                }
                result_str = DIV_ZZ_Z(ctx->integer1, ctx->integer2);
                if (result_str) {
                    printf("%s / %s = %s\n", 
                           ctx->integer1, ctx->integer2, result_str);
                }
                break;
                
            case 10: // MOD_ZZ_Z
                if (strcmp(ctx->integer2, "0") == 0 ||
                    (ctx->integer2[0] == '-' && ctx->integer2[1] == '0' && ctx->integer2[2] == '\0')) {
                    printf("Деление на ноль!\n");
                    break;
                }
                result_str = MOD_ZZ_Z(ctx->integer1, ctx->integer2);
                if (result_str) {
                    printf("%s mod %s = %s\n", 
                           ctx->integer1, ctx->integer2, result_str);
                }
                break;
        }
        
        if (result_str) free(result_str);
        
        printf("\nНажмите Enter для продолжения...");
        while (getchar() != '\n');
    }
}