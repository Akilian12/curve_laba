//
// Created by Владислав Сарахан on 18.10.2020.
//
#include <gmp.h>
#include <stdio.h>
#include "point.h"

#ifndef CURVE_LABA_CURVE_H
#define CURVE_LABA_CURVE_H


#define P_CURVE_ARG "00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD97"
#define E_CURVE_ARG "01"
#define D_CURVE_ARG "0605F6B7C183FA81578BC39CFAD518132B9DF62897009AF7E522C32D6DC7BFFB"
#define M_CURVE_ARG "01000000000000000000000000000000003F63377F21ED98D70456BD55B0D8319C"
#define Q_CURVE_ARG "400000000000000000000000000000000FD8CDDFC87B6635C115AF556C360C67"

struct curve{
    mpz_t A, B, A24, p;
};

void curve_construct(struct curve *cur);
void curve_ladder(struct point *rop, const struct point *point, const struct curve *curve, mpz_t power);
void curve_check_point(const struct point *point, const struct curve *curve);
void curve_clear(struct curve *curve);

#endif //CURVE_LABA_CURVE_H
