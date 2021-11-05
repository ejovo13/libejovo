#ifndef EJOVO_MATRIX
#define EJOVO_MATRIX

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "ejovo_rand.h"
#include <string.h>
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

/**
 * @brief Matrix structure that simulates a 2d matrix accessed by A(row, col).
 *
 * The Matrix structure contains valuable information about the number of rows and number of columns
 * stored in order to perform necessary logistic checks at execution time.
 * For example, two matrices can be added to each other if and only if they are the same size; *
 */
typedef struct mat_t {
    MATRIX_TYPE *restrict data; // SUPER IMPORTANT!!! I am declaring that the underlying data
                                // is only ever accessed by one pointer! In terms of Rust,
                                // data is the only owner of the matrix elements
    size_t nrows;
    size_t ncols;
} Matrix;

/**
 * @private
 * Allocate the space for a new matrix object, performing no checks
 */
extern Matrix *matalloc(size_t __nrows, size_t __ncols);

/**
 * Create a new __nrows x __ncols Matrix filled with zeros
 *
 * Calls calloc under the surface. The allocated matrix can be freed using the function
 * `Matrix_free`.
 */
extern Matrix *Matrix_new(int __nrows, int __ncols);

extern Matrix *Matrix_move(MATRIX_TYPE **__arr_ptr, size_t __nrows, size_t __ncols);

extern Matrix *Matrix_from(const MATRIX_TYPE *__arr, size_t __nrows, size_t __ncols);

/**
 * Create a column vector (A n x 1 matrix) from a given array
 *
 */
extern Matrix *Matrix_colvec(const MATRIX_TYPE *__arr, size_t __nrows);

/**
 * Create a row vector (A 1 x m matrix) from a given array
 *
 */
extern Matrix *Matrix_rowvec(const MATRIX_TYPE *__arr, size_t __ncols);

/**
 * Free the memory associated with the matrix and then free the pointer itself
 *
 *
 */
extern void Matrix_free(Matrix *__A);

/**
 * Check if the values of __i and __j are within the bounds of __m
 *
 */
extern bool Matrix_valid_bounds(const Matrix *__m, size_t __i, size_t __j);

/**
 * Return the value of the element at __m(__i, __j) [zero indexed]
 *
 * Return -1 if bounds are not respected and prints an error to the screen
 */
extern MATRIX_TYPE Matrix_at(const Matrix *__m, size_t __i, size_t __j);

/**
 * Return the value of the element at __m(__i, __j) without checking the indices
 */
extern MATRIX_TYPE matat(const Matrix *__m, size_t __i, size_t __j);

/**
 * Set value of the element at __m(__i, __j) [zero indexed]
 *
 * Return 0 if the bounds were respected, -1 elsewise
 *
 *
 */
extern int Matrix_set(Matrix *__m, size_t __i, size_t __j, MATRIX_TYPE __value);

// set value of the element at __m(__i, __j) without checking the indices
extern void matset(Matrix *__m, size_t __i, size_t __j, MATRIX_TYPE __value);

/**
 *  Return a pointer to the element at __m(__i, __j) [zero indexed]
 */
extern MATRIX_TYPE * Matrix_access(const Matrix *__m, size_t __i, size_t __j);

// return a pointer to the element at __m(__i, __j) without checking the indices
extern MATRIX_TYPE *matacc(const Matrix *__m, size_t __i, size_t __j);

extern MATRIX_TYPE *matacc_check(const Matrix *__m, size_t __i, size_t __j);
/**
 * Print a matrix to stdout
 */
extern void Matrix_print(const Matrix *__m);

extern void matprint(const Matrix *__m);

/**
 * Print the size of a matrix to stdout
 */
extern void Matrix_summary(const Matrix *__m);


// Take the inner product of the the __irow row of __A with the __icol col of __B
// used as a subroutine called in matmul
/** @private
 */
extern MATRIX_TYPE matcdr_check(const Matrix *__A, const Matrix *__B, size_t __irow, size_t __icol);

// Compute the dot product without checking any indices MATrix Column Dot Row.
extern MATRIX_TYPE matcdr(const Matrix *__A, const Matrix *__B, size_t __irow, size_t __icol);

// return true if __A and __B have the same size and all of the elements are identical
/** @private
 */
extern bool matcmp(const Matrix *__A, const Matrix *__B);

extern bool matcmp_bytes(const Matrix *__A, const Matrix *__B);


// Are __A and __B compatible for addition?
/** @private
 *
 *  Low level function that tests if __A is compatible to add with __B. That is, are __A and __B the same size?
 */
extern bool Matrix_comp_add(const Matrix *__A, const Matrix *__B);

// Are __A and __B compatible for addition?
/** @private
 *
 *  Low level function that tests if __A is compatible to multiply by __B.
 */
extern bool Matrix_comp_mult(const Matrix *__A, const Matrix *__B);

// Copy the bytes
// this is a utility function and should not be used by the end user
/** @private
 */
// static bool matcpy(Matrix *restrict __dest, const Matrix *restrict __src);

/** @private
 *  copy the contents of matrix __src into __dest
 */
extern Matrix * matclone(const Matrix *restrict __src);

/**
 * Create a new Matrix from the contents of __src
 *
 * @return A Matrix with the same size and shape as `__src` and the same exact elements.
 * This is a clone operation and thus new data is allocated for the returned Matrix.
 *
 */
extern Matrix * Matrix_clone(const Matrix *restrict __src);

/** @private
 * Fortran named function to compute the multiplication of two matrices __A * __B
 */
extern Matrix * matmul(const Matrix *__A, const Matrix *__B);


/**
 * Multiply two matrices __A*__B.
 */
Matrix * Matrix_multiply(Matrix * __A, Matrix * __B);

// IDEA!! MAKE THESE VARIADIC FUNCTIONS!!!
/** @private
 */
void matadd(Matrix *__A, const Matrix *__B);

/**
 * Add two matrices and store the sum in the return value
 */
Matrix *Matrix_add(const Matrix *__A, const Matrix *__B);

// Extract submatrix __A(__istart:__iend, __jstart:__jend)
/** @private
 */
Matrix * submat(Matrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

// Alternative spelling for object-oriented approach.
/**
 * Extract a submatrix of __A: A(__istart:__iend, __jstart:__jend) using 0 based indices
 *
 */
Matrix * Matrix_submat(Matrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

/**
 * Fill a Matrix __A with the value __value.
 */
void Matrix_fill(Matrix *__A, const MATRIX_TYPE __value);

/**
 * Fill the elements without checking bounds
 */
void matfill(Matrix *__A, const MATRIX_TYPE __value);

/**
 *  Instantiate new matrix with the value filled in at every element
 */
Matrix * Matrix_value(size_t __nrows, size_t __ncols, MATRIX_TYPE __value);

// Return specific matrix types
/**
 * Return a matrix of all 1's
 */
Matrix * Matrix_ones(size_t __nrows, size_t __ncols);

/**
 *  Matrix whose elements are i + j (starting with i,j = 1)
 */
Matrix * Matrix_ij(size_t __nrows, size_t __ncols);

/**
 *  Fill a `__nrows` by `__ncols` Matrix with a uniform random variable ~ [`__min`, `__max`]
 *
 */
Matrix * Matrix_random(size_t __nrows, size_t __ncols, int __min, int __max);

/**
 * Fill a `__nrows` by `__ncols` Matrix with a uniform random variable ~ [0, 100]
 */
Matrix * Matrix_rand(size_t __nrows, size_t __ncols);

// /** @private
//  *
//  */
// extern bool is_square(const Matrix *__A);

extern size_t Matrix_size(const Matrix *__A);

/**
 * Check if a Matrix is square
 *
 * A matrix is sqaure if the nrows is equal to ncols.
 */
extern bool Matrix_is_square(const Matrix *__A);

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


// Copy the elements of __src into the submatrix of __dest prescribed by the start and end indices WITHOUT CHECKING THE BOUNDS
void matcpyele_unsafe(Matrix *__dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, Matrix *__src);


/**
 * Stack two matrices on top of each other
 */
extern Matrix * Matrix_rcat(Matrix * __A, Matrix * __B);

/**
 * Smush two matrices together
 */
extern Matrix * Matrix_ccat(Matrix * __A, Matrix * __B);

/**
 * Find the minor of a matrix
 *
 * The minor of a Matrix is the Original Matrix __A with the `__irow` row removed and the `__icol` col.
 */
extern Matrix * Matrix_minor(Matrix * __A, size_t __irow, size_t __icol);


/**
 * Recursive algorithm to compute the determinant of a matrix
 *
 */
extern double Matrix_det(Matrix * __A);


extern void mathad(Matrix *__A, const Matrix *__B);

extern void mathad_check(Matrix *__A, const Matrix *__B);

/**
 * Compute the Hadamard product (element-wise multiplication) of two matrices
 */
extern Matrix *Matrix_hadamard(const Matrix *__A, const Matrix *__B);


extern void matsetrow(Matrix *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n);

extern void matsetcol(Matrix *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n);

/**
 * Get a new malloc row vecot (1 x m matrix) corresponding to row __i
 */
extern Matrix *Matrix_get_row(const Matrix *__A, size_t __i);

/**
 * Get a new malloc row vecot (1 x m matrix) corresponding to row __i
 */
extern Matrix *Matrix_get_col(const Matrix *__A, size_t __j);

/**
 * Get a new malloc row vecot (1 x m matrix) corresponding to row __i
 */
extern int Matrix_set_row(Matrix *__A, size_t __i, const Matrix *__row);

/**
 * Get a new malloc row vecot (1 x m matrix) corresponding to row __i
 */
extern int Matrix_set_col(Matrix *__A, size_t __j, const Matrix *__col);

extern bool Matrix_is_row(const Matrix *__A);

extern bool Matrix_is_col(const Matrix *__A);

extern bool Matrix_is_vec(const Matrix *__A);

// Return a newly allocated column vector without checking indices
extern Matrix *matcol(const Matrix *__A, size_t __j);

// Return a newly allocated column vector without checking indices
extern Matrix *matrow(const Matrix *__A, size_t __i);

extern Matrix *Matrix_K(size_t __n);

extern Matrix *Matrix_C(size_t __n);

extern Matrix *Matrix_T(size_t __n);

extern Matrix *Matrix_B(size_t __n);

#endif