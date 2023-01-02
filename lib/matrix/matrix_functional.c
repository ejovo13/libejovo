// #include "ejovo_matrix_generic.h"
#ifndef MATRIX_TYPE
#define MATRIX_TYPE double
#endif


#include "ejovo_matrix.h"

// The identity function...
MATRIX_TYPE TYPED(Id)(MATRIX_TYPE x) {
    return x;
}

MATRIX_TYPE TYPED(x_squared)(MATRIX_TYPE x) {
    return x * x;
}

MATRIX_TYPE TYPED(x_cubed)(MATRIX_TYPE x) {
    return x * x * x;
}

// If the predicate is costly, we should consider using the Logical matrix counterpart that
// will filter using logical masks
 TYPED(Vector)*TYPED(filter)(const TYPED(Vector)*__v, TYPED(predicate_fn) __pred) {

    // First I need to pass through the vector to see how many times the predicate is true...
    int count = 0;

    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__v); !TYPED(MatIter_cmp)(it, TYPED(Matrix_end)(__v)); it = TYPED(MatIter_next)(it)) {
        if (__pred(TYPED(MatIter_value)(it))) count++;
    }

    TYPED(Vector)*out = TYPED(Matrix_new)(1, count);

    TYPED(MatIter) j = TYPED(Matrix_begin)(out);

    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__v); !TYPED(MatIter_cmp)(it, TYPED(Matrix_end)(__v)); it = TYPED(MatIter_next)(it)) {
        if (__pred(TYPED(MatIter_value)(it))) {
            TYPED(MatIter_set)(j, TYPED(MatIter_value)(it));
            j = TYPED(MatIter_next)(j);
        }
    }

    return out;

}

 TYPED(Vector)*TYPED(filter_lt)(const TYPED(Vector)*__v, MATRIX_TYPE __cutoff) {

    TYPED(Matrix) *log = TYPED(Matrix_lt)(__v, __cutoff);

    TYPED(Matrix) *out = TYPED(Matrix_logical_index)(__v, log);

    TYPED(Matrix_reset)(&log);

    return out;
}

 TYPED(Vector)*TYPED(filter_lteq)(const TYPED(Vector)*__v, MATRIX_TYPE __cutoff) {

    TYPED(Matrix) *log = TYPED(Matrix_lteq)(__v, __cutoff);

    TYPED(Matrix) *out = TYPED(Matrix_logical_index)(__v, log);

    TYPED(Matrix_reset)(&log);

    return out;

}

 TYPED(Vector)*TYPED(filter_gt)(const TYPED(Vector)*__v, MATRIX_TYPE __cutoff) {

    TYPED(Matrix) *log = TYPED(Matrix_gt)(__v, __cutoff);

    TYPED(Matrix) *out = TYPED(Matrix_logical_index)(__v, log);

    TYPED(Matrix_reset)(&log);

    return out;
}

 TYPED(Vector)*TYPED(filter_gteq)(const TYPED(Vector)*__v, MATRIX_TYPE __cutoff) {

    TYPED(Matrix) *log = TYPED(Matrix_gteq)(__v, __cutoff);

    TYPED(Matrix) *out = TYPED(Matrix_logical_index)(__v, log);

    TYPED(Matrix_reset)(&log);

    return out;
}

 TYPED(Vector)*TYPED(filter_if_not)(const TYPED(Vector)*__v, TYPED(predicate_fn) __pred) {

    int count = 0;

    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__v); !TYPED(MatIter_cmp)(it, TYPED(Matrix_end)(__v)); it = TYPED(MatIter_next)(it)) {
        if (!__pred(TYPED(MatIter_value)(it))) count++;
    }

    TYPED(Vector)*out = TYPED(Matrix_new)(1, count);

    TYPED(MatIter) j = TYPED(Matrix_begin)(out);

    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__v); !TYPED(MatIter_cmp)(it, TYPED(Matrix_end)(__v)); it = TYPED(MatIter_next)(it)) {
        if (!__pred(TYPED(MatIter_value)(it))) {
            TYPED(MatIter_set)(j, TYPED(MatIter_value)(it));
            j = TYPED(MatIter_next)(j);
        }
    }

    return out;

}

// Apply a function that takes a MATRIX_TYPE and returns a MATRIX_TYPE to the contents of a matrix
TYPED(Matrix) *TYPED(map)(const TYPED(Matrix) *__m, TYPED(function) fn) {

    // TYPED(Matrix) *dup = TYPED(matalloc)(__m->nrows, __m->ncols);
    TYPED(Matrix) *dup = TYPED(matclone)(__m);
    return TYPED(apply)(dup, fn);
}

// Apply a Double -> Double function to all of the elements of __m, modifying it in place.
// Then return a pointer to __m
TYPED(Matrix) *TYPED(apply)(TYPED(Matrix) *__m, TYPED(function) fn) {

    const size_t n = TYPED(Matrix_size)(__m);
    for (size_t i = 0; i < n; i++) {
        __m->data[i] = fn(__m->data[i]);
    }

    return __m;
}

// These functions should only operate on VECTORS
// Actually, I think I'm thinking about this wrong. These can operate on matrices but they
// will always return vectors because we can't preserve the size
MATRIX_TYPE TYPED(head)(const TYPED(Matrix) *__m) {
    return TYPED(Matrix_at)(__m, 0, 0);
}

 TYPED(Vector)*TYPED(tail)(const TYPED(Matrix) *__m) {

    // If the size of the matrix is 1, return null;
    if (TYPED(Matrix_size)(__m) <= 1) return NULL;

    TYPED(Matrix) *new = TYPED(Vector_new)(TYPED(Matrix_size)(__m) - 1);

    // Start iterating at the second value
    TYPED(MatIter) it = TYPED(MatIter_next)(TYPED(Matrix_begin)(__m));
    TYPED(MatIter) new_it = TYPED(Matrix_begin)(new);
    TYPED(MatIter) end = TYPED(Matrix_end)(__m);

    for (; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it), new_it = TYPED(MatIter_next)(new_it)) {
        TYPED(MatIter_set)(new_it, TYPED(MatIter_value)(it));
    }

    return new;
}

MATRIX_TYPE TYPED(last)(const TYPED(Matrix) *__m) {
    return TYPED(Matrix_last)(__m);
}


TYPED(Matrix) *TYPED(take)(const TYPED(Matrix) *__m, int n_el) {
    // copy n_el * sizeof(MATRIX_TYPE) bytes of memory from __m
    // to output
    TYPED(Matrix) *out = TYPED(matalloc)(1, n_el);
    memcpy(out->data, __m->data, n_el * sizeof(MATRIX_TYPE));
    return out;
}

// return the initial part of a Vector; TYPED(init)([A]:An) -> [A]
TYPED(Vector)*TYPED(init)(const TYPED(Matrix) *__m) {
    if (TYPED(Matrix_size)(__m) <= 1) return NULL;

    TYPED(Matrix) *new = TYPED(Vector_new)(TYPED(Matrix_size)(__m) - 1);

    // Start iterating at the first value, end from the second to last
    TYPED(MatIter) it = TYPED(MatIter_next)(TYPED(Matrix_begin)(__m));
    TYPED(MatIter) new_it = TYPED(Matrix_begin)(new);
    TYPED(MatIter) end = TYPED(Matrix_end)(__m);
    end.ptr = end.ptr - end.ptr_diff;

    for (; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it), new_it = TYPED(MatIter_next)(new_it)) {
        TYPED(MatIter_set)(new_it, TYPED(MatIter_value)(it));
    }

    return new;
}
