#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readPoly.h"
#include "Q.h"

Q* read_coeff(char *str) {
    if (!str || *str == '\0') {
        printf("Ошибка: пустой коэффициент!\n");
        return NULL;
    }


    char *buf = strdup(str);
    if (!buf) {
        printf("Ошибка: присутствует недопустимый символ!\n");
        return NULL;
    }


    char *slash = strchr(buf, '/');
    char *num_str, *den_str;


    if (slash == NULL) {
        num_str = buf;
        den_str = "1";
    } else {
        *slash = '\0';
        num_str = buf;
        den_str = slash + 1;
        if (*num_str == '\0' || *den_str == '\0') {
            printf("Ошибка: числитель или знаменатель!\n");
            free(buf);
            return NULL;
        }
    }


    for (size_t i = 0; i < strlen(num_str); i++) {
        if (!isdigit(num_str[i]) && !(i == 0 && num_str[i] == '-')) {
            printf("Ошибка: непустимый символ в числителе\n");
            free(buf);
            return NULL;
        }
    }
    if (num_str[0] == '-') {
        if (strlen(num_str) > 2 && num_str[1] == '0') {
            printf("Введите число без ведущих нулей!\n");
            free(buf);
            return NULL;
        }
    } else {
        if (num_str[0] == '0' && strlen(num_str) > 1) {
            printf("Введите число без ведущих нулей!\n");
            free(buf);
            return NULL;
        }
    }


    for (size_t i = 0; i < strlen(den_str); i++) {
        if (!isdigit((unsigned char)den_str[i])) {
            printf("Ошибка: непустимый символ в знаменателе\n");
            free(buf);
            return NULL;
        }
    }
    if (den_str[0] == '0') {
        if (strlen(den_str) > 1) {
            printf("Введите число без ведущих нулей!\n");
            free(buf);
            return NULL;
        } else {
            printf("Ошибка знаменатель не может быть равен нулю!\n");
            free(buf);
            return NULL;
        }
    }

    if (num_str[0] == '-' && strlen(num_str) == 1){ 
        printf("Неправильный ввод!\n");
            free(buf);
            return NULL;
    }


    char *num_copy = malloc(strlen(num_str) + 1);
    char *den_copy = malloc(strlen(den_str) + 1);
    if (!num_copy || !den_copy) {
        free(num_copy);
        free(den_copy);
        free(buf);
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    strcpy(num_copy, num_str);
    strcpy(den_copy, den_str);
    free(buf);


    Q *q = malloc(sizeof(Q));
    if (!q) {
        free(num_copy);
        free(den_copy);
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    q->numerator = num_copy;
    q->denominator = den_copy;
    q->nn = strlen(num_copy);
    q->dm = strlen(den_copy);
    return q;
}

char* read_exp(const char *str) {
    if (!str || *str == '\0') {
        printf("Ошибка: пустая степень!\n");
        return NULL;
    }
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (!isdigit(str[i])) {
            printf("Ошибка: присутсвтует непустимый символ\n");
            return NULL;
        }
    }
    if (str[0] == '0' && len > 1) {
        printf("Введите степень без ведущих нулей!\n");
        return NULL;
    }
    char *res = strdup(str);
    if (!res) printf("Ошибка выделения памяти!\n");
    return res;
}


int term_cmp(const void *p1, const void *p2) {
    const Term *t1 = p1, *t2 = p2;
    return -cmp_natural_str(t1->exp, t2->exp);
}


Polynomial* read_poly(void) {
    printf("Введите моном в формате <коэффициент степень>. Пустая строка завершает ввод.\n");


    Term *terms = NULL;
    int cap = 0, cnt = 0;
    char buf[10000];


    while (1) {
        printf("> ");
        if (!fgets(buf, sizeof(buf), stdin)) break;
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') buf[len - 1] = '\0';
        if (buf[0] == '\0') break;


        char *space = strchr(buf, ' ');
        if (!space) {
            printf("Ошибка: неправильный ввод!\n");
            continue;
        }
        *space = '\0';
        char *coeff_str = buf;
        char *exp_str = space + 1;
        while (*exp_str == ' ') exp_str++;
        if (*exp_str == '\0') {
            printf("Ошибка чтения степени!\n");
            continue;
        }


        Q *coeff = read_coeff(coeff_str);
        if (!coeff) continue;


        char *exp = read_exp(exp_str);
        if (!exp) {
            free_Q(coeff);
            continue;
        }


        if (cnt >= cap) {
            cap = cap ? cap * 2 : 4;
            Term *tmp = realloc(terms, cap * sizeof(Term));
            if (!tmp) {
                free_Q(coeff);
                free(exp);
                printf("Ошибка выделения памяти!\n");
                break;
            }
            terms = tmp;
        }
        terms[cnt].coeff = coeff;
        terms[cnt].exp = exp;
        cnt++;
    }


    if (cnt == 0) {
        printf("Нет введенных мономов!\n");
        free(terms);
        return NULL;
    }


    qsort(terms, cnt, sizeof(Term), term_cmp);


    Polynomial *p = malloc(sizeof(Polynomial));
    if (!p) {
        for (int i = 0; i < cnt; i++) {
            free_Q(terms[i].coeff);
            free(terms[i].exp);
        }
        free(terms);
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    p->terms = terms;
    p->count = cnt;
    return p;
}

void print_poly(Polynomial *p) {
    if (!p) return;
    int flag = 0;
    for (int i = 0; i < p->count; i++) {
        Q *q = p->terms[i].coeff;
        char *num = q->numerator;
        char *den = q->denominator;
        char *exp = p->terms[i].exp;


        if (strcmp(num, "0") == 0 || strcmp(num, "-0") == 0)
            continue;


        int is_neg = (num[0] == '-');
        const char *abs_num = is_neg ? num + 1 : num;


        if (flag) {
            printf(" %c ", is_neg ? '-' : '+');
        } else {
            if (is_neg) printf("-");
        }


        int coeff_is_one = (strcmp(abs_num, "1") == 0 && strcmp(den, "1") == 0);
        int exp_is_zero = (strcmp(exp, "0") == 0);


        if (exp_is_zero) {
            if (strcmp(den, "1") == 0)
                printf("%s", abs_num);
            else
                printf("%s/%s", abs_num, den);
        } else {
            if (!coeff_is_one) {
                if (strcmp(den, "1") == 0)
                    printf("%s", abs_num);
                else
                    printf("%s/%s", abs_num, den);
            }
            if (strcmp(exp, "1") == 0)
                printf("x");
            else
                printf("x^%s", exp);
        }
        flag = 1;
    }
    if (!flag) printf("0");
}


void free_poly(Polynomial *p) {
    if (!p) return;
    for (int i = 0; i < p->count; i++) {
        free_Q(p->terms[i].coeff);
        free(p->terms[i].exp);
    }
    free(p->terms);
    free(p);
}
