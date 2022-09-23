#include "ejovo_matrix.h"

// The identity function...
double ID(double x) {
    return x;
}

double x_squared(double x) {
    return x * x;
}

double x_cubed(double x) {
    return x * x * x;
}

// If the predicate is costly, we should consider using the Logical matrix counterpart that
// will filter using logical masks
Vector *filter(const Vector *__v, predicate_fn __pred) {

    // First I need to pass through the vector to see how many times the predicate is true...
    int count = 0;

    for (MatIter it = Matrix_begin(__v); !MatIter_cmp(it, Matrix_end(__v)); it = MatIter_next(it)) {
        if (__pred(MatIter_value(it))) count++;
    }

    Vector *out = Matrix_new(1, count);

    MatIter j = Matrix_begin(out);

    for (MatIter it = Matrix_begin(__v); !MatIter_cmp(it, Matrix_end(__v)); it = MatIter_next(it)) {
        if (__pred(MatIter_value(it))) {
            MatIter_set(j, MatIter_value(it));
            j = MatIter_next(j);
        }
    }

    return out;

}

Vector *filter_lt(const Vector *__v, double __cutoff) {

    Matrix *log = Matrix_lt(__v, __cutoff);

    Matrix *out = Matrix_logical_index(__v, log);

    Matrix_reset(&log);

    return out;
}

Vector *filter_lteq(const Vector *__v, double __cutoff) {

    Matrix *log = Matrix_lteq(__v, __cutoff);

    Matrix *out = Matrix_logical_index(__v, log);

    Matrix_reset(&log);

    return out;

}

Vector *filter_gt(const Vector *__v, double __cutoff) {

    Matrix *log = Matrix_gt(__v, __cutoff);

    Matrix *out = Matrix_logical_index(__v, log);

    Matrix_reset(&log);

    return out;
}

Vector *filter_gteq(const Vector *__v, double __cutoff) {

    Matrix *log = Matrix_gteq(__v, __cutoff);

    Matrix *out = Matrix_logical_index(__v, log);

    Matrix_reset(&log);

    return out;
}

Vector *filter_if_not(const Vector *__v, predicate_fn __pred) {

    int count = 0;

    for (MatIter it = Matrix_begin(__v); !MatIter_cmp(it, Matrix_end(__v)); it = MatIter_next(it)) {
        if (!__pred(MatIter_value(it))) count++;
    }

    Vector *out = Matrix_new(1, count);

    MatIter j = Matrix_begin(out);

    for (MatIter it = Matrix_begin(__v); !MatIter_cmp(it, Matrix_end(__v)); it = MatIter_next(it)) {
        if (!__pred(MatIter_value(it))) {
            MatIter_set(j, MatIter_value(it));
            j = MatIter_next(j);
        }
    }

    return out;

}

// Apply a function that takes a double and returns a double to the contents of a matrix
Matrix *map(const Matrix *__m, function fn) {

    Matrix *dup = matalloc(__m->nrows, __m->ncols);

    MatIter dup_it = Matrix_begin(dup);

    for (MatIter it = Matrix_begin(__m); !MatIter_cmp(it, Matrix_end(__m)); it = MatIter_next(it), dup_it = MatIter_next(dup_it)) {
        MatIter_set(dup_it, fn(MatIter_value(it)));
    }

    return dup;
}

// Apply a Double -> Double function to all of the elements of __m, modifying it in place.
// Then return a pointer to __m
Matrix *apply(Matrix *__m, function fn) {

    MatIter it = Matrix_begin(__m);
    MatIter end = Matrix_end(__m);

    for (it; !MatIter_cmp(it, end); it = MatIter_next(it)) {
        MatIter_set(it, fn(MatIter_value(it)));
    }

    return __m;
}

// These functions should only operate on VECTORS
// Actually, I think I'm thinking about this wrong. These can operate on matrices but they
// will always return vectors because we can't preserve the size
MATRIX_TYPE head(const Matrix *__m) {
    return Matrix_at(__m, 0, 0);
}

Vector *tail(const Matrix *__m) {

    // If the size of the matrix is 1, return null;
    if (Matrix_size(__m) <= 1) return NULL;

    Matrix *new = Vector_new(Matrix_size(__m) - 1);

    // Start iterating at the second value
    MatIter it = MatIter_next(Matrix_begin(__m));
    MatIter new_it = Matrix_begin(new);
    MatIter end = Matrix_end(__m);

    for (it; !MatIter_cmp(it, end); it = MatIter_next(it), new_it = MatIter_next(new_it)) {
        MatIter_set(new_it, MatIter_value(it));
    }

    return new;
}

MATRIX_TYPE last(const Matrix *__m) {
    return Matrix_last(__m);
}

// return the initial part of a Vector; init([A]:An) -> [A]
Vector *init (const Matrix *__m) {
    if (Matrix_size(__m) <= 1) return NULL;

    Matrix *new = Vector_new(Matrix_size(__m) - 1);

    // Start iterating at the first value, end from the second to last
    MatIter it = MatIter_next(Matrix_begin(__m));
    MatIter new_it = Matrix_begin(new);
    MatIter end = Matrix_end(__m);
    end.ptr = end.ptr - end.ptr_diff;

    for (it; !MatIter_cmp(it, end); it = MatIter_next(it), new_it = MatIter_next(new_it)) {
        MatIter_set(new_it, MatIter_value(it));
    }

    return new;
}
