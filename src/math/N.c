#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "N.h"

//Новожилова Дарья
int COM_NN_D(char* x, char* y){
    int lenx = strlen(x);
    int leny = strlen(y);


    if(lenx > leny){
        return 2;
    }
    else if(lenx < leny){
        return 1;
    }

    else{

        if(strcmp(x, y) == 0) return 0;
        for(int i=0; i < lenx; i++){
            if (x[i] > y[i]) return 2;
            if (x[i] < y[i]) return 1;
        }
    }
    return 0;
}

char* TRANS_N_Z(char* x) {
    if (!x) return NULL;
    
    int len = strlen(x);
    char* result = (char*)malloc(len + 1);
    if (!result) return NULL;
    
    strcpy(result, x);
    
    return result;
}

//Новожилова Дарья
char* NZER_N_B(char* x) {
    int len = strlen(x);
   
    for (int i = 0; i < len; i++) {
        if (x[i] != '0') {
            return "да";
        }
    }
    return "нет";
}

//Новожилова Дарья
char* ADD_1N_N(const char* x) {
    char* copy = malloc(10*(strlen(x) + 1));
    strcpy(copy, x);
    
    for (int i = strlen(copy) - 1; i >= 0; i--) {
        if (copy[i] != '9') {
            copy[i] = copy[i] + 1;
            return copy;
        }
        copy[i] = '0';
    }
    
    int len = strlen(x);
    char* result = malloc(10*(len + 2));
    result[0] = '1';
    for (int i = 0; i < len; i++) {
        result[i + 1] = '0';
    }
    result[len + 1] = '\0';
    free(copy);
    return result;
}

//Вероника Богачева
char* ADD_NN_N(const char* a, const char* b) {
   int lenA = strlen(a);
   int lenB = strlen(b);
  
   int maxLen = (lenA > lenB ? lenA : lenB);


   char* result = (char*)malloc(10*(maxLen + 2) * sizeof(char));
   if (result == NULL) {
       return NULL;
   }


   int i = lenA - 1;
   int j = lenB - 1;
   int k = 0;
   int carry = 0;


   while (i >= 0 || j >= 0 || carry) {
       int digitA = (i >= 0) ? (a[i] - '0') : 0;
       int digitB = (j >= 0) ? (b[j] - '0') : 0;


       int sum = digitA + digitB + carry;
       result[k++] = (sum % 10) + '0';
       carry = sum / 10;


       i--;
       j--;
   }


   result[k] = '\0';


   for (int l = 0; l < k / 2; l++) {
       char temp = result[l];
       result[l] = result[k - l - 1];
       result[k - l - 1] = temp;
   }


   return result;
}

//Вероника Богачева
char* MUL_ND_N(const char* num, char digit_char) {
   if (digit_char < '0' || digit_char > '9') {
       return NULL;
   }


   int digit = digit_char - '0';
   int len = strlen(num);

   if (digit == 0) {
       char* zero = (char*)malloc(2);
       if (!zero) return NULL;
       zero[0] = '0';
       zero[1] = '\0';
       return zero;
   }


   char* result = (char*)malloc(100*(len + 2));
   if (!result) return NULL;


   int carry = 0;
   int k = 0;


   for (int i = len - 1; i >= 0; i--) {
       int n = num[i] - '0';


       int prod = n * digit + carry;


       result[k++] = (prod % 10) + '0';
       carry = prod / 10;
   }

   while (carry > 0) {
       result[k++] = (carry % 10) + '0';
       carry /= 10;
   }

   result[k] = '\0';

   for (int i = 0; i < k / 2; i++) {
       char tmp = result[i];
       result[i] = result[k - i - 1];
       result[k - i - 1] = tmp;
   }


   return result;
}

//Итыгилов Архип
char* SUB_NN_N(char *a, char *b){
   
    if(COM_NN_D(a, b) == 1) return 0;
    if(COM_NN_D(a,b) == 0){
        char* ans = malloc(2);
        ans[0] = '0';
        ans[1] = '\0';
        return ans;
    }


    if(COM_NN_D(a,b) == 2){
        int as = strlen(a);
        int bs = strlen(b);
        char* res = malloc(10*(as+1));
        if (!res){
            printf("ошибка выделения памяти\n");
            free(res);
            return NULL;
        }
        int c=0;


        char* at = malloc(10*(as+1));
        if (!at){
            printf("ошибка выделения памяти\n");
            free(at);
            return NULL;
        }
        strcpy(at, a);
       
        for(int i = as - 1, j = bs - 1; i>=0; i--, j--){
            if(j>=0){
                if(at[i]<b[j]){
                    at[i]+=10;
                    at[i-1]--;
                }
                res[c++] = (at[i]-b[j])+'0';
            } else{
                if(at[i]<'0'){
                    at[i]+=10;
                    at[i-1]--;
                }
                res[c++] = at[i];
            }
        } res[c] = '\0';

        for(int i = 0; i < c / 2; i++) {
            char tmp = res[i];
            res[i] = res[c - 1 - i];
            res[c - 1 - i] = tmp;
        }

        char* start = res;
        while(*start == '0') {
            start++;
        }

        char* final = malloc(10*(strlen(start) + 1));
        if (!final){
            printf("ошибка выделения памяти\n");
            free(final);
            return NULL;
        }
        strcpy(final, start);
        free(at);
        free(res);
        return final;
    }
    return 0;
}

//Итыгилов Архип
char* MUL_Nk_N(char* a, char* k){
    int as = strlen(a);
    int kn = atoi(k);
    char* res = malloc(10*(as + kn + 1));
    strcpy(res, a);
   
    for(int i=as; i<as+kn; i++){
        res[i]='0';
    } res[as+kn] ='\0';


    return res;
}    

//Итыгилов Архип
char* SUB_NDN_N(char* a, char* b, char k){
    char* bk = MUL_ND_N(b, k);

    char* res = SUB_NN_N(a, bk);
   
    return res;
}

//Колесникова Дарья
char* MUL_NN_N(const char* a, const char* b) {
   int lenA = strlen(a);
   int lenB = strlen(b);

   int isZero(const char* num) {
       for (size_t i = 0; i < strlen(num); i++) {
           if (num[i] != '0') return 0;
       }
       return 1;
   }

   if (isZero(a) || isZero(b)) {
       char* zero = (char*)malloc(2);
       if (!zero) return NULL;
       zero[0] = '0';
       zero[1] = '\0';
       return zero;
   }
  
   const char* multiplicand;
   const char* multiplier;
  
   if (lenA >= lenB) {
       multiplicand = a;
       multiplier = b;
   } else {
       multiplicand = b;
       multiplier = a;
   }
  
   char* result = (char*)malloc(2);
   if (!result) return NULL;
   result[0] = '0';
   result[1] = '\0';
  
   int multLen = strlen(multiplier);
  
   for (int i = multLen - 1; i >= 0; i--) {
       char digit = multiplier[i];
      
       char* temp = MUL_ND_N(multiplicand, digit);
       if (!temp) {
           free(result);
           return NULL;
       }
      
       char k_str[16];
       int zeros = multLen - 1 - i;
       snprintf(k_str, sizeof(k_str), "%d", zeros);
       char* shifted = MUL_Nk_N(temp, k_str);
       free(temp);
      
       if (!shifted) {
           free(result);
           return NULL;
       }
      
       char* new_result = ADD_NN_N(result, shifted);
       free(shifted);
       free(result);
      
       if (!new_result) return NULL;
       result = new_result;
   }
  
   return result;
}

//Костромицкая Вероника
char* DIV_NN_Dk(char* N, int D, int* k) {
    if (D <= 0 || D > 9 || k == NULL || N == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (N[len] != '\0') len++;

    char* result = (char*)malloc(10*(len + 1));
    if (result == NULL) {
        return NULL;
    }

    size_t pos = 0;
    int rem = 0;

    for(size_t i = 0; i < len; i++) {
        rem = rem * 10 + (N[i] - '0');
        rem = rem % D;
    }

    for(size_t i = 0; i < len; i++) {
        rem = rem * 10 + (N[i] - '0');
        int q = rem / D;

        if (q > 0 || pos > 0) {
            result[pos++] = (char)(q + '0');
        }
    }

    if (pos == 0) {
        result[pos++] = '0';
    }
    result[pos] = '\0';

    *k = rem;

    char* final_res = (char*)realloc(result, pos + 1);
    return (final_res != NULL) ? final_res : result;
}

//Костромицкая Вероника
char* DIV_NN_N(char* A, char* B) {
    if (!A || !B || B[0] == '\0') return NULL;

    if (B[0] == '1' && B[1] == '\0') {
        size_t len = 0;
        while (A[len] != '\0') len++;

        char* res = malloc(10*(len + 1));
        if (!res) {
            printf("ошибка выделения памяти\n");
            free(res);
            return NULL;
        }

        for (size_t i = 0; i <= len; i++)
            res[i] = A[i];

        return res;
    }

    // A < B
    if (COM_NN_D(A, B) == 1) {
        char* zero = malloc(2);
        if (!zero) {
            printf("ошибка выделения памяти\n");
            free(zero);
            return NULL;
        }

        zero[0] = '0';
        zero[1] = '\0';

        return zero;
    }

    // A == B
    if (COM_NN_D(A, B) == 0) {
        char* one = malloc(2);
        if (!one){
            printf("ошибка выделения памяти\n");
            free(one);
            return NULL;
        } 

        one[0] = '1';
        one[1] = '\0';

        return one;
    }

    size_t lenA = 0;
    while (A[lenA] != '\0') lenA++;

    char* rem = malloc(10*(lenA + 2));
    if (!rem) {
        printf("ошибка выделения памяти\n");
        free(rem);
        return NULL;
    }

    rem[0] = '\0';

    char* quot = malloc(10*(lenA + 1));
    if (!quot) {
        printf("ошибка выделения памяти\n");
        free(quot);
        return NULL;
    }

    size_t qpos = 0;

    for (size_t i = 0; i < lenA; i++) {

        size_t remLen = 0;
        while (rem[remLen] != '\0') remLen++;

        rem[remLen] = A[i];
        rem[remLen + 1] = '\0';

        size_t shift = 0;
        while (rem[shift] == '0' && rem[shift + 1] != '\0')
            shift++;

        if (shift > 0) {
            size_t newLen = remLen + 1 - shift;

            for (size_t k = 0; k < newLen; k++)
                rem[k] = rem[shift + k];

            rem[newLen] = '\0';
        }

        if (rem[0] == '0' && rem[1] == '\0') {
            quot[qpos++] = '0';
            quot[qpos] = '\0';
            continue;
        }

        int q = 9;

        while (q > 0) {
            char qChar = (char)(q + '0');

            char* prod = MUL_ND_N(B, qChar);
            if (!prod) {
                free(rem);
                free(quot);
                return NULL;
            }

            if (COM_NN_D(rem, prod) != 1) {
                free(prod);
                break;
            }

            free(prod);
            q--;
        }

        quot[qpos++] = (char)(q + '0');
        quot[qpos] = '\0';

        char qChar = (char)(q + '0');

        char* prod = MUL_ND_N(B, qChar);
        if (!prod) {
            free(rem);
            free(quot);
            return NULL;
        }

        if (q != 0) {
            char* newRem = SUB_NN_N(rem, prod);
            if (!newRem) {
                free(prod);
                free(rem);
                free(quot);
                return NULL;
            }
            strcpy(rem, newRem);
            free(newRem);
        }

        free(prod);
    }

    size_t qShift = 0;
    while (quot[qShift] == '0' && quot[qShift + 1] != '\0')
        qShift++;

    size_t finalLen = qpos - qShift;

    char* finalQuot = malloc(10*(finalLen + 1));
    if (!finalQuot) {
        free(rem);
        free(quot);
        return NULL;
    }

    for (size_t k = 0; k < finalLen; k++)
        finalQuot[k] = quot[qShift + k];

    finalQuot[finalLen] = '\0';

    free(rem);
    free(quot);

    return finalQuot;
}


//Осипова Евгения
char* MOD_NN_N(char* a, char* b){
    if (!a || !b) return NULL;
    
    if (strcmp(NZER_N_B(b), "нет") == 0){
        printf("Ошибка: деление на ноль запрещено");
        return NULL;
    }
    
    char* q = DIV_NN_N(a, b);
    if (!q){
        printf("Error div\n");
       return NULL; 
    } 
    
    char* bq = MUL_NN_N(b, q);
    if (!bq){
        printf("error mul\n");
        free(q);
        return NULL;
    }
    char* r = SUB_NN_N(a, bq);
    if (r == NULL){
        printf("err sub\n");
        free(q);
        free(bq);
        return NULL;
    }

    free(q);
    free(bq);
    
    return r;    
}

//Осипова Евгения
char* GCF_NN_N(char* a, char* b){
    if(!a || !b) return NULL;
    
   if ((a[0] == '1' && a[1] == '\0') || (b[0] == '1' && b[1] == '\0')) { 
        char* res = malloc(2);
        if (!res) return NULL;
        res[0] = '1';
        res[1] = '\0';
        return res;
    }

    int cmp = COM_NN_D(a, b);
    if (cmp == 0){
        char* res = malloc(10*(strlen(a)+1));
        if (!res) return NULL;
        strcpy(res, a);
        return res;
    }

    const char* xsrc = (cmp == 2) ? a : b;
    const char* ysrc = (cmp == 2) ? b : a;

    char *x = malloc(10*(strlen(xsrc) + 1));
    char *y = malloc(10*(strlen(ysrc) + 1));
    if (x && y) {
        strcpy(x, xsrc);
        strcpy(y, ysrc);
    }
    if (!x || !y) {
        free(x);  
        free(y);
        printf("err\n");
        return NULL;
    }
    
    while (strcmp(NZER_N_B(y), "да") == 0){
        char* r = MOD_NN_N(x, y);
        if (!r){
            printf("errorrrrrrrrr\n");
            free(x); 
            free(y); 
            return NULL;
        }
        free(x);
        x = y;
        y = r;
    }
    
    free(y);
    return x;
}

//Осипова Евгения
char* LCM_NN_N(char* a, char* b) {
    if (!a || !b) return NULL;
    
    char* gcf = GCF_NN_N(a, b);
    if (!gcf){
        printf("error gfc!");
        return NULL;
    }

    
    char* mul = MUL_NN_N(a, b);
    if (!mul){
        printf("error mul\n");
        return NULL;
    }

    char* lcm = DIV_NN_N(mul, gcf);
    
    return lcm; 
}

