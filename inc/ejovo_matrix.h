
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "ejovo_rand.h"

#ifndef MATRIX_TYPE
#define MATRIX_TYPE long
#endif
typedef struct mat_t {
    MATRIX_TYPE * data;
    size_t nrows;
    size_t ncols;
} Matrix;

Matrix * Matrix_new(int __nrows, int __ncols);

// Free the memory associated with the matrix and then free the pointer itself
void Matrix_free(Matrix * __A);

bool Matrix_valid_bounds(Matrix * __m, size_t __i, size_t __j);


// return the value of the element at __m(__i, __j) [zero indexed]
// return -1 if bounds are not respected and prints an error to the screen
MATRIX_TYPE Matrix_at(Matrix * __m, size_t __i, size_t __j);

// set value of the element at __m(__i, __j) [zero indexed]
// return 0 if the bounds were respected, -1 elsewise
int Matrix_set(Matrix * __m, size_t __i, size_t __j, MATRIX_TYPE __value);

// return a pointer to the element at __m(__i, __j) [zero indexed]
MATRIX_TYPE * Matrix_access(Matrix * __m, size_t __i, size_t __j);

void Matrix_print(Matrix * __m);

void Matrix_summary(Matrix * __m);


// Take the inner product of the the __irow row of __A with the __icol col of __B
// used as a subroutine called in matmul
MATRIX_TYPE col_dot_row(Matrix * __A, Matrix * __B, size_t __irow, size_t __icol);

// return true if __A and __B have the same size and all of the elements are identical
bool matcmp(Matrix * __A, Matrix * __B);

// Are __A and __B compatible for addition?
bool Matrix_comp_add(Matrix * __A, Matrix * __B);

// Are __A and __B compatible for addition?
bool Matrix_comp_mult(Matrix * __A, Matrix * __B);

// Copy the bytes
// this is a utility function and should not be used by the end user
static bool matcpy(Matrix * __dest, Matrix * __src);


// copy the contents of matrix __src into __dest
Matrix * matclone(Matrix * __src);

Matrix * matmul(Matrix * __A, Matrix * __B);

Matrix * Matrix_multiply(Matrix * __A, Matrix * __B);

// IDEA!! MAKE THESE VARIADIC FUNCTIONS!!!
Matrix * matadd(Matrix * __A, Matrix * __B);

Matrix * Matrix_add(Matrix * __A, Matrix * __B);

// Extract submatrix __A(__istart:__iend, __jstart:__jend)
Matrix * submat(Matrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

// Alternative spelling for object-oriented approach.
Matrix * Matrix_submat(Matrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

Matrix * Matrix_fill(Matrix * __A, MATRIX_TYPE __value);

// instantiate new matrix with the value filled in at every element
Matrix * Matrix_value(size_t __nrows, size_t __ncols, MATRIX_TYPE __value);

// Return specific matrix types

Matrix * Matrix_ones(size_t __nrows, size_t __ncols);

// matrix whose elements are i + j (starting with i,j = 1)
Matrix * Matrix_ij(size_t __nrows, size_t __ncols);

Matrix * Matrix_random(size_t __nrows, size_t __ncols, int __min, int __max);

Matrix * Matrix_rand(size_t __nrows, size_t __ncols);

bool is_square(Matrix * __A);

Matrix * Matrix_pow(Matrix * __A, size_t __power);

// Copy the matrix __src into the submatrix of __dest prescribed by the start and end indices
int Matrix_copy_elements(Matrix * __dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, Matrix * __src);


Matrix * Matrix_rcat(Matrix * __A, Matrix * __B);

Matrix * Matrix_ccat(Matrix * __A, Matrix * __B);

Matrix * Matrix_minor(Matrix * __A, size_t __irow, size_t __icol);
// recursive algorithm to compute the determinant of a matrix
double Matrix_det(Matrix * __A);