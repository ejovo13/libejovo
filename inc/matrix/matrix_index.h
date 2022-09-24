#pragma once

// This submodule contains important routines for using a vector of integers as indices.

// General routines for verifying that a vector indeed represents a list of integers would be nice

#include "matrix.h"
#include "matrix_core.h"
#include "matrix_vector.h"
#include "matrix_functional.h"
#include "matrix_logical.h"

// A new typedef of "Index" is a type of Vector whose values are integers


// Use your functional tools to simply cast __m to a floor
Vector *MATRIX_FN(as_index)(const MATRIX_T *__m);

// Take a supposed index matrix and scrub it -- making sure that all of the elements fall within
// the true bounds of __m
Vector *MATRIX_FN(scrub_index)(const MATRIX_T *__m, const Index *__ind);

// dont even scrub the indices, just extract the data!
Vector *MAT_FN(index)(const MATRIX_T *__m, const Index *__ind);

Vector *MATRIX_FN(index)(const MATRIX_T *__m, const Index *__ind);

// Receiving a logical index that is the same shape as __m, return a Vector where
// the mask is true
Vector *MATRIX_FN(logical_index)(const MATRIX_T *__m, const Logical *__log);

// Return the indices where a predicate is satisfied
Index *MATRIX_FN(where)(const MATRIX_T *__m, pred_fn __fn);

// Given a Logical matrix (1.0s and 0.0s), return a column vector whose elements are the indices
// of the nonzero elements and whose length is the number of nozero elements, or sum(__log).
Index *Logical_get_index(const Logical *__log);

// Return the indices where a predicate is satisfied
Index *MATRIX_FN(where_lt)(const MATRIX_T *__m, double __k);

// Return the indices where a predicate is satisfied
Index *MATRIX_FN(where_lteq)(const MATRIX_T *__m, double __k);

// Return the indices where a predicate is satisfied
Index *MATRIX_FN(where_gt)(const MATRIX_T *__m, double __k);

// Return the indices where a predicate is satisfied
Index *MATRIX_FN(where_gteq)(const MATRIX_T *__m, double __k);

MATRIX_T *MAT_FN(setind)(MATRIX_T *__m, const MATRIX_T *__ind, const MATRIX_T *__val);

MATRIX_T *MATRIX_FN(set_index)(const MATRIX_T *__m, const MATRIX_T *__ind, const MATRIX_T *__val);

MATRIX_T *MATRIX_FN(extract_rows)(const MATRIX_T *__m, Index *__ind);

MATRIX_T *MATRIX_FN(extract_cols)(const MATRIX_T *__m, Index *__ind);

// Take a supposed index matrix and scrub it -- making sure that all of the elements fall within
// the appropriate columns
Vector *MATRIX_FN(scrub_col_index)(const MATRIX_T *__m, const Index *__ind);

Vector *MATRIX_FN(scrub_row_index)(const MATRIX_T *__m, const Index *__ind);

/**================================================================================================
 *!              Utility functions for dealing with indices -- probably shouldnt be exported
 *================================================================================================**/
static bool is_int(double x) {
    return x == floor(x);
}

// Return true if all of the elements in __ind are valid column indices of __m
static bool are_col_indices_valid(const MATRIX_T *__m, const Index *__ind) {

    // loop through the __index vector
    MATITER_T it = MATRIX_FN(begin)(__ind);
    const MATITER_T end = MATRIX_FN(begin)(__ind);

    for(it; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it)) {

        double val = MATITER_FN(value)(it);
        // make sure the elements of __ind are positive, integers, and within __m's column range
        if (val < 0 || !is_int(val) || val >= __m->ncols) return false;
    }

    return true;
}

// Return true if all of the elements in __ind are valid column indices of __m
static bool are_row_indices_valid(const MATRIX_T *__m, const Index *__ind) {

    // loop through the __index vector
    MATITER_T it = MATRIX_FN(begin)(__ind);
    const MATITER_T end = MATRIX_FN(begin)(__ind);

    for(it; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it)) {

        double val = MATITER_FN(value)(it);
        // make sure the elements of __ind are positive, integers, and within __m's column range
        if (val < 0 || !is_int(val) || val >= __m->nrows) return false;
    }

    return true;
}

// I want to return the index of the max or min element.
int MATITER_FN(max_index)(MATITER_T begin, const MATITER_T end);

// I want to return the index of the max or min element.
int MATITER_FN(min_index)(MATITER_T begin, const MATITER_T end);

int MATRIX_FN(row_min_index)(const MATRIX_T *__m, size_t __i);

int MATRIX_FN(row_max_index)(const MATRIX_T *__m, size_t __i);

int MATRIX_FN(col_min_index)(const MATRIX_T *__m, size_t __i);

int MATRIX_FN(col_max_index)(const MATRIX_T *__m, size_t __i);

int MATRIX_FN(col_max_index_from_row)(const MATRIX_T *__m, size_t __j, size_t __i);

// Find the max value of column j starting from row i
int MATRIX_FN(col_min_index_from_row)(const MATRIX_T *__m, size_t __j, size_t __i);

int MATRIX_FN(row_max_index_from_col)(const MATRIX_T *__m, size_t __i, size_t __j);

int MATRIX_FN(row_min_index_from_col)(const MATRIX_T *__m, size_t __i, size_t __j);