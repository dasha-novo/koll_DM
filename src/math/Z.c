#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Z.h"
#include "N.h"

//Новожилова Дарья
char* ABS_Z_N(char* x){
    int len = strlen(x);
    char* result = (char*)malloc(10*((len + 1) * sizeof(char)));
    if (result == NULL) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }


    int i = 0;
    if(x[0] == '-') i++;
    int j = 0;
    for (; i < len; i++, j++) {
        result[j] = x[i];
    }
    result[j] = '\0';
    return result;
}

//Новожилова Дарья
int POZ_Z_D(char* x){
    if(strlen(x) == 1 && x[0] == '0'){ return 0; }
    if (x[0] == '-') { return -1; }
    return 1;
}

//Богачева Вероника
char* MUL_ZM_Z(const char* num) {
   int len = strlen(num);

   if ((len == 1 && num[0] == '0') ||
       (len == 2 && num[0] == '-' && num[1] == '0')) {
      
       char* zero = (char*)malloc(2);
       if (!zero) return NULL;
       zero[0] = '0';
       zero[1] = '\0';
       return zero;
   }

   if (num[0] == '-') {
       char* result = (char*)malloc(10*(len));
       if (!result) return NULL;


       memcpy(result, num + 1, len);
       return result;
   }

   char* result = (char*)malloc(10*(len + 2));
   if (!result) return NULL;

   result[0] = '-';
   memcpy(result + 1, num, len + 1);

   return result;
}

//Богачева Вероника
char* TRANS_Z_N(const char* num) {
   if (num[0] == '-') {
       return NULL;
   }


   int len = strlen(num);
   int i = 0;

   while (i < len && num[i] == '0') {
       i++;
   }

   if (i == len) {
       return NULL;
   }

   int newLen = len - i;


   char* result = (char*)malloc(10*(newLen + 1));
   if (!result) return NULL;


   memcpy(result, num + i, newLen);
   result[newLen] = '\0';

   return result;
}

//Итыгилов Архип
char* ADD_ZZ_Z(char* a, char* b){
    if(POZ_Z_D(b) == 0){
            char* copy = malloc(10*(strlen(a) + 1));
            strcpy(copy, a);
            return copy;
        }
    if(POZ_Z_D(a) == 0){
        char* copy = malloc(10*(strlen(b) + 1));
        strcpy(copy, b);
        return copy;
    }


    int asign = POZ_Z_D(a);
    int bsign = POZ_Z_D(b);


    char* an = ABS_Z_N(a);
    char* bn = ABS_Z_N(b);


    if(asign == bsign){
        char* res = TRANS_N_Z(ADD_NN_N(an, bn));


        if(asign == -1){
            char* neg_res = MUL_ZM_Z(res);
            free(an);
            free(bn);
            free(res);
            return neg_res;
        } else{
            free(an);
            free(bn);
            return res;
        }
    } else {
        int cmp = COM_NN_D(an, bn);
        char* max_ab = (cmp == 2) ? an : bn;
        int max_sign = (cmp == 2)  ? asign : bsign;
        char* min_ab = (cmp == 2) ? bn : an;


        char* res = TRANS_N_Z(SUB_NN_N(max_ab, min_ab));
        if(max_sign == -1){
            char* neg_res = MUL_ZM_Z(res);
            free(max_ab);
            free(min_ab);
            free(res);
            return neg_res;
        } else{
            free(max_ab);
            free(min_ab);
            return res;
        }
    }
}

//Итыгилов Архип
char* SUB_ZZ_Z(char* a, char* b){
    if(POZ_Z_D(b) == 0){
            char* copy = malloc(10*(strlen(a) + 1));
            strcpy(copy, a);
            return copy;
        }
    if(POZ_Z_D(a) == 0){
        char* neg_b = MUL_ZM_Z(b);
        return neg_b;
    }


    int asign = POZ_Z_D(a);
    int bsign = POZ_Z_D(b);


    char* an = ABS_Z_N(a);
    char* bn = ABS_Z_N(b);


    if(asign != bsign){
        char* res = TRANS_N_Z(ADD_NN_N(an, bn));


        if(asign == -1){
            char* neg_res = MUL_ZM_Z(res);
            free(an);
            free(bn);
            free(res);
            return neg_res;
        } else{
            free(an);
            free(bn);
            return res;
        }
    } else {
        int cmp = COM_NN_D(an, bn);
        char* max_ab = (cmp == 2) ? an : bn;
        char* min_ab = (cmp == 2) ? bn : an;


        char* res = TRANS_N_Z(SUB_NN_N(max_ab, min_ab));
        if((cmp == 2 && asign == -1) || (cmp == 1 && bsign == 1)){
            char* neg_res = MUL_ZM_Z(res);
            free(max_ab);
            free(min_ab);
            free(res);
            return neg_res;
        } else{
            free(max_ab);
            free(min_ab);
            return res;
        }
    }
}

//Колесникова Дарья
char* MUL_ZZ_Z(const char* a, const char* b) {
   char* abs_a = ABS_Z_N((char*)a);
   if (!abs_a) return NULL;
  
   char* abs_b = ABS_Z_N((char*)b);
   if (!abs_b) {
       free(abs_a);
       return NULL;
   }
  
   if ((strlen(abs_a) == 1 && abs_a[0] == '0') ||
       (strlen(abs_b) == 1 && abs_b[0] == '0')) {
       free(abs_a);
       free(abs_b);
      
       char* zero = (char*)malloc(2);
       if (zero) {
           zero[0] = '0';
           zero[1] = '\0';
       }
       return zero;
   }
  
   char* result = TRANS_N_Z(MUL_NN_N(abs_a, abs_b));
   free(abs_a);
   free(abs_b);
  
   if (!result) return NULL;
  
   int sign_a = POZ_Z_D((char*)a);
   int sign_b = POZ_Z_D((char*)b);
  
   if (sign_a * sign_b < 0) {
       char* negative_result = MUL_ZM_Z(result);
       free(result);
       return negative_result;
   }
  
   return result;
}

//Колесникова Дарья
char* DIV_ZZ_Z(char* x, char* y) {
    if (y == NULL || strlen(y) == 0 ||
        (strlen(y) == 1 && y[0] == '0')) {
        printf("Ошибка: деление на ноль!\n");
        return NULL;
    }

    if (x == NULL || strlen(x) == 0 ||
        (strlen(x) == 1 && x[0] == '0')) {

        char* result = malloc(2);

        if (result) {
            result[0] = '0';
            result[1] = '\0';
        }

        return result;
    }

    int sign_x = POZ_Z_D(x);
    int sign_y = POZ_Z_D(y);

    int result_sign = sign_x * sign_y;

    char* abs_x = ABS_Z_N(x);
    char* abs_y = ABS_Z_N(y);

    if (abs_x == NULL || abs_y == NULL) {
        free(abs_x);
        free(abs_y);
        return NULL;
    }

    char* quotient = TRANS_N_Z(DIV_NN_N(abs_x, abs_y));

    if (quotient == NULL) {
        free(abs_x);
        free(abs_y);
        return NULL;
    }

    char* remainder = MOD_NN_N(abs_x, abs_y);

    if (remainder == NULL) {
        free(abs_x);
        free(abs_y);
        free(quotient);
        return NULL;
    }

    int has_remainder =
        !(strlen(remainder) == 1 && remainder[0] == '0');

    if (result_sign == -1 && has_remainder) {

        char* temp = ADD_ZZ_Z(quotient, "1");

        free(quotient);
        quotient = temp;

        if (quotient == NULL) {
            free(abs_x);
            free(abs_y);
            free(remainder);
            return NULL;
        }
    }

    free(remainder);

    char* result;

    if (result_sign == -1 &&
        !(strlen(quotient) == 1 && quotient[0] == '0')) {

        result = malloc(10*(strlen(quotient) + 2));

        if (result == NULL) {
            free(abs_x);
            free(abs_y);
            free(quotient);
            return NULL;
        }

        result[0] = '-';
        strcpy(result + 1, quotient);

    } else {

        result = malloc(10*(strlen(quotient) + 1));

        if (result == NULL) {
            free(abs_x);
            free(abs_y);
            free(quotient);
            return NULL;
        }

        strcpy(result, quotient);
    }

    free(abs_x);
    free(abs_y);
    free(quotient);

    return result;
}



//Колесникова Дарья
char* MOD_ZZ_Z(char* x, char* y) {
   if (y == NULL || strlen(y) == 0 || (strlen(y) == 1 && y[0] == '0')) {
       printf("Ошибка: деление на ноль!\n");
       return NULL;
   }
   if (x == NULL || strlen(x) == 0 || (strlen(x) == 1 && x[0] == '0')) {
       char* result = malloc(2);
       if (result) {
           result[0] = '0';
           result[1] = '\0';
       }
       return result;
   }
  
   char* quotient = DIV_ZZ_Z(x, y);
  
   if (quotient == NULL) {
       return NULL;
   }
  
   char* product = MUL_ZZ_Z(y, quotient);
   free(quotient);
  
   if (product == NULL) {
       return NULL;
   }

   char* remainder = SUB_ZZ_Z(x, product);
   free(product);
  
   return remainder;
}
