#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Unary Matrix Operators
 *================================================================================================**/

Matrix * Matrix_pow(Matrix * __A, size_t __power) {

    assert(Matrix_is_square(__A));
    if ( __power == 0 ) {
        return Matrix_identity(__A->nrows);
    }

    if ( __power == 1 ) {
        return Matrix_clone(__A);
    }

    Matrix * m = Matrix_clone(__A);

    for (size_t i = 2; i <= __power; i++) {
        m = Matrix_multiply(__A, m);
    }

    return m;

}


// recursive algorithm to compute the determinant of a matrix
double Matrix_det(Matrix * __A) {

    assert(Matrix_is_square(__A));

    double local_det = 0;

    if (__A->ncols == 1 && __A->nrows == 1) {
        return matat(__A, 0, 0);
    } else {

        size_t i = 0;
        for (size_t j = 0; j < __A->ncols; j++) {
            double cofactor = pow(-1.0, j)*Matrix_det(Matrix_minor(__A, i, j));
            // printf("Cofactor: %lf, i: %lu, j: %lu\n", cofactor, i, j);
            local_det += cofactor * matat(__A, i, j);
        }
    }

    return local_det;
}

/**================================================================================================
 *!                                        Matrix-Scalar Operators
 *================================================================================================**/

/**================================================================================================
 *!                                        Matrix-Vector Operators
 *================================================================================================**/

/**================================================================================================
 *!                                        Matrix-Matrix Operators
 *================================================================================================**/

// Take the inner product of the the __irow row of __A with the __icol col of __B
// used as a subroutine called in matmul
MATRIX_TYPE matcdr_check(const Matrix *__A, const Matrix *__B, size_t __irow, size_t __icol) {

    // #if MATRIX_TYPE == Complex

    //     MATRIX_TYPE inner_product = Complex_zero();
    //     for (size_t i = 0; i < __A->ncols; i++) {
    //         inner_product = Complex_add(inner_product, ())
    //     }

    // #else
        // We are assuming that __A and __B are compatible matrices for matrix multiplication
        MATRIX_TYPE inner_product = 0;
        for (size_t i = 0; i < __A->ncols; i++) {
            inner_product += (Matrix_at(__A, __irow, i) * Matrix_at(__B, i, __icol));
        }
        return inner_product;
    // #endif
}

// Compute the dot product without checking any indices
MATRIX_TYPE matcdr(const Matrix *__A, const Matrix *__B, size_t __irow, size_t __icol) {
        MATRIX_TYPE inner_product = 0;
        for (size_t i = 0; i < __A->ncols; i++) {
            inner_product += (matat(__A, __irow, i) * matat(__B, i, __icol));
        }
        return inner_product;
}

Matrix *matmul(const Matrix *__A, const Matrix *__B) {

    Matrix *product = Matrix_new(__A->nrows, __B->ncols);

    if (product){
        for (size_t i = 0; i < __A->nrows; i++) {
            for (size_t j = 0; j < __B->ncols; j++) {
                matset(product, i, j, matcdr(__A, __B, i, j));
            }
        }
    }

    return product;
}

Matrix * Matrix_multiply(const Matrix *__A, const Matrix *__B) {

    Matrix *prod = NULL;

    if (Matrix_comp_mult(__A, __B)) {
        prod = matmul(__A, __B);
    } else {
        perror("Trying to multiply incompatible matrices");
    }

    return prod;
}

// matadd modifies __A in place for more efficient additions when we don't need the original matrix
void matadd(Matrix *__A, const Matrix *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            a = matacc(__A, i, j);
            b = matacc(__B, i, j);

            *a += *b;
        }
    }
}

Matrix *Matrix_add(const Matrix *__A, const Matrix *__B) {

    Matrix *sum = NULL;

    if (Matrix_comp_add(__A, __B)) {

        sum = matclone(__A); // clone the matrix and modify this new matrix in place
        matadd(sum, __B);

    } else {

        perror("Trying to add two incompatible matrices");

    }

    return sum;
}

void mathad(Matrix *__A, const Matrix *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    // Iterate through the columns and rows of __A and multiply the elements by __B
    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {

            a = matacc(__A, i, j);
            b = matacc(__B, i, j);

            *a *= *b;
        }
    }
}

// Call hadamard multiplication, checking the indices with each access.
void mathad_check(Matrix *__A, const Matrix *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    // Iterate through the columns and rows of __A and multiply the elements by __B
    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {

            a = matacc_check(__A, i, j);
            b = matacc_check(__B, i, j);

            *a *= *b;
        }
    }
}

/**
 * Compute the Hadamard product (element-wise multiplication) of two matrices
 */
Matrix *Matrix_hadamard(const Matrix *__A, const Matrix *__B) {
    // Don't compute the product in place.
    if (!Matrix_comp_add(__A, __B)) {
        perror("Cannot take the hadamard product of two incompatible matrices!");
    }
    // verify that the matrices can be added

    Matrix *C = matclone(__A);
    mathad(C, __B);

    return C;
}

// NUMERICAL LINEAR ALGEBRA ROUTEINES!!!!!!

// Subtract matrix __B from __A, modifying __A in place!
void matsub(Matrix *__A, const Matrix *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {

            a = matacc(__A, i, j);
            b = matacc(__B, i, j);

            *a -= *b;

        }
    }
}

Matrix *Matrix_subtract(const Matrix *__A, const Matrix *__B) {

    Matrix *A = Matrix_clone(__A);
    matsub(A, __B);
    return A;

}

/**================================================================================================
 *!                                        Normalizations
 *================================================================================================**/

// Calculate the norm of a column using ColIter's
MATRIX_TYPE colnorm(ColIter *__begin, const ColIter *__end) {

    MATRIX_TYPE sum = 0;

    do {
        sum += ColIter_value(__begin) * ColIter_value(__begin);
        ColIter_next(__begin);
    } while(!ColIter_cmp(__begin, __end));

    return sqrt(sum);

}

// Calculate the norm of a specific column
MATRIX_TYPE Matrix_col_norm(const Matrix *__A, size_t __j) {

    if (__j < __A->ncols) {
        return colnorm(Matrix_col_begin(__A, __j), Matrix_col_end(__A, __j));
    } else {
        perror("Col requested exceeds bounds");
        return -1;
    }
}

void matnormcol(ColIter *__begin, const ColIter *__end) {

    ColIter *c = ColIter_clone(__begin);
    MATRIX_TYPE norm = colnorm(__begin, __end);

    // now that we have calculated the norm, divide the columns values by the norm

    while (!ColIter_cmp(c, __end)) {
        *(c->ptr) /= norm;
        ColIter_next(c);
    }
    // *(c->ptr) /= norm;
}

void matnormcols(Matrix *__A) {
    for (size_t j = 0; j < __A->ncols; j++) {
        matnormcol(Matrix_col_begin(__A, j), Matrix_col_end(__A, j));
    }
}

void Matrix_normalize_col(Matrix *__A, size_t __j) {

    if (__j < __A->ncols) {
        matnormcol(Matrix_col_begin(__A, __j), Matrix_col_end(__A, __j));
    } else {
        printf("selected column is out of bounds");
        return;
    }
}

void Matrix_normalize_cols(Matrix *__A) {
    matnormcols(__A);
}

/**================================================================================================
 *!                                        Decomposition Algorithms
 *================================================================================================**/

/**================================================================================================
 *!                                        General Algorithms
 *================================================================================================**/

// Return a column vector that contains the solutions
// this column vector can be null if there are no solutions/infinitely many solutions
Matrix *gausselim(Matrix *__A, const Matrix *__B) {








}