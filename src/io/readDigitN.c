#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readDigitN.h"

char* read_digN() {
    char buff[10000];
   
    if (fgets(buff, sizeof(buff), stdin) == NULL) {
        printf("Ошибка при считывании!\n");
        return NULL;
    }


    int len = strlen(buff);
    if (len > 0 && buff[len - 1] == '\n') {
        buff[len - 1] = '\0';
        len--;
    }


    if (len == 0) {
        printf("Ошибка: пустой ввод\n");
        return NULL;
    }

    char* result = (char*)malloc((len + 1) * sizeof(char));
    if (result == NULL) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }

    for (int i = 0; i < len; i++) {
        if (isdigit(buff[i])) {
            result[i] = buff[i];
        } else {
            printf("Ошибка: присутствует недопустимый символ!\n");
            free(result);
            return NULL;
        }
    }


    if((result[0] == '0' && len != 1)){
        printf("Введите число без ведущих нулей!\n");
        return NULL;
    }

    result[len] = '\0';
    return result;
}
