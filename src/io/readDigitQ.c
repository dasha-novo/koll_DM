#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readDigitQ.h"

Q* read_digQ() {
   
    char buff[10000*2];
    if (fgets(buff, sizeof(buff), stdin) == NULL) {
        printf("Ошибка при считывании\n");
        return NULL;
    }
   
    int len = strlen(buff);
    if (len > 0 && buff[len - 1] == '\n') {
        buff[len - 1] = '\0';
        len--;
    }
   
    char* slash = strchr(buff, '/');
    if (slash == NULL) {
        printf("Ошибка: отсутствует знак '/'\n");
        return NULL;
    }
   
    *slash = '\0';
    char* num_str = buff;
    char* den_str = slash + 1;
   
    if (strlen(num_str) == 0 || strlen(den_str) == 0) {
        printf("Ошибка: пустой числитель или знаменатель\n");
        return NULL;
    }
   
    char* numerator = malloc(strlen(num_str) + 1);
    char* denominator = malloc(strlen(den_str) + 1);
   
    if (!numerator || !denominator) {
        free(numerator);
        free(denominator);
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
   
    strcpy(numerator, num_str);
    strcpy(denominator, den_str);


    for (size_t i = 0; i < strlen(numerator); i++) { //заменили int на size_t
        if (!isdigit(numerator[i]) && !(i == 0 && numerator[i] == '-')) {
            printf("Ошибка: присутствует недопустимый символ!\n");
            free(numerator);
            free(denominator);
            return NULL;
        }
    }
   
    for (size_t i = 0; i < strlen(denominator); i++) { //заменили int на size_t
        if (!isdigit(denominator[i])) {
            printf("Ошибка: присутствует недопустимый символ!\n");
            free(numerator);
            free(denominator);
            return NULL;
        }
    }
   
    if (strlen(denominator) == 1 && denominator[0] == '0') {
        printf("ошибка знаменатель не может быть равен нулю!\n");
        free(numerator);
        free(denominator);
        return NULL;
    }
   
    Q* q_number = malloc(sizeof(Q));
    if (!q_number) {
        free(numerator);
        free(denominator);
        return NULL;
    }
   
    q_number->numerator = numerator;
    q_number->denominator = denominator;
    q_number->nn = strlen(numerator);
    q_number->dm = strlen(denominator);
   
    return q_number;
}
void free_Q(Q* q) {
    if (q) {
        if (q->numerator) free(q->numerator);
        if (q->denominator) free(q->denominator);
        free(q);
    }
}
