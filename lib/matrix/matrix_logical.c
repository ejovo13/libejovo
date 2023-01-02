// This module contains essential routines to deal with a "logical" TYPED(Matrix) data type that is represented
// by A matrix that is UNIQUELY ones and zeros
// #include "ejovo_matrix_generic.h"
#include "ejovo_matrix.h"
#include "ejovo_bin.h"
// #include "matrix_logical.h"

MATRIX_TYPE TYPED(TRUE) = 1.0;
MATRIX_TYPE TYPED(FALSE) = 0.0;

// A Logical TYPED(Matrix) shall be typedef'd as a "Mask" to express intent
// This is used as a predicate function. Can be used to make a "true"
// matrix that is the same size as a passed matrix with
// TYPED(Matrix_as_logical)(m, true_fn); as TYPED(Matrix_as_logical) will accept a
// predicate as an argument
MATRIX_TYPE TYPED(true_fn)(MATRIX_TYPE d) {
    use(&d);
    return TYPED(TRUE);
}

MATRIX_TYPE TYPED(NOT)(MATRIX_TYPE d) {
    if (d == TYPED(FALSE)) return TYPED(TRUE);
    else return TYPED(FALSE);
}

MATRIX_TYPE TYPED(AND)(MATRIX_TYPE a, MATRIX_TYPE b) {
    return (a == TYPED(TRUE)) && (b == TYPED(TRUE));
}

MATRIX_TYPE TYPED(OR)(MATRIX_TYPE a, MATRIX_TYPE b) {
    return (a == TYPED(TRUE)) || (b == TYPED(TRUE));
}

// First routine that I should implement is having the notion of "if the vector is logical"
bool TYPED(Matrix_is_logical)(const TYPED(Matrix) *__log) {

    // All of the elements MUST be either 1.0 or 0.0
    TYPED(MatIter) it = TYPED(Matrix_begin)(__log);
    TYPED(MatIter) end = TYPED(Matrix_end)(__log);
    MATRIX_TYPE val = 0;

    for (; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it)) {

        val = TYPED(MatIter_value)(it);
        if (!(val == TYPED(TRUE) || val == TYPED(FALSE))) {
            // printf("%lf registered as different \n", val);
            return false;
        }
    }

    return true;
}


bool TYPED(Vector_is_logical)(const TYPED(Vector)*__log) {
    return TYPED(Matrix_is_logical)(__log);
}

// I need to be able to create logical vectors now...
int TYPED(Matrix_mask_count)(const TYPED(Matrix) *__mask) {
    return TYPED(Vector_mask_count)(__mask);
}

// Create a logical vector that is the same size as another matrix and set all of it's values to true.
int TYPED(Vector_mask_count)(const TYPED(Vector)*__mask) {

    if (!TYPED(Matrix_is_logical)(__mask)) return -1;

    return TYPED(sum)(__mask);
}

// An alternative way to count the value is to count the non zero values


// Create a new logical matrix/vector from a current matrix and a predicate
TYPED(Matrix) *TYPED(Matrix_as_logical)(const TYPED(Matrix) *__m, TYPED(pred_fn) __fn) {

    TYPED(Matrix) *log = TYPED(matalloc)(__m->nrows, __m->ncols);

    TYPED(MatIter) end = TYPED(Matrix_end)(__m);
    TYPED(MatIter) logit = TYPED(Matrix_begin)(log);

    // printf("logit points to: %lf\n", TYPED(MatIter_value)(logit));

    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__m); !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it), logit = TYPED(MatIter_next)(logit)) {
        // printf("Processing: %lf\n", TYPED(MatIter_value)(it));
        TYPED(MatIter_set)(logit, __fn(TYPED(MatIter_value)(it)));
    }

    return log;
}

// Return a Logical mask of all the values in __m that are lt __k
TYPED(Logical) *TYPED(Matrix_lt)(const TYPED(Matrix) *__m, MATRIX_TYPE __k) {

    TYPED(Matrix) *log = TYPED(matalloc)(__m->nrows, __m->ncols);

    TYPED(MatIter) end = TYPED(Matrix_end)(__m);
    TYPED(MatIter) logit = TYPED(Matrix_begin)(log);

    // printf("logit points to: %lf\n", TYPED(MatIter_value)(logit));

    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__m); !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it), logit = TYPED(MatIter_next)(logit)) {
        // printf("Processing: %lf\n", TYPED(MatIter_value)(it));
    #ifdef MATRIX_COMPLEX
        TYPED(MatIter_set)(logit, cabs(TYPED(MatIter_value)(it)) < cabs(__k));
    #else
        TYPED(MatIter_set)(logit, TYPED(MatIter_value)(it) < __k);
    #endif
    }

    return log;
}

// Return a Logical mask of all the values in __m that are <= __k
TYPED(Logical) *TYPED(Matrix_lteq)(const TYPED(Matrix) *__m, MATRIX_TYPE __k) {

    TYPED(Matrix) *log = TYPED(matalloc)(__m->nrows, __m->ncols);

    TYPED(MatIter) end = TYPED(Matrix_end)(__m);
    TYPED(MatIter) logit = TYPED(Matrix_begin)(log);

    // printf("logit points to: %lf\n", TYPED(MatIter_value)(logit));

    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__m); !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it), logit = TYPED(MatIter_next)(logit)) {
        // printf("Processing: %lf\n", TYPED(MatIter_value)(it));
    #ifdef MATRIX_COMPLEX
        TYPED(MatIter_set)(logit, cabs(TYPED(MatIter_value)(it)) <= cabs(__k));
    #else
        TYPED(MatIter_set)(logit, TYPED(MatIter_value)(it) <= __k);
    #endif
    }

    return log;
}

// Return a Logical mask of all the values in __m that are > lt __k
TYPED(Logical) *TYPED(Matrix_gt)(const TYPED(Matrix) *__m, MATRIX_TYPE __k) {

    TYPED(Matrix) *log = TYPED(matalloc)(__m->nrows, __m->ncols);

    TYPED(MatIter) end = TYPED(Matrix_end)(__m);
    TYPED(MatIter) logit = TYPED(Matrix_begin)(log);

    // printf("logit points to: %lf\n", TYPED(MatIter_value)(logit));

    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__m); !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it), logit = TYPED(MatIter_next)(logit)) {
        // printf("Processing: %lf\n", TYPED(MatIter_value)(it));
    #ifdef MATRIX_COMPLEX
        TYPED(MatIter_set)(logit, cabs(TYPED(MatIter_value)(it)) > cabs(__k));
    #else
        TYPED(MatIter_set)(logit, TYPED(MatIter_value)(it) > __k);
    #endif
    }

    return log;
}

// Return a Logical mask of all the values in __m that are >= __k
TYPED(Logical) *TYPED(Matrix_gteq)(const TYPED(Matrix) *__m, MATRIX_TYPE __k) {

    TYPED(Matrix) *log = TYPED(matalloc)(__m->nrows, __m->ncols);

    TYPED(MatIter) end = TYPED(Matrix_end)(__m);
    TYPED(MatIter) logit = TYPED(Matrix_begin)(log);

    // printf("logit points to: %lf\n", TYPED(MatIter_value)(logit));

    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__m); !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it), logit = TYPED(MatIter_next)(logit)) {
        // printf("Processing: %lf\n", TYPED(MatIter_value)(it));
    #ifdef MATRIX_COMPLEX
        TYPED(MatIter_set)(logit, cabs(TYPED(MatIter_value)(it)) >= cabs(__k));
    #else
        TYPED(MatIter_set)(logit, TYPED(MatIter_value)(it) >= __k);
    #endif
    }

    return log;
}






TYPED(Matrix) *TYPED(Matrix_as_true)(const TYPED(Matrix) *__m) {
    return TYPED(Matrix_as_logical)(__m, TYPED(true_fn));
}

// Wherever the mask is true, set __m to the __val
void TYPED(matsetmask)(TYPED(Matrix) *__m, const TYPED(Matrix) *__mask, MATRIX_TYPE __val) {

    TYPED(MatIter) it_mask = TYPED(Matrix_begin)(__mask);

    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__m); !TYPED(MatIter_cmp)(it, TYPED(Matrix_end)(__m)); it = TYPED(MatIter_next)(it), it_mask = TYPED(MatIter_next)(it_mask)) {

        if (TYPED(MatIter_value)(it_mask) == TYPED(TRUE)) TYPED(MatIter_set)(it, __val);
    }
}

void TYPED(matsetpred)(TYPED(Matrix) *__m, TYPED(pred_fn) __predicate, MATRIX_TYPE __val) {

    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__m); !TYPED(MatIter_cmp)(it, TYPED(Matrix_end)(__m)); it = TYPED(MatIter_next)(it)) {
        if (__predicate(TYPED(MatIter_value)(it)) == TYPED(TRUE)) TYPED(MatIter_set)(it, __val);
    }
}

// Return a column vector of elements that correspond to a particular mask
 TYPED(Vector)*TYPED(Matrix_filter_mask)(const TYPED(Matrix) *__m, const TYPED(Matrix) *__mask) {

    // First thing to do is a forward pass to count the number of nonzeros
    int count = TYPED(Vector_mask_count)(__mask);

    // Now allocate a new column vector
    if (count == -1) return NULL;

    TYPED(Vector)*new = TYPED(matalloc)(count, 1);

    TYPED(MatIter) nit = TYPED(Matrix_begin)(new);
    TYPED(MatIter) mask_it = TYPED(Matrix_begin)(__mask);

    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__m); !TYPED(MatIter_cmp)(it, TYPED(Matrix_end)(__m)); it = TYPED(MatIter_next)(it), mask_it = TYPED(MatIter_next)(mask_it)) {

        if (TYPED(MatIter_value)(mask_it) == TYPED(TRUE)) {
            TYPED(MatIter_set)(nit, TYPED(MatIter_value)(it));
            nit = TYPED(MatIter_next)(nit);
        }
    }

    return new;
}

// return true if count == size of the mask
bool TYPED(Logical_all)(const TYPED(Matrix) *__mask) {
    return ((size_t) TYPED(Matrix_mask_count)(__mask) == TYPED(Matrix_size)(__mask));
}

// return true is any of the logical components are true
bool TYPED(Logical_any)(const TYPED(Matrix) *__mask) {

    TYPED(MatIter) it = TYPED(Matrix_begin)(__mask);
    TYPED(MatIter) end = TYPED(Matrix_end)(__mask);

    for (; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it)) {
        if (TYPED(MatIter_value)(it) == TYPED(TRUE)) return true;
    }

    return false;
}

// Return !__mask
TYPED(Logical) *TYPED(Logical_not)(const TYPED(Matrix) *__mask) {
    return TYPED(map)(__mask, TYPED(NOT));
}