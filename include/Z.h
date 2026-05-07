#ifndef Z_H
#define Z_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ABS_Z_N(char* x);
int POZ_Z_D(char* x);
char* MUL_ZM_Z(const char* num);
char* TRANS_Z_N(const char* num);
char* ADD_ZZ_Z(char* a, char* b);
char* SUB_ZZ_Z(char* a, char* b);
char* MUL_ZZ_Z(const char* a, const char* b);
char* DIV_ZZ_Z(char* x, char* y);
char* MOD_ZZ_Z(char* x, char* y);

#endif