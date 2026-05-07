#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Q.h"
#include "Z.h"
#include "context.h"

void clear_screen();

typedef struct {
    int id;
    const char* russian_name;
    const char* description;
    int num_operands;
} RatOperation;

static RatOperation rat_operations[] = {
    {1, "Сокращение дроби", "Приведение дроби к несократимому виду", 1},
    {2, "Проверка на целое", "Является ли дробь целым числом", 1},
    {3, "Целое в дробное", "Преобразование целого числа в дробь", 1},
    {4, "Дробное в целое", "Преобразование дроби в целое (если возможно)", 1},
    {5, "Сложение", "Сумма двух дробей", 2},
    {6, "Вычитание", "Разность двух дробей", 2},
    {7, "Умножение", "Произведение двух дробей", 2},
    {8, "Деление", "Частное двух дробей", 2},
    {0, NULL, NULL, 0}
};

void handle_rational_operations(Context* ctx) {
    int running = 1;
    
    while (running) {
        clear_screen();
        printf("================================================\n");
        printf("       ОПЕРАЦИИ С РАЦИОНАЛЬНЫМИ ЧИСЛАМИ\n");
        printf("================================================\n\n");
        
        printf("ДОСТУПНЫЕ ЧИСЛА:\n");
        if (ctx->has_rational1) {
            printf("  Дробь 1: %s/%s\n", 
                   ctx->rational1->numerator, 
                   ctx->rational1->denominator);
        } else {
            printf("  Дробь 1: не введена\n");
        }
        if (ctx->has_rational2) {
            printf("  Дробь 2: %s/%s\n", 
                   ctx->rational2->numerator, 
                   ctx->rational2->denominator);
        } else {
            printf("  Дробь 2: не введена\n");
        }
        
        printf("\nДОСТУПНЫЕ ОПЕРАЦИИ:\n");
        for (int i = 0; rat_operations[i].id != 0; i++) {
            printf("  %2d. %-25s — %s\n", 
                   rat_operations[i].id,
                   rat_operations[i].russian_name,
                   rat_operations[i].description);
        }
        printf("   0. Вернуться в главное меню\n");
        
        printf("\nВаш выбор: ");
        
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
        
        RatOperation* op = NULL;
        for (int i = 0; rat_operations[i].id != 0; i++) {
            if (rat_operations[i].id == choice) {
                op = &rat_operations[i];
                break;
            }
        }
        
        if (!op) {
            printf("\nНеверная операция!\n");
            printf("Нажмите Enter...");
            while (getchar() != '\n');
            continue;
        }
        
        if (op->num_operands >= 1 && !ctx->has_rational1) {
            printf("\nСначала введите дробь 1 в главном меню!\n");
            printf("Нажмите Enter...");
            while (getchar() != '\n');
            continue;
        }
        if (op->num_operands >= 2 && !ctx->has_rational2) {
            printf("\nНужны две дроби! Введите дробь 2 в главном меню.\n");
            printf("Нажмите Enter...");
            while (getchar() != '\n');
            continue;
        }
        
        printf("\n=== %s ===\n", op->russian_name);
        
        Q* result_q = NULL;
        char* result_str = NULL;
        
        switch (choice) {
            case 1: // RED_Q_Q
                result_q = RED_Q_Q(ctx->rational1);
                if (result_q) {
                    printf("%s/%s -> %s/%s\n", 
                           ctx->rational1->numerator,
                           ctx->rational1->denominator,
                           result_q->numerator,
                           result_q->denominator);
                }
                break;
                
            case 2: // INT_Q_B
                result_str = INT_Q_B(ctx->rational1);
                printf("Дробь %s/%s — %s\n", 
                       ctx->rational1->numerator,
                       ctx->rational1->denominator,
                       result_str);
                break;
                
            case 3: // TRANS_Z_Q
                if (!ctx->has_integer1) {
                    printf("Нужно целое число! Введите его в главном меню.\n");
                    break;
                }
                result_q = TRANS_Z_Q(ctx->integer1);
                if (result_q) {
                    printf("Целое %s как дробь: %s/%s\n", 
                           ctx->integer1,
                           result_q->numerator,
                           result_q->denominator);
                }
                break;
                
            case 4: // TRANS_Q_Z
                result_str = TRANS_Q_Z(ctx->rational1);
                if (result_str) {
                    printf("Дробь %s/%s как целое: %s\n", 
                           ctx->rational1->numerator,
                           ctx->rational1->denominator,
                           result_str);
                } else {
                    printf("Нельзя преобразовать в целое (знаменатель не равен 1)\n");
                }
                break;
                
            case 5: // ADD_QQ_Q
                result_q = ADD_QQ_Q(ctx->rational1, ctx->rational2);
                if (result_q) {
                    printf("%s/%s + %s/%s = %s/%s\n", 
                           ctx->rational1->numerator, ctx->rational1->denominator,
                           ctx->rational2->numerator, ctx->rational2->denominator,
                           result_q->numerator, result_q->denominator);
                }
                break;
                
            case 6: // SUB_QQ_Q
                result_q = SUB_QQ_Q(ctx->rational1, ctx->rational2);
                if (result_q) {
                    printf("%s/%s - %s/%s = %s/%s\n", 
                           ctx->rational1->numerator, ctx->rational1->denominator,
                           ctx->rational2->numerator, ctx->rational2->denominator,
                           result_q->numerator, result_q->denominator);
                }
                break;
                
            case 7: // MUL_QQ_Q
                result_q = MUL_QQ_Q(ctx->rational1, ctx->rational2);
                if (result_q) {
                    printf("%s/%s * %s/%s = %s/%s\n", 
                           ctx->rational1->numerator, ctx->rational1->denominator,
                           ctx->rational2->numerator, ctx->rational2->denominator,
                           result_q->numerator, result_q->denominator);
                }
                break;
                
            case 8: // DIV_QQ_Q
                if (ctx->rational2->numerator[0] == '0' && 
                    ctx->rational2->numerator[1] == '\0') {
                    printf("Деление на ноль!\n");
                    break;
                }
                result_q = DIV_QQ_Q(ctx->rational1, ctx->rational2);
                if (result_q) {
                    printf("(%s/%s) / (%s/%s) = %s/%s\n", 
                           ctx->rational1->numerator, ctx->rational1->denominator,
                           ctx->rational2->numerator, ctx->rational2->denominator,
                           result_q->numerator, result_q->denominator);
                }
                break;
        }
        
        if (result_q) free_Q(result_q);
        if (result_str && choice != 2) free(result_str);
        
        printf("\nНажмите Enter для продолжения...");
        while (getchar() != '\n');
    }
}