
#include "curve.h"

int main() {
    //vars
    mpz_t max_random, k, q, one, k1, k2, k1k2, k1_k2, invert;
    gmp_randstate_t rstate;
    unsigned long seed;
    struct point point, result, result1, result2, result3;
    struct curve curve;
    //inits
    mpz_init(max_random); mpz_init(k); mpz_init(one); mpz_init(k1); mpz_init(k2); mpz_init(invert); mpz_init(k1k2); mpz_init(k1_k2); mpz_init(q);
    mpz_set_str(max_random, M_CURVE_ARG, 16);
    mpz_set_str(q, Q_CURVE_ARG, 16);
    gmp_randinit_mt(rstate);
    gmp_randseed_ui(rstate, seed);
    mpz_urandomm(k, rstate, max_random);
    mpz_urandomm(k1, rstate, max_random);
    mpz_urandomm(k2, rstate, max_random);
    mpz_add(k1k2, k1, k2);
    mpz_sub(k1_k2, k1, k2);
    mpz_abs(k1_k2, k1_k2);
    curve_construct(&curve);
    point_construct(&point, curve.p);
    point_init(&result); point_init(&result1); point_init(&result2); point_init(&result3);
    mpz_set_str(one, "1", 16);

    //3.1
    printf("Start point:\n");
    gmp_printf("x = %Zd \n", point.x);
    gmp_printf("z = %Zd \n", point.z);

    //3.2
    gmp_printf("\nk = %Zd \n", k);

    //4.1
    curve_ladder(&result, &point, &curve, k);
    printf("\n[k]P:\n");
    gmp_printf("x = %Zd \n", result.x);
    gmp_printf("z = %Zd \n", result.z);
    curve_check_point(&curve, &result);

    //4.2
    curve_ladder(&result, &point, &curve, q);
    printf("\n[q]P: ");
    point_is_neutral(&result);

    //4.3
    mpz_add(q, q, one);
    curve_ladder(&result1, &point, &curve, q);
    mpz_sub(q, q, one); mpz_sub(q, q, one);
    curve_ladder(&result2, &point, &curve, q);

    if (point_is_equivalent(&result1, &result2) && point_is_equivalent(&result1, &point))
        printf("\n[q + 1]P = P and [q - 1]P = -P\n");
    else
        printf("\n[q + 1]P != P and [q - 1]P = -P\n");

    //4.4
    gmp_printf("\nk1 = %Zd \n", k1);
    gmp_printf("k2 = %Zd \n", k2);
    curve_ladder(&result1, &point, &curve, k1);
    curve_ladder(&result2, &point, &curve, k2);
    curve_ladder(&result3, &point, &curve, k1_k2);
    curve_ladder(&result, &point, &curve, k1k2);
    point_add(&result1, &result1, &result2, &result3, curve.p);
    if (mpz_sgn(result1.z)){
        mpz_invert(invert, result1.z, curve.p);
        mpz_mul(result1.x, result1.x, invert);
        mpz_mod(result1.x, result1.x, curve.p);
        mpz_mul(result1.z, result1.z, invert);
        mpz_mod(result1.z, result1.z, curve.p);
    } else{
        mpz_invert(invert, result1.x, curve.p);
        mpz_mul(result1.x, result1.x, invert);
        mpz_mod(result1.x, result.x, curve.p);
        mpz_init_set(result1.z, result1.z);
    }
    if (point_is_equivalent(&result1, &result))
        printf("[k1]P + [k2]P = [k1 + k2]P\n");
    else
        printf("[k1]P + [k2]P != [k1 + k2]P\n");

    //clear
    mpz_clear(max_random); mpz_clear(k); mpz_clear(one); mpz_clear(k1); mpz_clear(k2); mpz_clear(invert); mpz_clear(k1k2); mpz_clear(k1_k2); mpz_clear(q);
    curve_clear(&curve);
    point_clear(&point); point_clear(&result); point_clear(&result1); point_clear(&result2); point_clear(&result3);

    return 0;
}