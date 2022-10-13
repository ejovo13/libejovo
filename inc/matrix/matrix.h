#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "ejovo_rand.h"
#include <string.h>
#include <stdarg.h>
#include "generic_macros.h"
#include "complex.h"
// #include "ejovo_comp.h"

/** @file
 *
 *  @brief Implement a TYPED(Matrix) framework for performing basic Linear Algebra tasks
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

#ifndef TYPE_SUFFIX
#define TYPE_SUFFIX _d
#endif

/**========================================================================
 *!                           GENERIC FUNCTIONS
 *========================================================================**/
// #define RESHAPE CAT3(reshape, _, MATRIX_TYPE)

#define MAX_STEP_SIZE 100000

extern const double PI;
extern const double TWO_PI;
extern const double HALF_PI;
extern const double EPS;

// TYPED(Matrix_get)
// struct Matrix_complex;
// struct Matrix_bool;

#define DECLARE_MATRIX(TYPE) typedef struct Matrix_ ## TYPE {\
    TYPE *data;\
    size_t nrows;\
    size_t ncols;\
} Matrix_ ## TYPE\

#ifdef DECLARE_NUMERIC_TYPES

    DECLARE_MATRIX(int);
    DECLARE_MATRIX(float);
    DECLARE_MATRIX(double);

#endif

// #ifndef MATRIX_INT_DEFINED
// DEFINE_MATRIX()


/**
 * @brief TYPED(Matrix) structure that simulates a 2d matrix accessed by A(row, col).
 *
 * The TYPED(Matrix) structure contains valuable information about the number of rows and number of columns
 * stored in order to perform necessary logistic checks at execution time.
 * For example, two matrices can be added to each other if and only if they are the same size; *
 */
typedef struct TYPED(Matrix) {
    MATRIX_TYPE *data;
    size_t nrows;
    size_t ncols;
} TYPED(Matrix);




extern TYPED(Matrix) *TYPED(g_ANON);

// Iterate through a column, stopping when we've reached the final element
/**
 * @brief A C++ style iterator that iterates along a Matrix's column.
 *
 * A ColIter contains minimal information that allows it to access the proper memory locations
 * in an iterative fashion that correspond to the column that was selected of a parent matrix.
 *
 * For example:
 * ```C
 * TYPED(Matrix) *m = TYPED(Matrix_new)(10, 10);
 * ColIter *begin = TYPED(Matrix_col_begin)(m, 2) // Create the begining iterator that points
 *                                         // to the first element in m's third column
 * ColIter *end = TYPED(Matrix_col_end)(m, 5);
 * ```
 *
 * We can use `ColIter`s to compute the norm of a column more effectively
 * For example, the function `TYPED(Matrix_col_norm)` makes use of `ColIter`s
 *
 */
typedef struct {
    MATRIX_TYPE *ptr;
    size_t ncols; //! This needs to be renamed to "diff" or something like that
} TYPED(ColIter);

// used to iterate through a row, although I suspect this will be used less than a column iterator
typedef struct {
    MATRIX_TYPE *ptr;
    size_t ptr_diff; // pointer difference between elements in the same row
} TYPED(RowIter);

typedef struct {
    MATRIX_TYPE *ptr;
    size_t ptr_diff;
} TYPED(MatIter);

/**
 * A `Vector` is a `Matrix` that is either a column or row vector.
 * This typedef is used to express intent in the code.
 * For example, the function `TYPED(Vector_new)` will create a new
 * col vector when only passing one parameter, the desired number of
 * elements.
 *
 */
typedef TYPED(Matrix) TYPED(Vector);
typedef void (* TYPED(EDITOR)) (MATRIX_TYPE *); // A function that will modify the pointer foreach element
typedef void (* TYPED(EDITOR_2)) (MATRIX_TYPE *, MATRIX_TYPE *); // A function that will modify the pointer foreach element
typedef void (* TYPED(EDITOR_K)) (MATRIX_TYPE *, MATRIX_TYPE); // A function that will modify the pointer foreach element

/**================================================================================================
 *!                                        TYPED(Matrix) Mask functions
 *================================================================================================**/
// This mask API should allow me to set values according to a certain condition
typedef bool (* TYPED(Mask)) (MATRIX_TYPE *); // A "Mask" is a pointer to a function that tests a condition
                                       // based on the inputted element.
                                       // Masks then can be used to only interact with data
                                       // that fit a specific criterion

// I'll have to revise this because what a mask really should be is a matrix with elements either 1 or 0.
// This can be constructed with a Mask Function

/**================================================================================================
 *!                                        TYPED(Matrix) Decompositions
 *================================================================================================**/

typedef struct {
    TYPED(Matrix) *L;
    TYPED(Matrix) *U;
} TYPED(LU);

typedef struct {
    TYPED(Matrix) *L;
    TYPED(Matrix) *U;
    TYPED(Vector)*P;
} TYPED(LUP);

typedef struct {
    TYPED(Matrix) *L;
    TYPED(Matrix) *D; // I need to encode a new matrix structure that is a diagonal
    TYPED(Vector)*U;
} TYPED(LDU);

typedef void (* TYPED(MatIterFn)) (TYPED(MatIter));
typedef void (* TYPED(MatIterFn_k)) (TYPED(MatIter), MATRIX_TYPE);
typedef void (* TYPED(MatIterFn_ptr)) (TYPED(MatIter), const MATRIX_TYPE *);
typedef void (* TYPED(MatIterFn_iter)) (TYPED(MatIter), TYPED(MatIter));
typedef void (* TYPED(MatIterFn_iter_k)) (TYPED(MatIter), TYPED(MatIter), const MATRIX_TYPE);

typedef void (* TYPED(ColIterFn)) (TYPED(ColIter) *);
typedef void (* TYPED(ColIterFn_k)) (TYPED(ColIter )*, MATRIX_TYPE);
typedef void (* TYPED(ColIterFn_ptr)) (TYPED(ColIter )*, const MATRIX_TYPE *);
typedef void (* TYPED(ColIterFn_iter)) (TYPED(ColIter )*, TYPED(ColIter )*);

typedef void (* TYPED(RowIterFn)) (TYPED(RowIter )*);
typedef void (* TYPED(RowIterFn_k)) (TYPED(RowIter )*, MATRIX_TYPE);
typedef void (* TYPED(RowIterFn_ptr)) (TYPED(RowIter )*, const MATRIX_TYPE *);
typedef void (* TYPED(RowIterFn_iter)) (TYPED(RowIter )*, TYPED(RowIter )*);
typedef void (* TYPED(RowIterFn_iter_k)) (TYPED(RowIter )*, TYPED(RowIter )*, const MATRIX_TYPE);

typedef MATRIX_TYPE (* TYPED(function)) (MATRIX_TYPE); // declare a function type that can be mapped to items of the matrix

/**========================================================================
 *!                           Functional patters
 *========================================================================**/
typedef bool (* TYPED(predicate_fn)) (MATRIX_TYPE); // used to filter out values

typedef TYPED(Matrix) TYPED(Index);

// #endif // MATRIX_TYPE
// #endif // TYPE_SUFFIX

#endif // MATRIX_H