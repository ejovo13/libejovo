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
    size_t ncols;
} ColIter;

// used to iterate through a row, although I suspect this will be used less than a column iterator
typedef struct mat_row_iterator_t {
    MATRIX_TYPE *ptr;
    size_t nrows;
} RowIter;

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
 *!                                       matrix_core.c
 *================================================================================================**/
/**
 * @private
 * Allocate the space for a new matrix object, performing no checks
 *
 * @return a new malloc'ed matrix
 */
extern Matrix *matalloc(size_t __nrows, size_t __ncols);

/**
 * Create a new __nrows x __ncols Matrix filled with zeros
 *
 * Calls calloc under the surface. The allocated matrix can be freed using the function
 * `Matrix_free`.
 *
 * @return a new malloc'ed matrix
 */
extern Matrix *Matrix_new(int __nrows, int __ncols);

/**
 * Take ownership of the data pointed to by `*__arr_ptr` and nullify it afterwards
 *
 * After data has been moved, it is no longer safe to access. This method of creating
 * a new Matrix is highly discouraged but is provided for special cases
 */
extern Matrix *Matrix_move(MATRIX_TYPE **__arr_ptr, size_t __nrows, size_t __ncols);

/**
 * Create a new matrix from an array of `MATRIX_TYPE`s.
 *
 * Specify the number of rows and columns and create a new malloc'ed Matrix. This method
 * will CLONE the array pointed to by __arr.
 */
extern Matrix *Matrix_from(const MATRIX_TYPE *__arr, size_t __nrows, size_t __ncols);

/**
 * Create a column vector (A `n x 1` matrix) from a given array
 *
 */
extern Matrix *Matrix_colvec(const MATRIX_TYPE *__arr, size_t __nrows);

/**
 * Create a row vector (A `1 x m` matrix) from a given array
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

/**
 * Set value of the element at __m(__i, __j) without checking the indices
 *
 * @warning This function is considered "unsafe" and should only be used when
 * the programmer is sure that the elements being set are valid bounds.
 * If you are not writing an algorithm where performance is super critical,
 * consider using Matrix_set
 *
 */
extern void matset(Matrix *__m, size_t __i, size_t __j, MATRIX_TYPE __value);

/**
 *  Return a pointer to the element at __m(__i, __j) [zero indexed]
 */
extern MATRIX_TYPE * Matrix_access(const Matrix *__m, size_t __i, size_t __j);

/**
 *  Return a pointer to the element at __m(__i, __j) without checking the indices
 */
extern MATRIX_TYPE *matacc(const Matrix *__m, size_t __i, size_t __j);

/** Return a pointer to the element at __m(__i, __j), checking that the indices are valid
 */
extern MATRIX_TYPE *matacc_check(const Matrix *__m, size_t __i, size_t __j);

/**
 * Print a matrix to stdout
 */
extern void Matrix_print(const Matrix *__m);

/**
 * Print a matrix to stdout without checking the bounds
 */
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

/** @private
 *  Compute the dot product without checking any indices MATrix Column Dot Row.
 *
 *  This function is a lower leverl function that should mainly be used behind the scenes
 */
extern MATRIX_TYPE matcdr(const Matrix *__A, const Matrix *__B, size_t __irow, size_t __icol);

// return true if __A and __B have the same size and all of the elements are identical
/** @private
 */
extern bool matcmp(const Matrix *__A, const Matrix *__B);

/** @private
 *
 *  Compare if two matrices are identical at the byte-level
 *
 * That is, is the data pointed to by __A->data the same as __B->data?
 */
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
extern Matrix * Matrix_multiply(const Matrix * __A, const Matrix * __B);

/**
 *  Underlying function used in a foreach_2 function pointer approach to
 * iterating through the elements of a matrix.
 */
extern void add_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b);

/**
 * @private
 */
extern void sub_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b);

/**
 * @private
 */
extern void mult_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b);

/**
 * @private
 */
extern void div_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b);

/**
 * @private
 */
extern void matadd_foreach(Matrix *__A, const Matrix *__B);

/**
 * @private
 */
extern void matsub_foreach(Matrix *__A, const Matrix *__B);

/**
 * @private
 */
extern void matmult_foreach(Matrix *__A, const Matrix *__B);

/**
 * @private
 */
extern void matdiv_foreach(Matrix *__A, const Matrix *__B);

// IDEA!! MAKE THESE VARIADIC FUNCTIONS!!!
/** @private
 *
 * low level function to mutate __A in place by adding __B
 */
extern void matadd(Matrix *__A, const Matrix *__B);

/**
 * Add two matrices and store the sum in the return value
 */
extern Matrix *Matrix_add(const Matrix *__A, const Matrix *__B);

// Extract submatrix __A(__istart:__iend, __jstart:__jend)
/** @private
 */
extern Matrix * submat(Matrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

// Alternative spelling for object-oriented approach.
/**
 * Extract a submatrix of __A: A(__istart:__iend, __jstart:__jend) using 0 based indices
 *
 */
extern Matrix * Matrix_submat(Matrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

/**
 * Fill a Matrix __A with the value __value.
 */
extern void Matrix_fill(Matrix *__A, const MATRIX_TYPE __value);

/**
 * Fill the elements without checking bounds
 */
extern void matfill(Matrix *__A, const MATRIX_TYPE __value);

/**
 *  Instantiate new matrix with the value filled in at every element
 */
extern Matrix * Matrix_value(size_t __nrows, size_t __ncols, MATRIX_TYPE __value);

// Return specific matrix types
/**
 * Return a matrix of all 1's
 */
extern Matrix * Matrix_ones(size_t __nrows, size_t __ncols);

/**
 *  Matrix whose elements are i + j (starting with i,j = 1)
 */
extern Matrix * Matrix_ij(size_t __nrows, size_t __ncols);

/**
 *  Fill a `__nrows` by `__ncols` Matrix with a uniform random variable ~ [`__min`, `__max`]
 *
 */
extern Matrix * Matrix_random(size_t __nrows, size_t __ncols, int __min, int __max);

/**
 * Fill a `__nrows` by `__ncols` Matrix with a uniform random variable ~ [0, 100]
 */
extern Matrix * Matrix_rand(size_t __nrows, size_t __ncols);

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
extern Matrix * Matrix_pow(Matrix * __A, size_t __power);

/** @private
 *
 *  @brief Matrix copy elements
 *
 * Copy the matrix __src into the submatrix of __dest prescribed by the start and end indices
 *
 *  This is a low lever helper function that shouldn't need to be called by the high level Matrix API.
 */
extern int matcpyele(Matrix * __dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, Matrix * __src);


// Copy the elements of __src into the submatrix of __dest prescribed by the start and end indices WITHOUT CHECKING THE BOUNDS
extern void matcpyele_unsafe(Matrix *__dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, Matrix *__src);


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

extern Matrix *Matrix_K(size_t __n);

extern Matrix *Matrix_C(size_t __n);

extern Matrix *Matrix_T(size_t __n);

extern Matrix *Matrix_B(size_t __n);

extern void matsub(Matrix *__A, const Matrix *__B);

extern Matrix *Matrix_subtract(const Matrix *__A, const Matrix *__B);

extern Matrix *Matrix_subtract(const Matrix *__A, const Matrix *__B);

extern void Matrix_foreach(Matrix *__A, EDITOR __fnc);

extern void Matrix_foreach_2(Matrix *__A, Matrix *__B, EDITOR_2 __fnc);

extern void Matrix_foreach_k(Matrix *__A, EDITOR_K __fnc, MATRIX_TYPE __k);

extern void matmultscalar(Matrix *__A, const MATRIX_TYPE __k);

extern void mataddscalar(Matrix *__A, const MATRIX_TYPE __k);

extern void matdivscalar(Matrix *__A, const MATRIX_TYPE __k);

extern void matsubscalar(Matrix *__A, const MATRIX_TYPE __k);

// MY FIRST EDITOR_K
extern void multscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k);

extern void addscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k);

extern void divscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k);

extern void subscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k);

extern Matrix *Matrix_mult_scalar(const Matrix *__A, const MATRIX_TYPE __k);

extern Matrix *Matrix_add_scalar(const Matrix *__A, const MATRIX_TYPE __k);

extern Matrix *Matrix_sub_scalar(const Matrix *__A, const MATRIX_TYPE __k);

extern Matrix *Matrix_div_scalar(const Matrix *__A, const MATRIX_TYPE __k);


extern MATRIX_TYPE vecpnorm(const Matrix *__A);

// Euclidean norm
extern MATRIX_TYPE vecnorm(const Vector *__A);

// Calculate the norm of a column using ColIter's
extern MATRIX_TYPE colnorm(ColIter *__begin, const ColIter *__end);

// Calculate the norm of a specific column
extern MATRIX_TYPE Matrix_col_norm(const Matrix *__A, size_t __j);

extern void matnormcol(ColIter *__begin, const ColIter *__end);

extern void matnormcols(Matrix *__A);

extern void vecnormalize(Vector *__u);

// Return the norm of a vector (checking bounds?)
extern MATRIX_TYPE Vector_norm(const Vector *__u);

// return a normalized version of this vector
extern Vector *Vector_normalize(const Vector *__u);

extern void Matrix_normalize_col(Matrix *__A, size_t __j);

extern void Matrix_normalize_cols(Matrix *__A);

// Return a column vector that contains the solutions
// this column vector can be null if there are no solutions/infinitely many solutions
extern Matrix *gausselim(Matrix *__A, const Matrix *__B);

/**================================================================================================
 *!                                        Vector declarations
 *================================================================================================**/

// Default to making a column vector
extern Vector *Vector_new(size_t __nrows);

extern Vector *Vector_rand(size_t __nrows);

extern Vector *Vector_random(size_t __nrows, int __min, int __max);

// Take the dot product of __u and __v in place, storing the results in u!
// we are also just assuming that __u and __v are column (OR ROW) vectors of the same size
extern MATRIX_TYPE vecdot(const Vector *__u, const Vector *__v);

extern MATRIX_TYPE Vector_inner(const Vector *__u, const Vector *__v);

extern Vector *vecproject(const Vector *__v, const Vector *__u);

// Take vector __v and project it ONTO __u
extern Vector *Vector_project_onto(const Vector *__v, const Vector *__u);

/**================================================================================================
 *!                                        ColIter functions
 *================================================================================================**/

extern ColIter *ColIter_new(MATRIX_TYPE *__ptr, size_t __nrows);

extern ColIter *ColIter_clone(const ColIter *__c);

extern void ColIter_free(ColIter *__c);

extern void ColIter_next(ColIter *__c);

// Return true if the __lhs and __rhs point to the same element
extern bool ColIter_cmp(const ColIter *__lhs, const ColIter *__rhs);

extern ColIter *matcolpos(const Matrix *__A, size_t __i, size_t __j);


// return a new Column Iterator that points to the final element in this column
extern ColIter *Matrix_col_end(const Matrix *__A, size_t __j);

extern ColIter *Matrix_col_begin(const Matrix *__A, size_t __j);

extern MATRIX_TYPE ColIter_value(const ColIter *__c);

/**================================================================================================
 *!                                        Matrix Mask functions
 *================================================================================================**/
// This mask API should allow me to set values according to a certain condition
typedef bool (* Mask) (MATRIX_TYPE *); // A "Mask" is a pointer to a function that tests a condition
                                       // based on the inputted element.
                                       // Masks then can be used to only interact with data
                                       // that fit a specific criterion

/**
 * Perform an operation on a matrix when a given mask evauates to true
 */
extern void Matrix_mask(Matrix *__A, Mask __mask, EDITOR __operator);

extern void Matrix_set_mask(Matrix *__A, Mask __mask, const MATRIX_TYPE __value);










#endif