#ifndef Q_H
#define Q_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readDigitQ.h"

char* INT_Q_B(Q* q);
Q* TRANS_Z_Q(const char* num);
char* TRANS_Q_Z(const Q* q);
Q* RED_Q_Q(Q* frac);
Q* ADD_QQ_Q(Q* frac1, Q* frac2);
Q* SUB_QQ_Q(Q* a, Q* b);
Q* MUL_QQ_Q(Q* Q1, Q* Q2);
Q* DIV_QQ_Q(Q* Q1, Q* Q2);

#endif