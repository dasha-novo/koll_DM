#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readDigitN.h"

char* read_digN() {
    char buff[10000];
   
    if (fgets(buff, sizeof(buff), stdin) == NULL) {
        printf("Error!\n");
        return NULL;
    }


    int len = strlen(buff);
    if (len > 0 && buff[len - 1] == '\n') {
        buff[len - 1] = '\0';
        len--;
    }


    if (len == 0) {
        printf("Error!\n");
        return NULL;
    }


    if(len == 1 && buff[0] == '0'){
        printf("Not natural number!");
        return NULL;
    }


    char* result = (char*)malloc((len + 1) * sizeof(char));
    if (result == NULL) {
        printf("Memory error!\n");
        return NULL;
    }

    for (int i = 0; i < len; i++) {
        if (isdigit(buff[i])) {
            result[i] = buff[i];
        } else {
            printf("Error! Not a digit!\n");
            free(result);
            return NULL;
        }
    }


    if(result[0] == '0' && result[1] == '0'){
        printf("Enter a number without trailing zeros!\n");
        return NULL;
    }

    result[len] = '\0';
    return result;
}
