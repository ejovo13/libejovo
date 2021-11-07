// Define a series of functions that deal with looping through all of the elements of a matrix,
// looping through all of the columns of a matrix, in essence this file deals with iteration
#include "ejovo_matrix.h"

// series of functions used to add two elements that Matrix_access pointers are pointing to
void add_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) += (*__b);
}

void sub_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) -= (*__b);
}

void mult_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) *= (*__b);
}

void div_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) /= (*__b);
}

// add a __B to __A, mutating __A in place, using a "foreach" construct
void matadd_foreach(Matrix *__A, const Matrix *__B) {
    Matrix_foreach_2(__A, __B, add_each);
}

void matsub_foreach(Matrix *__A, const Matrix *__B) {
    Matrix_foreach_2(__A, __B, sub_each);
}

void matmult_foreach(Matrix *__A, const Matrix *__B) {
    Matrix_foreach_2(__A, __B, mult_each);
}

void matdiv_foreach(Matrix *__A, const Matrix *__B) {
    Matrix_foreach_2(__A, __B, div_each);
}

void Matrix_foreach(Matrix *__A, EDITOR __fnc) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            __fnc(matacc(__A, i, j));
        }
    }
}

void Matrix_foreach_2(Matrix *__A, Matrix *__B, EDITOR_2 __fnc) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            __fnc(matacc(__A, i, j), matacc(__B, i, j));
        }
    }
}

void Matrix_foreach_k(Matrix *__A, EDITOR_K __fnc, MATRIX_TYPE __k) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            __fnc(matacc(__A, i, j), __k);
        }
    }
}

void matmultscalar(Matrix *__A, const MATRIX_TYPE __k) {
    Matrix_foreach_k(__A, multscalar, __k);
}

void mataddscalar(Matrix *__A, const MATRIX_TYPE __k) {
    Matrix_foreach_k(__A, addscalar, __k);
}

void matdivscalar(Matrix *__A, const MATRIX_TYPE __k) {
    Matrix_foreach_k(__A, divscalar, __k);
}

void matsubscalar(Matrix *__A, const MATRIX_TYPE __k) {
    Matrix_foreach_k(__A, subscalar, __k);
}

// MY FIRST EDITOR_K
void multscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) *= __k;
}

void addscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) += __k;
}

void divscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) /= __k;
}

void subscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) -= __k;
}
/**================================================================================================
 *!                                        FOREACH style functions
 *================================================================================================**/

Matrix *Matrix_mult_scalar(const Matrix *__A, const MATRIX_TYPE __k) {
    Matrix *A = Matrix_clone(__A);
    matmultscalar(A, __k);
    return A;
}

Matrix *Matrix_add_scalar(const Matrix *__A, const MATRIX_TYPE __k) {
    Matrix *A = Matrix_clone(__A);
    mataddscalar(A, __k);
    return A;
}

Matrix *Matrix_sub_scalar(const Matrix *__A, const MATRIX_TYPE __k) {
    Matrix *A = Matrix_clone(__A);
    matsubscalar(A, __k);
    return A;
}

Matrix *Matrix_div_scalar(const Matrix *__A, const MATRIX_TYPE __k) {
    Matrix *A = Matrix_clone(__A);
    matdivscalar(A, __k);
    return A;
}


/**================================================================================================
 *!                                        Matrix Mask functions
 *================================================================================================**/

/**
 * Perform an operation on a matrix when a given mask evaluates to true
 */
void Matrix_mask(Matrix *__A, Mask __mask, EDITOR __operator) {

    MATRIX_TYPE *el = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            el = matacc(__A, i, j); // access the ith, jth element
            if (__mask(el)) __operator(el); // if the __mask is true, do something to __el
        }
    }
}
// __mask is only applied to matrix __A
void Matrix_mask_2(Matrix *__A, Matrix *__B, Mask __mask, EDITOR_2 __operator) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            a = matacc(__A, i, j); // access the ith, jth element
            b = matacc(__B, i, j); // access the ith, jth element
            if (__mask(a)) __operator(a, b); // if the __mask is true, do something to __el
        }
    }
}

void Matrix_mask_k(Matrix *__A, Mask __mask, EDITOR_K __operator, const MATRIX_TYPE __k) {

    MATRIX_TYPE *el = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            el = matacc(__A, i, j); // access the ith, jth element
            if (__mask(el)) __operator(el, __k); // if the __mask is true, do something to __el
        }
    }
}

/**
 * Set the element that a pointer is pointing to to __value
 */
void setelement(MATRIX_TYPE *__el, const MATRIX_TYPE __value) {
    *__el = __value;
}

/**
 * Set all of the elements who fulfill a mask equal to the value
 */
void Matrix_set_mask(Matrix *__A, Mask __mask, const MATRIX_TYPE __value) {
    Matrix_mask_k(__A, __mask, setelement, __value);
}