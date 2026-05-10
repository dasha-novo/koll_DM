#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "P.h"
#include "Q.h"
#include "context.h"

void clear_screen();

typedef struct {
    int id;
    const char* russian_name;
    const char* description;
    int num_operands;
} PolyOperation;

static PolyOperation poly_operations[] = {
    {1, "Сложение", "Сумма двух многочленов", 2},
    {2, "Вычитание", "Разность двух многочленов", 2},
    {3, "Умножение на дробь", "Произведение многочлена на рациональное число", 1},
    {4, "Умножение на x^k", "Сдвиг степеней на k вправо", 1},
    {5, "Старший коэффициент", "Коэффициент при максимальной степени", 1},
    {6, "Степень многочлена", "Максимальная степень с ненулевым коэффициентом", 1},
    {7, "Умножение", "Произведение двух многочленов", 2},
    {8, "Частное", "Неполное частное от деления", 2},
    {9, "Остаток", "Остаток от деления", 2},
    {10, "НОД", "Наибольший общий делитель многочленов", 2},
    {11, "Производная", "Производная многочлена", 1},
    {12, "Кратные корни", "Преобразование — кратные корни в простые", 1},
    {0, NULL, NULL, 0}
};

void handle_polynomial_operations(Context* ctx) {
    int running = 1;
    
    while (running) {
        clear_screen();
        printf("================================================\n");
        printf("         ОПЕРАЦИИ С МНОГОЧЛЕНАМИ\n");
        printf("================================================\n\n");
        
        printf("ДОСТУПНЫЕ МНОГОЧЛЕНЫ:\n");
        if (ctx->has_polynom1) {
            printf("  P1: ");
            print_poly(ctx->polynom1);
            printf("\n");
        } else {
            printf("  P1: не введен\n");
        }
        if (ctx->has_polynom2) {
            printf("  P2: ");
            print_poly(ctx->polynom2);
            printf("\n");
        } else {
            printf("  P2: не введен\n");
        }
        
        printf("\nДОСТУПНЫЕ ОПЕРАЦИИ:\n");
        for (int i = 0; poly_operations[i].id != 0; i++) {
            printf("  %2d. %-25s — %s\n", 
                   poly_operations[i].id,
                   poly_operations[i].russian_name,
                   poly_operations[i].description);
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
        
        PolyOperation* op = NULL;
        for (int i = 0; poly_operations[i].id != 0; i++) {
            if (poly_operations[i].id == choice) {
                op = &poly_operations[i];
                break;
            }
        }
        
        if (!op) {
            printf("\nНеверная операция!\n");
            printf("Нажмите Enter...");
            while (getchar() != '\n');
            continue;
        }
        
        if (op->num_operands >= 1 && !ctx->has_polynom1) {
            printf("\nСначала введите многочлен 1 в главном меню!\n");
            printf("Нажмите Enter...");
            while (getchar() != '\n');
            continue;
        }
        if (op->num_operands >= 2 && !ctx->has_polynom2) {
            printf("\nНужны два многочлена! Введите многочлен 2 в главном меню.\n");
            printf("Нажмите Enter...");
            while (getchar() != '\n');
            continue;
        }
        
        printf("\n=== %s ===\n", op->russian_name);
        
        Polynomial* result_p = NULL;
        Q* result_q = NULL;
        char* result_str = NULL;
        
        switch (choice) {
            case 1: // ADD_PP_P
                result_p = ADD_PP_P(ctx->polynom1, ctx->polynom2);
                if (result_p) {
                    printf("P1 + P2 = ");
                    print_poly(result_p);
                    printf("\n");
                }
                break;
                
            case 2: // SUB_PP_P
                result_p = SUB_PP_P(ctx->polynom1, ctx->polynom2);
                if (result_p) {
                    printf("P1 - P2 = ");
                    print_poly(result_p);
                    printf("\n");
                }
                break;
                
            case 3: // MUL_PQ_P
                if (!ctx->has_rational1) {
                    printf("Нужна дробь! Введите её в главном меню.\n");
                    break;
                }
                result_p = MUL_PQ_P(ctx->polynom1, ctx->rational1);
                if (result_p) {
                    printf("P1 * (%s/%s) = ", 
                           ctx->rational1->numerator,
                           ctx->rational1->denominator);
                    print_poly(result_p);
                    printf("\n");
                }
                break;
                
            case 4: // MUL_Pxk_P
                printf("Введите степень k: ");
                char k_str[32];
                scanf("%s", k_str);
                while (getchar() != '\n');
                result_p = MUL_Pxk_P(ctx->polynom1, k_str);
                if (result_p) {
                    printf("P1 * x^%s = ", k_str);
                    print_poly(result_p);
                    printf("\n");
                }
                break;
                
            case 5: // LED_P_Q
                result_q = LED_P_Q(ctx->polynom1);
                if (result_q) {
                    printf("Старший коэффициент: %s/%s\n", 
                           result_q->numerator, result_q->denominator);
                }
                break;
                
            case 6: // DEG_P_N
                result_str = DEG_P_N(ctx->polynom1);
                if (result_str) {
                    printf("Степень многочлена: %s\n", result_str);
                }
                break;
                
            case 7: // MUL_PP_P
                result_p = MUL_PP_P(ctx->polynom1, ctx->polynom2);
                if (result_p) {
                    printf("P1 * P2 = ");
                    print_poly(result_p);
                    printf("\n");
                }
                break;
                
            case 8: // DIV_PP_P
                if (ctx->polynom2->count == 0) {
                    printf("Деление на нулевой многочлен!\n");
                    break;
                }
                result_p = DIV_PP_P(ctx->polynom1, ctx->polynom2);
                if (result_p) {
                    printf("P1 / P2 = ");
                    print_poly(result_p);
                    printf("\n");
                }
                break;
                
            case 9: // MOD_PP_P
                if (ctx->polynom2->count == 0) {
                    printf("Деление на нулевой многочлен!\n");
                    break;
                }
                result_p = MOD_PP_P(ctx->polynom1, ctx->polynom2);
                if (result_p) {
                    printf("P1 mod P2 = ");
                    print_poly(result_p);
                    printf("\n");
                }
                break;
                
            case 10: // GCF_PP_P
                result_p = GCF_PP_P(ctx->polynom1, ctx->polynom2);
                if (result_p) {
                    printf("НОД(P1, P2) = ");
                    print_poly(result_p);
                    printf("\n");
                }
                break;
                
            case 11: // DER_P_P
                result_p = DER_P_P(ctx->polynom1);
                if (result_p) {
                    printf("P1' = ");
                    print_poly(result_p);
                    printf("\n");
                }
                break;
                
            case 12: // NMR_P_P
                result_p = NMR_P_P(ctx->polynom1);
                if (result_p) {
                    printf("Преобразованный многочлен: ");
                    print_poly(result_p);
                    printf("\n");
                }
                break;
        }
        
        if (result_p) free_poly(result_p);
        if (result_q) free_Q(result_q);
        if (result_str) free(result_str);
        
        printf("\nНажмите Enter для продолжения...");
        while (getchar() != '\n');
    }
}