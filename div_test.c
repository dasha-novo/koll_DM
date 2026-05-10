#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "P.h"
#include "Q.h"
#include "readPoly.h"

static Q* make_q(const char* num, const char* den) {
    Q* q = malloc(sizeof(Q));
    if (!q) return NULL;
    q->numerator = strdup(num);
    q->denominator = strdup(den);
    if (!q->numerator || !q->denominator) {
        free(q->numerator);
        free(q->denominator);
        free(q);
        return NULL;
    }
    q->nn = (int)strlen(q->numerator);
    q->dm = (int)strlen(q->denominator);
    return q;
}

static Polynomial* make_poly_2(const char* a_num, const char* a_den, const char* a_exp,
                              const char* b_num, const char* b_den, const char* b_exp) {
    Polynomial* p = malloc(sizeof(Polynomial));
    if (!p) return NULL;
    p->count = 2;
    p->terms = malloc(sizeof(Term) * 2);
    if (!p->terms) { free(p); return NULL; }

    p->terms[0].coeff = make_q(a_num, a_den);
    p->terms[0].exp = strdup(a_exp);
    p->terms[1].coeff = make_q(b_num, b_den);
    p->terms[1].exp = strdup(b_exp);

    if (!p->terms[0].coeff || !p->terms[0].exp || !p->terms[1].coeff || !p->terms[1].exp) {
        free_poly(p);
        return NULL;
    }
    return p;
}

int main(void) {
    Polynomial* p1 = make_poly_2("1", "1", "1000", "1", "1", "0");     // x^1000 + 1
    Polynomial* p2 = make_poly_2("1000", "1", "1", "1", "1", "0");     // 1000x + 1
    if (!p1 || !p2) {
        printf("alloc failed\n");
        free_poly(p1);
        free_poly(p2);
        return 1;
    }

    Polynomial* q = DIV_PP_P(p1, p2);
    if (!q) {
        printf("DIV_PP_P returned NULL\n");
        free_poly(p1);
        free_poly(p2);
        return 2;
    }

    printf("p1 = "); print_poly(p1); printf("\n");
    printf("p2 = "); print_poly(p2); printf("\n");
    printf("q  = "); print_poly(q);  printf("\n");

    free_poly(q);
    free_poly(p1);
    free_poly(p2);
    return 0;
}

