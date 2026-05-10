#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readDigZ.h"

#define MAX 100000

char* read_digZ() {
    char buff[MAX];
   
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
        if(i == 0 && buff[i] == '-'){
            result[i] = buff[i];
        }
        else if (isdigit(buff[i])) {
            result[i] = buff[i];
        } else {
            printf("Ошибка: присутствует недопустимый символ!\n");
            free(result);
            return NULL;
        }
    }

    if (len == 2 && result[0] == '-' && result[1] == '0'){
        result[0] = '0';
        result[1] = '\0';
        len--;
    }


    if((result[0] == '0' && len > 1) || (result[0] == '-' && result[1] == '0' && len >2)){
        printf("Введите число без ведущих нулей!\n");
        return NULL;
    }


    result[len] = '\0';


    return result;
}
