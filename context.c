#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "context.h"

Context* create_context() {
    Context* ctx = (Context*)malloc(sizeof(Context));
    if (!ctx) return NULL;
    
    memset(ctx, 0, sizeof(Context));
    
    return ctx;
}

void clear_naturals(Context* ctx) {
    if (!ctx) return;
    if (ctx->natural1) { free(ctx->natural1); ctx->natural1 = NULL; }
    if (ctx->natural2) { free(ctx->natural2); ctx->natural2 = NULL; }
    ctx->has_natural1 = 0;
    ctx->has_natural2 = 0;
}

void clear_integers(Context* ctx) {
    if (!ctx) return;
    if (ctx->integer1) { free(ctx->integer1); ctx->integer1 = NULL; }
    if (ctx->integer2) { free(ctx->integer2); ctx->integer2 = NULL; }
    ctx->has_integer1 = 0;
    ctx->has_integer2 = 0;
}

void clear_rationals(Context* ctx) {
    if (!ctx) return;
    if (ctx->rational1) { free_Q(ctx->rational1); ctx->rational1 = NULL; }
    if (ctx->rational2) { free_Q(ctx->rational2); ctx->rational2 = NULL; }
    ctx->has_rational1 = 0;
    ctx->has_rational2 = 0;
}

void clear_polynomials(Context* ctx) {
    if (!ctx) return;
    if (ctx->polynom1) { free_poly(ctx->polynom1); ctx->polynom1 = NULL; }
    if (ctx->polynom2) { free_poly(ctx->polynom2); ctx->polynom2 = NULL; }
    ctx->has_polynom1 = 0;
    ctx->has_polynom2 = 0;
}

void clear_all(Context* ctx) {
    clear_naturals(ctx);
    clear_integers(ctx);
    clear_rationals(ctx);
    clear_polynomials(ctx);
    printf("Память очищена.\n");
}

void print_context_status(const Context* ctx) {
    printf("  Натуральные: ");
    if (ctx->has_natural1) {
        printf("1-е [%s]", ctx->natural1);
        if (ctx->has_natural2)
            printf(", 2-е [%s]", ctx->natural2);
        else
            printf(", 2-е: нужно ввести");
    } else {
        printf("не введены");
    }
    printf("\n");
    
    printf("  Целые:       ");
    if (ctx->has_integer1) {
        printf("1-е [%s]", ctx->integer1);
        if (ctx->has_integer2)
            printf(", 2-е [%s]", ctx->integer2);
        else
            printf(", 2-е: нужно ввести");
    } else {
        printf(" не введены");
    }
    printf("\n");
    
    printf("  Дроби:       ");
    if (ctx->has_rational1) {
        printf("1-я [%s/%s]", 
               ctx->rational1->numerator, 
               ctx->rational1->denominator);
        if (ctx->has_rational2)
            printf(", 2-я [%s/%s]", 
                   ctx->rational2->numerator, 
                   ctx->rational2->denominator);
        else
            printf(", 2-я: нужно ввести");
    } else {
        printf(" не введены");
    }
    printf("\n");
    
    printf("  Многочлены:  ");
    if (ctx->has_polynom1) {
        printf("1-й [степень %s]", 
               ctx->polynom1->count > 0 ? 
               ctx->polynom1->terms[0].exp : "?");
        if (ctx->has_polynom2)
            printf(", 2-й [степень %s]", 
                   ctx->polynom2->count > 0 ? 
                   ctx->polynom2->terms[0].exp : "?");
        else
            printf(", 2-й: нужно ввести");
    } else {
        printf(" не введены");
    }
    printf("\n");
}

void free_context(Context* ctx) {
    if (!ctx) return;
    
    clear_naturals(ctx);
    clear_integers(ctx);
    clear_rationals(ctx);
    clear_polynomials(ctx);
    
    free(ctx);
}