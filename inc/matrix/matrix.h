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
 *  @brief Implement a MATRIX_T framework for performing basic Linear Algebra tasks
 *
 *  In order to tackle the exercises prescribed in TP4, I decided to create a matrix framework to make my life
 *  easier when writing the matrix multiplication and determinant finding routines.
 *
 *  @author Evan Voyles
 *  @date 16 October 2021
 *
 */
// #define MATRIX_TYPE int

// Type of the matrix that will be determined at compile time. Should be a numberic value like `float` or `int`
#ifndef MATRIX_TYPE
#define MATRIX_TYPE double 
#endif

#ifndef __BIZARRE_MACROS__
#define __BIZARRE_MACROS__

    // #define STRINGIFY(X) STRINGIFY2(X)
    // #define STRINGIFY2(X) #X
    // Used to expand the definition of MATRIX_TYPe 
    // when calling MATRIX
    #define CAT(X, Y) CAT2(X, Y)
    #define CAT2(X, Y) X##Y

    #define CAT3(X, Y, Z) CAT32(X, Y, Z)
    #define CAT32(X, Y, Z) X ## Y ## Z

#endif

#define MATRIX_T CAT(Matrix_, MATRIX_TYPE)
#define VECTOR_T CAT(Vector_, MATRIX_TYPE)

#define MAT_T CAT(mat, MATRIX_TYPE)
#define MAT_FN(fn_name) CAT2(MAT_T, fn_name)

#define MATRIX(TYPE) CAT(Matrix_, TYPE) 
#define MATRIX_FN(fn_name) CAT3(MATRIX_T, _, fn_name)
#define VECTOR_FN(fn_name) CAT3(VECTOR_T, _, fn_name)
#define MATITER_NEW CAT3(MATITER_T, _, new)
#define MATITER_T CAT(MatIter_, MATRIX_TYPE)
#define MATITER_FN(fn_name) CAT3(MATITER_T, _, fn_name)

#define MAX_STEP_SIZE 100000

const extern double PI;
const extern double TWO_PI;
const extern double HALF_PI;

// MATRIX_FN(get)

/**
 * @brief MATRIX_T structure that simulates a 2d matrix accessed by A(row, col).
 *
 * The MATRIX_T structure contains valuable information about the number of rows and number of columns
 * stored in order to perform necessary logistic checks at execution time.
 * For example, two matrices can be added to each other if and only if they are the same size; *
 */
typedef struct MATRIX_T {
    MATRIX_TYPE *data; // SUPER IMPORTANT!!! I am declaring that the underlying data
                                // is only ever accessed by one pointer! In terms of Rust,
                                // data is the only owner of the matrix elements
    size_t nrows;
    size_t ncols;
} MATRIX_T;

extern MATRIX_T *g_ANON;

// Iterate through a column, stopping when we've reached the final element
/**
 * @brief A C++ style iterator that iterates along a Matrix's column.
 *
 * A ColIter contains minimal information that allows it to access the proper memory locations
 * in an iterative fashion that correspond to the column that was selected of a parent matrix.
 *
 * For example:
 * ```C
 * MATRIX_T *m = MATRIX_FN(new)(10, 10);
 * ColIter *begin = MATRIX_FN(col_begin)(m, 2) // Create the begining iterator that points
 *                                         // to the first element in m's third column
 * ColIter *end = MATRIX_FN(col_end)(m, 5);
 * ```
 *
 * We can use `ColIter`s to compute the norm of a column more effectively
 * For example, the function `MATRIX_FN(col_norm)` makes use of `ColIter`s
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
} MATITER_T;

/**
 * A `Vector` is a `Matrix` that is either a column or row vector.
 * This typedef is used to express intent in the code.
 * For example, the function `VECTOR_FN(new)` will create a new
 * col vector when only passing one parameter, the desired number of
 * elements.
 *
 */
typedef MATRIX_T Vector;
typedef void (* EDITOR) (MATRIX_TYPE *); // A function that will modify the pointer foreach element
typedef void (* EDITOR_2) (MATRIX_TYPE *, MATRIX_TYPE *); // A function that will modify the pointer foreach element
typedef void (* EDITOR_K) (MATRIX_TYPE *, MATRIX_TYPE); // A function that will modify the pointer foreach element

/**================================================================================================
 *!                                        MATRIX_T Mask functions
 *================================================================================================**/
// This mask API should allow me to set values according to a certain condition
typedef bool (* Mask) (MATRIX_TYPE *); // A "Mask" is a pointer to a function that tests a condition
                                       // based on the inputted element.
                                       // Masks then can be used to only interact with data
                                       // that fit a specific criterion

// I'll have to revise this because what a mask really should be is a matrix with elements either 1 or 0.
// This can be constructed with a Mask Function

/**================================================================================================
 *!                                        MATRIX_T Decompositions
 *================================================================================================**/

typedef struct lu_t {
    MATRIX_T *L;
    MATRIX_T *U;
} LU;

typedef struct lup_t {
    MATRIX_T *L;
    MATRIX_T *U;
    Vector *P;
} LUP;

typedef struct ldu_t {
    MATRIX_T *L;
    MATRIX_T *D; // I need to encode a new matrix structure that is a diagonal
    Vector *U;
} LDU;

typedef void (* MatIterFn) (MATITER_T);
typedef void (* MatIterFn_k) (MATITER_T, MATRIX_TYPE);
typedef void (* MatIterFn_ptr) (MATITER_T, const MATRIX_TYPE *);
typedef void (* MatIterFn_iter) (MATITER_T, MATITER_T);
typedef void (* MatIterFn_iter_k) (MATITER_T, MATITER_T, const MATRIX_TYPE);

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
typedef bool (* predicate_fn) (MATRIX_TYPE); // used to filter out values

typedef MATRIX_T Index;