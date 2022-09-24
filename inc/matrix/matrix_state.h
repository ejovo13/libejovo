#ifndef MATRIX_STATE_H
#define MATRIX_STATE_H
// Functions that are used to inquire about the state of a matrix
// For example, is_square, is_symmetric, is_transpose etc etc

#include "matrix.h"

bool MATRIX_FN(valid_bounds)(const MATRIX_T *__m, size_t __i, size_t __j);

// return true if __A and __B have the same size and all of the elements are identical
bool MAT_FN(cmp)(const MATRIX_T *__A, const MATRIX_T *__B);

// compare the bytes of the data using memcmp
bool MAT_FN(cmp_bytes)(const MATRIX_T *__A, const MATRIX_T *__B);

// Are __A and __B compatible for addition?
bool MATRIX_FN(comp_add)(const MATRIX_T *__A, const MATRIX_T *__B);

// Are __A and __B compatible for addition?
bool MATRIX_FN(comp_mult)(const MATRIX_T *__A, const MATRIX_T *__B);

static inline size_t MATRIX_FN(size)(const MATRIX_T *__A) {
    return __A->nrows * __A->ncols;
}

bool MATRIX_FN(is_square)(const MATRIX_T *__A);

// return true if __A has one row
bool MATRIX_FN(is_row)(const MATRIX_T *__A);

// return true if __A has one column
bool MATRIX_FN(is_col)(const MATRIX_T *__A);

bool MATRIX_FN(is_vec)(const MATRIX_T *__A);

// Return the limiting dimension of __A.
size_t MATRIX_FN(rect_limit)(const MATRIX_T *__A);

#endif