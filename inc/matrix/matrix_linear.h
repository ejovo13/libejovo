#ifndef MATRIX_LINEAR_H
#define MATRIX_LINEAR_H

#include "matrix.h"

/**================================================================================================
 *!                                        Unary MATRIX_T Operators
 *================================================================================================**/

MATRIX_T *MATRIX_FN(pow)(MATRIX_T * __A, size_t __power);


// recursive algorithm to compute the determinant of a matrix
double MATRIX_FN(det)(const MATRIX_T * __A);

/**================================================================================================
 *!                                        Matrix-Scalar Operators
 *================================================================================================**/

/**================================================================================================
 *!                                        Matrix-Vector Operators
 *================================================================================================**/

// MATRIX_T dot vector (take the row of a matrix and multiply that by a vector)



/**================================================================================================
 *!                                        Matrix-MATRIX_T Operators
 *================================================================================================**/

// Take the inner product of the the __irow row of __A with the __icol col of __B
// used as a subroutine called in matmul
MATRIX_TYPE MAT_FN(cdr_check)(const MATRIX_T *__A, const MATRIX_T *__B, size_t __irow, size_t __icol);

// Compute the dot product without checking any indices
// Compute the dot product without checking any indices
static inline MATRIX_TYPE MAT_FN(cdr)(const MATRIX_T *__A, const MATRIX_T *__B, size_t __irow, size_t __icol) {
        MATRIX_TYPE inner_product = 0;
        for (size_t i = 0; i < __A->ncols; i++) {
            inner_product += (MAT_FN(at)(__A, __irow, i) * MAT_FN(at)(__B, i, __icol));
        }
        return inner_product;
}

static inline MATRIX_T *MAT_FN(mul)(const MATRIX_T *__A, const MATRIX_T *__B) {

    MATRIX_T *product = MATRIX_FN(new)(__A->nrows, __B->ncols);

    if (product){
        for (size_t i = 0; i < __A->nrows; i++) {
            for (size_t j = 0; j < __B->ncols; j++) {
                MAT_FN(set)(product, i, j, MAT_FN(cdr)(__A, __B, i, j));
            }
        }
    }

    return product;
}

MATRIX_T * MATRIX_FN(multiply)(const MATRIX_T *__A, const MATRIX_T *__B);

// matadd modifies __A in place for more efficient additions when we don't need the original matrix
void MAT_FN(add)(MATRIX_T *__A, const MATRIX_T *__B);

MATRIX_T *MATRIX_FN(add)(const MATRIX_T *__A, const MATRIX_T *__B);

void MAT_FN(had)(MATRIX_T *__A, const MATRIX_T *__B);

// Call hadamard multiplication, checking the indices with each access.
void MAT_FN(had_check)(MATRIX_T *__A, const MATRIX_T *__B);

void MAT_FN(hadexp)(MATRIX_T *__A, int __k);

/**
 * Compute the Hadamard product (element-wise multiplication) of two matrices
 */
MATRIX_T *MATRIX_FN(hadamard)(const MATRIX_T *__A, const MATRIX_T *__B);

// NUMERICAL LINEAR ALGEBRA ROUTEINES!!!!!!

// Subtract matrix __B from __A, modifying __A in place!
void MAT_FN(sub)(MATRIX_T *__A, const MATRIX_T *__B);

MATRIX_T *MATRIX_FN(subtract)(const MATRIX_T *__A, const MATRIX_T *__B);

/**================================================================================================
 *!                                        Normalizations
 *================================================================================================**/

// Calculate the norm of a column using MatIter's
MATRIX_TYPE TYPED_FN(colnorm)(const MATITER_T __begin, const MATITER_T __end);

// Calculate the norm of a specific column
MATRIX_TYPE MATRIX_FN(col_norm)(const MATRIX_T *__A, size_t __j);

void MAT_FN(normcol)(const MATITER_T __begin, const MATITER_T __end);

void MAT_FN(normcols)(MATRIX_T *__A);

void MATRIX_FN(normalize_col)(MATRIX_T *__A, size_t __j);

void MATRIX_FN(normalize_cols)(MATRIX_T *__A);

/**
 * Return the Frobenius norm of a matrix, which is basically treating the matrix like a
 * single column vector and taking the euclidean norm
 */
MATRIX_TYPE MATRIX_FN(frobenius)(const MATRIX_T *__A);

/**================================================================================================
 *!                                        Decomposition Algorithms
 *================================================================================================**/

// compute the LU decomposition matrix without performing any pivots
// So the returned matrix is actually The lower triangular and the __A gets modified in place to
// produce the upper matrix
MATRIX_T *MAT_FN(lu_nopivot)(MATRIX_T *__A);

TYPED(LU) MATRIX_FN(lu)(const MATRIX_T *__A);

// I need a function that performs back_substitution and also forward_substitution






/**================================================================================================
 *!                                        General Algorithms
 *================================================================================================**/

MATRIX_T *MATRIX_FN(solve_lu)(const MATRIX_T *__A, const Vector *__b);




// Return a column vector that contains the solutions
// this column vector can be null if there are no solutions/infinitely many solutions
MATRIX_T *TYPED_FN(gausselim)(const MATRIX_T *__A, const MATRIX_T *__B);

MATRIX_T *MATRIX_FN(inverse)(const MATRIX_T *__A);

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
Vector *TYPED_FN(jacobi_iteration)(const MATRIX_T *__A, const Vector *__b, const Vector *__x0, MATRIX_TYPE __crit);

MATRIX_T *MATRIX_FN(vandermonde)(const Vector *__v);

MATRIX_T *MATRIX_FN(vandermonde_reduced)(const Vector *__v, size_t __degree);

// These elementary operations will be considered low level and don't consider checking bounds...
// void MATRIX_FN(switch_rows)(OrderedMATRIX_T m, size_t __r1, size_t __r2) {
void TYPED_FN(Row_switch)(const MATRIX_T *__m, Index *__ind, size_t __r1, size_t __r2);

void TYPED_FN(Row_multiply)(MATRIX_T *__m, Index *__ind, size_t __r, double __k);

// Modify the contents of __r1 by adding __r2 in place.
void TYPED_FN(Row_addition)(MATRIX_T *__m, Index *__ind, size_t __r1, size_t __r2);

// r1 = r1 + k * r2
void TYPED_FN(Row_addition_k)(MATRIX_T *__m, Index *__ind, size_t __r1, size_t __r2, double __k);

// Now that we have an inverse, vandermonde, and transpose operator, let's go ahead and compute a linear
// regression!

// Vector *linear

#endif