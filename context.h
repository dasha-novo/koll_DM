#ifndef CONTEXT_H
#define CONTEXT_H

#include "readDigitQ.h"
#include "readPoly.h"

typedef struct {
    char* natural1;
    char* natural2;
    
    char* integer1;
    char* integer2;
    
    Q* rational1;
    Q* rational2;
    
    Polynomial* polynom1;
    Polynomial* polynom2;
    
    int has_natural1;
    int has_natural2;
    int has_integer1;
    int has_integer2;
    int has_rational1;
    int has_rational2;
    int has_polynom1;
    int has_polynom2;
} Context;

Context* create_context();
void free_context(Context* ctx);
void print_context_status(const Context* ctx);
void clear_all(Context* ctx);    
void clear_naturals(Context* ctx);
void clear_integers(Context* ctx);
void clear_rationals(Context* ctx);
void clear_polynomials(Context* ctx);

#endif