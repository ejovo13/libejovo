#pragma once

// functions that deal with the creation of iterator objects

#include "matrix.h"

// TODO I think it might be a good idea to actually
//! implement the functions that use col iters
//! should be passing copies of the colIter and NOT a pointer
//! I don't really want to modify/ consume the iterator...

// /**================================================================================================
//  *!                                        Column Iterators
//  *================================================================================================**/
// ColIter *ColIter_new(MATRIX_TYPE *__ptr, size_t __ncols);

// ColIter *ColIter_clone(const ColIter *__c);

// void ColIter_free(ColIter *__c);

// void ColIter_next(ColIter *__c);

// // Return true if the __lhs and __rhs point to the same element
// bool ColIter_cmp(const ColIter *__lhs, const ColIter *__rhs);

// // ColIter *matcolpos(const Matrix *__A, size_t __i, size_t __j);


// // // return a new Column Iterator that points to the final element in this column
// // ColIter *Matrix_col_end(const Matrix *__A, size_t __j);

// // ColIter *Matrix_col_begin(const Matrix *__A, size_t __j);

// MATRIX_TYPE ColIter_value(const ColIter *__c);

// /**================================================================================================
//  *!                                        ColIter basic utility routines - SINGLE
//  *================================================================================================**/

// /**======================
//  *!    Scalar operations
//  *========================**/
// void ColIter_set(ColIter *__c, const MATRIX_TYPE __k);

// void ColIter_add_k(ColIter *__c, const MATRIX_TYPE __k);

// void ColIter_sub_k(ColIter *__c, const MATRIX_TYPE __k);

// void ColIter_mult_k(ColIter *__c, const MATRIX_TYPE __k);

// void ColIter_div_k(ColIter *__c, const MATRIX_TYPE __k);

// /**======================
//  *!    Pointer operations
//  *========================**/
// void ColIter_set_ptr(ColIter *__c, const MATRIX_TYPE *__ptr);

// void ColIter_add_ptr(ColIter *__c, const MATRIX_TYPE *__ptr);

// void ColIter_sub_ptr(ColIter *__c, const MATRIX_TYPE *__ptr);

// void ColIter_mult_ptr(ColIter *__c, const MATRIX_TYPE *__ptr);

// void ColIter_div_ptr(ColIter *__c, const MATRIX_TYPE *__ptr);

// /**======================
//  *!    Iterator functions
//  *========================**/
// void ColIter_set_iter(ColIter *__a, const ColIter *__b);

// void ColIter_add_iter(ColIter *__a, const ColIter *__b);

// void ColIter_sub_iter(ColIter *__a, const ColIter *__b);

// void ColIter_mult_iter(ColIter *__a, const ColIter *__b);

// void ColIter_div_iter(ColIter *__a, const ColIter *__b);

// /**================================================================================================
//  *!                                        ColIter basic utility routines - COLUMN
//  *================================================================================================**/

// // Set the elements of a row when given a row iterator and a value k
// void ColIter_col_set_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k);

// void ColIter_col_add_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k);

// void ColIter_col_sub_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k);

// void ColIter_col_mult_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k);

// void ColIter_col_div_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k);

// // Add to row __a the elements of row __b
// void ColIter_col_add_col(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin);

// /**================================================================================================
//  *!                                        Experimental APPLY functions
//  *================================================================================================**/

// // Appy functions are a way to iterate a ColIter until we reach the "end" point

// void ColIter_apply(ColIter *__cbegin, const ColIter *__cend, ColIterFn __fn);

// void ColIter_apply_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k, ColIterFn_k __fn_k);

// void ColIter_apply_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr, ColIterFn_ptr __fn_ptr);

// void ColIter_apply_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin, ColIterFn_iter __fn_iter);

// /**================================================================================================
//  *!                                        Col manipulations using apply functions
//  *================================================================================================**/

// /**======================
//  *!    Scalar operations
//  *========================**/
// void ColIter_apply_set_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k);

// void ColIter_apply_add_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k);

// void ColIter_apply_sub_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k);

// void ColIter_apply_mult_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k);

// void ColIter_apply_div_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k);

// /**======================
//  *!    Pointer operations
//  *========================**/

// void ColIter_apply_set_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr);

// void ColIter_apply_add_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr);

// void ColIter_apply_sub_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr);

// void ColIter_apply_mult_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr);

// void ColIter_apply_div_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr);

// /**======================
//  *!    Iterator operations
//  *========================**/

// void ColIter_apply_set_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin);

// void ColIter_apply_add_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin);

// void ColIter_apply_sub_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin);

// void ColIter_apply_mult_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin);

// void ColIter_apply_div_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin);

// /**================================================================================================
//  *!                                        Row Iterators
//  *================================================================================================**/
// RowIter *RowIter_new(MATRIX_TYPE *__ptr, size_t __ptr_diff);

// RowIter *RowIter_clone(const RowIter *__c);

// //! This function should actually never be called
// void RowIter_free(RowIter *__c);

// // Increment the row iter
// void RowIter_next(RowIter *__c);

// // Return true if the __lhs and __rhs point to the same element
// bool RowIter_cmp(const RowIter *__lhs, const RowIter *__rhs);

// // RowIter *matrowpos(const Matrix *__A, size_t __i, size_t __j);

// // // get row iterator without checking bounds
// // RowIter *matrowbegin(const Matrix *__A, size_t __i);

// // RowIter *matrowend(const Matrix *__A, size_t __i);

// // // return a new Column Iterator that points to the final element in this column
// // RowIter *Matrix_row_end(const Matrix *__A, size_t __i);

// // RowIter *Matrix_row_begin(const Matrix *__A, size_t __i);

// MATRIX_TYPE RowIter_value(const RowIter *__c);

// /**================================================================================================
//  *!                                        RowIter basic utility routines - SINGLE
//  *================================================================================================**/

// void RowIter_set(RowIter *__r, const MATRIX_TYPE __k);

// void RowIter_add_k(RowIter *__r, const MATRIX_TYPE __k);

// void RowIter_sub_k(RowIter *__r, const MATRIX_TYPE __k);

// void RowIter_mult_k(RowIter *__r, const MATRIX_TYPE __k);

// void RowIter_div_k(RowIter *__r, const MATRIX_TYPE __k);

// void RowIter_set_ptr(RowIter *__r, const MATRIX_TYPE *__ptr);

// void RowIter_add_ptr(RowIter *__r, const MATRIX_TYPE *__ptr);

// void RowIter_sub_ptr(RowIter *__r, const MATRIX_TYPE *__ptr);

// void RowIter_mult_ptr(RowIter *__r, const MATRIX_TYPE *__ptr);

// void RowIter_div_ptr(RowIter *__r, const MATRIX_TYPE *__ptr);

// void RowIter_set_iter(RowIter *__a, const RowIter *__b);

// void RowIter_add_iter(RowIter *__a, const RowIter *__b);

// void RowIter_add_iter_scaled(RowIter *__a, const RowIter *__b, const MATRIX_TYPE __k);

// void RowIter_sub_iter(RowIter *__a, const RowIter *__b);

// void RowIter_mult_iter(RowIter *__a, const RowIter *__b);

// void RowIter_div_iter(RowIter *__a, const RowIter *__b);

// // Get the maximum value in a row
// MATRIX_TYPE RowIter_max(RowIter *__a, const RowIter *__b);

// // Get the maximum value in a row
// MATRIX_TYPE RowIter_min(RowIter *__a, const RowIter *__b);



// /**================================================================================================
//  *!                                        RowIter basic utility routines - ROW
//  *================================================================================================**/

// // Set the elements of a row when given a row iterator and a value k
// void RowIter_row_set_k(const RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k);

// void RowIter_row_add_k(const RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k);

// void RowIter_row_sub_k(const RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k);

// void RowIter_row_mult_k(const RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k);

// void RowIter_row_div_k(const RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k);

// // Add to row __a the elements of row __b
// void RowIter_row_add_row(const RowIter *__abegin, const RowIter *__aend, const RowIter *__bbegin);


// /**================================================================================================
//  *!                                        Experimental APPLY functions
//  *================================================================================================**/

// // Appy functions are a way to iterate a ColIter until we reach the "end" point


// void RowIter_apply(const RowIter *__rbegin, const RowIter *__rend, RowIterFn __fn);

// void RowIter_apply_k(const RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k, RowIterFn_k __fn_k);

// void RowIter_apply_ptr(const RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr, RowIterFn_ptr __fn_ptr);

// void RowIter_apply_iter(const RowIter *__abegin, const RowIter *__aend, const RowIter *__bbegin, RowIterFn_iter __fn_iter);

// void RowIter_apply_iter_scaled(const RowIter *__abegin, const RowIter *__aend, const RowIter *__bbegin, const MATRIX_TYPE __k, RowIterFn_iter_k __fn_iter_k);

// /**================================================================================================
//  *!                                        Row manipulations using apply functions
//  *================================================================================================**/

// /**======================
//  *!    Scalar operations
//  *========================**/
// void RowIter_apply_set_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k);

// void RowIter_apply_add_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k);

// void RowIter_apply_sub_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k);

// void RowIter_apply_mult_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k);

// void RowIter_apply_div_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k);

// /**======================
//  *!    Pointer operations
//  *========================**/

// void RowIter_apply_set_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr);

// void RowIter_apply_add_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr);

// void RowIter_apply_sub_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr);

// void RowIter_apply_mult_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr);

// void RowIter_apply_div_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr);

// /**======================
//  *!    Iterator operations
//  *========================**/

// void RowIter_apply_set_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin);

// void RowIter_apply_add_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin);

// void RowIter_apply_sub_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin);

// void RowIter_apply_mult_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin);

// void RowIter_apply_div_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin);

// /**======================
//  *!    add iter scaled
//  *========================**/
// void RowIter_apply_add_iter_scaled(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin, const MATRIX_TYPE __k);

/**================================================================================================
 *!                                        RowCol and ColIter
 *================================================================================================**/

MATRIX_TYPE Iter_dot(const MatIter *__r, const MatIter *__rend, const MatIter *__c);




/**=======================================================================================================================
 *!                                           Matrix Interface to Iter functions
 *=======================================================================================================================**/

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



MatIter *matcolpos(const Matrix *__A, size_t __i, size_t __j);


// return a new Matumn Iterator that points to the final element in this column
MatIter *Matrix_col_end(const Matrix *__A, size_t __j);

MatIter *Matrix_col_begin(const Matrix *__A, size_t __j);

MatIter *matcolbegin(const Matrix *__A, size_t __i);

MatIter *matcolend(const Matrix *__A, size_t __i);

MatIter *matrowpos(const Matrix *__A, size_t __i, size_t __j);

// get row iterator without checking bounds
MatIter *matrowbegin(const Matrix *__A, size_t __i);

MatIter *matrowend(const Matrix *__A, size_t __i);

// return a new Column Iterator that points to the final element in this column
MatIter *Matrix_row_end(const Matrix *__A, size_t __i);

MatIter *Matrix_row_begin(const Matrix *__A, size_t __i);

/**=======================================================================================================================
 *!                                                   MIter that has more general capabilities
 *=======================================================================================================================**/
MatIter *MatIter_new(MATRIX_TYPE *__ptr, size_t __ptr_diff);

MatIter *MatIter_clone(const MatIter *__c);

//! This function should actually never be called
void MatIter_free(MatIter *__c);

// Increment the row iter
void MatIter_next(MatIter *__c);

// Return true if the __lhs and __rhs point to the same element
bool MatIter_cmp(const MatIter *__lhs, const MatIter *__rhs);

MATRIX_TYPE MatIter_value(const MatIter *__c);

// Return the number of iteration between begin and end
size_t MatIter_length(const MatIter *begin, const MatIter *end);

/**========================================================================
 *!                           Functional Iter functions
 *========================================================================**/
MATRIX_TYPE MatIter_sum(const MatIter *__begin, const MatIter *__end);

MATRIX_TYPE MatIter_prod(const MatIter *__begin, const MatIter *__end);

// Get the maximum value in a row
MATRIX_TYPE MatIter_max(MatIter *__a, const MatIter *__b);

// Get the maximum value in a row
MATRIX_TYPE MatIter_min(MatIter *__a, const MatIter *__b);

/**================================================================================================
 *!                                        MatIter basic utility routines - SINGLE
 *================================================================================================**/

void MatIter_set(MatIter *__r, const MATRIX_TYPE __k);

void MatIter_add_k(MatIter *__r, const MATRIX_TYPE __k);

void MatIter_sub_k(MatIter *__r, const MATRIX_TYPE __k);

void MatIter_mult_k(MatIter *__r, const MATRIX_TYPE __k);

void MatIter_div_k(MatIter *__r, const MATRIX_TYPE __k);

void MatIter_set_ptr(MatIter *__r, const MATRIX_TYPE *__ptr);

void MatIter_add_ptr(MatIter *__r, const MATRIX_TYPE *__ptr);

void MatIter_sub_ptr(MatIter *__r, const MATRIX_TYPE *__ptr);

void MatIter_mult_ptr(MatIter *__r, const MATRIX_TYPE *__ptr);

void MatIter_div_ptr(MatIter *__r, const MATRIX_TYPE *__ptr);

void MatIter_set_iter(MatIter *__a, const MatIter *__b);

void MatIter_add_iter(MatIter *__a, const MatIter *__b);

void MatIter_add_iter_scaled(MatIter *__a, const MatIter *__b, const MATRIX_TYPE __k);

void MatIter_sub_iter(MatIter *__a, const MatIter *__b);

void MatIter_mult_iter(MatIter *__a, const MatIter *__b);

void MatIter_div_iter(MatIter *__a, const MatIter *__b);





/**================================================================================================
 *!                                        MatIter basic utility routines - ROW
 *================================================================================================**/

// Set the elements of a row when given a row iterator and a value k
void MatIter_row_set_k(const MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k);

void MatIter_row_add_k(const MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k);

void MatIter_row_sub_k(const MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k);

void MatIter_row_mult_k(const MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k);

void MatIter_row_div_k(const MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k);

// Add to row __a the elements of row __b
void MatIter_row_add_row(const MatIter *__abegin, const MatIter *__aend, const MatIter *__bbegin);


/**================================================================================================
 *!                                        Experimental APPLY functions
 *================================================================================================**/

// Appy functions are a way to iterate a ColIter until we reach the "end" point


void MatIter_apply(const MatIter *__rbegin, const MatIter *__rend, MatIterFn __fn);

void MatIter_apply_k(const MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k, MatIterFn_k __fn_k);

void MatIter_apply_ptr(const MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE *__ptr, MatIterFn_ptr __fn_ptr);

void MatIter_apply_iter(const MatIter *__abegin, const MatIter *__aend, const MatIter *__bbegin, MatIterFn_iter __fn_iter);

void MatIter_apply_iter_scaled(const MatIter *__abegin, const MatIter *__aend, const MatIter *__bbegin, const MATRIX_TYPE __k, MatIterFn_iter_k __fn_iter_k);

/**================================================================================================
 *!                                        Mat manipulations using apply functions
 *================================================================================================**/

/**======================
 *!    Scalar operations
 *========================**/
void MatIter_apply_set_k(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k);

void MatIter_apply_add_k(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k);

void MatIter_apply_sub_k(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k);

void MatIter_apply_mult_k(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k);

void MatIter_apply_div_k(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k);

/**======================
 *!    Pointer operations
 *========================**/

void MatIter_apply_set_ptr(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE *__ptr);

void MatIter_apply_add_ptr(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE *__ptr);

void MatIter_apply_sub_ptr(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE *__ptr);

void MatIter_apply_mult_ptr(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE *__ptr);

void MatIter_apply_div_ptr(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE *__ptr);

/**======================
 *!    Iterator operations
 *========================**/

void MatIter_apply_set_iter(MatIter *__abegin, const MatIter *__aend, MatIter *__bbegin);

void MatIter_apply_add_iter(MatIter *__abegin, const MatIter *__aend, MatIter *__bbegin);

void MatIter_apply_sub_iter(MatIter *__abegin, const MatIter *__aend, MatIter *__bbegin);

void MatIter_apply_mult_iter(MatIter *__abegin, const MatIter *__aend, MatIter *__bbegin);

void MatIter_apply_div_iter(MatIter *__abegin, const MatIter *__aend, MatIter *__bbegin);

/**======================
 *!    add iter scaled
 *========================**/
void MatIter_apply_add_iter_scaled(MatIter *__abegin, const MatIter *__aend, MatIter *__bbegin, const MATRIX_TYPE __k);


