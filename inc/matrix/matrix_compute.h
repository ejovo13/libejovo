#ifndef MATRIX_COMPUTE_H
#define MATRIX_COMPUTE_H

// Routines that are used in Computational Science and Engineering

// #include "ejovo_matrix_generic.h"
#include "matrix.h"

/**================================================================================================
 *!                                        Finite Differences Matrices
 *================================================================================================**/

// Tridiagonal K matrix
MATRIX_T *MATRIX_FN(K)(size_t __n);

// Circular matrix
MATRIX_T *MATRIX_FN(C)(size_t __n);

MATRIX_T *MATRIX_FN(T)(size_t __n);

MATRIX_T *MATRIX_FN(B)(size_t __n);

#endif