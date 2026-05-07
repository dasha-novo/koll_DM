#ifndef N_H
#define N_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int COM_NN_D(char* x, char* y);
char* NZER_N_B(char* x);
char* ADD_1N_N(const char* x);
char* ADD_NN_N(const char* a, const char* b);
char* SUB_NN_N(char* a, char* b);
char* MUL_ND_N(const char* num, char digit_char);
char* MUL_Nk_N(char* a, char* k);
char* SUB_NDN_N(char* a, char* b, char k);
char* MUL_NN_N(const char* a, const char* b);
char* DIV_NN_N(char* A, char* B);
char* MOD_NN_N(char* a, char* b);
char* GCF_NN_N(char* a, char* b);
char* LCM_NN_N(char* a, char* b);

#endif