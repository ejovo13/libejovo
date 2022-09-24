#ifndef MATRIX_CORE_H
#define MATRIX_CORE_H

// matrix_core.c contains essential functions
// that deal with the creation, destruction and setting of matrix elements

#include "matrix.h"

/**================================================================================================
 *!                                        Memory and Allocation
 *================================================================================================**/

/**
 * @brief Allocate the necessary space to store an m x n matrix.
 *
 * This low-level function makes two calls to malloc, one call to allocate the `MATRIX_T *` object itself
 * and a second call to allocate the `double *` array that stores the actual elements of our Matrix. This
 * routine performs no sanity checks and should rarely be used by the user. Instead, it is used by other
 * matrix constructors once the input has been validated.
 *
 * Furthermore, `matalloc` makes a call to malloc and **not** calloc, thus we are not even instantiating the
 * arrays elements, we are only asking the operating system for the required space.
 *
 * @param m Number of rows
 * @param n Number of columns
 * @return Matrix* A pointer to a newly allocated MATRIX_T object.
 */
static inline MATRIX_T *MAT_FN(alloc)(size_t __nrows, size_t __ncols) {

    MATRIX_T *x = (MATRIX_T *) malloc(sizeof(MATRIX_T));
    MATRIX_TYPE *data = (MATRIX_TYPE *) malloc(sizeof(MATRIX_TYPE) * (__nrows * __ncols));
    x->data = data;
    x->nrows = __nrows;
    x->ncols = __ncols;

    return x;
}

/**
 * @brief Create a 1 x 1 `MATRIX_T *` whose only element is the scalar `k`
 *
 * @param k
 * @return Matrix*
 */
MATRIX_T *MAT_FN(vec)(double k);

MATRIX_T *MAT_FN(anon)(int __count, ...);

// low level function to literally just free both pointers
static inline void MAT_FN(free)(MATRIX_T *__A) {
    free(__A->data); // if data is null, don't call free on it!!!
    free(__A);
}

/**
 * @brief Free all of the memory associated with A, verifying that the A and A->data are not null
 *
 * `MATRIX_FN(free)` will free the memory pointed to by A and the underlying data as well. However, `MATRIX_FN(free)` will
 * not set the pointer to NULL after it is called, which isn't best practice. Prefer to use `MATRIX_FN(reset)(&A)`, which
 * takes a pointer to a `MATRIX_T *`, setting the A to NULL after freeing the associated memory
 *
 * @param A
 */
static inline void MATRIX_FN(free)(MATRIX_T *__A) {
    if (__A) {
        if (__A->data) free(__A->data);
        free(__A);
    }
}

// Free the memeory and set the pointer equal to NULL
static inline void MATRIX_FN(reset)(MATRIX_T **__A_ptr) {
    if (*__A_ptr) {
        if ((*__A_ptr)->data) free((*__A_ptr)->data);
        free (*__A_ptr);
    }

    *__A_ptr = NULL;
}

MATRIX_T *MATRIX_FN(renew)(MATRIX_T *A, int m, int n);
// Copy the bytes
// this is a utility function and should not be used by the end user
static inline bool MAT_FN(cpy)(MATRIX_T *restrict __dest, const MATRIX_T *restrict __src) {

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
MATRIX_T * MAT_FN(clone)(const MATRIX_T *restrict __src);

// Catch an unnamed MATRIX_T pointer returned from the right side and store it in the
// lhs_ptr. Return the rhs
// This Is useful for preventing memory leaks for expressions of the type A = A * B
MATRIX_T *MATRIX_FN(catch)(MATRIX_T **__lhs_ptr, MATRIX_T *__anon_rhs);

// Used to manage memory of anonymous Matrices that are the results of intermediate operations
// FOr example MATRIX_FN(print)(MATRIX_FN(mult)(a, b))
// will lead to a memory leak.
// Instead, wrap the previous call with
// MATRIX_FN(print)(MATRIX_FN(anon)(MATRIX_FN(mult)(a, b)));
// and finall, at the end of the program / scope call
// MATRIX_FN(anon_free)
MATRIX_T *MATRIX_FN(anon)(MATRIX_T *__anon_rhs);


void MATRIX_FN(anon_free)();

MATRIX_T *MATRIX_FN(transpose)(const MATRIX_T *m);

/**================================================================================================
 *!                                        Assignment Operator
 *================================================================================================**/
// I'd like to make the statement A = MATRIX_FN(take)(A, M); allow the matrix A to point to the data
// of matrix M, and then to free the other matrix

MATRIX_T *MATRIX_FN(shallow_copy)(const MATRIX_T *rhs);

// This function has a FATAL FLAW since it does not deallocate the matrix that is potentially being stored in the left hand side!!
MATRIX_T *MATRIX_FN(take)(MATRIX_T *rhs);




/**================================================================================================
 *!                                        MATRIX_T Constructors
 *================================================================================================**/

MATRIX_T * MATRIX_FN(new)(int nrows, int ncols);

// when given an ordinary array, construct a matrix from it, taking the prrevious memory.
// MOVE should only be called with arrays that are allocated on the heap so that that is no
// array jank that happens as a side effect.
MATRIX_T *MATRIX_FN(move)(MATRIX_TYPE **arr_ptr, size_t nrows, size_t ncols);

// When given an array, clone the array (copy its memory)
MATRIX_T *MATRIX_FN(from)(const MATRIX_TYPE *arr, size_t nrows, size_t ncols);

// When creating vectors we can just go ahead and memcpy the data!
MATRIX_T *MATRIX_FN(colvec)(const MATRIX_TYPE *arr, size_t nrows);

MATRIX_T *MATRIX_FN(rowvec)(const MATRIX_TYPE *arr, size_t ncols);

MATRIX_T * MATRIX_FN(clone)(const MATRIX_T *restrict src);

// matrix of all ones
MATRIX_T * MATRIX_FN(ones)(size_t nrows, size_t ncols);

MATRIX_T * MATRIX_FN(ij)(size_t nrows, size_t ncols);

Vector *TYPED_FN(linspace)(MATRIX_TYPE start, MATRIX_TYPE end, int N);

Vector *TYPED_FN(range)(int start, int end, int diff);

MATRIX_TYPE TYPED_FN(raisedBy10)(MATRIX_TYPE input); // used as a utility function for logspace

// use base 10
Vector *TYPED_FN(logspace)(double start, double end, int n);

Vector *VECTOR_FN(linspace)(MATRIX_TYPE start, MATRIX_TYPE end, int N);

Vector *VECTOR_FN(range)(double start, int end, int diff);



/**
 * @brief Create a square diagonal matrix with random entries from 1 to 10
 *
 * @param n
 * @return Matrix*
 */
MATRIX_T *MATRIX_FN(diagonal)(size_t n);

MATRIX_T *MATRIX_FN(tridiagonal)(size_t n);

MATRIX_T * MATRIX_FN(value)(size_t nrows, size_t ncols, MATRIX_TYPE value);

// MUST INITIALIZE EJOVO_SEED TO GET RANDOM VALUES
MATRIX_T * MATRIX_FN(random)(size_t nrows, size_t ncols, int min, int max);

MATRIX_T * MATRIX_FN(rand)(size_t nrows, size_t ncols);

MATRIX_T * MATRIX_FN(identity)(size_t n);

/**================================================================================================
 *!                                        Miscellaneous
 *================================================================================================**/
void MAT_FN(print)(const MATRIX_T *m);

void MATRIX_FN(print)(const MATRIX_T *m);

void VECTOR_FN(print_head)(const MATRIX_T *m, int n);

// Print in the; iter style
void MATRIX_FN(print_iter)(const MATRIX_T *m);

void MATRIX_FN(summary)(const MATRIX_T *m);

void MATRIX_FN(print_all_digits)(const MATRIX_T *m);

void MATRIX_FN(print_fixed)(const MATRIX_T *m);

MATRIX_T *MATRIX_FN(id)(size_t m, size_t n);

#endif