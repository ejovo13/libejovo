#include "ejovo_matrix.h"

// Basic statistic routines that will operate on either vectors or a pair of MatIters

MATRIX_TYPE MatIter_mean(const MatIter __begin, const MatIter __end) {
    MATRIX_TYPE sum = MatIter_sum(__begin, __end);
    return sum / MatIter_length(__begin, __end);
}

MATRIX_TYPE MatIter_sum_squared(const MatIter __begin, const MatIter __end) {

    MatIter iter = __begin;
    MATRIX_TYPE sum_squared = 0;

    while (! MatIter_cmp(iter, __end)) {
        sum_squared += MatIter_value(iter) * MatIter_value(iter);
        iter = MatIter_next(iter);
    }

    return sum_squared;
}

MATRIX_TYPE MatIter_mean_squared(const MatIter __begin, const MatIter __end) {
    MATRIX_TYPE sum_squared = MatIter_sum_squared(__begin, __end);
    return sum_squared / MatIter_length(__begin, __end);
}

MATRIX_TYPE MatIter_rms(const MatIter __begin, const MatIter __end) {
    MATRIX_TYPE mean_squared = MatIter_mean_squared(__begin, __end);
    return sqrt(mean_squared);
}

MATRIX_TYPE MatIter_var(const MatIter __begin, const MatIter __end) {

    // First thing that I need to do is create a new disposable vector from __begin and __end
    Vector *copy = Vector_from_iter(__begin, __end);

    // compute the average
    MATRIX_TYPE mean = MatIter_mean(__begin, __end);

    // subtract the average from our copy
    MatIter_row_sub_k(Vector_begin(copy), Vector_end(copy), mean);

    // now simply take the rms right??
    MATRIX_TYPE var = MatIter_mean_squared(Vector_begin(copy), Vector_end(copy));

    Matrix_free(copy);
    return var;
}

MATRIX_TYPE MatIter_std(const MatIter __begin, const MatIter __end) {
    return sqrt(MatIter_var(__begin, __end));
}

MATRIX_TYPE Vector_iter_sum(const Vector *__v) {
    return MatIter_sum(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_prod(const Vector *__v) {
    return MatIter_prod(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_mean(const Vector *__v) {
    return MatIter_mean(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_mean_squared(const Vector *__v) {
    return MatIter_mean_squared(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_rms(const Vector *__v) {
    return MatIter_rms(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_min(const Vector *__v) {
    return MatIter_min(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_max(const Vector *__v) {
    return MatIter_max(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_var(const Vector *__v) {
    return MatIter_var(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_std(const Vector *__v) {
    return MatIter_std(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Matrix_iter_sum(const Matrix *__m) {
    return MatIter_sum(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_prod(const Matrix *__m) {
    return MatIter_prod(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_mean(const Matrix *__m) {
    return MatIter_mean(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_mean_squared(const Matrix *__m) {
    return MatIter_mean_squared(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_rms(const Matrix *__m) {
    return MatIter_rms(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_min(const Matrix *__m) {
    return MatIter_min(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_max(const Matrix *__m) {
    return MatIter_max(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_var(const Matrix *__m) {
    return MatIter_var(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_std(const Matrix *__m) {
    return MatIter_std(Matrix_begin(__m), Matrix_end(__m));
}