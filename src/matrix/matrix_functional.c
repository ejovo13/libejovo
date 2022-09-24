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

    for (MATITER_T it = MATRIX_FN(begin)(__v); !MATITER_FN(cmp)(it, MATRIX_FN(end)(__v)); it = MATITER_FN(next)(it)) {
        if (__pred(MATITER_FN(value)(it))) count++;
    }

    Vector *out = MATRIX_FN(new)(1, count);

    MATITER_T j = MATRIX_FN(begin)(out);

    for (MATITER_T it = MATRIX_FN(begin)(__v); !MATITER_FN(cmp)(it, MATRIX_FN(end)(__v)); it = MATITER_FN(next)(it)) {
        if (__pred(MATITER_FN(value)(it))) {
            MATITER_FN(set)(j, MATITER_FN(value)(it));
            j = MATITER_FN(next)(j);
        }
    }

    return out;

}

Vector *filter_lt(const Vector *__v, double __cutoff) {

    MATRIX_T *log = MATRIX_FN(lt)(__v, __cutoff);

    MATRIX_T *out = MATRIX_FN(logical_index)(__v, log);

    MATRIX_FN(reset)(&log);

    return out;
}

Vector *filter_lteq(const Vector *__v, double __cutoff) {

    MATRIX_T *log = MATRIX_FN(lteq)(__v, __cutoff);

    MATRIX_T *out = MATRIX_FN(logical_index)(__v, log);

    MATRIX_FN(reset)(&log);

    return out;

}

Vector *filter_gt(const Vector *__v, double __cutoff) {

    MATRIX_T *log = MATRIX_FN(gt)(__v, __cutoff);

    MATRIX_T *out = MATRIX_FN(logical_index)(__v, log);

    MATRIX_FN(reset)(&log);

    return out;
}

Vector *filter_gteq(const Vector *__v, double __cutoff) {

    MATRIX_T *log = MATRIX_FN(gteq)(__v, __cutoff);

    MATRIX_T *out = MATRIX_FN(logical_index)(__v, log);

    MATRIX_FN(reset)(&log);

    return out;
}

Vector *filter_if_not(const Vector *__v, predicate_fn __pred) {

    int count = 0;

    for (MATITER_T it = MATRIX_FN(begin)(__v); !MATITER_FN(cmp)(it, MATRIX_FN(end)(__v)); it = MATITER_FN(next)(it)) {
        if (!__pred(MATITER_FN(value)(it))) count++;
    }

    Vector *out = MATRIX_FN(new)(1, count);

    MATITER_T j = MATRIX_FN(begin)(out);

    for (MATITER_T it = MATRIX_FN(begin)(__v); !MATITER_FN(cmp)(it, MATRIX_FN(end)(__v)); it = MATITER_FN(next)(it)) {
        if (!__pred(MATITER_FN(value)(it))) {
            MATITER_FN(set)(j, MATITER_FN(value)(it));
            j = MATITER_FN(next)(j);
        }
    }

    return out;

}

// Apply a function that takes a double and returns a double to the contents of a matrix
MATRIX_T *map(const MATRIX_T *__m, function fn) {

    // MATRIX_T *dup = MAT_FN(alloc)(__m->nrows, __m->ncols);
    MATRIX_T *dup = MAT_FN(clone)(__m);
    return apply(dup, fn);
}

// Apply a Double -> Double function to all of the elements of __m, modifying it in place.
// Then return a pointer to __m
MATRIX_T *apply(MATRIX_T *__m, function fn) {

    const size_t n = MATRIX_FN(size)(__m);
    for (size_t i = 0; i < n; i++) {
        __m->data[i] = fn(__m->data[i]);
    }

    return __m;
}

// These functions should only operate on VECTORS
// Actually, I think I'm thinking about this wrong. These can operate on matrices but they
// will always return vectors because we can't preserve the size
MATRIX_TYPE head(const MATRIX_T *__m) {
    return MATRIX_FN(at)(__m, 0, 0);
}

Vector *tail(const MATRIX_T *__m) {

    // If the size of the matrix is 1, return null;
    if (MATRIX_FN(size)(__m) <= 1) return NULL;

    MATRIX_T *new = VECTOR_FN(new)(MATRIX_FN(size)(__m) - 1);

    // Start iterating at the second value
    MATITER_T it = MATITER_FN(next)(MATRIX_FN(begin)(__m));
    MATITER_T new_it = MATRIX_FN(begin)(new);
    MATITER_T end = MATRIX_FN(end)(__m);

    for (it; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it), new_it = MATITER_FN(next)(new_it)) {
        MATITER_FN(set)(new_it, MATITER_FN(value)(it));
    }

    return new;
}

MATRIX_TYPE last(const MATRIX_T *__m) {
    return MATRIX_FN(last)(__m);
}

// return the initial part of a Vector; init([A]:An) -> [A]
Vector *init (const MATRIX_T *__m) {
    if (MATRIX_FN(size)(__m) <= 1) return NULL;

    MATRIX_T *new = VECTOR_FN(new)(MATRIX_FN(size)(__m) - 1);

    // Start iterating at the first value, end from the second to last
    MATITER_T it = MATITER_FN(next)(MATRIX_FN(begin)(__m));
    MATITER_T new_it = MATRIX_FN(begin)(new);
    MATITER_T end = MATRIX_FN(end)(__m);
    end.ptr = end.ptr - end.ptr_diff;

    for (it; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it), new_it = MATITER_FN(next)(new_it)) {
        MATITER_FN(set)(new_it, MATITER_FN(value)(it));
    }

    return new;
}
