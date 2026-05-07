#ifndef READ_DIGIT_Q_H
#define READ_DIGIT_Q_H

typedef struct Quotient {
    char* numerator;
    char* denominator;
    int nn;
    int dm;
} Q;

Q* read_digQ();
void free_Q(Q* q);

#endif