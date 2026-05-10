#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "P.h"
#include "Q.h"
#include "N.h"
#include "Z.h"
#include "readPoly.h"

//Осипова Евгения
Polynomial* copy_poly(Polynomial* p) {
    if (!p) return NULL;

    Polynomial* res = malloc(sizeof(Polynomial));
    if (!res) { printf("Ошибка выделения памяти!\n"); return NULL; }

    res->count = p->count;
    if (p->count == 0) {
        res->terms = NULL;
        return res;
    }

    res->terms = malloc(p->count * sizeof(Term));
    if (!res->terms) { free(res); printf("Ошибка выделения памяти!\n"); return NULL; }

    int i;
    for (i = 0; i < p->count; i++) {
        res->terms[i].coeff = malloc(sizeof(Q));
        if (!res->terms[i].coeff) break;
       
        res->terms[i].coeff->numerator = NULL;
        res->terms[i].coeff->denominator = NULL;

        res->terms[i].coeff->numerator = malloc(strlen(p->terms[i].coeff->numerator) + 1);
        if (!res->terms[i].coeff->numerator) break;
        strcpy(res->terms[i].coeff->numerator, p->terms[i].coeff->numerator);

        res->terms[i].coeff->denominator = malloc(strlen(p->terms[i].coeff->denominator) + 1);
        if (!res->terms[i].coeff->denominator) break;
        strcpy(res->terms[i].coeff->denominator, p->terms[i].coeff->denominator);

        res->terms[i].coeff->nn = p->terms[i].coeff->nn;
        res->terms[i].coeff->dm = p->terms[i].coeff->dm;

        size_t len_exp = strlen(p->terms[i].exp);
        res->terms[i].exp = malloc(len_exp + 1);
        if (!res->terms[i].exp) break;
        strcpy(res->terms[i].exp, p->terms[i].exp);
    }

    if (i < p->count) {
        for (int j = 0; j <= i; j++) {
            free_Q(res->terms[j].coeff);
            free(res->terms[j].exp);
        }
        free(res->terms);
        free(res);
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }

    return res;
}

//Колесникова Дарья
Polynomial* ADD_PP_P(Polynomial *poly1, Polynomial *poly2) {
   if (!poly1 || !poly2) return NULL;
  
   Polynomial *p1 = copy_poly(poly1);
   Polynomial *p2 = copy_poly(poly2);
  
   if (!p1 || !p2) {
       free_poly(p1);
       free_poly(p2);
       printf("Ошибка выделения памяти!\n");
       return NULL;
   }
  
   int max_terms = p1->count + p2->count;
   Term *result_terms = malloc(max_terms * sizeof(Term));
   if (!result_terms) {
       free_poly(p1);
       free_poly(p2);
       printf("Ошибка выделения памяти!\n");
       return NULL;
   }
  
   int i = 0, j = 0, k = 0;
  
   while (i < p1->count && j < p2->count) {
       int cmp = cmp_natural_str(p1->terms[i].exp, p2->terms[j].exp);
      
       if (cmp > 0) {
           result_terms[k].exp = strdup(p1->terms[i].exp);
           result_terms[k].coeff = p1->terms[i].coeff;
           i++;
           k++;
       }
       else if (cmp < 0) {
           result_terms[k].exp = strdup(p2->terms[j].exp);
           result_terms[k].coeff = p2->terms[j].coeff;
           j++;
           k++;
       }
       else {
           Q *sum_coeff = ADD_QQ_Q(p1->terms[i].coeff, p2->terms[j].coeff);
          
           if (strcmp(sum_coeff->numerator, "0") != 0) {
               result_terms[k].exp = strdup(p1->terms[i].exp);
               result_terms[k].coeff = sum_coeff;
               k++;
           } else {
               free_Q(sum_coeff); 
           }
           i++;
           j++;
       }
   }
  
   while (i < p1->count) {
       result_terms[k].exp = strdup(p1->terms[i].exp);
       result_terms[k].coeff = p1->terms[i].coeff;
       i++;
       k++;
   }
  
   while (j < p2->count) {
       result_terms[k].exp = strdup(p2->terms[j].exp);
       result_terms[k].coeff = p2->terms[j].coeff;
       j++;
       k++;
   }
  
   for (int t = 0; t < p1->count; t++) {
       p1->terms[t].coeff = NULL;
   }
   for (int t = 0; t < p2->count; t++) {
       p2->terms[t].coeff = NULL;
   }
  
   free_poly(p1);
   free_poly(p2);
  
   if (k == 0) {
       free(result_terms);
      
       Polynomial *result = malloc(sizeof(Polynomial));
       if (!result) {
           printf("Ошибка выделения памяти!\n");
           return NULL;
       }
      
       Term *zero_term = malloc(sizeof(Term));
       if (!zero_term) {
           free(result);
           printf("Ошибка выделения памяти!\n");
           return NULL;
       }
      
       Q *zero = malloc(sizeof(Q));
       zero->numerator = strdup("0");
       zero->denominator = strdup("1");
       zero->nn = 1;
       zero->dm = 1;
      
       zero_term->coeff = zero;
       zero_term->exp = strdup("0");
      
       result->terms = zero_term;
       result->count = 1;
      
       return result;
   }
   Polynomial *result = malloc(sizeof(Polynomial));
   if (!result) {
       for (int t = 0; t < k; t++) {
           free(result_terms[t].exp);
       }
       free(result_terms);
       printf("Ошибка выделения памяти!\n");
       return NULL;
   }
  
   result->terms = result_terms;
   result->count = k;
  
   return result;
}

//Костромицкая Вероника
static void negate_coeff(Q* q) {
    if (!q || !q->numerator || q->numerator[0] == '\0') return;
    if (q->numerator[0] == '-' && q->numerator[1] == '-') {
        size_t len = strlen(q->numerator);
        memmove(q->numerator, q->numerator + 1, len);
        q->nn = len - 1;
    } else {
        size_t len = strlen(q->numerator);
        q->numerator = realloc(q->numerator, len + 2);
        memmove(q->numerator + 1, q->numerator, len + 1);
        q->numerator[0] = '-';
        q->nn = len + 1;
    }
}

//Костромицкая Вероника
Polynomial* SUB_PP_P(Polynomial* P1, Polynomial* P2) {
    if (!P1 || !P2) return NULL;

    Polynomial* res = copy_poly(P1);
    if (!res) return NULL;

    int max_terms = P1->count + P2->count;
    if (max_terms > P1->count) {
        Term* tmp = realloc(res->terms, max_terms * sizeof(Term));
        if (!tmp) { free_poly(res); return NULL; }
        res->terms = tmp;
    }

    int i = 0, j = 0, k = 0;

    while (i < P1->count || j < P2->count) {
        if (i < P1->count && j < P2->count) {
            int cmp = COM_NN_D(P1->terms[i].exp, P2->terms[j].exp);

            if (cmp == 2) {
                res->terms[k] = P1->terms[i];
                i++; k++;
            } else if (cmp == 1) { 
                res->terms[k] = P2->terms[j];
                negate_coeff(res->terms[k].coeff);
                j++; k++;
            } else {
                Q* new_coeff = SUB_QQ_Q(P1->terms[i].coeff, P2->terms[j].coeff);
                if (!new_coeff) { free_poly(res); return NULL; }

                if (!(new_coeff->numerator[0] == '0' && new_coeff->numerator[1] == '\0')) {
                    res->terms[k].coeff = new_coeff;
                    res->terms[k].exp = malloc(strlen(P1->terms[i].exp) + 1);
                    if (res->terms[k].exp) strcpy(res->terms[k].exp, P1->terms[i].exp);
                    k++;
                } else {
                    free_Q(new_coeff);
                }
                i++; j++;
            }
        } else if (i < P1->count) {
            res->terms[k] = P1->terms[i];
            i++; k++;
        } else {
            res->terms[k] = P2->terms[j];
            negate_coeff(res->terms[k].coeff);
            j++; k++;
        }
    }

    if (k == 0) {
        free(res->terms);
        res->terms = NULL;
    } else {
        Term* tmp = realloc(res->terms, k * sizeof(Term));
        if (tmp) res->terms = tmp;
    }

    res->count = k;
    return res;
}

//Осипова Евгения
Polynomial* MUL_PQ_P(Polynomial* p, Q* q){
    if (!p || !q){
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    if (p->count == 0){
        Polynomial* res = malloc(sizeof(Polynomial));
        if (!res){
            printf("Ошибка выделения памяти!\n");
            return NULL;
        }
        res->terms = NULL;
        res->count = 0;
        return res;
    }
    
    Polynomial* res = malloc(sizeof(Polynomial));
    if (!res){
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    
    res->count = p->count;
    res->terms = (Term*)malloc(p->count * sizeof(Term));
    if (!res->terms){
        printf("Ошибка выделения памяти!\n");
        free(res);
        return NULL;
    }
    for (int i = 0; i< res->count; i++){
        res->terms[i].coeff = MUL_QQ_Q(p->terms[i].coeff, q);
        if (! res->terms[i].coeff){
            printf("Ошибка выделения памяти!\n");
            for (int j = 0; j <i; j++){
                free_Q(res->terms[j].coeff);
                free(res->terms[j].exp);
            }
            free(res->terms);
            free(res);
            return NULL;
        }
        
        size_t len_exp = strlen(p->terms[i].exp);
        res->terms[i].exp = (char*)malloc(len_exp+1);
        if (!res->terms[i].exp){
            printf("Ошибка выделения памяти!\n");
            free_Q(res->terms[i].coeff);
            for (int j = 0; j <i; j++){
                free_Q(res->terms[j].coeff);
                free(res->terms[j].exp);
            }
            free(res->terms);
            free(res);
            return NULL;
        }
        
        strcpy(res->terms[i].exp, p->terms[i].exp);
    }
    
    return res;
}

//Итыгилов Архип
Polynomial* MUL_Pxk_P(Polynomial* p, char* k){
    if (POZ_Z_D(k) == -1) return 0;


    Polynomial* res = copy_poly(p);
   
    if (*k == '0') return res;


    for(int i = 0; i < res->count; i++){
        char* new_exp = ADD_NN_N(res->terms[i].exp, k);
        free(res->terms[i].exp);
       
        res->terms[i].exp = new_exp;
    }
    return res;
}

//Богачева Вероника
Q* LED_P_Q(const Polynomial* p) {
    if (!p || !p->terms || p->count == 0) {
        return NULL;
    }

    for (int i = 0; i < p->count; i++) {
        Q *q = p->terms[i].coeff;

        if (strcmp(q->numerator, "0") == 0 ||
            strcmp(q->numerator, "-0") == 0) {
            continue;
        }

        Q *res = malloc(sizeof(Q));
        if (!res) return NULL;

        res->numerator = strdup(q->numerator);
        res->denominator = strdup(q->denominator);

        if (!res->numerator || !res->denominator) {
            free(res->numerator);
            free(res->denominator);
            free(res);
            return NULL;
        }

        res->nn = q->nn;
        res->dm = q->dm;

        return res;
    }

    Q *zero = malloc(sizeof(Q));
    if (!zero) return NULL;

    zero->numerator = strdup("0");
    zero->denominator = strdup("1");

    if (!zero->numerator || !zero->denominator) {
        free(zero->numerator);
        free(zero->denominator);
        free(zero);
        return NULL;
    }

    zero->nn = 1;
    zero->dm = 1;

    return zero;
}

//Новожилова Дарья
int cmp_natural_str(const char *a, const char *b) {
    size_t la = strlen(a), lb = strlen(b);
    if (la != lb) return la - lb;
    return strcmp(a, b);
}

//Новожилова Дарья
char* DEG_P_N(Polynomial *p) {
    if (!p) return NULL;


    char *max_deg = malloc(2);
    if (max_deg) {
        max_deg[0] = '0';
        max_deg[1] = '\0';
    }
    if (!max_deg) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }


    for (int i = 0; i < p->count; i++) {
        char *num = p->terms[i].coeff->numerator;
        if (strcmp(num, "0") == 0 || strcmp(num, "-0") == 0)
            continue;


        if (cmp_natural_str(p->terms[i].exp, max_deg) > 0) {
            free(max_deg);
            size_t len = strlen(p->terms[i].exp);
            max_deg = malloc(len + 1);
            if (!max_deg) {
                printf("Ошибка выделения памяти!\n");
                return NULL;
            }
            strcpy(max_deg, p->terms[i].exp);
        }
    }
    return max_deg;
}

//Колесникова Дарья
Polynomial* DER_P_P(Polynomial *p) {
   if (!p) return NULL;
   if (p->count == 1 && strcmp(p->terms[0].exp, "0") == 0) {
       Polynomial *result = malloc(sizeof(Polynomial));
       if (!result) return NULL;
      
       Term *zero_term = malloc(sizeof(Term));
       Q *zero = malloc(sizeof(Q));
       zero->numerator = strdup("0");
       zero->denominator = strdup("1");
       zero->nn = 1;
       zero->dm = 1;
      
       zero_term->coeff = zero;
       zero_term->exp = strdup("0");
      
       result->terms = zero_term;
       result->count = 1;
       return result;
   }
  
   Term *result_terms = malloc(p->count * sizeof(Term));
   if (!result_terms) {
       printf("Ошибка выделения памяти!\n");
       return NULL;
   }
  
   int k = 0;
  
   for (int i = 0; i < p->count; i++) {
       char *exp = p->terms[i].exp;
       int degree = atoi(exp);
      
       if (degree == 0) {
           continue;
       }
      
       Q *degree_q = malloc(sizeof(Q));
       if (!degree_q) continue;
      
       char degree_str[20];
       sprintf(degree_str, "%d", degree);
       degree_q->numerator = strdup(degree_str);
       degree_q->denominator = strdup("1");
       degree_q->nn = strlen(degree_str);
       degree_q->dm = 1;
      
       Q *new_coeff = MUL_QQ_Q(p->terms[i].coeff, degree_q);
      
       free_Q(degree_q);
      
       int new_degree = degree - 1;
       char new_exp[20];
       sprintf(new_exp, "%d", new_degree);
      
       result_terms[k].exp = strdup(new_exp);
       result_terms[k].coeff = new_coeff;
       k++;
   }
  
   if (k == 0) {
       free(result_terms);
      
       Polynomial *result = malloc(sizeof(Polynomial));
       Term *zero_term = malloc(sizeof(Term));
       Q *zero = malloc(sizeof(Q));
       zero->numerator = strdup("0");
       zero->denominator = strdup("1");
       zero->nn = 1;
       zero->dm = 1;
      
       zero_term->coeff = zero;
       zero_term->exp = strdup("0");
      
       result->terms = zero_term;
       result->count = 1;
       return result;
   }
  
   Term *final_terms = realloc(result_terms, k * sizeof(Term));
   if (!final_terms && k > 0) {
       final_terms = result_terms;
   }
  
   Polynomial *result = malloc(sizeof(Polynomial));
   if (!result) {
       for (int t = 0; t < k; t++) {
           free_Q(final_terms[t].coeff);
           free(final_terms[t].exp);
       }
       free(final_terms);
       printf("Ошибка выделения памяти!\n");
       return NULL;
   }
  
   result->terms = final_terms;
   result->count = k;
  
   return result;
}

//Костромицкая Вероника
Polynomial* MUL_PP_P(Polynomial* P1, Polynomial* P2) {
    if (!P1 || !P2) return NULL;

    if (P1->count == 0 || P2->count == 0) {
        Polynomial* zero = malloc(sizeof(Polynomial));
        if (zero) {
            zero->terms = NULL;
            zero->count = 0;
        }
        return zero;
    }

    Polynomial* res = malloc(sizeof(Polynomial));
    if (!res) return NULL;
    res->terms = NULL;
    res->count = 0;

    for (int i = 0; i < P2->count; i++) {
        Polynomial* temp1 = MUL_PQ_P(P1, P2->terms[i].coeff);
        if (!temp1) {
            free_poly(res);
            return NULL;
        }

        Polynomial* temp2 = MUL_Pxk_P(temp1, P2->terms[i].exp);
        free_poly(temp1); 
        if (!temp2) {
            free_poly(res);
            return NULL;
        }

        Polynomial* new_res = ADD_PP_P(res, temp2);
        free_poly(temp2);
        free_poly(res);
        if (!new_res) return NULL;

        res = new_res;
    }

    return res;
}

//Осипова Евгения
Polynomial* DIV_PP_P(Polynomial* p1, Polynomial* p2){
    if (!p1 || !p2){ printf("Ошибка выделения памяти!\n"); return NULL; }
    
    if (p2->count == 0){
        printf("Ошибка: деление на нулевой многочлен!\n");
        return NULL;
    }
    
    char* deg_1 = DEG_P_N(p1);
    char* deg_2 = DEG_P_N(p2);
    if (!deg_1 || !deg_2) {
        free(deg_1); free(deg_2);
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    
    if (p1->count == 0 || cmp_natural_str(deg_1, deg_2) < 0){ 
        free(deg_1); free(deg_2);
        Polynomial* res = malloc(sizeof(Polynomial));
        if(!res) { printf("Ошибка выделения памяти!\n"); return NULL; }
        
        res->terms = NULL;
        res->count = 0;
        return res; 
    }
    free(deg_1); free(deg_2);
    
   
    Polynomial* R = malloc(sizeof(Polynomial));
    if (!R){ printf("Ошибка выделения памяти!\n"); return NULL; }
    R->count = p1->count;
    R->terms = (Term*)malloc(p1->count * sizeof(Term));
    if (!R->terms){ free(R); printf("Ошибка выделения памяти!\n"); return NULL; }
    
    int i;
    for (i = 0; i < p1->count; i++){
        R->terms[i].coeff = malloc(sizeof(Q));
        if (!R->terms[i].coeff) break;
       
        R->terms[i].coeff->numerator = malloc(strlen(p1->terms[i].coeff->numerator) + 1);
        if (!R->terms[i].coeff->numerator) break;
        strcpy(R->terms[i].coeff->numerator, p1->terms[i].coeff->numerator);
        
        R->terms[i].coeff->denominator = malloc(strlen(p1->terms[i].coeff->denominator) + 1);
        if (!R->terms[i].coeff->denominator) break;
        strcpy(R->terms[i].coeff->denominator, p1->terms[i].coeff->denominator);

        R->terms[i].coeff->nn = p1->terms[i].coeff->nn;
        R->terms[i].coeff->dm = p1->terms[i].coeff->dm;
        
        size_t len = strlen(p1->terms[i].exp);
        R->terms[i].exp = malloc(len + 1);
        if (!R->terms[i].exp) break;
        strcpy(R->terms[i].exp, p1->terms[i].exp);
    }
    
    if (i < p1->count){
        for (int j = 0; j <= i; j++){
            free_Q(R->terms[j].coeff);
            free(R->terms[j].exp);
        }
        free(R->terms); 
        free(R);
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    
    Polynomial* Q = malloc(sizeof(Polynomial));
    if (!Q){ 
        free_poly(R); 
        printf("Ошибка выделения памяти!\n"); 
        return NULL; 
    }
    Q->terms = NULL;
    Q->count = 0;
    
    struct Quotient *lead_R, *lead_p2, *step_coeff;
    while (R->count > 0){
        char* deg_R = DEG_P_N(R);
        char* deg_p2 = DEG_P_N(p2);
        if (!deg_R || !deg_p2 || cmp_natural_str(deg_R, deg_p2) < 0){
            free(deg_R); free(deg_p2);
            break;
        }
        
        char* diff = SUB_NN_N(deg_R, deg_p2);
        free(deg_R); free(deg_p2);
        if (!diff){ free_poly(R); free_poly(Q); return NULL; }
        
        lead_R = R->terms[0].coeff;
        lead_p2 = p2->terms[0].coeff;
        step_coeff = DIV_QQ_Q(lead_R, lead_p2);
        if (!step_coeff){ free(diff); free_poly(R); free_poly(Q); return NULL; }
        
        Polynomial* p2_scaled = MUL_PQ_P(p2, step_coeff);
        if (!p2_scaled){ 
            free_Q(step_coeff); 
            free(diff); free_poly(R); 
            free_poly(Q); return NULL;
        }
        
        Polynomial* p2_shifted = MUL_Pxk_P(p2_scaled, diff);
        free_poly(p2_scaled);
        if (!p2_shifted){ 
            free_Q(step_coeff); 
            free(diff); free_poly(R); 
            free_poly(Q); return NULL; 
        }
        
        Polynomial* R_new = SUB_PP_P(R, p2_shifted);
        free_poly(p2_shifted);
        if (!R_new){ 
            free_Q(step_coeff); 
            free(diff); free_poly(R); 
            free_poly(Q); return NULL; 
        }
        free_poly(R);
        R = R_new;
        
        Polynomial* term = malloc(sizeof(Polynomial));
        if (!term){ free_Q(step_coeff); free(diff); free_poly(R); free_poly(Q); return NULL; }
        term->count = 1;
        term->terms = malloc(sizeof(Term));
        if (!term->terms){ 
            free(term); 
            free_Q(step_coeff); 
            free(diff); free_poly(R); 
            free_poly(Q); 
            return NULL; 
        }
        
        term->terms[0].coeff = step_coeff;
        term->terms[0].exp = diff;
        
        Polynomial* Q_new = ADD_PP_P(Q, term);
        free_poly(term); 
        if (!Q_new){ 
            free_poly(R); 
            free_poly(Q); 
            return NULL; 
        }
        free_poly(Q);
        Q = Q_new;
    }
    
    free_poly(R);
    return Q;
}

//Осипова Евгения
Polynomial* MOD_PP_P(Polynomial* A, Polynomial* B){
    if (!A || !B){ printf("Ошибка выделения памяти!\n"); return NULL; }
    if (B->count == 0){ 
        printf("Ошибка: деление на нулевой многочлен!\n"); 
        return NULL; 
        
    }
    Polynomial* Q = DIV_PP_P(A, B);
    if (!Q) return NULL;
    Polynomial* B_Q = MUL_PP_P(B, Q);
    free_poly(Q); 
    if (!B_Q) return NULL;
    Polynomial* R = SUB_PP_P(A, B_Q);
    free_poly(B_Q);
    
    return R; 
}

//Костромицкая Вероника
Polynomial* GCF_PP_P(Polynomial* A, Polynomial* B) {
    if (!A || !B) return NULL;

    char* deg_B = DEG_P_N(B);
    if (!deg_B) return NULL;

    while (COM_NN_D(deg_B, "0") != 0) {
        Polynomial* R = MOD_PP_P(A, B);
        if (!R) {
            free(deg_B);
            return NULL;
        }

        free_poly(A);

        A = B;
        B = R;

        free(deg_B);

        deg_B = DEG_P_N(B);
        if (!deg_B) return A;
    }

    free_poly(B);
    free(deg_B);

    return A;
}

//Колесникова Дарья
typedef struct {
   Q *multiplier;
   Polynomial *poly;
} MultiplierPoly;


MultiplierPoly* FAC_P_Q(Polynomial *p) {
   if (!p || p->count == 0) return NULL;
  
   MultiplierPoly *result = malloc(sizeof(MultiplierPoly));
   if (!result) return NULL;
  
   char *gcd_num = NULL;
   char *lcm_den = NULL;
   int first = 1;
   int all_zero = 1;
  
   for (int i = 0; i < p->count; i++) {
       Q *coeff = p->terms[i].coeff;
      
       if (strcmp(coeff->numerator, "0") == 0) continue;
      
       all_zero = 0;
      
       char *num = coeff->numerator;
       if (num[0] == '-') num++;
      
       if (first) {
           gcd_num = strdup(num);
       } else {
           char *new_gcd = GCF_NN_N(gcd_num, num);
           free(gcd_num);
           gcd_num = new_gcd;
       }
      
       if (strcmp(coeff->denominator, "1") != 0) {
           if (first) {
               lcm_den = strdup(coeff->denominator);
           } else if (lcm_den) {
               char *new_lcm = LCM_NN_N(lcm_den, coeff->denominator);
               free(lcm_den);
               lcm_den = new_lcm;
           } else {
               lcm_den = strdup(coeff->denominator);
           }
       }
      
       first = 0;
   }
  
   if (all_zero) {
       result->multiplier = malloc(sizeof(Q));
       result->multiplier->numerator = strdup("0");
       result->multiplier->denominator = strdup("1");
       result->multiplier->nn = 1;
       result->multiplier->dm = 1;
      
       result->poly = copy_poly(p);
       return result;
   }
  
   if (!lcm_den) {
       lcm_den = strdup("1");
   }
  
   
   result->multiplier = malloc(sizeof(Q));
   result->multiplier->numerator = strdup(gcd_num);
   result->multiplier->denominator = strdup(lcm_den);
   result->multiplier->nn = strlen(gcd_num);
   result->multiplier->dm = strlen(lcm_den);
  
   result->poly = copy_poly(p);
  
   for (int i = 0; i < result->poly->count; i++) {
       Q *coeff = result->poly->terms[i].coeff;
      
       if (strcmp(coeff->numerator, "0") == 0) continue;
      
       Q *inv = malloc(sizeof(Q));
       inv->numerator = strdup(lcm_den);
       inv->denominator = strdup(gcd_num);
       inv->nn = strlen(lcm_den);
       inv->dm = strlen(gcd_num);
      
       Q *new_coeff = MUL_QQ_Q(coeff, inv);
      
       free_Q(coeff);
       result->poly->terms[i].coeff = new_coeff;
      
       free_Q(inv);
   }
  
   free(gcd_num);
   free(lcm_den);
  
   return result;
}

//Осипова Евгения
Polynomial* NMR_P_P(Polynomial* p){
    if (!p){ printf("Ошибка выделения памяти!\n"); return NULL; }
    if (p->count == 0){
        Polynomial* res = malloc(sizeof(Polynomial));
        if(!res){ printf("Ошибка выделения памяти!\n"); return NULL; }
        res->terms = NULL; res->count = 0;
        return res;
    }

    Polynomial* der = DER_P_P(p);
    if (!der){ printf("Ошибка выделения памяти!\n"); return NULL; }

    if (der->count == 0 || (der->count == 1 && strcmp(der->terms[0].coeff->numerator, "0") == 0)){
        free_poly(der);
        return copy_poly(p);
        
    }

    Polynomial* gcd = GCF_PP_P(p, der);
    free_poly(der);
    if (!gcd){ printf("Ошибка выделения памяти!\n"); return NULL; }

    Polynomial* res = DIV_PP_P(p, gcd);
    free_poly(gcd);
    return res;
}
