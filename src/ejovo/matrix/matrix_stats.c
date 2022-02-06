#include "ejovo_matrix.h"

// Basic statistic routines that will operate on either vectors or a pair of MatIters

MATRIX_TYPE MatIter_mean(const MatIter __begin, const MatIter __end) {
    MATRIX_TYPE sum = MatIter_sum(__begin, __end);
    printf("[MatIter_mean]     end->ptr: %x, begin->ptr: %x\n", __end.ptr, __begin.ptr);
    printf("MatIter_length inside mean: %ld\n", MatIter_length(__begin, __end));
    return sum / MatIter_length(__begin, __end);
}

MATRIX_TYPE MatIter_sum_squared(const MatIter __begin, const MatIter __end) {

    MatIter iter = __begin;
    MATRIX_TYPE sum_squared = 0;

    while (! MatIter_cmp(iter, __end)) {
        sum_squared += MatIter_value(iter) * MatIter_value(iter);
        MatIter_next(iter);
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

MATRIX_TYPE Vector_iter_sum(const Vector *__v) {
    return MatIter_sum(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_prod(const Vector *__v) {
    return MatIter_prod(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_mean(const Vector *__v) {
    MatIter b = Vector_begin(__v);
    MatIter e = Vector_end(__v);

    printf("[Vector_iter_mean] end->ptr: %x, begin->ptr: %x\n", e.ptr, b.ptr);

    MATRIX_TYPE mean = MatIter_mean(b, e);

    return mean;

    // return MatIter_mean(Vector_begin(__v), Vector_end(__v));
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