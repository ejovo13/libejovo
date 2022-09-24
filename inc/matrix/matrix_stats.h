#ifndef MATRIX_STATS_H
#define MATRIX_STATS_H

#include "matrix.h"

// Basic statistic routines that will operate on either vectors or a pair of MatIters

static inline MATRIX_TYPE TYPED_FN(log)(MATRIX_TYPE x) {
    return log(x);
}

MATRIX_TYPE MATITER_FN(mean)(const MATITER_T __begin, const MATITER_T __end);

MATRIX_TYPE MATITER_FN(sum_squared)(const MATITER_T __begin, const MATITER_T __end);

MATRIX_TYPE MATITER_FN(mean_squared)(const MATITER_T __begin, const MATITER_T __end);

MATRIX_TYPE MATITER_FN(rms)(const MATITER_T __begin, const MATITER_T __end);

MATRIX_TYPE MATITER_FN(var)(const MATITER_T __begin, const MATITER_T __end);

MATRIX_TYPE MATITER_FN(std)(const MATITER_T __begin, const MATITER_T __end);

MATRIX_TYPE VECTOR_FN(iter_sum)(const Vector *__v);

MATRIX_TYPE VECTOR_FN(iter_prod)(const Vector *__v);

MATRIX_TYPE VECTOR_FN(iter_mean)(const Vector *__v);

MATRIX_TYPE VECTOR_FN(iter_mean_squared)(const Vector *__v);

MATRIX_TYPE VECTOR_FN(iter_rms)(const Vector *__v);

MATRIX_TYPE VECTOR_FN(iter_min)(const Vector *__v);

MATRIX_TYPE VECTOR_FN(iter_max)(const Vector *__v);

MATRIX_TYPE VECTOR_FN(iter_var)(const Vector *__v);

MATRIX_TYPE VECTOR_FN(iter_std)(const Vector *__v);

MATRIX_TYPE MATRIX_FN(iter_sum)(const MATRIX_T *__m);

MATRIX_TYPE MATRIX_FN(iter_prod)(const MATRIX_T *__m);

MATRIX_TYPE MATRIX_FN(iter_mean)(const MATRIX_T *__m);

MATRIX_TYPE MATRIX_FN(iter_mean_squared)(const MATRIX_T *__m);

MATRIX_TYPE MATRIX_FN(iter_rms)(const MATRIX_T *__m);

MATRIX_TYPE MATRIX_FN(iter_min)(const MATRIX_T *__m);

MATRIX_TYPE MATRIX_FN(iter_max)(const MATRIX_T *__m);

MATRIX_TYPE MATRIX_FN(iter_var)(const MATRIX_T *__m);

MATRIX_TYPE MATRIX_FN(iter_std)(const MATRIX_T *__m);

typedef MATRIX_TYPE (* mat_iter_fn) (const MATITER_T, const MATITER_T);

MATRIX_TYPE MATRIX_FN(iterate)(const MATRIX_T *__m, mat_iter_fn fn);

/**========================================================================
 *!                           Typed functions
 *========================================================================**/

MATRIX_TYPE TYPED_FN(mean)(const MATRIX_T *__m);

MATRIX_TYPE TYPED_FN(sum)(const MATRIX_T *__m);

MATRIX_TYPE TYPED_FN(std)(const MATRIX_T *__m);

MATRIX_TYPE TYPED_FN(var)(const MATRIX_T *__m);

MATRIX_TYPE TYPED_FN(min)(const MATRIX_T *__m);

MATRIX_TYPE TYPED_FN(max)(const MATRIX_T *__m);

MATRIX_TYPE TYPED_FN(rms)(const MATRIX_T *__m);

MATRIX_TYPE TYPED_FN(mean_squared)(const MATRIX_T *__m);

MATRIX_TYPE TYPED_FN(cov)(const MATRIX_T *__x, const MATRIX_T *__y);

MATRIX_TYPE TYPED_FN(prod)(const MATRIX_T *__m);

MATRIX_TYPE TYPED_FN(cor)(const MATRIX_T *__x, const MATRIX_T *__y);

// central moment
MATRIX_TYPE TYPED_FN(cmoment)(const Vector *__v, int __k);

// raw moment
MATRIX_TYPE TYPED_FN(rmoment)(const Vector *__v, int __k);

Vector *TYPED_FN(linear_regression)(const Vector *__x, const Vector *__y);

Vector *TYPED_FN(loglog_regression)(const Vector *__x, const Vector *__y);

Vector *TYPED_FN(least_squares)(const Vector *__x, const Vector *__y, int degree);

MATRIX_T *TYPED_FN(runif)(int n, double a, double b);

MATRIX_T *TYPED_FN(runif_gen)(int n, double a, double b, RNG_FN rng_fn);

#endif