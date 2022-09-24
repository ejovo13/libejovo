#pragma once

// Routines that are used in Computational Science and Engineering

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