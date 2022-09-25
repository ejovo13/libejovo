#ifndef MATRIX_COMPUTE_H
#define MATRIX_COMPUTE_H

// Routines that are used in Computational Science and Engineering

// #include "ejovo_matrix_generic.h"
#include "matrix.h"

/**================================================================================================
 *!                                        Finite Differences Matrices
 *================================================================================================**/

// Tridiagonal K matrix
TYPED(Matrix) *TYPED(Matrix_K)(size_t __n);

// Circular matrix
TYPED(Matrix) *TYPED(Matrix_C)(size_t __n);

TYPED(Matrix) *TYPED(Matrix_T)(size_t __n);

TYPED(Matrix) *TYPED(Matrix_B)(size_t __n);

#endif