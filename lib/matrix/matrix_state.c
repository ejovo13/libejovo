// Functions that are used to inquire about the state of a matrix
// For example, is_square, is_symmetric, is_transpose etc etc

// #include "ejovo_matrix_generic.h"
#include "ejovo_matrix.h"


// return true if __A and __B have the same size and all of the elements are identical
bool TYPED(matcmp)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {

    if ( __A->nrows != __B->nrows || __A->ncols != __B->ncols) {
        return false;
    }
    return TYPED(matcmp_bytes)(__A, __B);
}

// compare the bytes of the data using memcmp
bool TYPED(matcmp_bytes)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {
    return memcmp((void *) __A->data, (void *) __B->data, sizeof(MATRIX_TYPE) * (__A->nrows * __A->ncols)) == 0;
}

// Are __A and __B compatible for addition?
bool TYPED(Matrix_comp_add)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {
    return (__A->nrows == __B->nrows && __A->ncols == __B->ncols);
}

// Are __A and __B compatible for addition?
bool TYPED(Matrix_comp_mult)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {
    return (__A->ncols == __B->nrows);
}

// size_t TYPED(Matrix_size)(const TYPED(Matrix) *__A) {
//     return __A->nrows * __A->ncols;
// }

bool TYPED(Matrix_is_square)(const TYPED(Matrix) *__A) {
    return __A->nrows == __A->ncols;
}

// return true if __A has one row
bool TYPED(Matrix_is_row)(const TYPED(Matrix) *__A) {
    return __A->nrows == 1;
}

// return true if __A has one column
bool TYPED(Matrix_is_col)(const TYPED(Matrix) *__A) {
    return __A->ncols == 1;
}

bool TYPED(Matrix_is_vec)(const TYPED(Matrix) *__A) {
    return TYPED(Matrix_is_row)(__A) || TYPED(Matrix_is_col)(__A);
}

// Return the limiting dimension of __A.
size_t TYPED(Matrix_rect_limit)(const TYPED(Matrix) *__A) {
    return __A->nrows < __A->ncols ? __A->nrows : __A->ncols;
}