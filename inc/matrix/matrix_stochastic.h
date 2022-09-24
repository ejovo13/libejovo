#pragma once

#include "matrix.h"

MATRIX_T *MATRIX_FN(runif)(size_t __m, size_t __n, double __a, double __b);

MATRIX_T *MATRIX_FN(rnorm)(size_t __m, size_t __n, double __mean, double __std);

MATRIX_T *as_stochastic(MATRIX_T *__m);

// make it so the rows sum up to 1
MATRIX_T *as_row_stochastic(MATRIX_T *__m);

// modify a matrix in place so that the columns sum up to 1
MATRIX_T *as_col_stochastic(MATRIX_T *__m);

MATRIX_T *as_doubly_stochastic(MATRIX_T *__m);

// Try and implement a fancy algorithm to compute a doubly stochastic matrix.
MATRIX_T *as_doubly_stochastic_DEPRECATED(MATRIX_T *__m);

MATRIX_T *MATRIX_FN(rexp)(size_t __m, size_t __n, double __rate);

MATRIX_T *MATRIX_FN(as_stochastic)(const MATRIX_T *__m);

// Create a new Stochastic matrix whose elements come from a uniform distribution
MATRIX_T *Stochastic_runif(size_t __n, double __a, double __b);

MATRIX_T *Stochastic_rnorm(size_t __n, double __mean, double __std);

MATRIX_T *Stochastic_rexp(size_t __n, double __rate);

Vector *VECTOR_FN(prob_unif)(size_t __n);


/**========================================================================
 *!                           Utility functions
 *========================================================================**/
Vector *compute_row_sums(const MATRIX_T *__m);

Vector *compute_col_sums(const MATRIX_T *__m);