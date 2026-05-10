#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "rational_menu.h"
#include "polynomial_menu.h"
#include "context.h"
#include "natural_menu.h"
#include "integer_menu.h"
#include "readDigitN.h"
#include "readDigZ.h"
#include "readDigitQ.h"
#include "readPoly.h"

void clear_screen() {
    printf("\033[2J\033[H");
}

void print_welcome() {
    printf("\n");
    printf("================================================\n");
    printf("   СИСТЕМА КОМПЬЮТЕРНОЙ АЛГЕБРЫ\n");
    printf("   для длинных чисел\n");
    printf("================================================\n");
    printf("\n");
}

void print_help() {
    printf("\n");
    printf("------------------ СПРАВКА ------------------\n");
    printf("\n");
    printf("1. Введите нужные числа в главном меню\n");
    printf("   (они сохраняются в памяти)\n");
    printf("2. Выберите раздел операций\n");
    printf("3. Выберите нужную операцию\n");
    printf("4. Повторяйте, пока не надоест\n");
    printf("\n");
    printf("ПОДСКАЗКА: Сначала введите числа,\n");
    printf("потом переходите к операциям.\n");
    printf("\n");
    printf("----------------------------------------------\n");
}

void print_main_menu(Context* ctx) {
    printf("\n");
    printf("---------------- ГЛАВНОЕ МЕНЮ ----------------\n");
    printf("\n");
    printf("  ВВОД ЧИСЕЛ:\n");
    printf("  1. Ввести натуральное число\n");
    printf("  2. Ввести целое число\n");
    printf("  3. Ввести рациональное число (дробь)\n");
    printf("  4. Ввести многочлен\n");
    printf("\n");
    printf("  СОСТОЯНИЕ ПАМЯТИ:\n");
    print_context_status(ctx);
    printf("\n");
    printf("  ОПЕРАЦИИ:\n");
    printf("  5. Операции с натуральными числами\n");
    printf("  6. Операции с целыми числами\n");
    printf("  7. Операции с рациональными числами\n");
    printf("  8. Операции с многочленами\n");
    printf("\n");
    printf("  ОЧИСТКА ПАМЯТИ:\n");
    printf("  10. Очистить натуральные числа\n");
    printf("  11. Очистить целые числа\n");
    printf("  12. Очистить рациональные числа\n");
    printf("  13. Очистить многочлены\n");
    printf("  14. Очистить ВСЁ\n");
    printf("\n");
    printf("  9. Справка\n");
    printf("  0. Выход\n");
    printf("\n");
    printf("----------------------------------------------\n");
    printf("Ваш выбор: ");
}

int main() {
    Context* ctx = create_context();
    if (!ctx) {
        printf("Ошибка создания контекста!\n");
        return 1;
    }
    
    clear_screen();
    print_welcome();
    
    int running = 1;
    while (running) {
        print_main_menu(ctx);
        
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("\nОшибка ввода! Введите число от 0 до 9.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        
        printf("\n");
        
        switch (choice) {
            case 1: {
                printf("------- ВВОД НАТУРАЛЬНОГО ЧИСЛА -------\n");
                printf("Формат: последовательность цифр без пробелов\n");
                printf("Пример: 12345678901234567890\n");
                printf("----------------------------------------\n");
                printf("Введите число: ");
                
                char* num = read_digN();
                if (num) {
                    if (!ctx->has_natural1) {
                        ctx->natural1 = num;
                        ctx->has_natural1 = 1;
                        printf("Число сохранено как ПЕРВОЕ натуральное\n");
                    } else if (!ctx->has_natural2) {
                        ctx->natural2 = num;
                        ctx->has_natural2 = 1;
                        printf("Число сохранено как ВТОРОЕ натуральное\n");
                    } else {
                        printf("Память заполнена! Выполните операцию или очистите память.\n");
                        printf("Число НЕ сохранено.\n");
                        free(num);
                    }
                }
                printf("\nНажмите Enter для продолжения...");
                while (getchar() != '\n');
                break;
            }
                
            case 2: {
                printf("---------- ВВОД ЦЕЛОГО ЧИСЛА ----------\n");
                printf("Формат: [-]цифры (минус опционально)\n");
                printf("Пример: -1234567890 или 9876543210\n");
                printf("----------------------------------------\n");
                printf("Введите число: ");
                
                char* num = read_digZ();
                if (num) {
                    if (!ctx->has_integer1) {
                        ctx->integer1 = num;
                        ctx->has_integer1 = 1;
                        printf("Число сохранено как ПЕРВОЕ целое\n");
                    } else if (!ctx->has_integer2) {
                        ctx->integer2 = num;
                        ctx->has_integer2 = 1;
                        printf("Число сохранено как ВТОРОЕ целое\n");
                    } else {
                        printf("Память заполнена!\n");
                        free(num);
                    }
                }
                printf("\nНажмите Enter для продолжения...");
                while (getchar() != '\n');
                break;
            }
                
            case 3: {
                printf("------- ВВОД РАЦИОНАЛЬНОГО ЧИСЛА ------\n");
                printf("Формат: [-]числитель/знаменатель\n");
                printf("Пример: -3/4 или 5/6 или -123/456\n");
                printf("Знаменатель не может быть нулем!\n");
                printf("----------------------------------------\n");
                printf("Введите дробь: ");
                
                Q* q = read_digQ();
                if (q) {
                    if (!ctx->has_rational1) {
                        ctx->rational1 = q;
                        ctx->has_rational1 = 1;
                        printf("Дробь сохранена как ПЕРВАЯ рациональная\n");
                    } else if (!ctx->has_rational2) {
                        ctx->rational2 = q;
                        ctx->has_rational2 = 1;
                        printf("Дробь сохранена как ВТОРАЯ рациональная\n");
                    } else {
                        printf("Память заполнена!\n");
                        free_Q(q);
                    }
                }
                printf("\nНажмите Enter для продолжения...");
                while (getchar() != '\n');
                break;
            }
                
            case 4: {
                printf("---------- ВВОД МНОГОЧЛЕНА -----------\n");
                printf("Формат: коэффициент степень (через пробел)\n");
                printf("Коэффициент: [-]числитель[/знаменатель]\n");
                printf("Степень: натуральное число или 0\n");
                printf("Пример: 3/4 5  -1 3  2 0\n");
                printf("Вводите по одному слагаемому на строку\n");
                printf("Пустая строка завершает ввод\n");
                printf("--------------------------------------\n");
                
                Polynomial* p = read_poly();
                if (p) {
                    printf("Введен многочлен: ");
                    print_poly(p);
                    printf("\n");
                    
                    if (!ctx->has_polynom1) {
                        ctx->polynom1 = p;
                        ctx->has_polynom1 = 1;
                        printf("Многочлен сохранен как ПЕРВЫЙ\n");
                    } else if (!ctx->has_polynom2) {
                        ctx->polynom2 = p;
                        ctx->has_polynom2 = 1;
                        printf("Многочлен сохранен как ВТОРОЙ\n");
                    } else {
                        printf("Память заполнена!\n");
                        free_poly(p);
                    }
                }
                printf("\nНажмите Enter для продолжения...");
                while (getchar() != '\n');
                break;
            }
                
            case 5:
                handle_natural_operations(ctx);
                break;
                
            case 6:
                handle_integer_operations(ctx);
                break;
                
            case 7:
                handle_rational_operations(ctx);
                break;
                
            case 8:
                handle_polynomial_operations(ctx);
                break;
                
            case 9:
                print_help();
                printf("\nНажмите Enter для продолжения...");
                while (getchar() != '\n');
                break;
                
            case 0:
                printf("\nДо свидания!\n");
                running = 0;
                break;
            
            case 10:
                clear_naturals(ctx);
                printf("Натуральные числа очищены.\n");
                printf("\nНажмите Enter для продолжения...");
                while (getchar() != '\n');
                break;
                
            case 11:
                clear_integers(ctx);
                printf("Целые числа очищены.\n");
                printf("\nНажмите Enter для продолжения...");
                while (getchar() != '\n');
                break;
                
            case 12:
                clear_rationals(ctx);
                printf("Рациональные числа очищены.\n");
                printf("\nНажмите Enter для продолжения...");
                while (getchar() != '\n');
                break;
                
            case 13:
                clear_polynomials(ctx);
                printf("Многочлены очищены.\n");
                printf("\nНажмите Enter для продолжения...");
                while (getchar() != '\n');
                break;
                
            case 14:
                clear_all(ctx);
                printf("\nНажмите Enter для продолжения...");
                while (getchar() != '\n');
                break;

            default:
                printf("\nНеверный выбор! Введите число от 0 до 9.\n");
                printf("\nНажмите Enter для продолжения...");
                while (getchar() != '\n');
                break;
        }
        clear_screen();
    }
    
    free_context(ctx);
    return 0;
}