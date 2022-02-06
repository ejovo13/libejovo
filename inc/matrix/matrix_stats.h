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