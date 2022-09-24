#ifndef MATRIX_ITER_H
#define MATRIX_ITER_H

// functions that deal with the creation of iterator objects

#include "matrix.h"

// TODO I need to add checks for some of my iterator functions like matdiagend -> MATRIX_FN(diag_end)

/**================================================================================================
 *!                                        Special Types of Iterators
 *================================================================================================**/
// Should have row, col, diagonal iterators. There are even some special iterators like "checkerboards"
// that can hit every other element.

MATITER_T MAT_FN(diagbegin)(const MATRIX_T *__m, const int __d);

MATITER_T MAT_FN(diagend)(const MATRIX_T *__m, const int __d);

void MATITER_FN(print)(const MATITER_T __begin, const MATITER_T __end);


// The 0th diagonal will start at the position __m(0, 0)
// The 1st diagonal will start at the position __m(0, 1)
// The -1  diagonal will start at the position __m(1, 0)
// MATITER_T MATRIX_FN(diag_begin)(const MATRIX_T *__m, const int __d);






/**================================================================================================
 *!                                        RowCol and ColIter
 *================================================================================================**/

MATRIX_TYPE TYPED_FN(Iter_dot)(const MATITER_T __r, const MATITER_T __rend, const MATITER_T __c);

/**=======================================================================================================================
 *!                                           MATRIX_T Interface to Iter functions
 *=======================================================================================================================**/

void MATRIX_FN(print_row)(const MATRIX_T *__A, size_t __i);

void MATRIX_FN(print_col)(const MATRIX_T *__A, size_t __j);


void MATRIX_FN(print_diag)(const MATRIX_T *__A, size_t __d);

// Here I want to be able to manipulate the functions defined above to create clean and simple MATRIX_T api

// let's start simple and add rows together

// matrix elementary row operation (add two rows)
void MAT_FN(rowop_add)(MATRIX_T *__A, const size_t __r1, const size_t __r2, const size_t __col_offset);

// matrix elementary row operation (add two rows)
void MAT_FN(rowop_add_scaled)(MATRIX_T *__A, const size_t __r1, const size_t __r2, const MATRIX_TYPE __k, const size_t __col_offset);

void MATRIX_FN(rowop_add)(MATRIX_T *__A, const size_t __r1, const size_t __r2);

void MATRIX_FN(rowop_add_offset)(MATRIX_T *__A, const size_t __r1, const size_t __r2, const size_t __col_offset);

void MATRIX_FN(rowop_add_scaled)(MATRIX_T *__A, const size_t __r1, const size_t __r2, const MATRIX_TYPE __k);

MATRIX_TYPE MATRIX_FN(row_min)(const MATRIX_T *__A, const size_t __i);

MATRIX_TYPE MATRIX_FN(row_max)(const MATRIX_T *__A, const size_t __i);

MATRIX_TYPE MATRIX_FN(col_min)(const MATRIX_T *__A, const size_t __j);

MATRIX_TYPE MATRIX_FN(col_max)(const MATRIX_T *__A, const size_t __j);

MATRIX_TYPE MATRIX_FN(diag_min)(const MATRIX_T *__A, const size_t __j);

MATRIX_TYPE MATRIX_FN(diag_max)(const MATRIX_T *__A, const size_t __j);

MATRIX_TYPE MATRIX_FN(row_prod)(const MATRIX_T *__A, const size_t __i);

MATRIX_TYPE MATRIX_FN(col_prod)(const MATRIX_T *__A, const size_t __i);

MATRIX_TYPE MATRIX_FN(diag_prod)(const MATRIX_T *__A, const size_t __i);


MATRIX_TYPE MATRIX_FN(row_sum)(const MATRIX_T *__A, const size_t __i);

MATRIX_TYPE MATRIX_FN(col_sum)(const MATRIX_T *__A, const size_t __i);

MATRIX_TYPE MATRIX_FN(diag_sum)(const MATRIX_T *__A, const size_t __i);



MATITER_T MAT_FN(colpos)(const MATRIX_T *__A, size_t __i, size_t __j);

// return a new Matumn Iterator that points to the final element in this column
MATITER_T MATRIX_FN(col_end)(const MATRIX_T *__A, size_t __j);

MATITER_T MATRIX_FN(col_begin)(const MATRIX_T *__A, size_t __j);

MATITER_T MAT_FN(colbegin)(const MATRIX_T *__A, size_t __i);

MATITER_T MAT_FN(colend)(const MATRIX_T *__A, size_t __i);

MATITER_T MAT_FN(rowpos)(const MATRIX_T *__A, size_t __i, size_t __j);

// get row iterator without checking bounds
MATITER_T MAT_FN(rowbegin)(const MATRIX_T *__A, size_t __i);

MATITER_T MAT_FN(rowend)(const MATRIX_T *__A, size_t __i);

// return a new Column Iterator that points to the final element in this column
MATITER_T MATRIX_FN(row_end)(const MATRIX_T *__A, size_t __i);

MATITER_T MATRIX_FN(row_begin)(const MATRIX_T *__A, size_t __i);

/**=======================================================================================================================
 *!                                                   MIter that has more general capabilities
 *=======================================================================================================================**/
MATITER_T MATITER_NEW(MATRIX_TYPE *__ptr, size_t __ptr_diff);

MATITER_T MATITER_FN(null)();

bool MATITER_FN(is_null)(MATITER_T __i);

// Increment the row iter
MATITER_T MATITER_FN(next)(MATITER_T __c);

// Return true if the __lhs and __rhs point to the same element
bool MATITER_FN(cmp)(const MATITER_T __lhs, const MATITER_T __rhs);

MATRIX_TYPE MATITER_FN(value)(const MATITER_T __c);

// Return the number of iteration between begin and end
size_t MATITER_FN(length)(const MATITER_T begin, const MATITER_T end);

/**========================================================================
 *!                           Functional Iter functions
 *========================================================================**/
MATRIX_TYPE MATITER_FN(sum)(const MATITER_T __begin, const MATITER_T __end);

MATRIX_TYPE MATITER_FN(prod)(const MATITER_T __begin, const MATITER_T __end);

// Get the maximum value in a row
MATRIX_TYPE MATITER_FN(max)(MATITER_T __a, const MATITER_T __b);

// Get the maximum value in a row
MATRIX_TYPE MATITER_FN(min)(MATITER_T __a, const MATITER_T __b);

/**================================================================================================
 *!                                        MATITER_T basic utility routines - SINGLE
 *================================================================================================**/

void MATITER_FN(set)(MATITER_T __r, const MATRIX_TYPE __k);

void MATITER_FN(add_k)(MATITER_T __r, const MATRIX_TYPE __k);

void MATITER_FN(sub_k)(MATITER_T __r, const MATRIX_TYPE __k);

void MATITER_FN(mult_k)(MATITER_T __r, const MATRIX_TYPE __k);

void MATITER_FN(div_k)(MATITER_T __r, const MATRIX_TYPE __k);

void MATITER_FN(set_ptr)(MATITER_T __r, const MATRIX_TYPE *__ptr);

void MATITER_FN(add_ptr)(MATITER_T __r, const MATRIX_TYPE *__ptr);

void MATITER_FN(sub_ptr)(MATITER_T __r, const MATRIX_TYPE *__ptr);

void MATITER_FN(mult_ptr)(MATITER_T __r, const MATRIX_TYPE *__ptr);

void MATITER_FN(div_ptr)(MATITER_T __r, const MATRIX_TYPE *__ptr);

void MATITER_FN(set_iter)(MATITER_T __a, const MATITER_T __b);

void MATITER_FN(set_iter_pow)(MATITER_T __a, const MATITER_T __b, double __n);

void MATITER_FN(add_iter)(MATITER_T __a, const MATITER_T __b);

void MATITER_FN(add_iter_scaled)(MATITER_T __a, const MATITER_T __b, const MATRIX_TYPE __k);

void MATITER_FN(sub_iter)(MATITER_T __a, const MATITER_T __b);

void MATITER_FN(mult_iter)(MATITER_T __a, const MATITER_T __b);

void MATITER_FN(div_iter)(MATITER_T __a, const MATITER_T __b);





/**================================================================================================
 *!                                        MATITER_T basic utility routines - ROW
 *================================================================================================**/

// Set the elements of a row when given a row iterator and a value k
void MATITER_FN(row_set_k)(const MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k);

// Set the elements of a row when given a row iterator and another starting iterator
void MATITER_FN(row_set_iter)(const MATITER_T __rbegin, const MATITER_T __rend, const MATITER_T __bbegin);


void MATITER_FN(row_add_k)(const MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k);

void MATITER_FN(row_sub_k)(const MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k);

void MATITER_FN(row_mult_k)(const MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k);

void MATITER_FN(row_div_k)(const MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k);

// Add to row __a the elements of row __b
void MATITER_FN(row_add_row)(const MATITER_T __abegin, const MATITER_T __aend, const MATITER_T __bbegin);


/**================================================================================================
 *!                                        Experimental APPLY functions
 *================================================================================================**/

// Appy functions are a way to iterate a ColIter until we reach the "end" point


void MATITER_FN(apply)(const MATITER_T __rbegin, const MATITER_T __rend, TYPED(MatIterFn) __fn);

void MATITER_FN(apply_k)(const MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k, TYPED(MatIterFn_k) __fn_k);

void MATITER_FN(apply_ptr)(const MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE *__ptr, TYPED(MatIterFn_ptr) __fn_ptr);

void MATITER_FN(apply_iter)(const MATITER_T __abegin, const MATITER_T __aend, const MATITER_T __bbegin, TYPED(MatIterFn_iter) __fn_iter);

void MATITER_FN(apply_iter_scaled)(const MATITER_T __abegin, const MATITER_T __aend, const MATITER_T __bbegin, const MATRIX_TYPE __k, TYPED(MatIterFn_iter_k) __fn_iter_k);

/**================================================================================================
 *!                                        Mat manipulations using apply functions
 *================================================================================================**/

/**======================
 *!    Scalar operations
 *========================**/
void MATITER_FN(apply_set_k)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k);

void MATITER_FN(apply_add_k)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k);

void MATITER_FN(apply_sub_k)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k);

void MATITER_FN(apply_mult_k)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k);

void MATITER_FN(apply_div_k)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k);

/**======================
 *!    Pointer operations
 *========================**/

void MATITER_FN(apply_set_ptr)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE *__ptr);

void MATITER_FN(apply_add_ptr)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE *__ptr);

void MATITER_FN(apply_sub_ptr)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE *__ptr);

void MATITER_FN(apply_mult_ptr)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE *__ptr);

void MATITER_FN(apply_div_ptr)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE *__ptr);

/**======================
 *!    Iterator operations
 *========================**/

void MATITER_FN(apply_set_iter)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin);

void MATITER_FN(apply_set_iter_pow)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin, double __n);

void MATITER_FN(apply_add_iter)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin);

void MATITER_FN(apply_sub_iter)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin);

void MATITER_FN(apply_mult_iter)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin);

void MATITER_FN(apply_div_iter)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin);

/**======================
 *!    add iter scaled
 *========================**/
void MATITER_FN(apply_add_iter_scaled)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin, const MATRIX_TYPE __k);

MATRIX_T *MATRIX_FN(set_col_iter)(MATRIX_T *__m, size_t __j, MATITER_T __source);

// THIS FUNCTION MODIFIES IN PLACE
MATRIX_T *MATRIX_FN(set_row_iter)(MATRIX_T *__m, size_t __i, MATITER_T __source);

MATITER_T MATRIX_FN(row_begin_from_col)(const MATRIX_T *__A, size_t __i, size_t __j);

MATITER_T MATRIX_FN(col_begin_from_row)(const MATRIX_T *__A, size_t __j, size_t __i);

MATITER_T MATRIX_FN(diag_end)(const MATRIX_T *__m, const int __d);

MATITER_T MATRIX_FN(diag_begin)(const MATRIX_T *__m, const int __d);

Vector *MATITER_FN(difference)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin);

#endif