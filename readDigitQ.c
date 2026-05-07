#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readDigitQ.h"

Q* read_digQ() {
   
    char buff[10000*2];
    if (fgets(buff, sizeof(buff), stdin) == NULL) {
        printf("Error!\n");
        return NULL;
    }
   
    int len = strlen(buff);
    if (len > 0 && buff[len - 1] == '\n') {
        buff[len - 1] = '\0';
        len--;
    }
   
    char* slash = strchr(buff, '/');
    if (slash == NULL) {
        printf("Error! No '/'!\n");
        return NULL;
    }
   
    *slash = '\0';
    char* num_str = buff;
    char* den_str = slash + 1;
   
    if (strlen(num_str) == 0 || strlen(den_str) == 0) {
        printf("Error! Empty numerator or denominator!\n");
        return NULL;
    }
   
    char* numerator = malloc(strlen(num_str) + 1);
    char* denominator = malloc(strlen(den_str) + 1);
   
    if (!numerator || !denominator) {
        free(numerator);
        free(denominator);
        printf("Memory error!\n");
        return NULL;
    }
   
    strcpy(numerator, num_str);
    strcpy(denominator, den_str);


    for (int i = 0; i < strlen(numerator); i++) {
        if (!isdigit(numerator[i]) && !(i == 0 && numerator[i] == '-')) {
            printf("Error! Not a digit!\n");
            free(numerator);
            free(denominator);
            return NULL;
        }
    }
   
    for (int i = 0; i < strlen(denominator); i++) {
        if (!isdigit(denominator[i])) {
            printf("Error! Not a digit!\n");
            free(numerator);
            free(denominator);
            return NULL;
        }
    }
   
    if (strlen(denominator) == 1 && denominator[0] == '0') {
        printf("Error! Denominator cannot be zero!\n");
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
