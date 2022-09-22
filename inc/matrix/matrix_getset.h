#pragma once

// Essential routines to get and set elements and columns and rows of matrices

#include "matrix.h"

/**================================================================================================
 *!                                        Set/Get Individual Elements
 *================================================================================================**/

// return the value of the element at __m(__i, __j) [zero indexed]
// return -1 if bounds are not respected and prints an error to the screen
MATRIX_TYPE Matrix_at(const Matrix *__m, size_t __i, size_t __j);

MATRIX_TYPE matget(const Matrix *__m, size_t __i);

MATRIX_TYPE Matrix_first(const Matrix *__m);

MATRIX_TYPE Matrix_last(const Matrix *__m);

MatIter Matrix_begin(const Matrix *__m);

MatIter Matrix_end(const Matrix *__m);

// Return element at __m[__i][__j] without checking bounds
MATRIX_TYPE matat(const Matrix *__m, size_t __i, size_t __j);

// set value of the element at __m(__i, __j) [zero indexed]
// return 0 if the bounds were respected, -1 elsewise
int Matrix_set(Matrix * __m, size_t __i, size_t __j, MATRIX_TYPE __value);

// set value of the element at __m(__i, __j) without checking the indices
void matset(Matrix *__m, size_t __i, size_t __j, MATRIX_TYPE __value);

// return a pointer to the element at __m(__i, __j) [zero indexed]
MATRIX_TYPE *Matrix_access(const Matrix * __m, size_t __i, size_t __j);

// return a pointer to the element at __m(__i, __j) without checking the indices
MATRIX_TYPE *matacc(const Matrix *__m, size_t __i, size_t __j);

// return a pointer to the element at __m(__i, __j) checking the indices
// returns null if the bounds are not respected
MATRIX_TYPE *matacc_check(const Matrix *__m, size_t __i, size_t __j);
/**
 * Set the element that a pointer is pointing to to __value
 */
void setelement(MATRIX_TYPE *__el, const MATRIX_TYPE __value);

// Swap __a and __b
void matswap(MATRIX_TYPE *__a, MATRIX_TYPE *__b);

/**================================================================================================
 *!                                        Set/Get range of elements
 *================================================================================================**/

// Copy the matrix __src into the submatrix of __dest prescribed by the start and end indices
int matcpyele(Matrix * __dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, Matrix * __src);

// Copy the elements of __src into the submatrix of __dest prescribed by the start and end indices WITHOUT CHECKING THE BOUNDS
void matcpyele_unsafe(Matrix *__dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, Matrix *__src);

/**================================================================================================
 *!                                        Set/Get Rows/Cols
 *================================================================================================**/

// Set the first __n indices of row __i, starting at column __j
void matsetrow(Matrix *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n);

void matsetcol(Matrix *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n);

// matsetrow_mult_k
// matsetrow_div_k
// matsetrow_sub_k
// matsetrow_add_k

// multiply the row of a matrix times the value __k
void matsetrow_mult_k(Matrix *__A, MatIter __r, const MatIter __row_end, MATRIX_TYPE __k);

// multiply the row of a matrix times the value __k
void matsetrow_div_k(Matrix *__A, MatIter __r, const MatIter __row_end, MATRIX_TYPE __k);
// multiply the row of a matrix times the value __k
void matsetrow_add_k(Matrix *__A, MatIter __r, const MatIter __row_end, MATRIX_TYPE __k);

// multiply the row of a matrix times the value __k
void matsetrow_sub_k(Matrix *__A, MatIter __r, const MatIter __row_end, MATRIX_TYPE __k);

int Matrix_mult_row_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);

int Matrix_div_row_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);
int Matrix_add_row_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);

int Matrix_sub_row_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);

// editing columns now
void matsetcol_mult_k(Matrix *__A, MatIter __c, const MatIter __col_end, MATRIX_TYPE __k);

// multiply the col of a matrix times the value __k
void matsetcol_div_k(Matrix *__A, MatIter __c, const MatIter __col_end, MATRIX_TYPE __k);
// multiply the col of a matrix times the value __k
void matsetcol_add_k(Matrix *__A, MatIter __c, const MatIter __col_end, MATRIX_TYPE __k);

// multiply the col of a matrix times the value __k
void matsetcol_sub_k(Matrix *__A, MatIter __c, const MatIter __col_end, MATRIX_TYPE __k);

int Matrix_mult_col_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);

int Matrix_div_col_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);
int Matrix_add_col_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);

int Matrix_sub_col_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);




// SETS THE iTH ROW OF __A USING A ROW VECTOR!!!! That is, a ONE by M matrix
int Matrix_set_row(Matrix *__A, size_t __i, const Matrix *__cow);

// SETS THE iTH ROW OF __A USING A ROW VECTOR!!!! That is, a ONE by M matrix
int Matrix_set_col(Matrix *__A, size_t __j, const Matrix *__col);

// It is remarkably faster to extract a specific row since we are just memcpy a certain period of bytes!
Matrix *Matrix_get_col(const Matrix *__A, size_t __j);

// On the other hand, matrow is quite slow since we have to access the elements with a for loop.
// As a design choice, I'd like to implement some sort of low level "row iterator" that will allow us
// to iterate allong the row of a Matrix (to access it later) without actually performing a copy
Matrix *Matrix_get_row(const Matrix *__A, size_t __i);

// I want to create a function that is going to multiply the row of a matrix, starting with it's row iterator.








/**================================================================================================
 *!                                        Set/Get Submatrices
 *================================================================================================**/

// Extract submatrix __A(__istart:__iend, __jstart:__jend)
// This allocates a completely new matrix
Matrix * submat(const Matrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

// Alternative spelling for object-oriented approach.
Matrix * Matrix_submat(const Matrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

Matrix * Matrix_minor(const Matrix * __A, size_t __irow, size_t __icol);

/**================================================================================================
 *!                                        Set/Get Matrices
 *================================================================================================**/

void matfill(Matrix *__A, const MATRIX_TYPE __value);

// fill matrix with a single value
void Matrix_fill(Matrix * __A, const MATRIX_TYPE value);

/**
 * Set all of the elements who fulfill a mask equal to the value
 */
void Matrix_fill_mask(Matrix *__A, Mask __mask, const MATRIX_TYPE __value);

Matrix * Matrix_rcat(Matrix * __A, Matrix * __B);

Matrix * Matrix_ccat(Matrix * __A, Matrix * __B);