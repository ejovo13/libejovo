// This module contains essential routines to deal with a "logical" MATRIX_T data type that is represented
// by A matrix that is UNIQUELY ones and zeros
#include "ejovo_matrix_generic.h"
// #include "ejovo_matrix.h"
// #include "matrix_logical.h"

MATRIX_TYPE TYPED(TRUE) = 1.0;
MATRIX_TYPE TYPED(FALSE) = 0.0;

// A Logical MATRIX_T shall be typedef'd as a "Mask" to express intent
// This is used as a predicate function. Can be used to make a "true"
// matrix that is the same size as a passed matrix with
// MATRIX_FN(as_logical)(m, true_fn); as MATRIX_FN(as_logical) will accept a
// predicate as an argument
MATRIX_TYPE TYPED_FN(true_fn)(MATRIX_TYPE d) {
    return TYPED(TRUE);
}

MATRIX_TYPE TYPED_FN(NOT)(MATRIX_TYPE d) {
    if (d == TYPED(FALSE)) return TYPED(TRUE);
    else return TYPED(FALSE);
}

MATRIX_TYPE TYPED_FN(AND)(MATRIX_TYPE a, MATRIX_TYPE b) {
    return (a == TYPED(TRUE)) && (b == TYPED(TRUE));
}

MATRIX_TYPE TYPED_FN(OR)(MATRIX_TYPE a, MATRIX_TYPE b) {
    return (a == TYPED(TRUE)) || (b == TYPED(TRUE));
}

// First routine that I should implement is having the notion of "if the vector is logical"
bool MATRIX_FN(is_logical)(const MATRIX_T *__log) {

    // All of the elements MUST be either 1.0 or 0.0
    MATITER_T it = MATRIX_FN(begin)(__log);
    MATITER_T end = MATRIX_FN(end)(__log);
    MATRIX_TYPE val = 0;

    for (it; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it)) {

        val = MATITER_FN(value)(it);
        if (!(val == TYPED(TRUE) || val == TYPED(FALSE))) {
            // printf("%lf registered as different \n", val);
            return false;
        }
    }

    return true;
}


bool VECTOR_FN(is_logical)(const Vector *__log) {
    return MATRIX_FN(is_logical)(__log);
}

// I need to be able to create logical vectors now...
int MATRIX_FN(mask_count)(const MATRIX_T *__mask) {
    return VECTOR_FN(mask_count)(__mask);
}

// Create a logical vector that is the same size as another matrix and set all of it's values to true.
int VECTOR_FN(mask_count)(const Vector *__mask) {

    if (!MATRIX_FN(is_logical)(__mask)) return -1;

    return TYPED_FN(sum)(__mask);
}

// An alternative way to count the value is to count the non zero values


// Create a new logical matrix/vector from a current matrix and a predicate
MATRIX_T *MATRIX_FN(as_logical)(const MATRIX_T *__m, pred_fn __fn) {

    MATRIX_T *log = MAT_FN(alloc)(__m->nrows, __m->ncols);

    MATITER_T end = MATRIX_FN(end)(__m);
    MATITER_T logit = MATRIX_FN(begin)(log);

    // printf("logit points to: %lf\n", MATITER_FN(value)(logit));

    for (MATITER_T it = MATRIX_FN(begin)(__m); !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it), logit = MATITER_FN(next)(logit)) {
        // printf("Processing: %lf\n", MATITER_FN(value)(it));
        MATITER_FN(set)(logit, __fn(MATITER_FN(value)(it)));
    }

    return log;
}

// Return a Logical mask of all the values in __m that are lt __k
Logical *MATRIX_FN(lt)(const MATRIX_T *__m, MATRIX_TYPE __k) {

    MATRIX_T *log = MAT_FN(alloc)(__m->nrows, __m->ncols);

    MATITER_T end = MATRIX_FN(end)(__m);
    MATITER_T logit = MATRIX_FN(begin)(log);

    // printf("logit points to: %lf\n", MATITER_FN(value)(logit));

    for (MATITER_T it = MATRIX_FN(begin)(__m); !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it), logit = MATITER_FN(next)(logit)) {
        // printf("Processing: %lf\n", MATITER_FN(value)(it));
        MATITER_FN(set)(logit, MATITER_FN(value)(it) < __k);
    }

    return log;
}

// Return a Logical mask of all the values in __m that are <= __k
Logical *MATRIX_FN(lteq)(const MATRIX_T *__m, MATRIX_TYPE __k) {

    MATRIX_T *log = MAT_FN(alloc)(__m->nrows, __m->ncols);

    MATITER_T end = MATRIX_FN(end)(__m);
    MATITER_T logit = MATRIX_FN(begin)(log);

    // printf("logit points to: %lf\n", MATITER_FN(value)(logit));

    for (MATITER_T it = MATRIX_FN(begin)(__m); !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it), logit = MATITER_FN(next)(logit)) {
        // printf("Processing: %lf\n", MATITER_FN(value)(it));
        MATITER_FN(set)(logit, MATITER_FN(value)(it) <= __k);
    }

    return log;
}

// Return a Logical mask of all the values in __m that are > lt __k
Logical *MATRIX_FN(gt)(const MATRIX_T *__m, MATRIX_TYPE __k) {

    MATRIX_T *log = MAT_FN(alloc)(__m->nrows, __m->ncols);

    MATITER_T end = MATRIX_FN(end)(__m);
    MATITER_T logit = MATRIX_FN(begin)(log);

    // printf("logit points to: %lf\n", MATITER_FN(value)(logit));

    for (MATITER_T it = MATRIX_FN(begin)(__m); !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it), logit = MATITER_FN(next)(logit)) {
        // printf("Processing: %lf\n", MATITER_FN(value)(it));
        MATITER_FN(set)(logit, MATITER_FN(value)(it) > __k);
    }

    return log;
}

// Return a Logical mask of all the values in __m that are >= __k
Logical *MATRIX_FN(gteq)(const MATRIX_T *__m, MATRIX_TYPE __k) {

    MATRIX_T *log = MAT_FN(alloc)(__m->nrows, __m->ncols);

    MATITER_T end = MATRIX_FN(end)(__m);
    MATITER_T logit = MATRIX_FN(begin)(log);

    // printf("logit points to: %lf\n", MATITER_FN(value)(logit));

    for (MATITER_T it = MATRIX_FN(begin)(__m); !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it), logit = MATITER_FN(next)(logit)) {
        // printf("Processing: %lf\n", MATITER_FN(value)(it));
        MATITER_FN(set)(logit, MATITER_FN(value)(it) >= __k);
    }

    return log;
}






MATRIX_T *MATRIX_FN(as_true)(const MATRIX_T *__m) {
    return MATRIX_FN(as_logical)(__m, TYPED(true_fn));
}

// Wherever the mask is true, set __m to the __val
void MAT_FN(setmask)(MATRIX_T *__m, const MATRIX_T *__mask, MATRIX_TYPE __val) {

    MATITER_T it_mask = MATRIX_FN(begin)(__mask);

    for (MATITER_T it = MATRIX_FN(begin)(__m); !MATITER_FN(cmp)(it, MATRIX_FN(end)(__m)); it = MATITER_FN(next)(it), it_mask = MATITER_FN(next)(it_mask)) {

        if (MATITER_FN(value)(it_mask) == TYPED(TRUE)) MATITER_FN(set)(it, __val);
    }
}

void MAT_FN(setpred)(MATRIX_T *__m, pred_fn __predicate, MATRIX_TYPE __val) {

    for (MATITER_T it = MATRIX_FN(begin)(__m); !MATITER_FN(cmp)(it, MATRIX_FN(end)(__m)); it = MATITER_FN(next)(it)) {
        if (__predicate(MATITER_FN(value)(it)) == TYPED(TRUE)) MATITER_FN(set)(it, __val);
    }
}

// Return a column vector of elements that correspond to a particular mask
Vector *MATRIX_FN(filter_mask)(const MATRIX_T *__m, const MATRIX_T *__mask) {

    // First thing to do is a forward pass to count the number of nonzeros
    int count = VECTOR_FN(mask_count)(__mask);

    // Now allocate a new column vector
    if (count == -1) return NULL;

    Vector *new = MAT_FN(alloc)(count, 1);

    MATITER_T nit = MATRIX_FN(begin)(new);
    MATITER_T mask_it = MATRIX_FN(begin)(__mask);

    for (MATITER_T it = MATRIX_FN(begin)(__m); !MATITER_FN(cmp)(it, MATRIX_FN(end)(__m)); it = MATITER_FN(next)(it), mask_it = MATITER_FN(next)(mask_it)) {

        if (MATITER_FN(value)(mask_it) == TYPED(TRUE)) {
            MATITER_FN(set)(nit, MATITER_FN(value)(it));
            nit = MATITER_FN(next)(nit);
        }
    }

    return new;
}

// return true if count == size of the mask
bool TYPED_FN(Logical_all)(const MATRIX_T *__mask) {
    return (MATRIX_FN(mask_count)(__mask) == MATRIX_FN(size)(__mask));
}

// return true is any of the logical components are true
bool TYPED_FN(Logical_any)(const MATRIX_T *__mask) {

    MATITER_T it = MATRIX_FN(begin)(__mask);
    MATITER_T end = MATRIX_FN(end)(__mask);

    for (it; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it)) {
        if (MATITER_FN(value)(it) == TYPED(TRUE)) return true;
    }

    return false;
}

// Return !__mask
Logical *TYPED_FN(Logical_not)(const MATRIX_T *__mask) {
    return TYPED_FN(map)(__mask, TYPED(NOT));
}