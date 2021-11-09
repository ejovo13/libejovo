// Functions that are used to inquire about the state of a matrix
// For example, is_square, is_symmetric, is_transpose etc etc

#include "ejovo_matrix.h"

bool Matrix_valid_bounds(const Matrix *__m, size_t __i, size_t __j) {
    return (__i < __m->nrows && __j < __m->ncols);
}

// return true if __A and __B have the same size and all of the elements are identical
bool matcmp(const Matrix *__A, const Matrix *__B) {

    if ( __A->nrows != __B->nrows || __A->ncols != __B->ncols) {
        return false;
    }
    return matcmp_bytes(__A, __B);
}

// compare the bytes of the data using memcmp
bool matcmp_bytes(const Matrix *__A, const Matrix *__B) {
    return memcmp((void *) __A->data, (void *) __B->data, sizeof(MATRIX_TYPE) * (__A->nrows * __A->ncols)) == 0;
}

// Are __A and __B compatible for addition?
bool Matrix_comp_add(const Matrix *__A, const Matrix *__B) {
    return (__A->nrows == __B->nrows && __A->ncols == __B->ncols);
}

// Are __A and __B compatible for addition?
bool Matrix_comp_mult(const Matrix *__A, const Matrix *__B) {
    return (__A->ncols == __B->nrows);
}

size_t Matrix_size(const Matrix *__A) {
    return __A->nrows * __A->ncols;
}

bool Matrix_is_square(const Matrix *__A) {
    return __A->nrows == __A->ncols;
}

// return true if __A has one row
bool Matrix_is_row(const Matrix *__A) {
    return __A->nrows == 1;
}

// return true if __A has one column
bool Matrix_is_col(const Matrix *__A) {
    return __A->ncols == 1;
}

bool Matrix_is_vec(const Matrix *__A) {
    return Matrix_is_row(__A) || Matrix_is_col(__A);
}

// Return the limiting dimension of __A.
inline size_t Matrix_rect_limit(const Matrix *__A) {
    return __A->nrows < __A->ncols ? __A->nrows : __A->ncols;
}