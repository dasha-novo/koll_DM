#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Q.h"
#include "N.h"
#include "Z.h"

#define _POSIX_C_SOURCE 200809L

//Новожилова Дарья
char* INT_Q_B(Q* q) {
    if (strcmp(q->denominator, "1") == 0) {
        return "да";
    }
    return "нет";
}

//Богачева Вероника
Q* TRANS_Z_Q(const char* num) {
    if (!num) {
        return NULL;
    }

    Q* q = malloc(sizeof(Q));
    if (!q) {
        return NULL;
    }

    q->numerator = strdup(num);
    if (!q->numerator) {
        free(q);
        return NULL;
    }

    q->denominator = strdup("1");
    if (!q->denominator) {
        free(q->numerator);
        free(q);
        return NULL;
    }

    q->nn = strlen(q->numerator);
    q->dm = 1;

    return q;
}

//Богачева Вероника
char* TRANS_Q_Z(const Q* q) {
    if (!q || !q->numerator || !q->denominator) {
        return NULL;
    }

    if (strcmp(q->denominator, "1") != 0) {
        return NULL;
    }

    int len = strlen(q->numerator);
    char* result = (char*)malloc(len + 1);
    if (!result) {
        return NULL;
    }

    memcpy(result, q->numerator, len + 1);

    return result;
}

//Итыгилов Архип
Q* RED_Q_Q(Q* frac){
    Q* newfrac = malloc(sizeof(Q));
    if (!newfrac) return NULL;


    char* nod = GCF_NN_N(ABS_Z_N(frac->numerator), frac->denominator);


    newfrac->numerator = DIV_ZZ_Z(frac->numerator, nod);
    newfrac->denominator = DIV_ZZ_Z(frac->denominator, nod);
   
    newfrac->nn = strlen(newfrac->numerator);
    newfrac->dm = strlen(newfrac->denominator);
    free(nod);
    return newfrac;
}

//Итыгилов Архип
Q* ADD_QQ_Q(Q* frac1, Q* frac2){
    Q* newfrac = malloc(sizeof(Q));


    char* nok = LCM_NN_N(frac1->denominator, frac2->denominator);
   
    char* mul_n1 = DIV_ZZ_Z(nok, frac1->denominator);
    char* mul_n2 = DIV_ZZ_Z(nok, frac2->denominator);


    char* n1 = MUL_ZZ_Z(frac1->numerator, mul_n1);
    char* n2 = MUL_ZZ_Z(frac2->numerator, mul_n2);


    newfrac->numerator = ADD_ZZ_Z(n1,n2);
    newfrac->denominator = nok;
   
    newfrac->nn = strlen(newfrac->numerator);
    newfrac->dm = strlen(newfrac->denominator);


    Q* redfrac = RED_Q_Q(newfrac);
   
    free(newfrac->numerator);
    free(newfrac->denominator);
    free(newfrac);


    free(n1);
    free(n2);
    free(mul_n1);
    free(mul_n2);
    return redfrac;
}

//Колесникова Дарья
Q* SUB_QQ_Q(Q* a, Q* b) {
   if (!a || !b) return NULL;
  
   char* lcm = LCM_NN_N(a->denominator, b->denominator);
   if (!lcm) return NULL;
  
   char* mult1 = DIV_NN_N(lcm, a->denominator);
   if (!mult1) {
       free(lcm);
       return NULL;
   }
  
   char* mult2 = DIV_NN_N(lcm, b->denominator);
   if (!mult2) {
       free(lcm);
       free(mult1);
       return NULL;
   }
  
   char* num1_new = MUL_ZZ_Z(a->numerator, mult1);
   if (!num1_new) {
       free(lcm);
       free(mult1);
       free(mult2);
       return NULL;
   }
  
   char* num2_new = MUL_ZZ_Z(b->numerator, mult2);
   if (!num2_new) {
       free(lcm);
       free(mult1);
       free(mult2);
       free(num1_new);
       return NULL;
   }
  
   char* result_num = SUB_ZZ_Z(num1_new, num2_new);
   if (!result_num) {
       free(lcm);
       free(mult1);
       free(mult2);
       free(num1_new);
       free(num2_new);
       return NULL;
   }
  


   Q* result = (Q*)malloc(sizeof(Q));
   if (!result) {
       free(lcm);
       free(mult1);
       free(mult2);
       free(num1_new);
       free(num2_new);
       free(result_num);
       return NULL;
   }
  
   result->numerator = result_num;
   result->denominator = lcm;
   result->nn = strlen(result_num);
   result->dm = strlen(lcm);
  
   result = RED_Q_Q(result);
  
   free(mult1);
   free(mult2);
   free(num1_new);
   free(num2_new);
  
   return result;
}

//Костромицкая Вероника
Q* MUL_QQ_Q(Q* Q1, Q* Q2) {
    if (Q1 == NULL || Q2 == NULL ||
        Q1->numerator == NULL || Q1->denominator == NULL ||
        Q2->numerator == NULL || Q2->denominator == NULL) {
        return NULL;
    }
    char* res_num = MUL_ZZ_Z(Q1->numerator, Q2->numerator);
    if (res_num == NULL) {
        return NULL;
    }

    char* res_den = MUL_NN_N(Q1->denominator, Q2->denominator);
    if (res_den == NULL) {
        free(res_num);
        return NULL;
    }

    size_t len_num = 0;
    while (res_num[len_num] != '\0') {
        len_num++;
    }

    size_t len_den = 0;
    while (res_den[len_den] != '\0') {
        len_den++;
    }

    Q* result = (Q*)malloc(sizeof(Q));
    if (result == NULL) {
        free(res_num);
        free(res_den);
        return NULL;
    }

    result->numerator = res_num;
    result->denominator = res_den;
    result->nn = (int)len_num;
    result->dm = (int)len_den;

    return result;
}

//Костромицкая Вероника
Q* DIV_QQ_Q(Q* Q1, Q* Q2) {
    if (Q1 == NULL || Q2 == NULL ||
        Q1->numerator == NULL || Q1->denominator == NULL ||
        Q2->numerator == NULL || Q2->denominator == NULL) {
        return NULL;
    }

    if (Q2->numerator[0] == '0' && Q2->numerator[1] == '\0') {
        return NULL;
    }

    char* res_num = MUL_ZZ_Z(Q1->numerator, Q2->denominator);
    if (res_num == NULL) {
        return NULL;
    }

    char* res_den = MUL_ZZ_Z(Q1->denominator, Q2->numerator);
    if (res_den == NULL) {
        free(res_num);
        return NULL;
    }

    size_t len_num = 0;
    while (res_num[len_num] != '\0') {
        len_num++;
    }

    size_t len_den = 0;
    while (res_den[len_den] != '\0') {
        len_den++;
    }

    Q* result = (Q*)malloc(sizeof(Q));
    if (result == NULL) {
        free(res_num);
        free(res_den);
        return NULL;
    }

    result->numerator = res_num;
    result->denominator = res_den;
    result->nn = (int)len_num;
    result->dm = (int)len_den;

    return result;
}
