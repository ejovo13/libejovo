#pragma once

#include "matrix.h"

// Basic statistic routines that will operate on either vectors or a pair of MatIters

MATRIX_TYPE MatIter_mean(const MatIter __begin, const MatIter __end);

MATRIX_TYPE MatIter_sum_squared(const MatIter __begin, const MatIter __end);

MATRIX_TYPE MatIter_mean_squared(const MatIter __begin, const MatIter __end);

MATRIX_TYPE MatIter_rms(const MatIter __begin, const MatIter __end);

MATRIX_TYPE MatIter_var(const MatIter __begin, const MatIter __end);

MATRIX_TYPE MatIter_std(const MatIter __begin, const MatIter __end);

MATRIX_TYPE Vector_iter_sum(const Vector *__v);

MATRIX_TYPE Vector_iter_prod(const Vector *__v);

MATRIX_TYPE Vector_iter_mean(const Vector *__v);

MATRIX_TYPE Vector_iter_mean_squared(const Vector *__v);

MATRIX_TYPE Vector_iter_rms(const Vector *__v);

MATRIX_TYPE Vector_iter_min(const Vector *__v);

MATRIX_TYPE Vector_iter_max(const Vector *__v);

MATRIX_TYPE Vector_iter_var(const Vector *__v);

MATRIX_TYPE Vector_iter_std(const Vector *__v);

MATRIX_TYPE Matrix_iter_sum(const Matrix *__m);

MATRIX_TYPE Matrix_iter_prod(const Matrix *__m);

MATRIX_TYPE Matrix_iter_mean(const Matrix *__m);

MATRIX_TYPE Matrix_iter_mean_squared(const Matrix *__m);

MATRIX_TYPE Matrix_iter_rms(const Matrix *__m);

MATRIX_TYPE Matrix_iter_min(const Matrix *__m);

MATRIX_TYPE Matrix_iter_max(const Matrix *__m);

MATRIX_TYPE Matrix_iter_var(const Matrix *__m);

MATRIX_TYPE Matrix_iter_std(const Matrix *__m);

typedef MATRIX_TYPE (* mat_iter_fn) (const MatIter, const MatIter);

MATRIX_TYPE Matrix_iterate(const Matrix *__m, mat_iter_fn fn);

MATRIX_TYPE mean(const Matrix *__m);

MATRIX_TYPE sum(const Matrix *__m);

MATRIX_TYPE std(const Matrix *__m);

MATRIX_TYPE var(const Matrix *__m);

MATRIX_TYPE min(const Matrix *__m);

MATRIX_TYPE max(const Matrix *__m);

MATRIX_TYPE rms(const Matrix *__m);

MATRIX_TYPE mean_squared(const Matrix *__m);

MATRIX_TYPE cov(const Matrix *__x, const Matrix *__y);

MATRIX_TYPE prod(const Matrix *__m);

MATRIX_TYPE cor(const Matrix *__x, const Matrix *__y);

// central moment
MATRIX_TYPE cmoment(const Vector *__v, int __k);

// raw moment
MATRIX_TYPE rmoment(const Vector *__v, int __k);

Vector *linear_regression(const Vector *__x, const Vector *__y);

Vector *logistical_regression(const Vector *__x, const Vector *__y);

Matrix *runif(int n, double a, double b);

Matrix *runif_gen(int n, double a, double b, RNG_FN rng_fn);