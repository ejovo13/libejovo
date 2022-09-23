// Define a series of functions that deal with looping through all of the elements of a matrix,
// looping through all of the columns of a matrix, in essence this file deals with iteration
#include "ejovo_matrix.h"

// /**================================================================================================
//  *!                                        Single functions
//  *================================================================================================**/

// // series of functions used to add two elements that Matrix_access pointers are pointing to
// inline void add_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
//     (*__a) += (*__b);
// }

// // I'm going to want to use this for computing the LU decomposition
// inline void sub_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
//     (*__a) -= (*__b);
// }

// inline void mult_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
//     (*__a) *= (*__b);
// }

// inline void div_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
//     (*__a) /= (*__b);
// }

// //* Matrix times scalar

// inline void multscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
//     (*__el) *= __k;
// }

// inline void addscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
//     (*__el) += __k;
// }

// inline void divscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
//     (*__el) /= __k;
// }

// inline void subscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
//     (*__el) -= __k;
// }

/**================================================================================================
 *!                                        Foreach loops
 *================================================================================================**/

void Matrix_foreach(Matrix *__A, EDITOR __fnc) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            __fnc(matacc(__A, i, j));
        }
    }
}

void Matrix_foreach_2(Matrix *__A, const Matrix *__B, EDITOR_2 __fnc) {

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

/**================================================================================================
 *!                                        Single function + foreach loop
 *================================================================================================**/


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

MATRIX_TYPE matsum(const Matrix *__A) {

    MATRIX_TYPE sum = 0;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j <__A->ncols; j++) {
            sum += matat(__A, i, j);
        }
    }

    return sum;
}

MATRIX_TYPE matmin(const Matrix *__A) {

    MATRIX_TYPE min = matat(__A, 0, 0);

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            if (matat(__A, i, j) < min) min = matat(__A, i, j);
        }
    }

    return min;
}

MATRIX_TYPE matmax(const Matrix *__A) {

    MATRIX_TYPE max = matat(__A, 0, 0);

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            if (matat(__A, i, j) > max) max = matat(__A, i, j);
        }
    }

    return max;
}


/**================================================================================================
 *!                                       Matrix API foreach
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