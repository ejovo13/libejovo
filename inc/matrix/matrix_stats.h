#pragma once

#include "matrix.h"

// Basic statistic routines that will operate on either vectors or a pair of MatIters

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

MATRIX_TYPE mean(const MATRIX_T *__m);

MATRIX_TYPE sum(const MATRIX_T *__m);

MATRIX_TYPE std(const MATRIX_T *__m);

MATRIX_TYPE var(const MATRIX_T *__m);

MATRIX_TYPE min(const MATRIX_T *__m);

MATRIX_TYPE max(const MATRIX_T *__m);

MATRIX_TYPE rms(const MATRIX_T *__m);

MATRIX_TYPE mean_squared(const MATRIX_T *__m);

MATRIX_TYPE cov(const MATRIX_T *__x, const MATRIX_T *__y);

MATRIX_TYPE prod(const MATRIX_T *__m);

MATRIX_TYPE cor(const MATRIX_T *__x, const MATRIX_T *__y);

// central moment
MATRIX_TYPE cmoment(const Vector *__v, int __k);

// raw moment
MATRIX_TYPE rmoment(const Vector *__v, int __k);

Vector *linear_regression(const Vector *__x, const Vector *__y);

Vector *loglog_regression(const Vector *__x, const Vector *__y);

Vector *least_squares(const Vector *__x, const Vector *__y, int degree);



MATRIX_T *runif(int n, double a, double b);

MATRIX_T *runif_gen(int n, double a, double b, RNG_FN rng_fn);