#ifndef P_H
#define P_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Q.h"

typedef struct {
    Q* coeff;
    char* exp;
} Term;

typedef struct {
    Term* terms;
    int count;
} Polynomial;

int cmp_natural_str(const char* a, const char* b);

Polynomial* ADD_PP_P(Polynomial* poly1, Polynomial* poly2);
Polynomial* SUB_PP_P(Polynomial* P1, Polynomial* P2);
Polynomial* MUL_PQ_P(Polynomial* p, Q* q);
Polynomial* MUL_Pxk_P(Polynomial* p, char* k);
Q* LED_P_Q(const Polynomial* p);
char* DEG_P_N(Polynomial* p);
Polynomial* MUL_PP_P(Polynomial* P1, Polynomial* P2);
Polynomial* DIV_PP_P(Polynomial* p1, Polynomial* p2);
Polynomial* MOD_PP_P(Polynomial* A, Polynomial* B);
Polynomial* GCF_PP_P(Polynomial* A, Polynomial* B);
Polynomial* DER_P_P(Polynomial* p);

#endif