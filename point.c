//
// Created by Владислав Сарахан on 18.10.2020.
//
#include "point.h"

void point_construct(struct point *point, const mpz_t mod) {
    mpz_t u, v, up, down, one, down_inv;
    mpz_init(u); mpz_init(v); mpz_init(up); mpz_init(down); mpz_init(one); mpz_init(down_inv);
    mpz_init(point->x); mpz_init(point->z);
    mpz_set_str(u, U_CURVE_ARG, 16);
    mpz_set_str(v, V_CURVE_ARG, 16);
    mpz_set_str(one, "1", 16);
    mpz_add(up, one, v);
    mpz_sub(down, one, v);
    mpz_invert(down_inv, down, mod);
    mpz_mul(point->x, up, down_inv);
    mpz_mod(point->x, point->x, mod);
    mpz_set_str(point->z, "1", 16);
    mpz_mul(down, down, u);
    mpz_invert(down_inv, down, mod);
    mpz_mul(one, up, down_inv);
    mpz_mod(one, one, mod);
    mpz_clear(u); mpz_clear(v); mpz_clear(up); mpz_clear(down); mpz_clear(one);
}

void point_init(struct point *point) {
    mpz_init(point->x); mpz_init(point->z);
    mpz_set_str(point->x, "0", 16); mpz_set_str(point->z, "0", 16);
}

void point_neutral(struct point *point) {
    mpz_init(point->x); mpz_init(point->z);
    mpz_set_str(point->x, "1", 16); mpz_set_str(point->z, "0", 16);
}

void point_is_neutral(struct point *point) {
    struct point neutral;
    point_neutral(&neutral);
    if (!mpz_cmp(point->x, neutral.x) && !mpz_cmp(point->z, neutral.z))
        printf("Point is neutral!\n");
    else
        printf("Point is not neutral!\n");
    point_clear(&neutral);
}

int point_is_equivalent(struct point *op1, struct point *op2) {
    return (!mpz_cmp(op1->x, op2->x) && !mpz_cmp(op1->z, op2->z));
}

void point_add(struct point *rop, const struct point *op1, const struct  point *op2, const struct point *point, const mpz_t mod) {
    mpz_t a, b, c, d, da, cb;
    mpz_init(a); mpz_init(b); mpz_init(c); mpz_init(d); mpz_init(da); mpz_init(cb);
    mpz_add(a, op1->x, op1->z);
    mpz_sub(b, op1->x, op1->z);
    mpz_add(c, op2->x, op2->z);
    mpz_sub(d, op2->x, op2->z);
    mpz_mul(da, d, a);
    mpz_mul(cb, c, b);
    mpz_add(rop->x, da, cb);
    mpz_mul(rop->x, rop->x, rop->x);
    mpz_mul(rop->x, rop->x, point->z);
    mpz_mod(rop->x, rop->x, mod);
    mpz_sub(rop->z, cb, da);
    mpz_mul(rop->z, rop->z, rop->z);
    mpz_mul(rop->z, point->x, rop->z);
    mpz_mod(rop->z, rop->z, mod);
    mpz_clear(a); mpz_clear(b); mpz_clear(c); mpz_clear(d); mpz_clear(da); mpz_clear(cb);
}

void point_double(struct point *rop, const struct point *point, const mpz_t A24, const mpz_t mod) {
    mpz_t xz2, _xz2, w, wa;
    mpz_init(xz2); mpz_init(_xz2); mpz_init(w); mpz_init(wa);
    mpz_add(xz2, point->x, point->z);
    mpz_mul(xz2, xz2, xz2);
    mpz_sub(_xz2, point->x, point->z);
    mpz_mul(_xz2, _xz2, _xz2);
    mpz_sub(w, xz2, _xz2);
    mpz_mul(rop->x, xz2, _xz2);
    mpz_mod(rop->x, rop->x, mod);
    mpz_mul(wa, w, A24);
    mpz_add(wa, xz2, wa);
    mpz_mul(rop->z, w, wa);
    mpz_mod(rop->z, rop->z, mod);
    mpz_clear(xz2); mpz_clear(_xz2); mpz_clear(w); mpz_clear(wa);
}

void point_clear(struct point *point) {
    mpz_clear(point->x); mpz_clear(point->z);
}