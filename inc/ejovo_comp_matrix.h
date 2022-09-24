// MATRIX_T type but CompMATRIX_T instead.

// This API should be unified. I should be able to create a Real MATRIX_T from a Comp MATRIX_T type

#ifndef EJOVO_COMP_MATRIX
#define EJOVO_COMP_MATRIX

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "ejovo_rand.h"
#include "ejovo_comp.h"

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


// Type of the matrix that will be determined at compile time. Should be a numberic value like `float` or `int`
#ifndef COMPLEX_MATRIX_TYPE
#define COMPLEX_MATRIX_TYPE double
#endif

/**
 * @brief MATRIX_T structure that simulates a 2d matrix accessed by A(row, col).
 *
 * The MATRIX_T structure contains valuable information about the number of rows and number of columns
 * stored in order to perform necessary logistic checks at execution time.
 * For example, two matrices can be added to each other if and only if they are the same size; *
 */
typedef struct comp_mat_t {
    COMPLEX_MATRIX_TYPE *restrict data; // SUPER IMPORTANT!!! I am declaring that the underlying data
                                // is only ever accessed by one pointer! In terms of Rust,
                                // data is the only owner of the matrix elements
    size_t nrows;
    size_t ncols;
} ComplexMatrix;

/**
 * Create a new __nrows x __ncols ComplexMATRIX_T filled with zeros
 *
 * Calls calloc under the surface. The allocated ComplexMATRIX_T can be freed using the function
 * `ComplexMATRIX_FN(free)`.
 */
extern ComplexMATRIX_T * ComplexMATRIX_FN(new)(int __nrows, int __ncols);

/**
 * Free the memory associated with the ComplexMATRIX_T and then free the pointer itself
 *
 *
 */
extern void ComplexMATRIX_FN(free)(ComplexMATRIX_T *__A);

/**
 * Check if the values of __i and __j are within the bounds of __m
 *
 */
extern bool ComplexMATRIX_FN(valid_bounds)(const ComplexMATRIX_T *__m, size_t __i, size_t __j);

/**
 * Return the value of the element at __m(__i, __j) [zero indexed]
 *
 * Return -1 if bounds are not respected and prints an error to the screen
 */
extern COMPLEX_MATRIX_TYPE ComplexMATRIX_FN(at)(const ComplexMATRIX_T *__m, size_t __i, size_t __j);

/**
 * Set value of the element at __m(__i, __j) [zero indexed]
 *
 * Return 0 if the bounds were respected, -1 elsewise
 *
 *
 */
extern int ComplexMATRIX_FN(set)(ComplexMATRIX_T *__m, size_t __i, size_t __j, COMPLEX_MATRIX_TYPE __value);

/**
 *  Return a pointer to the element at __m(__i, __j) [zero indexed]
 */
extern COMPLEX_MATRIX_TYPE * ComplexMATRIX_FN(access)(const ComplexMATRIX_T *__m, size_t __i, size_t __j);


/**
 * Print a ComplexMATRIX_T to stdout
 */
extern void ComplexMATRIX_FN(print)(const ComplexMATRIX_T *__m);

/**
 * Print the size of a ComplexMATRIX_T to stdout
 */
extern void ComplexMATRIX_FN(summary)(const ComplexMATRIX_T *__m);


// Take the inner product of the the __irow row of __A with the __icol col of __B
// used as a subroutine called in matmul
/** @private
 */
extern COMPLEX_MATRIX_TYPE col_dot_row(const ComplexMATRIX_T *__A, const ComplexMATRIX_T *__B, size_t __irow, size_t __icol);

// return true if __A and __B have the same size and all of the elements are identical
/** @private
 */
extern bool MAT_FN(cmp)(const ComplexMATRIX_T *__A, const ComplexMATRIX_T *__B);

// Are __A and __B compatible for addition?
/** @private
 *
 *  Low level function that tests if __A is compatible to add with __B. That is, are __A and __B the same size?
 */
extern bool ComplexMATRIX_FN(comp_add)(const ComplexMATRIX_T *__A, const ComplexMATRIX_T *__B);

// Are __A and __B compatible for addition?
/** @private
 *
 *  Low level function that tests if __A is compatible to multiply by __B.
 */
extern bool ComplexMATRIX_FN(comp_mult)(const ComplexMATRIX_T *__A, const ComplexMATRIX_T *__B);

// Copy the bytes
// this is a utility function and should not be used by the end user
/** @private
 */
// static bool MAT_FN(cpy)(ComplexMATRIX_T *restrict __dest, const ComplexMATRIX_T *restrict __src);

/** @private
 *  copy the contents of ComplexMATRIX_T __src into __dest
 */
extern ComplexMATRIX_T * MAT_FN(clone)(const ComplexMATRIX_T *restrict __src);

/**
 * Create a new ComplexMATRIX_T from the contents of __src
 *
 * @return A ComplexMATRIX_T with the same size and shape as `__src` and the same exact elements.
 * This is a clone operation and thus new data is allocated for the returned ComplexMatrix.
 *
 */
extern ComplexMATRIX_T * ComplexMATRIX_FN(clone)(const ComplexMATRIX_T *restrict __src);

/** @private
 * Fortran named function to compute the multiplication of two matrices __A * __B
 */
ComplexMATRIX_T * MAT_FN(mul)(const ComplexMATRIX_T *__A, const ComplexMATRIX_T *__B);

/**
 * Multiply two matrices __A*__B.
 */
ComplexMATRIX_T * ComplexMATRIX_FN(multiply)(ComplexMATRIX_T * __A, ComplexMATRIX_T * __B);

// IDEA!! MAKE THESE VARIADIC FUNCTIONS!!!
/** @private
 */
ComplexMATRIX_T * MAT_FN(add)(ComplexMATRIX_T * __A, ComplexMATRIX_T * __B);

/**
 * Add two matrices and store the sum in the return value
 */
ComplexMATRIX_T * ComplexMATRIX_FN(add)(ComplexMATRIX_T * __A, MATRIX_T * __B);

// Extract submatrix __A(__istart:__iend, __jstart:__jend)
/** @private
 */
ComplexMATRIX_T * subMAT_FN()(ComplexMATRIX_T * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

// Alternative spelling for object-oriented approach.
/**
 * Extract a subComplexMATRIX_T of __A: A(__istart:__iend, __jstart:__jend) using 0 based indices
 *
 */
ComplexMATRIX_T * ComplexMATRIX_FN(submat)(ComplexMATRIX_T * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

/**
 * Fill a ComplexMATRIX_T __A with the value __value.
 */
void ComplexMATRIX_FN(fill)(ComplexMATRIX_T * __A, COMPLEX_MATRIX_TYPE __value);

/**
 *  Instantiate new ComplexMATRIX_T with the value filled in at every element
 */
ComplexMATRIX_T * ComplexMATRIX_FN(value)(size_t __nrows, size_t __ncols, COMPLEX_MATRIX_TYPE __value);

// Return specific ComplexMATRIX_T types
/**
 * Return a ComplexMATRIX_T of all 1's
 */
ComplexMATRIX_T * ComplexMATRIX_FN(ones)(size_t __nrows, size_t __ncols);

/**
 *  MATRIX_T whose elements are i + j (starting with i,j = 1)
 */
ComplexMATRIX_T * ComplexMATRIX_FN(ij)(size_t __nrows, size_t __ncols);

/**
 *  Fill a `__nrows` by `__ncols` ComplexMATRIX_T with a uniform random variable ~ [`__min`, `__max`]
 *
 */
ComplexMATRIX_T * ComplexMATRIX_FN(random)(size_t __nrows, size_t __ncols, int __min, int __max);

/**
 * Fill a `__nrows` by `__ncols` ComplexMATRIX_T with a uniform random variable ~ [0, 100]
 */
ComplexMATRIX_T * ComplexMATRIX_FN(rand)(size_t __nrows, size_t __ncols);

/** @private
 *
 */
bool is_square(ComplexMATRIX_T * __A);

/**
 * Check if a MATRIX_T is square
 *
 * A matrix is sqaure if the nrows is equal to ncols.
 */
bool ComplexMATRIX_FN(is_square)(ComplexMATRIX_T * __A);

/**
 * Compute the Power of a matrix
 */
MATRIX_T * MATRIX_FN(pow)(MATRIX_T * __A, size_t __power);

/** @private
 *
 *  @brief MATRIX_T copy elements
 *
 * Copy the matrix __src into the submatrix of __dest prescribed by the start and end indices
 *
 *  This is a low lever helper function that shouldn't need to be called by the high level MATRIX_T API.
 */
int MAT_FN(cpyele)(MATRIX_T * __dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, MATRIX_T * __src);

/**
 * Stack two matrices on top of each other
 */
MATRIX_T * MATRIX_FN(rcat)(MATRIX_T * __A, MATRIX_T * __B);

/**
 * Smush two matrices together
 */
MATRIX_T * MATRIX_FN(ccat)(MATRIX_T * __A, MATRIX_T * __B);

/**
 * Find the minor of a matrix
 *
 * The minor of a MATRIX_T is the Original MATRIX_T __A with the `__irow` row removed and the `__icol` col.
 */
MATRIX_T * MATRIX_FN(minor)(MATRIX_T * __A, size_t __irow, size_t __icol);


/**
 * Recursive algorithm to compute the determinant of a matrix
 *
 */
double MATRIX_FN(det)(MATRIX_T * __A);

#endif