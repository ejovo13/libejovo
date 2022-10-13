#ifndef MATRIX_ITER_H
#define MATRIX_ITER_H

// functions that deal with the creation of iterator objects

#include "matrix.h"
#include "matrix/matrix_getset.h"

// TODO I need to add checks for some of my iterator functions like matdiagend -> TYPED(Matrix_diag_end)

/**================================================================================================
 *!                                        Special Types of Iterators
 *================================================================================================**/
// Should have row, col, diagonal iterators. There are even some special iterators like "checkerboards"
// that can hit every other element.

TYPED(MatIter) TYPED(matdiagbegin)(const TYPED(Matrix) *__m, const int __d);

TYPED(MatIter) TYPED(matdiagend)(const TYPED(Matrix) *__m, const int __d);

void TYPED(MatIter_print)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end);


// The 0th diagonal will start at the position __m(0, 0)
// The 1st diagonal will start at the position __m(0, 1)
// The -1  diagonal will start at the position __m(1, 0)
// TYPED(MatIter) TYPED(Matrix_diag_begin)(const TYPED(Matrix) *__m, const int __d);






/**================================================================================================
 *!                                        RowCol and ColIter
 *================================================================================================**/

MATRIX_TYPE TYPED(Iter_dot)(const TYPED(MatIter) __r, const TYPED(MatIter) __rend, const TYPED(MatIter) __c);

/**=======================================================================================================================
 *!                                           TYPED(Matrix) Interface to Iter functions
 *=======================================================================================================================**/

void TYPED(Matrix_print_row)(const TYPED(Matrix) *__A, size_t __i);

void TYPED(Matrix_print_col)(const TYPED(Matrix) *__A, size_t __j);


void TYPED(Matrix_print_diag)(const TYPED(Matrix) *__A, size_t __d);

// Here I want to be able to manipulate the functions defined above to create clean and simple TYPED(Matrix) api

// let's start simple and add rows together

// matrix elementary row operation (add two rows)
void TYPED(matrowop_add)(TYPED(Matrix) *__A, const size_t __r1, const size_t __r2, const size_t __col_offset);

// matrix elementary row operation (add two rows)
void TYPED(matrowop_add_scaled)(TYPED(Matrix) *__A, const size_t __r1, const size_t __r2, const MATRIX_TYPE __k, const size_t __col_offset);

void TYPED(Matrix_rowop_add)(TYPED(Matrix) *__A, const size_t __r1, const size_t __r2);

void TYPED(Matrix_rowop_add_offset)(TYPED(Matrix) *__A, const size_t __r1, const size_t __r2, const size_t __col_offset);

void TYPED(Matrix_rowop_add_scaled)(TYPED(Matrix) *__A, const size_t __r1, const size_t __r2, const MATRIX_TYPE __k);

MATRIX_TYPE TYPED(Matrix_row_min)(const TYPED(Matrix) *__A, const size_t __i);

MATRIX_TYPE TYPED(Matrix_row_max)(const TYPED(Matrix) *__A, const size_t __i);

MATRIX_TYPE TYPED(Matrix_col_min)(const TYPED(Matrix) *__A, const size_t __j);

MATRIX_TYPE TYPED(Matrix_col_max)(const TYPED(Matrix) *__A, const size_t __j);

MATRIX_TYPE TYPED(Matrix_diag_min)(const TYPED(Matrix) *__A, const size_t __j);

MATRIX_TYPE TYPED(Matrix_diag_max)(const TYPED(Matrix) *__A, const size_t __j);

MATRIX_TYPE TYPED(Matrix_row_prod)(const TYPED(Matrix) *__A, const size_t __i);

MATRIX_TYPE TYPED(Matrix_col_prod)(const TYPED(Matrix) *__A, const size_t __i);

MATRIX_TYPE TYPED(Matrix_diag_prod)(const TYPED(Matrix) *__A, const size_t __i);


MATRIX_TYPE TYPED(Matrix_row_sum)(const TYPED(Matrix) *__A, const size_t __i);

MATRIX_TYPE TYPED(Matrix_col_sum)(const TYPED(Matrix) *__A, const size_t __i);

MATRIX_TYPE TYPED(Matrix_diag_sum)(const TYPED(Matrix) *__A, const size_t __i);



TYPED(MatIter) TYPED(matcolpos)(const TYPED(Matrix) *__A, size_t __i, size_t __j);

// return a new Matumn Iterator that points to the final element in this column
TYPED(MatIter) TYPED(Matrix_col_end)(const TYPED(Matrix) *__A, size_t __j);

TYPED(MatIter) TYPED(Matrix_col_begin)(const TYPED(Matrix) *__A, size_t __j);

TYPED(MatIter) TYPED(matcolbegin)(const TYPED(Matrix) *__A, size_t __i);

TYPED(MatIter) TYPED(matcolend)(const TYPED(Matrix) *__A, size_t __i);

TYPED(MatIter) TYPED(matrowpos)(const TYPED(Matrix) *__A, size_t __i, size_t __j);

// get row iterator without checking bounds
TYPED(MatIter) TYPED(matrowbegin)(const TYPED(Matrix) *__A, size_t __i);

TYPED(MatIter) TYPED(matrowend)(const TYPED(Matrix) *__A, size_t __i);

// return a new Column Iterator that points to the final element in this column
TYPED(MatIter) TYPED(Matrix_row_end)(const TYPED(Matrix) *__A, size_t __i);

TYPED(MatIter) TYPED(Matrix_row_begin)(const TYPED(Matrix) *__A, size_t __i);

/**=======================================================================================================================
 *!                                                   MIter that has more general capabilities
 *=======================================================================================================================**/
static inline TYPED(MatIter) MATITER_NEW(MATRIX_TYPE *__ptr, size_t __ptr_diff) {
    TYPED(MatIter) c = {.ptr = __ptr, .ptr_diff = __ptr_diff};
    return c;
}

static inline TYPED(MatIter) TYPED(MatIter_null)() {
    TYPED(MatIter) null = {.ptr = NULL, .ptr_diff = 0};
    return null;
}

static inline bool TYPED(MatIter_is_null)(TYPED(MatIter) __i) {
    return __i.ptr == NULL;
}

// Increment the row iter
static inline TYPED(MatIter) TYPED(MatIter_next)(TYPED(MatIter) __c) {
    TYPED(MatIter) next = {.ptr = __c.ptr += __c.ptr_diff, .ptr_diff = __c.ptr_diff};
    return next;
}

static inline bool TYPED(MatIter_cmp)(const TYPED(MatIter) __lhs, const TYPED(MatIter) __rhs) {
    return __lhs.ptr == __rhs.ptr;
}

static inline MATRIX_TYPE TYPED(MatIter_value)(const TYPED(MatIter) __c) {
    return *(__c.ptr);
}

// Return true if the __lhs and __rhs point to the same element
// bool TYPED(MatIter_cmp)(const TYPED(MatIter) __lhs, const TYPED(MatIter) __rhs);

// MATRIX_TYPE TYPED(MatIter_value)(const TYPED(MatIter) __c);

// Return the number of iteration between begin and end
// size_t TYPED(MatIter_length)(const TYPED(MatIter) begin, const TYPED(MatIter) end);

static inline size_t TYPED(MatIter_length)(const TYPED(MatIter) begin, const TYPED(MatIter) end) {
    // printf("[TYPED(MatIter_length)]   end->ptr: %x, begin->ptr: %x\n", end->ptr, begin->ptr);
    size_t diff = end.ptr - begin.ptr;
    return diff / begin.ptr_diff;
}

/**========================================================================
 *!                           Functional Iter functions
 *========================================================================**/
MATRIX_TYPE TYPED(MatIter_sum)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end);

MATRIX_TYPE TYPED(MatIter_prod)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end);

// Get the maximum value in a row
MATRIX_TYPE TYPED(MatIter_max)(TYPED(MatIter) __a, const TYPED(MatIter) __b);

// Get the maximum value in a row
MATRIX_TYPE TYPED(MatIter_min)(TYPED(MatIter) __a, const TYPED(MatIter) __b);

/**================================================================================================
 *!                                        TYPED(MatIter) basic utility routines - SINGLE
 *================================================================================================**/

void TYPED(MatIter_set)(TYPED(MatIter) __r, const MATRIX_TYPE __k);

void TYPED(MatIter_add_k)(TYPED(MatIter) __r, const MATRIX_TYPE __k);

void TYPED(MatIter_sub_k)(TYPED(MatIter) __r, const MATRIX_TYPE __k);

void TYPED(MatIter_mult_k)(TYPED(MatIter) __r, const MATRIX_TYPE __k);

void TYPED(MatIter_div_k)(TYPED(MatIter) __r, const MATRIX_TYPE __k);

void TYPED(MatIter_set_ptr)(TYPED(MatIter) __r, const MATRIX_TYPE *__ptr);

void TYPED(MatIter_add_ptr)(TYPED(MatIter) __r, const MATRIX_TYPE *__ptr);

void TYPED(MatIter_sub_ptr)(TYPED(MatIter) __r, const MATRIX_TYPE *__ptr);

void TYPED(MatIter_mult_ptr)(TYPED(MatIter) __r, const MATRIX_TYPE *__ptr);

void TYPED(MatIter_div_ptr)(TYPED(MatIter) __r, const MATRIX_TYPE *__ptr);

void TYPED(MatIter_set_iter)(TYPED(MatIter) __a, const TYPED(MatIter) __b);

void TYPED(MatIter_set_iter_pow)(TYPED(MatIter) __a, const TYPED(MatIter) __b, MATRIX_TYPE __n);

void TYPED(MatIter_add_iter)(TYPED(MatIter) __a, const TYPED(MatIter) __b);

void TYPED(MatIter_add_iter_scaled)(TYPED(MatIter) __a, const TYPED(MatIter) __b, const MATRIX_TYPE __k);

// static inline void TYPED(MatIter_add_iter_double)(TYPED(MatIter) __a, const TYPED(MatIter) __b, const double __k) {
//     *(__a.ptr) += *(__b.ptr) * __k;
// }

// static inline void TYPED(MatIter_set_iter_double)(TYPED(MatIter) __a, const TYPED(MatIter) __b, const double __k) {
//     *(__a.ptr) = __k;
// }

void TYPED(MatIter_sub_iter)(TYPED(MatIter) __a, const TYPED(MatIter) __b);

void TYPED(MatIter_mult_iter)(TYPED(MatIter) __a, const TYPED(MatIter) __b);

void TYPED(MatIter_div_iter)(TYPED(MatIter) __a, const TYPED(MatIter) __b);





/**================================================================================================
 *!                                        TYPED(MatIter) basic utility routines - ROW
 *================================================================================================**/

// Set the elements of a row when given a row iterator and a value k
void TYPED(MatIter_row_set_k)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k);

// Set the elements of a row when given a row iterator and another starting iterator
void TYPED(MatIter_row_set_iter)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const TYPED(MatIter) __bbegin);


void TYPED(MatIter_row_add_k)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k);

void TYPED(MatIter_row_sub_k)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k);

void TYPED(MatIter_row_mult_k)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k);

void TYPED(MatIter_row_div_k)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k);

// Add to row __a the elements of row __b
void TYPED(MatIter_row_add_row)(const TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, const TYPED(MatIter) __bbegin);


/**================================================================================================
 *!                                        Experimental APPLY functions
 *================================================================================================**/

// Appy functions are a way to iterate a ColIter until we reach the "end" point


void TYPED(MatIter_apply)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, TYPED(MatIterFn) __fn);

void TYPED(MatIter_apply_k)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k, TYPED(MatIterFn_k) __fn_k);

void TYPED(MatIter_apply_ptr)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE *__ptr, TYPED(MatIterFn_ptr) __fn_ptr);

void TYPED(MatIter_apply_iter)(const TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, const TYPED(MatIter) __bbegin, TYPED(MatIterFn_iter) __fn_iter);

void TYPED(MatIter_apply_iter_scaled)(const TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, const TYPED(MatIter) __bbegin, const MATRIX_TYPE __k, TYPED(MatIterFn_iter_k) __fn_iter_k);

/**================================================================================================
 *!                                        Mat manipulations using apply functions
 *================================================================================================**/

/**======================
 *!    Scalar operations
 *========================**/
void TYPED(MatIter_apply_set_k)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k);

void TYPED(MatIter_apply_add_k)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k);

void TYPED(MatIter_apply_sub_k)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k);

void TYPED(MatIter_apply_mult_k)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k);

void TYPED(MatIter_apply_div_k)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k);

/**======================
 *!    Pointer operations
 *========================**/

void TYPED(MatIter_apply_set_ptr)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE *__ptr);

void TYPED(MatIter_apply_add_ptr)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE *__ptr);

void TYPED(MatIter_apply_sub_ptr)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE *__ptr);

void TYPED(MatIter_apply_mult_ptr)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE *__ptr);

void TYPED(MatIter_apply_div_ptr)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE *__ptr);

/**======================
 *!    Iterator operations
 *========================**/

void TYPED(MatIter_apply_set_iter)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin);

void TYPED(MatIter_apply_set_iter_pow)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin, double __n);

void TYPED(MatIter_apply_add_iter)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin);

void TYPED(MatIter_apply_sub_iter)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin);

void TYPED(MatIter_apply_mult_iter)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin);

void TYPED(MatIter_apply_div_iter)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin);

/**======================
 *!    add iter scaled
 *========================**/
void TYPED(MatIter_apply_add_iter_scaled)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin, const MATRIX_TYPE __k);

TYPED(Matrix) *TYPED(Matrix_set_col_iter)(TYPED(Matrix) *__m, size_t __j, TYPED(MatIter) __source);

// THIS FUNCTION MODIFIES IN PLACE
TYPED(Matrix) *TYPED(Matrix_set_row_iter)(TYPED(Matrix) *__m, size_t __i, TYPED(MatIter) __source);

TYPED(MatIter) TYPED(Matrix_row_begin_from_col)(const TYPED(Matrix) *__A, size_t __i, size_t __j);

TYPED(MatIter) TYPED(Matrix_col_begin_from_row)(const TYPED(Matrix) *__A, size_t __j, size_t __i);

TYPED(MatIter) TYPED(Matrix_diag_end)(const TYPED(Matrix) *__m, const int __d);

TYPED(MatIter) TYPED(Matrix_diag_begin)(const TYPED(Matrix) *__m, const int __d);

 TYPED(Vector)*TYPED(MatIter_difference)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin);

#endif