#ifndef MATRIX_STOCHASTIC_H
#define MATRIX_STOCHASTIC_H

#include "matrix.h"

TYPED(Matrix) *TYPED(Matrix_runif)(size_t __m, size_t __n, MATRIX_TYPE __a, MATRIX_TYPE __b);

TYPED(Matrix) *TYPED(Matrix_rnorm)(size_t __m, size_t __n, MATRIX_TYPE __mean, MATRIX_TYPE __std);

TYPED(Matrix) *TYPED(as_stochastic)(TYPED(Matrix) *__m);

// make it so the rows sum up to 1
TYPED(Matrix) *TYPED(as_row_stochastic)(TYPED(Matrix) *__m);

// modify a matrix in place so that the columns sum up to 1
TYPED(Matrix) *TYPED(as_col_stochastic)(TYPED(Matrix) *__m);

TYPED(Matrix) *TYPED(as_doubly_stochastic)(TYPED(Matrix) *__m);

// Try and implement a fancy algorithm to compute a doubly stochastic matrix.
TYPED(Matrix) *TYPED(as_doubly_stochastic_DEPRECATED)(TYPED(Matrix) *__m);

TYPED(Matrix) *TYPED(Matrix_rexp)(size_t __m, size_t __n, double __rate);

TYPED(Matrix) *TYPED(Matrix_as_stochastic)(const TYPED(Matrix) *__m);

// Create a new Stochastic matrix whose elements come from a uniform distribution
TYPED(Matrix) *TYPED(Stochastic_runif)(size_t __n, double __a, double __b);

TYPED(Matrix) *TYPED(Stochastic_rnorm)(size_t __n, double __mean, double __std);

TYPED(Matrix) *TYPED(Stochastic_rexp)(size_t __n, double __rate);

 TYPED(Vector)*TYPED(Vector_prob_unif)(size_t __n);


/**========================================================================
 *!                           Utility functions
 *========================================================================**/
 TYPED(Vector)*TYPED(compute_row_sums)(const TYPED(Matrix) *__m);

 TYPED(Vector)*TYPED(compute_col_sums)(const TYPED(Matrix) *__m);

#endif