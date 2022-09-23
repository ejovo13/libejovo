#pragma once

#include "matrix.h"

/**================================================================================================
 *!                                        Unary Matrix Operators
 *================================================================================================**/

Matrix *Matrix_pow(Matrix * __A, size_t __power);


// recursive algorithm to compute the determinant of a matrix
double Matrix_det(const Matrix * __A);

/**================================================================================================
 *!                                        Matrix-Scalar Operators
 *================================================================================================**/

/**================================================================================================
 *!                                        Matrix-Vector Operators
 *================================================================================================**/

// Matrix dot vector (take the row of a matrix and multiply that by a vector)



/**================================================================================================
 *!                                        Matrix-Matrix Operators
 *================================================================================================**/

// Take the inner product of the the __irow row of __A with the __icol col of __B
// used as a subroutine called in matmul
MATRIX_TYPE matcdr_check(const Matrix *__A, const Matrix *__B, size_t __irow, size_t __icol);

// Compute the dot product without checking any indices
// Compute the dot product without checking any indices
static inline MATRIX_TYPE matcdr(const Matrix *__A, const Matrix *__B, size_t __irow, size_t __icol) {
        MATRIX_TYPE inner_product = 0;
        for (size_t i = 0; i < __A->ncols; i++) {
            inner_product += (matat(__A, __irow, i) * matat(__B, i, __icol));
        }
        return inner_product;
}

static inline Matrix *matmul(const Matrix *__A, const Matrix *__B) {

    Matrix *product = Matrix_new(__A->nrows, __B->ncols);

    if (product){
        for (size_t i = 0; i < __A->nrows; i++) {
            for (size_t j = 0; j < __B->ncols; j++) {
                matset(product, i, j, matcdr(__A, __B, i, j));
            }
        }
    }

    return product;
}

Matrix * Matrix_multiply(const Matrix *__A, const Matrix *__B);

// matadd modifies __A in place for more efficient additions when we don't need the original matrix
void matadd(Matrix *__A, const Matrix *__B);

Matrix *Matrix_add(const Matrix *__A, const Matrix *__B);

void mathad(Matrix *__A, const Matrix *__B);

// Call hadamard multiplication, checking the indices with each access.
void mathad_check(Matrix *__A, const Matrix *__B);

void mathadexp(Matrix *__A, int __k);

/**
 * Compute the Hadamard product (element-wise multiplication) of two matrices
 */
Matrix *Matrix_hadamard(const Matrix *__A, const Matrix *__B);

// NUMERICAL LINEAR ALGEBRA ROUTEINES!!!!!!

// Subtract matrix __B from __A, modifying __A in place!
void matsub(Matrix *__A, const Matrix *__B);

Matrix *Matrix_subtract(const Matrix *__A, const Matrix *__B);

/**================================================================================================
 *!                                        Normalizations
 *================================================================================================**/

// Calculate the norm of a column using MatIter's
MATRIX_TYPE colnorm(const MatIter __begin, const MatIter __end);

// Calculate the norm of a specific column
MATRIX_TYPE Matrix_col_norm(const Matrix *__A, size_t __j);

void matnormcol(const MatIter __begin, const MatIter __end);

void matnormcols(Matrix *__A);

void Matrix_normalize_col(Matrix *__A, size_t __j);

void Matrix_normalize_cols(Matrix *__A);

/**
 * Return the Frobenius norm of a matrix, which is basically treating the matrix like a
 * single column vector and taking the euclidean norm
 */
MATRIX_TYPE Matrix_frobenius(const Matrix *__A);

/**================================================================================================
 *!                                        Decomposition Algorithms
 *================================================================================================**/

// compute the LU decomposition matrix without performing any pivots
// So the returned matrix is actually The lower triangular and the __A gets modified in place to
// produce the upper matrix
Matrix *matlu_nopivot(Matrix *__A);

LU Matrix_lu(const Matrix *__A);

// I need a function that performs back_substitution and also forward_substitution






/**================================================================================================
 *!                                        General Algorithms
 *================================================================================================**/

Matrix *Matrix_solve_lu(const Matrix *__A, const Vector *__b);




// Return a column vector that contains the solutions
// this column vector can be null if there are no solutions/infinitely many solutions
Matrix *gausselim(const Matrix *__A, const Matrix *__B);

Matrix *Matrix_inverse(const Matrix *__A);

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
Vector *jacobi_iteration(const Matrix *__A, const Vector *__b, const Vector *__x0, MATRIX_TYPE __crit);

Matrix *Matrix_vandermonde(const Vector *__v);

Matrix *Matrix_vandermonde_reduced(const Vector *__v, size_t __degree);

// These elementary operations will be considered low level and don't consider checking bounds...
// void Matrix_switch_rows(OrderedMatrix m, size_t __r1, size_t __r2) {
void Row_switch(const Matrix *__m, Index *__ind, size_t __r1, size_t __r2);

void Row_multiply(Matrix *__m, Index *__ind, size_t __r, double __k);

// Modify the contents of __r1 by adding __r2 in place.
void Row_addition(Matrix *__m, Index *__ind, size_t __r1, size_t __r2);

// r1 = r1 + k * r2
void Row_addition_k(Matrix *__m, Index *__ind, size_t __r1, size_t __r2, double __k);

// Now that we have an inverse, vandermonde, and transpose operator, let's go ahead and compute a linear
// regression!

// Vector *linear