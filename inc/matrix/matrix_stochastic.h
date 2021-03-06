#pragma once

#include "matrix.h"

Matrix *Matrix_runif(size_t __m, size_t __n, double __a, double __b);

Matrix *Matrix_rnorm(size_t __m, size_t __n, double __mean, double __std);

Matrix *as_stochastic(Matrix *__m);

Matrix *Matrix_rexp(size_t __m, size_t __n, double __rate);

Matrix *Matrix_as_stochastic(const Matrix *__m);

// Create a new Stochastic matrix whose elements come from a uniform distribution
Matrix *Stochastic_runif(size_t __n, double __a, double __b);

Matrix *Stochastic_rnorm(size_t __n, double __mean, double __std);

Matrix *Stochastic_rexp(size_t __n, double __rate);

Vector *Vector_prob_unif(size_t __n);