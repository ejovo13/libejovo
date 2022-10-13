#ifndef MATRIX_INDEX_H
#define MATRIX_INDEX_H
// This submodule contains important routines for using a vector of integers as indices.

// General routines for verifying that a vector indeed represents a list of integers would be nice

#include "matrix.h"
#include "matrix_core.h"
#include "matrix_vector.h"
#include "matrix_functional.h"
#include "matrix_logical.h"
#include "matrix_getset.h"

// A new typedef of "Index" is a type of TYPED(Vector)whose values are integers
// #ifndef MATRIX_INT_DEFINED
// #define MATRIX_INT_DEFINED

//     typedef struct Matrix_i {
//         int *data;
//         size_t nrows;
//         size_t ncols;
//     } Matrix_i;

// #endif
// Use your functional tools to simply cast __m to a floor
TYPED(Matrix) *TYPED(Matrix_as_index)(const TYPED(Matrix) *__m);

// Take a supposed index matrix and scrub it -- making sure that all of the elements fall within
// the true bounds of __m
 TYPED(Vector)*TYPED(Matrix_scrub_index)(const TYPED(Matrix) *__m, const TYPED(Index) *__ind);

// dont even scrub the indices, just extract the data!
 TYPED(Vector)*TYPED(matindex)(const TYPED(Matrix) *__m, const TYPED(Index) *__ind);

 TYPED(Vector)*TYPED(Matrix_index)(const TYPED(Matrix) *__m, const TYPED(Index) *__ind);

// Receiving a logical index that is the same shape as __m, return a TYPED(Vector)where
// the mask is true
 TYPED(Vector)*TYPED(Matrix_logical_index)(const TYPED(Matrix) *__m, const TYPED(Logical) *__log);

// Return the indices where a predicate is satisfied
TYPED(Index) *TYPED(Matrix_where)(const TYPED(Matrix) *__m, TYPED(pred_fn) __fn);

// Given a Logical matrix (1.0s and 0.0s), return a column vector whose elements are the indices
// of the nonzero elements and whose length is the number of nozero elements, or sum(__log).
static inline TYPED(Index) *TYPED(Logical_get_index)(const TYPED(Logical) *__log) {

    // Should I validate the index?

    // Create a vector to store the indices, whose nrows is the number of elements in __log
    TYPED(Index) *ind = TYPED(Vector_new)(TYPED(Vector_mask_count)(__log));

    // Now let's iterate through our logical matrix. If the logical matrix is true,
    // add the index counter to ind
    // TYPED(MatIter) ind_it = TYPED(Matrix_begin)(ind);
    TYPED(MatIter) it = TYPED(Matrix_begin)(ind);
    // TYPED(MatIter) end = TYPED(Matrix_end)(log);


    for (size_t i = 0; i < TYPED(Matrix_size)(__log); i++) {
        if (TYPED(matget)(__log, i) == TYPED(TRUE)) {
            TYPED(MatIter_set)(it, i);
            it = TYPED(MatIter_next)(it);
        }
    }

    return ind;
}

// Return the indices where a predicate is satisfied
TYPED(Index) *TYPED(Matrix_where_lt)(const TYPED(Matrix) *__m, double __k);

// Return the indices where a predicate is satisfied
TYPED(Index) *TYPED(Matrix_where_lteq)(const TYPED(Matrix) *__m, double __k);

// Return the indices where a predicate is satisfied
TYPED(Index) *TYPED(Matrix_where_gt)(const TYPED(Matrix) *__m, double __k);

// Return the indices where a predicate is satisfied
TYPED(Index) *TYPED(Matrix_where_gteq)(const TYPED(Matrix) *__m, double __k);

TYPED(Matrix) *TYPED(matsetind)(TYPED(Matrix) *__m, const TYPED(Matrix) *__ind, const TYPED(Matrix) *__val);

TYPED(Matrix) *TYPED(Matrix_set_index)(const TYPED(Matrix) *__m, const TYPED(Matrix) *__ind, const TYPED(Matrix) *__val);

TYPED(Matrix) *TYPED(Matrix_extract_rows)(const TYPED(Matrix) *__m, TYPED(Index) *__ind);

TYPED(Matrix) *TYPED(Matrix_extract_cols)(const TYPED(Matrix) *__m, TYPED(Index) *__ind);

// Take a supposed index matrix and scrub it -- making sure that all of the elements fall within
// the appropriate columns
 TYPED(Vector)*TYPED(Matrix_scrub_col_index)(const TYPED(Matrix) *__m, const TYPED(Index) *__ind);

 TYPED(Vector)*TYPED(Matrix_scrub_row_index)(const TYPED(Matrix) *__m, const TYPED(Index) *__ind);

/**================================================================================================
 *!              Utility functions for dealing with indices -- probably shouldnt be exported
 *================================================================================================**/
static inline bool TYPED(is_int)(double x) {
    return x == floor(x);
}

// Return true if all of the elements in __ind are valid column indices of __m
static inline bool TYPED(are_col_indices_valid)(const TYPED(Matrix) *__m, const TYPED(Index) *__ind) {

    // loop through the __index vector
    TYPED(MatIter) it = TYPED(Matrix_begin)(__ind);
    const TYPED(MatIter) end = TYPED(Matrix_begin)(__ind);

    for(; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it)) {

        double val = TYPED(MatIter_value)(it);
        // make sure the elements of __ind are positive, integers, and within __m's column range
        if (val < 0 || !TYPED(is_int)(val) || val >= __m->ncols) return false;
    }

    return true;
}

// Return true if all of the elements in __ind are valid column indices of __m
static inline bool TYPED(are_row_indices_valid)(const TYPED(Matrix) *__m, const TYPED(Index) *__ind) {


    // loop through the __index vector
    TYPED(MatIter) it = TYPED(Matrix_begin)(__ind);
    const TYPED(MatIter) end = TYPED(Matrix_begin)(__ind);

    for(; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it)) {

        double val = TYPED(MatIter_value)(it);
        // make sure the elements of __ind are positive, integers, and within __m's column range
        if (val < 0 || !TYPED(is_int)(val) || val >= __m->nrows) return false;
    }

    return true;
}

// I want to return the index of the max or min element.
int TYPED(MatIter_max_index)(TYPED(MatIter) begin, const TYPED(MatIter) end);

// I want to return the index of the max or min element.
int TYPED(MatIter_min_index)(TYPED(MatIter) begin, const TYPED(MatIter) end);

int TYPED(Matrix_row_min_index)(const TYPED(Matrix) *__m, size_t __i);

int TYPED(Matrix_row_max_index)(const TYPED(Matrix) *__m, size_t __i);

int TYPED(Matrix_col_min_index)(const TYPED(Matrix) *__m, size_t __i);

int TYPED(Matrix_col_max_index)(const TYPED(Matrix) *__m, size_t __i);

int TYPED(Matrix_col_max_index_from_row)(const TYPED(Matrix) *__m, size_t __j, size_t __i);

// Find the max value of column j starting from row i
int TYPED(Matrix_col_min_index_from_row)(const TYPED(Matrix) *__m, size_t __j, size_t __i);

int TYPED(Matrix_row_max_index_from_col)(const TYPED(Matrix) *__m, size_t __i, size_t __j);

int TYPED(Matrix_row_min_index_from_col)(const TYPED(Matrix) *__m, size_t __i, size_t __j);

#endif