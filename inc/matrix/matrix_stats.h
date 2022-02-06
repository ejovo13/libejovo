#pragma once

#include "matrix.h"

// Basic statistic routines that will operate on either vectors or a pair of MatIters

MATRIX_TYPE MatIter_mean(const MatIter __begin, const MatIter __end);

MATRIX_TYPE MatIter_sum_squared(const MatIter __begin, const MatIter __end);

MATRIX_TYPE MatIter_mean_squared(const MatIter __begin, const MatIter __end);

MATRIX_TYPE MatIter_rms(const MatIter __begin, const MatIter __end);

MATRIX_TYPE Vector_iter_sum(const Vector *__v);

MATRIX_TYPE Vector_iter_prod(const Vector *__v);

MATRIX_TYPE Vector_iter_mean(const Vector *__v);

MATRIX_TYPE Vector_iter_mean_squared(const Vector *__v);

MATRIX_TYPE Vector_iter_rms(const Vector *__v);

MATRIX_TYPE Vector_iter_min(const Vector *__v);

MATRIX_TYPE Vector_iter_max(const Vector *__v);