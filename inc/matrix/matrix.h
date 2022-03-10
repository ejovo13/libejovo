#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "ejovo_rand.h"
#include <string.h>
#include <stdarg.h>
// #include "ejovo_comp.h"

/** @file
 *
 *  @brief Implement a Matrix framework for performing basic Linear Algebra tasks
 *
 *  In order to tackle the exercises prescribed in TP4, I decided to create a matrix framework to make my life
 *  easier when writing the matrix multiplication and determinant finding routines.
 *
 *  @author Evan Voyles
 *  @date 16 October 2021
 *
 */


// Type of the matrix that will be determined at compile time. Should be a numberic value like `float` or `int`
#ifndef MATRIX_TYPE
#define MATRIX_TYPE double
#endif

#define MAX_STEP_SIZE 100000

const extern double PI;
const extern double TWO_PI;
const extern double HALF_PI;

/**
 * @brief Matrix structure that simulates a 2d matrix accessed by A(row, col).
 *
 * The Matrix structure contains valuable information about the number of rows and number of columns
 * stored in order to perform necessary logistic checks at execution time.
 * For example, two matrices can be added to each other if and only if they are the same size; *
 */
typedef struct mat_t {
    MATRIX_TYPE *data; // SUPER IMPORTANT!!! I am declaring that the underlying data
                                // is only ever accessed by one pointer! In terms of Rust,
                                // data is the only owner of the matrix elements
    size_t nrows;
    size_t ncols;
} Matrix;

extern Matrix *g_ANON;

// Iterate through a column, stopping when we've reached the final element
/**
 * @brief A C++ style iterator that iterates along a Matrix's column.
 *
 * A ColIter contains minimal information that allows it to access the proper memory locations
 * in an iterative fashion that correspond to the column that was selected of a parent matrix.
 *
 * For example:
 * ```C
 * Matrix *m = Matrix_new(10, 10);
 * ColIter *begin = Matrix_col_begin(m, 2) // Create the begining iterator that points
 *                                         // to the first element in m's third column
 * ColIter *end = Matrix_col_end(m, 5);
 * ```
 *
 * We can use `ColIter`s to compute the norm of a column more effectively
 * For example, the function `Matrix_col_norm` makes use of `ColIter`s
 *
 */
typedef struct mat_col_iterator_t {
    MATRIX_TYPE *ptr;
    size_t ncols; //! This needs to be renamed to "diff" or something like that
} ColIter;

// used to iterate through a row, although I suspect this will be used less than a column iterator
typedef struct mat_row_iterator_t {
    MATRIX_TYPE *ptr;
    size_t ptr_diff; // pointer difference between elements in the same row
} RowIter;

typedef struct mat_iterator_t {
    MATRIX_TYPE *ptr;
    size_t ptr_diff;
} MatIter;

/**
 * A `Vector` is a `Matrix` that is either a column or row vector.
 * This typedef is used to express intent in the code.
 * For example, the function `Vector_new` will create a new
 * col vector when only passing one parameter, the desired number of
 * elements.
 *
 */
typedef Matrix Vector;
typedef void (* EDITOR) (MATRIX_TYPE *); // A function that will modify the pointer foreach element
typedef void (* EDITOR_2) (MATRIX_TYPE *, MATRIX_TYPE *); // A function that will modify the pointer foreach element
typedef void (* EDITOR_K) (MATRIX_TYPE *, MATRIX_TYPE); // A function that will modify the pointer foreach element

/**================================================================================================
 *!                                        Matrix Mask functions
 *================================================================================================**/
// This mask API should allow me to set values according to a certain condition
typedef bool (* Mask) (MATRIX_TYPE *); // A "Mask" is a pointer to a function that tests a condition
                                       // based on the inputted element.
                                       // Masks then can be used to only interact with data
                                       // that fit a specific criterion

// I'll have to revise this because what a mask really should be is a matrix with elements either 1 or 0.
// This can be constructed with a Mask Function

/**================================================================================================
 *!                                        Matrix Decompositions
 *================================================================================================**/

typedef struct lu_t {
    Matrix *L;
    Matrix *U;
} LU;

typedef struct lup_t {
    Matrix *L;
    Matrix *U;
    Vector *P;
} LUP;

typedef struct ldu_t {
    Matrix *L;
    Matrix *D; // I need to encode a new matrix structure that is a diagonal
    Vector *U;
} LDU;

typedef void (* MatIterFn) (MatIter);
typedef void (* MatIterFn_k) (MatIter, MATRIX_TYPE);
typedef void (* MatIterFn_ptr) (MatIter, const MATRIX_TYPE *);
typedef void (* MatIterFn_iter) (MatIter, MatIter);
typedef void (* MatIterFn_iter_k) (MatIter, MatIter, const MATRIX_TYPE);

typedef void (* ColIterFn) (ColIter *);
typedef void (* ColIterFn_k) (ColIter *, MATRIX_TYPE);
typedef void (* ColIterFn_ptr) (ColIter *, const MATRIX_TYPE *);
typedef void (* ColIterFn_iter) (ColIter *, ColIter *);

typedef void (* RowIterFn) (RowIter *);
typedef void (* RowIterFn_k) (RowIter *, MATRIX_TYPE);
typedef void (* RowIterFn_ptr) (RowIter *, const MATRIX_TYPE *);
typedef void (* RowIterFn_iter) (RowIter *, RowIter *);
typedef void (* RowIterFn_iter_k) (RowIter *, RowIter *, const MATRIX_TYPE);

typedef MATRIX_TYPE (* function) (MATRIX_TYPE); // declare a function type that can be mapped to items of the matrix

/**========================================================================
 *!                           Functional patters
 *========================================================================**/
typedef bool (* predicate_fn) (double); // used to filter out values