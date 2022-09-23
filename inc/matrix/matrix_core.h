#pragma once

// matrix_core.c contains essential functions
// that deal with the creation, destruction and setting of matrix elements

#include "matrix.h"

/**================================================================================================
 *!                                        Memory and Allocation
 *================================================================================================**/

// perform literally 0 checks, just allocate the space for a new matrix
// Matrix *matalloc(size_t __nrows, size_t __ncols);

// perform literally 0 checks, just allocate the space for a new matrix
static inline Matrix *matalloc(size_t __nrows, size_t __ncols) {

    Matrix *x = (Matrix *) malloc(sizeof(Matrix));
    MATRIX_TYPE *data = (MATRIX_TYPE *) malloc(sizeof(MATRIX_TYPE) * (__nrows * __ncols));
    x->data = data;
    x->nrows = __nrows;
    x->ncols = __ncols;

    return x;
}

Matrix *vec(double __k);

Matrix *anon(int __count, ...);

// low level function to literally just free both pointers
static inline void matfree(Matrix *__A) {
    free(__A->data); // if data is null, don't call free on it!!!
    free(__A);
}

// Free the memory associated with the matrix and then free the pointer itself
static inline void Matrix_free(Matrix *__A) {
    if (__A) {
        if (__A->data) free(__A->data);
        free(__A);
    }
}

// Free the memeory and set the pointer equal to NULL
static inline void Matrix_reset(Matrix **__A_ptr) {
    if (*__A_ptr) {
        if ((*__A_ptr)->data) free((*__A_ptr)->data);
        free (*__A_ptr);
    }

    *__A_ptr = NULL;
}

// Copy the bytes
// this is a utility function and should not be used by the end user
static inline bool matcpy(Matrix *restrict __dest, const Matrix *restrict __src) {

    // Copy the bytes of __src->data into __dest->data
    memcpy(__dest->data, __src->data, sizeof(MATRIX_TYPE)*(__src->nrows * __src->ncols));
    __dest->ncols = __src->ncols;
    __dest->nrows = __src->nrows;
    if(__dest && __src && __dest->data) { // if all the pointers are not null, return true
        return  true;
    } else {
        return false;
    }
}
// copy the contents of matrix __src into __dest
Matrix * matclone(const Matrix *restrict __src);

// Catch an unnamed Matrix pointer returned from the right side and store it in the
// __lhs_ptr. Return the __rhs
// This Is useful for preventing memory leaks for expressions of the type A = A * B
Matrix *Matrix_catch(Matrix **__lhs_ptr, Matrix *__anon_rhs);

// Used to manage memory of anonymous Matrices that are the results of intermediate operations
// FOr example Matrix_print(Matrix_mult(a, b))
// will lead to a memory leak.
// Instead, wrap the previous call with
// Matrix_print(Matrix_anon(Matrix_mult(a, b)));
// and finall, at the end of the program / scope call
// Matrix_anon_free
Matrix *Matrix_anon(Matrix *__anon_rhs);

void Matrix_anon_free();

Matrix *Matrix_transpose(const Matrix *__m);

/**================================================================================================
 *!                                        Assignment Operator
 *================================================================================================**/
// I'd like to make the statement A = Matrix_take(A, M); allow the matrix A to point to the data
// of matrix M, and then to free the other matrix

Matrix *Matrix_shallow_copy(const Matrix *__rhs);

// This function has a FATAL FLAW since it does not deallocate the matrix that is potentially being stored in the left hand side!!
Matrix *Matrix_take(Matrix *__rhs);




/**================================================================================================
 *!                                        Matrix Constructors
 *================================================================================================**/

Matrix * Matrix_new(int __nrows, int __ncols);

// when given an ordinary array, construct a matrix from it, taking the prrevious memory.
// MOVE should only be called with arrays that are allocated on the heap so that that is no
// array jank that happens as a side effect.
Matrix *Matrix_move(MATRIX_TYPE **__arr_ptr, size_t __nrows, size_t __ncols);

// When given an array, clone the array (copy its memory)
Matrix *Matrix_from(const MATRIX_TYPE *__arr, size_t __nrows, size_t __ncols);

// When creating vectors we can just go ahead and memcpy the data!
Matrix *Matrix_colvec(const MATRIX_TYPE *__arr, size_t __nrows);

Matrix *Matrix_rowvec(const MATRIX_TYPE *__arr, size_t __ncols);

Matrix * Matrix_clone(const Matrix *restrict __src);

// matrix of all ones
Matrix * Matrix_ones(size_t __nrows, size_t __ncols);

Matrix * Matrix_ij(size_t __nrows, size_t __ncols);

Vector *linspace(MATRIX_TYPE __start, MATRIX_TYPE __end, int __N);

Vector *range(int __start, int __end, int __diff);

double raisedBy10(double __input); // used as a utility function for logspace

// use base 10
Vector *logspace(double __start, double __end, int __n);

Vector *Vector_linspace(MATRIX_TYPE __start, MATRIX_TYPE __end, int __N);

Vector *Vector_range(double __start, int __end, int __diff);



/**
 * @brief Create a square diagonal matrix with random entries from 1 to 10
 *
 * @param __n
 * @return Matrix*
 */
Matrix *Matrix_diagonal(size_t __n);

Matrix *Matrix_tridiagonal(size_t __n);

Matrix * Matrix_value(size_t __nrows, size_t __ncols, MATRIX_TYPE __value);

// MUST INITIALIZE EJOVO_SEED TO GET RANDOM VALUES
Matrix * Matrix_random(size_t __nrows, size_t __ncols, int __min, int __max);

Matrix * Matrix_rand(size_t __nrows, size_t __ncols);

Matrix * Matrix_identity(size_t __n);

/**================================================================================================
 *!                                        Miscellaneous
 *================================================================================================**/
void matprint(const Matrix *__m);

void Matrix_print(const Matrix *__m);

void Vector_print_head(const Matrix *__m, int __n);

// Print in the; iter style
void Matrix_print_iter(const Matrix *__m);

void Matrix_summary(const Matrix *__m);

void Matrix_print_all_digits(const Matrix *__m);

void Matrix_print_fixed(const Matrix *__m);

Matrix *Matrix_id(size_t __m, size_t __n);