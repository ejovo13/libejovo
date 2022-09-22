#pragma once

// Define a series of functions that deal with looping through all of the elements of a matrix,
// looping through all of the columns of a matrix, in essence this file deals with iteration
#include "matrix.h"

/**================================================================================================
 *!                                        Single functions
 *================================================================================================**/

// series of functions used to add two elements that Matrix_access pointers are pointing to
void add_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b);

// I'm going to want to use this for computing the LU decomposition
void sub_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b);

void mult_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b);

void div_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b);

//* Matrix times scalar

void multscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k);

void addscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k);

void divscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k);

void subscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k);

/**================================================================================================
 *!                                        Foreach loops
 *================================================================================================**/

void Matrix_foreach(Matrix *__A, EDITOR __fnc);

void Matrix_foreach_2(Matrix *__A, const Matrix *__B, EDITOR_2 __fnc);

void Matrix_foreach_k(Matrix *__A, EDITOR_K __fnc, MATRIX_TYPE __k);

/**================================================================================================
 *!                                        Single function + foreach loop
 *================================================================================================**/


// add a __B to __A, mutating __A in place, using a "foreach" construct
void matadd_foreach(Matrix *__A, const Matrix *__B);

void matsub_foreach(Matrix *__A, const Matrix *__B);

void matmult_foreach(Matrix *__A, const Matrix *__B);

void matdiv_foreach(Matrix *__A, const Matrix *__B);

void matmultscalar(Matrix *__A, const MATRIX_TYPE __k);

void mataddscalar(Matrix *__A, const MATRIX_TYPE __k);

void matdivscalar(Matrix *__A, const MATRIX_TYPE __k);

void matsubscalar(Matrix *__A, const MATRIX_TYPE __k);

MATRIX_TYPE matsum(const Matrix *__A);

MATRIX_TYPE matmin(const Matrix *__A);

MATRIX_TYPE matmax(const Matrix *__A);


/**================================================================================================
 *!                                       Matrix API foreach
 *================================================================================================**/

Matrix *Matrix_mult_scalar(const Matrix *__A, const MATRIX_TYPE __k);

Matrix *Matrix_add_scalar(const Matrix *__A, const MATRIX_TYPE __k);

Matrix *Matrix_sub_scalar(const Matrix *__A, const MATRIX_TYPE __k);

Matrix *Matrix_div_scalar(const Matrix *__A, const MATRIX_TYPE __k);


/**================================================================================================
 *!                                        Matrix Mask functions
 *================================================================================================**/

/**
 * Perform an operation on a matrix when a given mask evaluates to true
 */
void Matrix_mask(Matrix *__A, Mask __mask, EDITOR __operator);
// __mask is only applied to matrix __A
void Matrix_mask_2(Matrix *__A, Matrix *__B, Mask __mask, EDITOR_2 __operator);

void Matrix_mask_k(Matrix *__A, Mask __mask, EDITOR_K __operator, const MATRIX_TYPE __k);