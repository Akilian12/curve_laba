//
// Created by Владислав Сарахан on 18.10.2020.
//
#include "curve.h"

void curve_construct(struct curve *cur) {
    mpz_t e, d, up, up_mul, down, constanta;
    mpz_init(e); mpz_init(d); mpz_init(up); mpz_init(up_mul); mpz_init(down); mpz_init(constanta);
    mpz_init(cur->A); mpz_init(cur->B); mpz_init(cur->p); mpz_init(cur->A24);
    mpz_set_str(e, E_CURVE_ARG, 16);
    mpz_set_str(d, D_CURVE_ARG, 16);
    mpz_set_str(cur->p, P_CURVE_ARG, 16);
    mpz_set_str(constanta, "4", 16);
    mpz_add(up, e, d);
    mpz_sub(down, e, d);
    mpz_invert(down, down, cur->p);
    mpz_mul(cur->B, constanta, down);
    mpz_mod(cur->B, cur->B, cur->p);
    mpz_set_str(constanta, "2", 16);
    mpz_mul(up_mul, constanta, up);
    mpz_mul(cur->A, up_mul, down);
    mpz_mod(cur->A, cur->A, cur->p);
    mpz_sub(up, cur->A, constanta);
    mpz_set_str(constanta, "4", 16);
    mpz_invert(down, constanta, cur->p);
    mpz_mul(cur->A24, up, down);
    mpz_mod(cur->A24, cur->A24, cur->p);
    mpz_clear(e); mpz_clear(d); mpz_clear(up); mpz_clear(up_mul); mpz_clear(down); mpz_clear(constanta);
}

void curve_ladder(struct point *rop, const struct point *point, const struct curve *curve, mpz_t power){
    int size = mpz_sizeinbase(power, 2);
    mpz_t invert;
    mpz_init(invert);
    struct point q, r;
    point_neutral(&q);
    mpz_init_set(r.x, point->x);
    mpz_init_set(r.z, point->z);
    for (int i = size - 1; i >= 0; i--){
        if(mpz_tstbit(power, i)){
            point_add(&q, &q, &r, point, curve->p);
            point_double(&r, &r, curve->A24, curve->p);
        } else{
            point_add(&r, &r, &q, point, curve->p);
            point_double(&q, &q, curve->A24, curve->p);
        }
    }
    if (mpz_sgn(q.z)){
        mpz_invert(invert, q.z, curve->p);
        mpz_mul(rop->x, q.x, invert);
        mpz_mod(rop->x, rop->x, curve->p);
        mpz_mul(rop->z, q.z, invert);
        mpz_mod(rop->z, rop->z, curve->p);
    } else{
        mpz_invert(invert, q.x, curve->p);
        mpz_mul(rop->x, q.x, invert);
        mpz_mod(rop->x, rop->x, curve->p);
        mpz_init_set(rop->z, q.z);
    }
    mpz_clear(invert);
    point_clear(&q); point_clear(&r);
}

void curve_check_point(const struct point *point, const struct curve *curve) {
    mpz_t res, x3, ax, invert;
    mpz_init(res); mpz_init(x3); mpz_init(ax); mpz_init(invert);
    mpz_pow_ui(x3, point->x, 3);
    mpz_mul(ax, point->x, point->x);
    mpz_mul(ax, curve->A, ax);
    mpz_add(res, x3, ax);
    mpz_add(res, point->x, res);
    mpz_invert(invert, curve->B, curve->p);
    mpz_mul(res, res, invert);
    mpz_mod(res, res, curve->p);
    if (mpz_jacobi(res, curve->p))
        printf("On curve!!!\n");
    else
        printf("Is not on curve!!!\n");
    mpz_clear(res); mpz_clear(x3); mpz_clear(ax); mpz_clear(invert);
}

void curve_clear(struct curve *curve) {
    mpz_clear(curve->A); mpz_clear(curve->B); mpz_clear(curve->p); mpz_clear(curve->A24);
}