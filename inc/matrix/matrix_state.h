#ifndef MATRIX_STATE_H
#define MATRIX_STATE_H
// Functions that are used to inquire about the state of a matrix
// For example, is_square, is_symmetric, is_transpose etc etc

#include "matrix.h"

static inline bool TYPED(Matrix_valid_bounds)(const TYPED(Matrix) *__m, size_t __i, size_t __j) {
    return (__i < __m->nrows && __j < __m->ncols);
}

// return true if __A and __B have the same size and all of the elements are identical
bool TYPED(matcmp)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

// compare the bytes of the data using memcmp
bool TYPED(matcmp_bytes)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

// Are __A and __B compatible for addition?
bool TYPED(Matrix_comp_add)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

// Are __A and __B compatible for addition?
bool TYPED(Matrix_comp_mult)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

static inline size_t TYPED(Matrix_size)(const TYPED(Matrix) *__A) {
    return __A->nrows * __A->ncols;
}

bool TYPED(Matrix_is_square)(const TYPED(Matrix) *__A);

// return true if __A has one row
bool TYPED(Matrix_is_row)(const TYPED(Matrix) *__A);

// return true if __A has one column
bool TYPED(Matrix_is_col)(const TYPED(Matrix) *__A);

bool TYPED(Matrix_is_vec)(const TYPED(Matrix) *__A);

// Return the limiting dimension of __A.
size_t TYPED(Matrix_rect_limit)(const TYPED(Matrix) *__A);

#endif