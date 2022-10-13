#ifndef MATRIX_LINEAR_H
#define MATRIX_LINEAR_H

#include "matrix.h"
#include "matrix_getset.h"
#include "matrix_core.h"

/**================================================================================================
 *!                                        Unary TYPED(Matrix) Operators
 *================================================================================================**/

TYPED(Matrix) *TYPED(Matrix_pow)(TYPED(Matrix) * __A, size_t __power);


// recursive algorithm to compute the determinant of a matrix
double TYPED(Matrix_det)(const TYPED(Matrix) * __A);

/**================================================================================================
 *!                                        Matrix-Scalar Operators
 *================================================================================================**/

/**================================================================================================
 *!                                        Matrix- TYPED(Vector)Operators
 *================================================================================================**/

// TYPED(Matrix) dot vector (take the row of a matrix and multiply that by a vector)



/**================================================================================================
 *!                                        Matrix-TYPED(Matrix) Operators
 *================================================================================================**/

// Take the inner product of the the __irow row of __A with the __icol col of __B
// used as a subroutine called in matmul
MATRIX_TYPE TYPED(matcdr_check)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B, size_t __irow, size_t __icol);

// Compute the dot product without checking any indices
// Compute the dot product without checking any indices
static inline MATRIX_TYPE TYPED(matcdr)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B, size_t __irow, size_t __icol) {
        MATRIX_TYPE inner_product = 0;
        for (size_t i = 0; i < __A->ncols; i++) {
            inner_product += (TYPED(matat)(__A, __irow, i) * TYPED(matat)(__B, i, __icol));
        }
        return inner_product;
}

static inline TYPED(Matrix) *TYPED(matmul)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {

    TYPED(Matrix) *product = TYPED(Matrix_new)(__A->nrows, __B->ncols);

    if (product){
        for (size_t i = 0; i < __A->nrows; i++) {
            for (size_t j = 0; j < __B->ncols; j++) {
                TYPED(matset)(product, i, j, TYPED(matcdr)(__A, __B, i, j));
            }
        }
    }

    return product;
}

TYPED(Matrix) * TYPED(Matrix_multiply)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

// matadd modifies __A in place for more efficient additions when we don't need the original matrix
void TYPED(matadd)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

TYPED(Matrix) *TYPED(Matrix_add)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

void TYPED(mathad)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

// Call hadamard multiplication, checking the indices with each access.
void TYPED(mathad_check)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

void TYPED(mathadexp)(TYPED(Matrix) *__A, int __k);

/**
 * Compute the Hadamard product (element-wise multiplication) of two matrices
 */
TYPED(Matrix) *TYPED(Matrix_hadamard)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

// NUMERICAL LINEAR ALGEBRA ROUTEINES!!!!!!

// Subtract matrix __B from __A, modifying __A in place!
void TYPED(matsub)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

TYPED(Matrix) *TYPED(Matrix_subtract)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

/**================================================================================================
 *!                                        Normalizations
 *================================================================================================**/

// Calculate the norm of a column using MatIter's
MATRIX_TYPE TYPED(colnorm)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end);

// Calculate the norm of a specific column
MATRIX_TYPE TYPED(Matrix_col_norm)(const TYPED(Matrix) *__A, size_t __j);

void TYPED(matnormcol)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end);

void TYPED(matnormcols)(TYPED(Matrix) *__A);

void TYPED(Matrix_normalize_col)(TYPED(Matrix) *__A, size_t __j);

void TYPED(Matrix_normalize_cols)(TYPED(Matrix) *__A);

/**
 * Return the Frobenius norm of a matrix, which is basically treating the matrix like a
 * single column vector and taking the euclidean norm
 */
MATRIX_TYPE TYPED(Matrix_frobenius)(const TYPED(Matrix) *__A);

/**================================================================================================
 *!                                        Decomposition Algorithms
 *================================================================================================**/

// compute the LU decomposition matrix without performing any pivots
// So the returned matrix is actually The lower triangular and the __A gets modified in place to
// produce the upper matrix
TYPED(Matrix) *TYPED(matlu_nopivot)(TYPED(Matrix) *__A);

TYPED(LU) TYPED(Matrix_lu)(const TYPED(Matrix) *__A);

// I need a function that performs back_substitution and also forward_substitution






/**================================================================================================
 *!                                        General Algorithms
 *================================================================================================**/

TYPED(Matrix) *TYPED(Matrix_solve_lu)(const TYPED(Matrix) *__A, const TYPED(Vector)*__b);




// Return a column vector that contains the solutions
// this column vector can be null if there are no solutions/infinitely many solutions
TYPED(Matrix) *TYPED(gausselim)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

TYPED(Matrix) *TYPED(Matrix_inverse)(const TYPED(Matrix) *__A);

/**================================================================================================
 *!                                        Iterative Algorithms
 *================================================================================================**/

/**
 * @brief Jacobi Iteration
 *
 * Jacobi iteration consists of solving for the diagonals (x_i) of each equation (the rows of A) when given
 * the equation Ax = b to solve.
 *
 * @param __A an Invertible matrix
 * @param __b a column or row Vector
 * @param __x0 Initial guess of the solution
 * @attention The parameter __b will be treated exclusively as a col vector to resolve the equation Ax = b,
 * where x and b are column vectors
 *
 * @returns a newly allocated vector
 *
 */
 TYPED(Vector)*TYPED(jacobi_iteration)(const TYPED(Matrix) *__A, const TYPED(Vector)*__b, const TYPED(Vector)*__x0, MATRIX_TYPE __crit);

TYPED(Matrix) *TYPED(Matrix_vandermonde)(const TYPED(Vector)*__v);

TYPED(Matrix) *TYPED(Matrix_vandermonde_reduced)(const TYPED(Vector)*__v, size_t __degree);

// These elementary operations will be considered low level and don't consider checking bounds...
// void TYPED(Matrix_switch_rows)(OrderedTYPED(Matrix) m, size_t __r1, size_t __r2) {
void TYPED(Row_switch)(TYPED(Index) *__ind, size_t __r1, size_t __r2);

void TYPED(Row_multiply)(TYPED(Matrix) *__m, TYPED(Index) *__ind, size_t __r, double __k);

// Modify the contents of __r1 by adding __r2 in place.
void TYPED(Row_addition)(TYPED(Matrix) *__m, TYPED(Index) *__ind, size_t __r1, size_t __r2);

// r1 = r1 + k * r2
void TYPED(Row_addition_k)(TYPED(Matrix) *__m, TYPED(Index) *__ind, size_t __r1, size_t __r2, double __k);

// Now that we have an inverse, vandermonde, and transpose operator, let's go ahead and compute a linear
// regression!

// TYPED(Vector)*linear

#endif