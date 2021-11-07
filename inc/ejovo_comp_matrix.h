// Matrix type but CompMatrix instead.

// This API should be unified. I should be able to create a Real Matrix from a Comp Matrix type

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
#ifndef COMPLEX_MATRIX_TYPE
#define COMPLEX_MATRIX_TYPE double
#endif

/**
 * @brief Matrix structure that simulates a 2d matrix accessed by A(row, col).
 *
 * The Matrix structure contains valuable information about the number of rows and number of columns
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
 * Create a new __nrows x __ncols ComplexMatrix filled with zeros
 *
 * Calls calloc under the surface. The allocated ComplexMatrix can be freed using the function
 * `ComplexMatrix_free`.
 */
extern ComplexMatrix * ComplexMatrix_new(int __nrows, int __ncols);

/**
 * Free the memory associated with the ComplexMatrix and then free the pointer itself
 *
 *
 */
extern void ComplexMatrix_free(ComplexMatrix *__A);

/**
 * Check if the values of __i and __j are within the bounds of __m
 *
 */
extern bool ComplexMatrix_valid_bounds(const ComplexMatrix *__m, size_t __i, size_t __j);

/**
 * Return the value of the element at __m(__i, __j) [zero indexed]
 *
 * Return -1 if bounds are not respected and prints an error to the screen
 */
extern COMPLEX_MATRIX_TYPE ComplexMatrix_at(const ComplexMatrix *__m, size_t __i, size_t __j);

/**
 * Set value of the element at __m(__i, __j) [zero indexed]
 *
 * Return 0 if the bounds were respected, -1 elsewise
 *
 *
 */
extern int ComplexMatrix_set(ComplexMatrix *__m, size_t __i, size_t __j, COMPLEX_MATRIX_TYPE __value);

/**
 *  Return a pointer to the element at __m(__i, __j) [zero indexed]
 */
extern COMPLEX_MATRIX_TYPE * ComplexMatrix_access(const ComplexMatrix *__m, size_t __i, size_t __j);


/**
 * Print a ComplexMatrix to stdout
 */
extern void ComplexMatrix_print(const ComplexMatrix *__m);

/**
 * Print the size of a ComplexMatrix to stdout
 */
extern void ComplexMatrix_summary(const ComplexMatrix *__m);


// Take the inner product of the the __irow row of __A with the __icol col of __B
// used as a subroutine called in matmul
/** @private
 */
extern COMPLEX_MATRIX_TYPE col_dot_row(const ComplexMatrix *__A, const ComplexMatrix *__B, size_t __irow, size_t __icol);

// return true if __A and __B have the same size and all of the elements are identical
/** @private
 */
extern bool matcmp(const ComplexMatrix *__A, const ComplexMatrix *__B);

// Are __A and __B compatible for addition?
/** @private
 *
 *  Low level function that tests if __A is compatible to add with __B. That is, are __A and __B the same size?
 */
extern bool ComplexMatrix_comp_add(const ComplexMatrix *__A, const ComplexMatrix *__B);

// Are __A and __B compatible for addition?
/** @private
 *
 *  Low level function that tests if __A is compatible to multiply by __B.
 */
extern bool ComplexMatrix_comp_mult(const ComplexMatrix *__A, const ComplexMatrix *__B);

// Copy the bytes
// this is a utility function and should not be used by the end user
/** @private
 */
// static bool matcpy(ComplexMatrix *restrict __dest, const ComplexMatrix *restrict __src);

/** @private
 *  copy the contents of ComplexMatrix __src into __dest
 */
extern ComplexMatrix * matclone(const ComplexMatrix *restrict __src);

/**
 * Create a new ComplexMatrix from the contents of __src
 *
 * @return A ComplexMatrix with the same size and shape as `__src` and the same exact elements.
 * This is a clone operation and thus new data is allocated for the returned ComplexMatrix.
 *
 */
extern ComplexMatrix * ComplexMatrix_clone(const ComplexMatrix *restrict __src);

/** @private
 * Fortran named function to compute the multiplication of two matrices __A * __B
 */
ComplexMatrix * matmul(const ComplexMatrix *__A, const ComplexMatrix *__B);

/**
 * Multiply two matrices __A*__B.
 */
ComplexMatrix * ComplexMatrix_multiply(ComplexMatrix * __A, ComplexMatrix * __B);

// IDEA!! MAKE THESE VARIADIC FUNCTIONS!!!
/** @private
 */
ComplexMatrix * matadd(ComplexMatrix * __A, ComplexMatrix * __B);

/**
 * Add two matrices and store the sum in the return value
 */
ComplexMatrix * ComplexMatrix_add(ComplexMatrix * __A, Matrix * __B);

// Extract submatrix __A(__istart:__iend, __jstart:__jend)
/** @private
 */
ComplexMatrix * submat(ComplexMatrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

// Alternative spelling for object-oriented approach.
/**
 * Extract a subComplexMatrix of __A: A(__istart:__iend, __jstart:__jend) using 0 based indices
 *
 */
ComplexMatrix * ComplexMatrix_submat(ComplexMatrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

/**
 * Fill a ComplexMatrix __A with the value __value.
 */
void ComplexMatrix_fill(ComplexMatrix * __A, COMPLEX_MATRIX_TYPE __value);

/**
 *  Instantiate new ComplexMatrix with the value filled in at every element
 */
ComplexMatrix * ComplexMatrix_value(size_t __nrows, size_t __ncols, COMPLEX_MATRIX_TYPE __value);

// Return specific ComplexMatrix types
/**
 * Return a ComplexMatrix of all 1's
 */
ComplexMatrix * ComplexMatrix_ones(size_t __nrows, size_t __ncols);

/**
 *  Matrix whose elements are i + j (starting with i,j = 1)
 */
ComplexMatrix * ComplexMatrix_ij(size_t __nrows, size_t __ncols);

/**
 *  Fill a `__nrows` by `__ncols` ComplexMatrix with a uniform random variable ~ [`__min`, `__max`]
 *
 */
ComplexMatrix * ComplexMatrix_random(size_t __nrows, size_t __ncols, int __min, int __max);

/**
 * Fill a `__nrows` by `__ncols` ComplexMatrix with a uniform random variable ~ [0, 100]
 */
ComplexMatrix * ComplexMatrix_rand(size_t __nrows, size_t __ncols);

/** @private
 *
 */
bool is_square(ComplexMatrix * __A);

/**
 * Check if a Matrix is square
 *
 * A matrix is sqaure if the nrows is equal to ncols.
 */
bool ComplexMatrix_is_square(ComplexMatrix * __A);

/**
 * Compute the Power of a matrix
 */
Matrix * Matrix_pow(Matrix * __A, size_t __power);

/** @private
 *
 *  @brief Matrix copy elements
 *
 * Copy the matrix __src into the submatrix of __dest prescribed by the start and end indices
 *
 *  This is a low lever helper function that shouldn't need to be called by the high level Matrix API.
 */
int matcpyele(Matrix * __dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, Matrix * __src);

/**
 * Stack two matrices on top of each other
 */
Matrix * Matrix_rcat(Matrix * __A, Matrix * __B);

/**
 * Smush two matrices together
 */
Matrix * Matrix_ccat(Matrix * __A, Matrix * __B);

/**
 * Find the minor of a matrix
 *
 * The minor of a Matrix is the Original Matrix __A with the `__irow` row removed and the `__icol` col.
 */
Matrix * Matrix_minor(Matrix * __A, size_t __irow, size_t __icol);


/**
 * Recursive algorithm to compute the determinant of a matrix
 *
 */
double Matrix_det(Matrix * __A);

#endif