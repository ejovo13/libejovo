// TYPED(Matrix) type but CompTYPED(Matrix) instead.

// This API should be unified. I should be able to create a Real TYPED(Matrix) from a Comp TYPED(Matrix) type

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
 *  @brief Implement a TYPED(Matrix) framework for performing basic Linear Algebra tasks
 *
 *  In order to tackle the exercises prescribed in TP4, I decided to create a matrix framework to make my life
 *  easier when writing the matrix multiplication and determinant finding routines.
 *
 *  @author Evan Voyles
 *  @date 16 October 2021
 *
 */


// Type of the matrix that will be determined at compile time. Should be a numberic value like `float` or `int`
#ifndef COMPLEX_TYPED(Matrix)YPE
#define COMPLEX_TYPED(Matrix)YPE double
#endif

/**
 * @brief TYPED(Matrix) structure that simulates a 2d matrix accessed by A(row, col).
 *
 * The TYPED(Matrix) structure contains valuable information about the number of rows and number of columns
 * stored in order to perform necessary logistic checks at execution time.
 * For example, two matrices can be added to each other if and only if they are the same size; *
 */
typedef struct comp_mat_t {
    COMPLEX_TYPED(Matrix)YPE *restrict data; // SUPER IMPORTANT!!! I am declaring that the underlying data
                                // is only ever accessed by one pointer! In terms of Rust,
                                // data is the only owner of the matrix elements
    size_t nrows;
    size_t ncols;
} ComplexMatrix;

/**
 * Create a new __nrows x __ncols ComplexTYPED(Matrix) filled with zeros
 *
 * Calls calloc under the surface. The allocated ComplexTYPED(Matrix) can be freed using the function
 * `ComplexTYPED(Matrix_free)`.
 */
extern ComplexTYPED(Matrix) * ComplexTYPED(Matrix_new)(int __nrows, int __ncols);

/**
 * Free the memory associated with the ComplexTYPED(Matrix) and then free the pointer itself
 *
 *
 */
extern void ComplexTYPED(Matrix_free)(ComplexTYPED(Matrix) *__A);

/**
 * Check if the values of __i and __j are within the bounds of __m
 *
 */
extern bool ComplexTYPED(Matrix_valid_bounds)(const ComplexTYPED(Matrix) *__m, size_t __i, size_t __j);

/**
 * Return the value of the element at __m(__i, __j) [zero indexed]
 *
 * Return -1 if bounds are not respected and prints an error to the screen
 */
extern COMPLEX_TYPED(Matrix)YPE ComplexTYPED(Matrix_at)(const ComplexTYPED(Matrix) *__m, size_t __i, size_t __j);

/**
 * Set value of the element at __m(__i, __j) [zero indexed]
 *
 * Return 0 if the bounds were respected, -1 elsewise
 *
 *
 */
extern int ComplexTYPED(Matrix_set)(ComplexTYPED(Matrix) *__m, size_t __i, size_t __j, COMPLEX_TYPED(Matrix)YPE __value);

/**
 *  Return a pointer to the element at __m(__i, __j) [zero indexed]
 */
extern COMPLEX_TYPED(Matrix)YPE * ComplexTYPED(Matrix_access)(const ComplexTYPED(Matrix) *__m, size_t __i, size_t __j);


/**
 * Print a ComplexTYPED(Matrix) to stdout
 */
extern void ComplexTYPED(Matrix_print)(const ComplexTYPED(Matrix) *__m);

/**
 * Print the size of a ComplexTYPED(Matrix) to stdout
 */
extern void ComplexTYPED(Matrix_summary)(const ComplexTYPED(Matrix) *__m);


// Take the inner product of the the __irow row of __A with the __icol col of __B
// used as a subroutine called in matmul
/** @private
 */
extern COMPLEX_TYPED(Matrix)YPE col_dot_row(const ComplexTYPED(Matrix) *__A, const ComplexTYPED(Matrix) *__B, size_t __irow, size_t __icol);

// return true if __A and __B have the same size and all of the elements are identical
/** @private
 */
extern bool TYPED(matcmp)(const ComplexTYPED(Matrix) *__A, const ComplexTYPED(Matrix) *__B);

// Are __A and __B compatible for addition?
/** @private
 *
 *  Low level function that tests if __A is compatible to add with __B. That is, are __A and __B the same size?
 */
extern bool ComplexTYPED(Matrix_comp_add)(const ComplexTYPED(Matrix) *__A, const ComplexTYPED(Matrix) *__B);

// Are __A and __B compatible for addition?
/** @private
 *
 *  Low level function that tests if __A is compatible to multiply by __B.
 */
extern bool ComplexTYPED(Matrix_comp_mult)(const ComplexTYPED(Matrix) *__A, const ComplexTYPED(Matrix) *__B);

// Copy the bytes
// this is a utility function and should not be used by the end user
/** @private
 */
// static bool TYPED(matcpy)(ComplexTYPED(Matrix) *restrict __dest, const ComplexTYPED(Matrix) *restrict __src);

/** @private
 *  copy the contents of ComplexTYPED(Matrix) __src into __dest
 */
extern ComplexTYPED(Matrix) * TYPED(matclone)(const ComplexTYPED(Matrix) *restrict __src);

/**
 * Create a new ComplexTYPED(Matrix) from the contents of __src
 *
 * @return A ComplexTYPED(Matrix) with the same size and shape as `__src` and the same exact elements.
 * This is a clone operation and thus new data is allocated for the returned ComplexMatrix.
 *
 */
extern ComplexTYPED(Matrix) * ComplexTYPED(Matrix_clone)(const ComplexTYPED(Matrix) *restrict __src);

/** @private
 * Fortran named function to compute the multiplication of two matrices __A * __B
 */
ComplexTYPED(Matrix) * TYPED(matmul)(const ComplexTYPED(Matrix) *__A, const ComplexTYPED(Matrix) *__B);

/**
 * Multiply two matrices __A*__B.
 */
ComplexTYPED(Matrix) * ComplexTYPED(Matrix_multiply)(ComplexTYPED(Matrix) * __A, ComplexTYPED(Matrix) * __B);

// IDEA!! MAKE THESE VARIADIC FUNCTIONS!!!
/** @private
 */
ComplexTYPED(Matrix) * TYPED(matadd)(ComplexTYPED(Matrix) * __A, ComplexTYPED(Matrix) * __B);

/**
 * Add two matrices and store the sum in the return value
 */
ComplexTYPED(Matrix) * ComplexTYPED(Matrix_add)(ComplexTYPED(Matrix) * __A, TYPED(Matrix) * __B);

// Extract submatrix __A(__istart:__iend, __jstart:__jend)
/** @private
 */
ComplexTYPED(Matrix) * subTYPED(mat)(ComplexTYPED(Matrix) * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

// Alternative spelling for object-oriented approach.
/**
 * Extract a subComplexTYPED(Matrix) of __A: A(__istart:__iend, __jstart:__jend) using 0 based indices
 *
 */
ComplexTYPED(Matrix) * ComplexTYPED(Matrix_submat)(ComplexTYPED(Matrix) * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

/**
 * Fill a ComplexTYPED(Matrix) __A with the value __value.
 */
void ComplexTYPED(Matrix_fill)(ComplexTYPED(Matrix) * __A, COMPLEX_TYPED(Matrix)YPE __value);

/**
 *  Instantiate new ComplexTYPED(Matrix) with the value filled in at every element
 */
ComplexTYPED(Matrix) * ComplexTYPED(Matrix_value)(size_t __nrows, size_t __ncols, COMPLEX_TYPED(Matrix)YPE __value);

// Return specific ComplexTYPED(Matrix) types
/**
 * Return a ComplexTYPED(Matrix) of all 1's
 */
ComplexTYPED(Matrix) * ComplexTYPED(Matrix_ones)(size_t __nrows, size_t __ncols);

/**
 *  TYPED(Matrix) whose elements are i + j (starting with i,j = 1)
 */
ComplexTYPED(Matrix) * ComplexTYPED(Matrix_ij)(size_t __nrows, size_t __ncols);

/**
 *  Fill a `__nrows` by `__ncols` ComplexTYPED(Matrix) with a uniform random variable ~ [`__min`, `__max`]
 *
 */
ComplexTYPED(Matrix) * ComplexTYPED(Matrix_random)(size_t __nrows, size_t __ncols, int __min, int __max);

/**
 * Fill a `__nrows` by `__ncols` ComplexTYPED(Matrix) with a uniform random variable ~ [0, 100]
 */
ComplexTYPED(Matrix) * ComplexTYPED(Matrix_rand)(size_t __nrows, size_t __ncols);

/** @private
 *
 */
bool is_square(ComplexTYPED(Matrix) * __A);

/**
 * Check if a TYPED(Matrix) is square
 *
 * A matrix is sqaure if the nrows is equal to ncols.
 */
bool ComplexTYPED(Matrix_is_square)(ComplexTYPED(Matrix) * __A);

/**
 * Compute the Power of a matrix
 */
TYPED(Matrix) * TYPED(Matrix_pow)(TYPED(Matrix) * __A, size_t __power);

/** @private
 *
 *  @brief TYPED(Matrix) copy elements
 *
 * Copy the matrix __src into the submatrix of __dest prescribed by the start and end indices
 *
 *  This is a low lever helper function that shouldn't need to be called by the high level TYPED(Matrix) API.
 */
int TYPED(matcpyele)(TYPED(Matrix) * __dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, TYPED(Matrix) * __src);

/**
 * Stack two matrices on top of each other
 */
TYPED(Matrix) * TYPED(Matrix_rcat)(TYPED(Matrix) * __A, TYPED(Matrix) * __B);

/**
 * Smush two matrices together
 */
TYPED(Matrix) * TYPED(Matrix_ccat)(TYPED(Matrix) * __A, TYPED(Matrix) * __B);

/**
 * Find the minor of a matrix
 *
 * The minor of a TYPED(Matrix) is the Original TYPED(Matrix) __A with the `__irow` row removed and the `__icol` col.
 */
TYPED(Matrix) * TYPED(Matrix_minor)(TYPED(Matrix) * __A, size_t __irow, size_t __icol);


/**
 * Recursive algorithm to compute the determinant of a matrix
 *
 */
double TYPED(Matrix_det)(TYPED(Matrix) * __A);

#endif