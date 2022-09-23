#pragma once

// matrix_core.c contains essential functions
// that deal with the creation, destruction and setting of matrix elements

#include "matrix.h"

/**================================================================================================
 *!                                        Memory and Allocation
 *================================================================================================**/

/**
 * @brief Allocate the necessary space to store an m x n matrix.
 *
 * This low-level function makes two calls to malloc, one call to allocate the `Matrix *` object itself
 * and a second call to allocate the `double *` array that stores the actual elements of our Matrix. This
 * routine performs no sanity checks and should rarely be used by the user. Instead, it is used by other
 * matrix constructors once the input has been validated.
 *
 * Furthermore, `matalloc` makes a call to malloc and **not** calloc, thus we are not even instantiating the
 * arrays elements, we are only asking the operating system for the required space.
 *
 * @param m Number of rows
 * @param n Number of columns
 * @return Matrix* A pointer to a newly allocated Matrix object.
 */
static inline Matrix *matalloc(size_t __nrows, size_t __ncols) {

    Matrix *x = (Matrix *) malloc(sizeof(Matrix));
    MATRIX_TYPE *data = (MATRIX_TYPE *) malloc(sizeof(MATRIX_TYPE) * (__nrows * __ncols));
    x->data = data;
    x->nrows = __nrows;
    x->ncols = __ncols;

    return x;
}

/**
 * @brief Create a 1 x 1 `Matrix *` whose only element is the scalar `k`
 *
 * @param k
 * @return Matrix*
 */
Matrix *vec(double k);

Matrix *anon(int __count, ...);

// low level function to literally just free both pointers
static inline void matfree(Matrix *__A) {
    free(__A->data); // if data is null, don't call free on it!!!
    free(__A);
}

/**
 * @brief Free all of the memory associated with A, verifying that the A and A->data are not null
 *
 * `Matrix_free` will free the memory pointed to by A and the underlying data as well. However, `Matrix_free` will
 * not set the pointer to NULL after it is called, which isn't best practice. Prefer to use `Matrix_reset(&A)`, which
 * takes a pointer to a `Matrix *`, setting the A to NULL after freeing the associated memory
 *
 * @param A
 */
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

Matrix *Matrix_renew(Matrix *A, int m, int n);
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
// lhs_ptr. Return the rhs
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

Matrix *Matrix_transpose(const Matrix *m);

/**================================================================================================
 *!                                        Assignment Operator
 *================================================================================================**/
// I'd like to make the statement A = Matrix_take(A, M); allow the matrix A to point to the data
// of matrix M, and then to free the other matrix

Matrix *Matrix_shallow_copy(const Matrix *rhs);

// This function has a FATAL FLAW since it does not deallocate the matrix that is potentially being stored in the left hand side!!
Matrix *Matrix_take(Matrix *rhs);




/**================================================================================================
 *!                                        Matrix Constructors
 *================================================================================================**/

Matrix * Matrix_new(int nrows, int ncols);

// when given an ordinary array, construct a matrix from it, taking the prrevious memory.
// MOVE should only be called with arrays that are allocated on the heap so that that is no
// array jank that happens as a side effect.
Matrix *Matrix_move(MATRIX_TYPE **arr_ptr, size_t nrows, size_t ncols);

// When given an array, clone the array (copy its memory)
Matrix *Matrix_from(const MATRIX_TYPE *arr, size_t nrows, size_t ncols);

// When creating vectors we can just go ahead and memcpy the data!
Matrix *Matrix_colvec(const MATRIX_TYPE *arr, size_t nrows);

Matrix *Matrix_rowvec(const MATRIX_TYPE *arr, size_t ncols);

Matrix * Matrix_clone(const Matrix *restrict src);

// matrix of all ones
Matrix * Matrix_ones(size_t nrows, size_t ncols);

Matrix * Matrix_ij(size_t nrows, size_t ncols);

Vector *linspace(MATRIX_TYPE start, MATRIX_TYPE end, int N);

Vector *range(int start, int end, int diff);

double raisedBy10(double input); // used as a utility function for logspace

// use base 10
Vector *logspace(double start, double end, int n);

Vector *Vector_linspace(MATRIX_TYPE start, MATRIX_TYPE end, int N);

Vector *Vector_range(double start, int end, int diff);



/**
 * @brief Create a square diagonal matrix with random entries from 1 to 10
 *
 * @param n
 * @return Matrix*
 */
Matrix *Matrix_diagonal(size_t n);

Matrix *Matrix_tridiagonal(size_t n);

Matrix * Matrix_value(size_t nrows, size_t ncols, MATRIX_TYPE value);

// MUST INITIALIZE EJOVO_SEED TO GET RANDOM VALUES
Matrix * Matrix_random(size_t nrows, size_t ncols, int min, int max);

Matrix * Matrix_rand(size_t nrows, size_t ncols);

Matrix * Matrix_identity(size_t n);

/**================================================================================================
 *!                                        Miscellaneous
 *================================================================================================**/
void matprint(const Matrix *m);

void Matrix_print(const Matrix *m);

void Vector_print_head(const Matrix *m, int n);

// Print in the; iter style
void Matrix_print_iter(const Matrix *m);

void Matrix_summary(const Matrix *m);

void Matrix_print_all_digits(const Matrix *m);

void Matrix_print_fixed(const Matrix *m);

Matrix *Matrix_id(size_t m, size_t n);