#pragma once

#include "matrix.h"

Matrix *Matrix_runif(size_t __m, size_t __n, double __a, double __b);

Matrix *Matrix_rnorm(size_t __m, size_t __n, double __mean, double __std);

Matrix *Matrix_rexp(size_t __m, size_t __n, double __rate);

Matrix *Matrix_as_stochastic(const Matrix *__m);