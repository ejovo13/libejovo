#pragma once

// Routines that are used in Computational Science and Engineering

#include "matrix.h"

/**================================================================================================
 *!                                        Finite Differences Matrices
 *================================================================================================**/

// Tridiagonal K matrix
Matrix *Matrix_K(size_t __n);

// Circular matrix
Matrix *Matrix_C(size_t __n);

Matrix *Matrix_T(size_t __n);

Matrix *Matrix_B(size_t __n);