#pragma once

// functions that deal with the creation of iterator objects

#include "matrix.h"

// TODO I need to add checks for some of my iterator functions like matdiagend -> Matrix_diag_end

/**================================================================================================
 *!                                        Special Types of Iterators
 *================================================================================================**/
// Should have row, col, diagonal iterators. There are even some special iterators like "checkerboards"
// that can hit every other element.

MatIter matdiagbegin(const Matrix *__m, const int __d);

MatIter matdiagend(const Matrix *__m, const int __d);

void MatIter_print(const MatIter __begin, const MatIter __end);


// The 0th diagonal will start at the position __m(0, 0)
// The 1st diagonal will start at the position __m(0, 1)
// The -1  diagonal will start at the position __m(1, 0)
// MatIter Matrix_diag_begin(const Matrix *__m, const int __d);






/**================================================================================================
 *!                                        RowCol and ColIter
 *================================================================================================**/

MATRIX_TYPE Iter_dot(const MatIter __r, const MatIter __rend, const MatIter __c);

/**=======================================================================================================================
 *!                                           Matrix Interface to Iter functions
 *=======================================================================================================================**/

void Matrix_print_row(const Matrix *__A, size_t __i);

void Matrix_print_col(const Matrix *__A, size_t __j);


void Matrix_print_diag(const Matrix *__A, size_t __d);

// Here I want to be able to manipulate the functions defined above to create clean and simple Matrix api

// let's start simple and add rows together

// matrix elementary row operation (add two rows)
void matrowop_add(Matrix *__A, const size_t __r1, const size_t __r2, const size_t __col_offset);

// matrix elementary row operation (add two rows)
void matrowop_add_scaled(Matrix *__A, const size_t __r1, const size_t __r2, const MATRIX_TYPE __k, const size_t __col_offset);

void Matrix_rowop_add(Matrix *__A, const size_t __r1, const size_t __r2);

void Matrix_rowop_add_offset(Matrix *__A, const size_t __r1, const size_t __r2, const size_t __col_offset);

void Matrix_rowop_add_scaled(Matrix *__A, const size_t __r1, const size_t __r2, const MATRIX_TYPE __k);

MATRIX_TYPE Matrix_row_min(const Matrix *__A, const size_t __i);

MATRIX_TYPE Matrix_row_max(const Matrix *__A, const size_t __i);

MATRIX_TYPE Matrix_col_min(const Matrix *__A, const size_t __j);

MATRIX_TYPE Matrix_col_max(const Matrix *__A, const size_t __j);

MATRIX_TYPE Matrix_diag_min(const Matrix *__A, const size_t __j);

MATRIX_TYPE Matrix_diag_max(const Matrix *__A, const size_t __j);

MATRIX_TYPE Matrix_row_prod(const Matrix *__A, const size_t __i);

MATRIX_TYPE Matrix_col_prod(const Matrix *__A, const size_t __i);

MATRIX_TYPE Matrix_diag_prod(const Matrix *__A, const size_t __i);


MATRIX_TYPE Matrix_row_sum(const Matrix *__A, const size_t __i);

MATRIX_TYPE Matrix_col_sum(const Matrix *__A, const size_t __i);

MATRIX_TYPE Matrix_diag_sum(const Matrix *__A, const size_t __i);



MatIter matcolpos(const Matrix *__A, size_t __i, size_t __j);

// return a new Matumn Iterator that points to the final element in this column
MatIter Matrix_col_end(const Matrix *__A, size_t __j);

MatIter Matrix_col_begin(const Matrix *__A, size_t __j);

MatIter matcolbegin(const Matrix *__A, size_t __i);

MatIter matcolend(const Matrix *__A, size_t __i);

MatIter matrowpos(const Matrix *__A, size_t __i, size_t __j);

// get row iterator without checking bounds
MatIter matrowbegin(const Matrix *__A, size_t __i);

MatIter matrowend(const Matrix *__A, size_t __i);

// return a new Column Iterator that points to the final element in this column
MatIter Matrix_row_end(const Matrix *__A, size_t __i);

MatIter Matrix_row_begin(const Matrix *__A, size_t __i);

/**=======================================================================================================================
 *!                                                   MIter that has more general capabilities
 *=======================================================================================================================**/
MatIter MatIter_new(MATRIX_TYPE *__ptr, size_t __ptr_diff);

MatIter MatIter_null();

bool MatIter_is_null(MatIter __i);

// Increment the row iter
MatIter MatIter_next(MatIter __c);

// Return true if the __lhs and __rhs point to the same element
bool MatIter_cmp(const MatIter __lhs, const MatIter __rhs);

MATRIX_TYPE MatIter_value(const MatIter __c);

// Return the number of iteration between begin and end
size_t MatIter_length(const MatIter begin, const MatIter end);

/**========================================================================
 *!                           Functional Iter functions
 *========================================================================**/
MATRIX_TYPE MatIter_sum(const MatIter __begin, const MatIter __end);

MATRIX_TYPE MatIter_prod(const MatIter __begin, const MatIter __end);

// Get the maximum value in a row
MATRIX_TYPE MatIter_max(MatIter __a, const MatIter __b);

// Get the maximum value in a row
MATRIX_TYPE MatIter_min(MatIter __a, const MatIter __b);

/**================================================================================================
 *!                                        MatIter basic utility routines - SINGLE
 *================================================================================================**/

void MatIter_set(MatIter __r, const MATRIX_TYPE __k);

void MatIter_add_k(MatIter __r, const MATRIX_TYPE __k);

void MatIter_sub_k(MatIter __r, const MATRIX_TYPE __k);

void MatIter_mult_k(MatIter __r, const MATRIX_TYPE __k);

void MatIter_div_k(MatIter __r, const MATRIX_TYPE __k);

void MatIter_set_ptr(MatIter __r, const MATRIX_TYPE *__ptr);

void MatIter_add_ptr(MatIter __r, const MATRIX_TYPE *__ptr);

void MatIter_sub_ptr(MatIter __r, const MATRIX_TYPE *__ptr);

void MatIter_mult_ptr(MatIter __r, const MATRIX_TYPE *__ptr);

void MatIter_div_ptr(MatIter __r, const MATRIX_TYPE *__ptr);

void MatIter_set_iter(MatIter __a, const MatIter __b);

void MatIter_set_iter_pow(MatIter __a, const MatIter __b, double __n);

void MatIter_add_iter(MatIter __a, const MatIter __b);

void MatIter_add_iter_scaled(MatIter __a, const MatIter __b, const MATRIX_TYPE __k);

void MatIter_sub_iter(MatIter __a, const MatIter __b);

void MatIter_mult_iter(MatIter __a, const MatIter __b);

void MatIter_div_iter(MatIter __a, const MatIter __b);





/**================================================================================================
 *!                                        MatIter basic utility routines - ROW
 *================================================================================================**/

// Set the elements of a row when given a row iterator and a value k
void MatIter_row_set_k(const MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k);

// Set the elements of a row when given a row iterator and another starting iterator
void MatIter_row_set_iter(const MatIter __rbegin, const MatIter __rend, const MatIter __bbegin);


void MatIter_row_add_k(const MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k);

void MatIter_row_sub_k(const MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k);

void MatIter_row_mult_k(const MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k);

void MatIter_row_div_k(const MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k);

// Add to row __a the elements of row __b
void MatIter_row_add_row(const MatIter __abegin, const MatIter __aend, const MatIter __bbegin);


/**================================================================================================
 *!                                        Experimental APPLY functions
 *================================================================================================**/

// Appy functions are a way to iterate a ColIter until we reach the "end" point


void MatIter_apply(const MatIter __rbegin, const MatIter __rend, MatIterFn __fn);

void MatIter_apply_k(const MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k, MatIterFn_k __fn_k);

void MatIter_apply_ptr(const MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE *__ptr, MatIterFn_ptr __fn_ptr);

void MatIter_apply_iter(const MatIter __abegin, const MatIter __aend, const MatIter __bbegin, MatIterFn_iter __fn_iter);

void MatIter_apply_iter_scaled(const MatIter __abegin, const MatIter __aend, const MatIter __bbegin, const MATRIX_TYPE __k, MatIterFn_iter_k __fn_iter_k);

/**================================================================================================
 *!                                        Mat manipulations using apply functions
 *================================================================================================**/

/**======================
 *!    Scalar operations
 *========================**/
void MatIter_apply_set_k(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k);

void MatIter_apply_add_k(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k);

void MatIter_apply_sub_k(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k);

void MatIter_apply_mult_k(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k);

void MatIter_apply_div_k(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k);

/**======================
 *!    Pointer operations
 *========================**/

void MatIter_apply_set_ptr(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE *__ptr);

void MatIter_apply_add_ptr(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE *__ptr);

void MatIter_apply_sub_ptr(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE *__ptr);

void MatIter_apply_mult_ptr(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE *__ptr);

void MatIter_apply_div_ptr(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE *__ptr);

/**======================
 *!    Iterator operations
 *========================**/

void MatIter_apply_set_iter(MatIter __abegin, const MatIter __aend, MatIter __bbegin);

void MatIter_apply_set_iter_pow(MatIter __abegin, const MatIter __aend, MatIter __bbegin, double __n);

void MatIter_apply_add_iter(MatIter __abegin, const MatIter __aend, MatIter __bbegin);

void MatIter_apply_sub_iter(MatIter __abegin, const MatIter __aend, MatIter __bbegin);

void MatIter_apply_mult_iter(MatIter __abegin, const MatIter __aend, MatIter __bbegin);

void MatIter_apply_div_iter(MatIter __abegin, const MatIter __aend, MatIter __bbegin);

/**======================
 *!    add iter scaled
 *========================**/
void MatIter_apply_add_iter_scaled(MatIter __abegin, const MatIter __aend, MatIter __bbegin, const MATRIX_TYPE __k);


