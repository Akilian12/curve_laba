//
// Created by Владислав Сарахан on 18.10.2020.
//
#include <gmp.h>
#include <stdio.h>

#ifndef CURVE_LABA_POINT_H
#define CURVE_LABA_POINT_H

#define U_CURVE_ARG "0D"
#define V_CURVE_ARG "60CA1E32AA475B348488C38FAB07649CE7EF8DBE87F22E81F92B2592DBA300E7"

struct point{
    mpz_t x, z;
};

void point_construct(struct point *point, const mpz_t mod);
void point_add(struct point *rop, const struct point *op1, const struct  point *op2, const struct point *point, const mpz_t mod);
void point_double(struct point *rop, const struct point *point, const mpz_t A24, const mpz_t mod);
void point_init(struct point *point);
void point_neutral(struct point *point);
void point_is_neutral(struct point *point);
int point_is_equivalent(struct point *op1, struct point *op2);
void point_clear(struct point *point);

#endif //CURVE_LABA_POINT_H
