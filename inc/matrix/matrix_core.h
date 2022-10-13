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
 * This low-level function makes two calls to malloc, one call to allocate the `TYPED(Matrix) *` object itself
 * and a second call to allocate the `double *` array that stores the actual elements of our Matrix. This
 * routine performs no sanity checks and should rarely be used by the user. Instead, it is used by other
 * matrix constructors once the input has been validated.
 *
 * Furthermore, `matalloc` makes a call to malloc and **not** calloc, thus we are not even instantiating the
 * arrays elements, we are only asking the operating system for the required space.
 *
 * @param m Number of rows
 * @param n Number of columns
 * @return Matrix* A pointer to a newly allocated TYPED(Matrix) object.
 */
static inline TYPED(Matrix) *TYPED(matalloc)(size_t __nrows, size_t __ncols) {

    TYPED(Matrix) *x = (TYPED(Matrix) *) malloc(sizeof(TYPED(Matrix)));
    MATRIX_TYPE *data = (MATRIX_TYPE *) malloc(sizeof(MATRIX_TYPE) * (__nrows * __ncols));
    x->data = data;
    x->nrows = __nrows;
    x->ncols = __ncols;

    return x;
}

/**
 * @brief Create a 1 x 1 `TYPED(Matrix) *` whose only element is the scalar `k`
 *
 * @param k
 * @return Matrix*
 */
TYPED(Matrix) *TYPED(matvec)(double k);

TYPED(Matrix) *TYPED(matanon)(int __count, ...);

// low level function to literally just free both pointers
static inline void TYPED(matfree)(TYPED(Matrix) *__A) {
    free(__A->data); // if data is null, don't call free on it!!!
    free(__A);
}

/**
 * @brief Free all of the memory associated with A, verifying that the A and A->data are not null
 *
 * `TYPED(Matrix_free)` will free the memory pointed to by A and the underlying data as well. However, `TYPED(Matrix_free)` will
 * not set the pointer to NULL after it is called, which isn't best practice. Prefer to use `TYPED(Matrix_reset)(&A)`, which
 * takes a pointer to a `TYPED(Matrix) *`, setting the A to NULL after freeing the associated memory
 *
 * @param A
 */
static inline void TYPED(Matrix_free)(TYPED(Matrix) *__A) {
    if (__A) {
        if (__A->data) free(__A->data);
        free(__A);
    }
}

// Free the memeory and set the pointer equal to NULL
static inline void TYPED(Matrix_reset)(TYPED(Matrix) **__A_ptr) {
    if (*__A_ptr) {
        if ((*__A_ptr)->data) free((*__A_ptr)->data);
        free (*__A_ptr);
    }

    *__A_ptr = NULL;
}

TYPED(Matrix) *TYPED(Matrix_renew)(TYPED(Matrix) *A, int m, int n);
// Copy the bytes
// this is a utility function and should not be used by the end user
static inline bool TYPED(matcpy)(TYPED(Matrix) *restrict __dest, const TYPED(Matrix) *restrict __src) {

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
TYPED(Matrix) * TYPED(matclone)(const TYPED(Matrix) *restrict __src);

// Catch an unnamed TYPED(Matrix) pointer returned from the right side and store it in the
// lhs_ptr. Return the rhs
// This Is useful for preventing memory leaks for expressions of the type A = A * B
TYPED(Matrix) *TYPED(Matrix_catch)(TYPED(Matrix) **__lhs_ptr, TYPED(Matrix) *__anon_rhs);

// Used to manage memory of anonymous Matrices that are the results of intermediate operations
// FOr example TYPED(Matrix_print)(TYPED(Matrix_mult)(a, b))
// will lead to a memory leak.
// Instead, wrap the previous call with
// TYPED(Matrix_print)(TYPED(Matrix_anon)(TYPED(Matrix_mult)(a, b)));
// and finall, at the end of the program / scope call
// TYPED(Matrix_anon_free)
TYPED(Matrix) *TYPED(Matrix_anon)(TYPED(Matrix) *__anon_rhs);


void TYPED(Matrix_anon_free)();

TYPED(Matrix) *TYPED(Matrix_transpose)(const TYPED(Matrix) *m);

/**================================================================================================
 *!                                        Assignment Operator
 *================================================================================================**/
// I'd like to make the statement A = TYPED(Matrix_take)(A, M); allow the matrix A to point to the data
// of matrix M, and then to free the other matrix

TYPED(Matrix) *TYPED(Matrix_shallow_copy)(const TYPED(Matrix) *rhs);

// This function has a FATAL FLAW since it does not deallocate the matrix that is potentially being stored in the left hand side!!
TYPED(Matrix) *TYPED(Matrix_take)(TYPED(Matrix) *rhs);




/**================================================================================================
 *!                                        TYPED(Matrix) Constructors
 *================================================================================================**/

TYPED(Matrix) * TYPED(Matrix_new)(int nrows, int ncols);

// when given an ordinary array, construct a matrix from it, taking the prrevious memory.
// MOVE should only be called with arrays that are allocated on the heap so that that is no
// array jank that happens as a side effect.
TYPED(Matrix) *TYPED(Matrix_move)(MATRIX_TYPE **arr_ptr, size_t nrows, size_t ncols);

// When given an array, clone the array (copy its memory)
TYPED(Matrix) *TYPED(Matrix_from)(const MATRIX_TYPE *arr, size_t nrows, size_t ncols);

// When creating vectors we can just go ahead and memcpy the data!
TYPED(Matrix) *TYPED(Matrix_colvec)(const MATRIX_TYPE *arr, size_t nrows);

TYPED(Matrix) *TYPED(Matrix_rowvec)(const MATRIX_TYPE *arr, size_t ncols);

TYPED(Matrix) * TYPED(Matrix_clone)(const TYPED(Matrix) *restrict src);

// matrix of all ones
TYPED(Matrix) * TYPED(Matrix_ones)(size_t nrows, size_t ncols);

TYPED(Matrix) * TYPED(Matrix_ij)(size_t nrows, size_t ncols);

 TYPED(Vector)*TYPED(linspace)(MATRIX_TYPE start, MATRIX_TYPE end, int N);

 TYPED(Vector)*TYPED(range)(int start, int end, int diff);

MATRIX_TYPE TYPED(raisedBy10)(MATRIX_TYPE input); // used as a utility function for logspace

// use base 10
 TYPED(Vector)*TYPED(logspace)(double start, double end, int n);

 TYPED(Vector)*TYPED(Vector_linspace)(MATRIX_TYPE start, MATRIX_TYPE end, int N);

 TYPED(Vector)*TYPED(Vector_range)(double start, int end, int diff);



/**
 * @brief Create a square diagonal matrix with random entries from 1 to 10
 *
 * @param n
 * @return Matrix*
 */
TYPED(Matrix) *TYPED(Matrix_diagonal)(size_t n);

TYPED(Matrix) *TYPED(Matrix_tridiagonal)(size_t n);

TYPED(Matrix) * TYPED(Matrix_value)(size_t nrows, size_t ncols, MATRIX_TYPE value);

// MUST INITIALIZE EJOVO_SEED TO GET RANDOM VALUES
TYPED(Matrix) * TYPED(Matrix_random)(size_t nrows, size_t ncols, int min, int max);

TYPED(Matrix) * TYPED(Matrix_rand)(size_t nrows, size_t ncols);

TYPED(Matrix) * TYPED(Matrix_identity)(size_t n);

/**================================================================================================
 *!                                        Miscellaneous
 *================================================================================================**/
void TYPED(matprint)(const TYPED(Matrix) *m);

void TYPED(Matrix_print)(const TYPED(Matrix) *m);

void TYPED(Vector_print_head)(const TYPED(Matrix) *m, int n);

// Print in the; iter style
void TYPED(Matrix_print_iter)(const TYPED(Matrix) *m);

void TYPED(Matrix_summary)(const TYPED(Matrix) *m);

void TYPED(Matrix_print_all_digits)(const TYPED(Matrix) *m);

void TYPED(Matrix_print_fixed)(const TYPED(Matrix) *m);

TYPED(Matrix) *TYPED(Matrix_id)(size_t m, size_t n);

// printing

static inline void TYPED(print_el)(const MATRIX_TYPE el) {
#if defined MATRIX_DOUBLE 
    printf("%4.4lf ", el);
#elif defined MATRIX_FLOAT 
    printf("%4.4f ", el);
#elif defined MATRIX_INT
    printf("%5d ", el);
#elif defined MATRIX_COMPLEX
    printf("(%4.4lf, %4.4lf) ", creal(el), cimag(el));
#endif
}

static inline void TYPED(print_el_end)(const MATRIX_TYPE el) {
#if defined MATRIX_DOUBLE 
    printf("%4.4lf}\n", el);
#elif defined MATRIX_FLOAT 
    printf("%4.4f}\n", el);
#elif defined MATRIX_INT
    printf("%5d}\n", el);
#elif defined MATRIX_COMPLEX
    printf("(%4.4lf, %4.4lf)}\n", creal(el), cimag(el));
#endif
}

#endif