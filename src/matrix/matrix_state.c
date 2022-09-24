// Functions that are used to inquire about the state of a matrix
// For example, is_square, is_symmetric, is_transpose etc etc

#include "ejovo_matrix_generic.h"
// #include "ejovo_matrix.h"

bool MATRIX_FN(valid_bounds)(const MATRIX_T *__m, size_t __i, size_t __j) {
    return (__i < __m->nrows && __j < __m->ncols);
}

// return true if __A and __B have the same size and all of the elements are identical
bool MAT_FN(cmp)(const MATRIX_T *__A, const MATRIX_T *__B) {

    if ( __A->nrows != __B->nrows || __A->ncols != __B->ncols) {
        return false;
    }
    return MAT_FN(cmp_bytes)(__A, __B);
}

// compare the bytes of the data using memcmp
bool MAT_FN(cmp_bytes)(const MATRIX_T *__A, const MATRIX_T *__B) {
    return memcmp((void *) __A->data, (void *) __B->data, sizeof(MATRIX_TYPE) * (__A->nrows * __A->ncols)) == 0;
}

// Are __A and __B compatible for addition?
bool MATRIX_FN(comp_add)(const MATRIX_T *__A, const MATRIX_T *__B) {
    return (__A->nrows == __B->nrows && __A->ncols == __B->ncols);
}

// Are __A and __B compatible for addition?
bool MATRIX_FN(comp_mult)(const MATRIX_T *__A, const MATRIX_T *__B) {
    return (__A->ncols == __B->nrows);
}

// size_t MATRIX_FN(size)(const MATRIX_T *__A) {
//     return __A->nrows * __A->ncols;
// }

bool MATRIX_FN(is_square)(const MATRIX_T *__A) {
    return __A->nrows == __A->ncols;
}

// return true if __A has one row
bool MATRIX_FN(is_row)(const MATRIX_T *__A) {
    return __A->nrows == 1;
}

// return true if __A has one column
bool MATRIX_FN(is_col)(const MATRIX_T *__A) {
    return __A->ncols == 1;
}

bool MATRIX_FN(is_vec)(const MATRIX_T *__A) {
    return MATRIX_FN(is_row)(__A) || MATRIX_FN(is_col)(__A);
}

// Return the limiting dimension of __A.
size_t MATRIX_FN(rect_limit)(const MATRIX_T *__A) {
    return __A->nrows < __A->ncols ? __A->nrows : __A->ncols;
}