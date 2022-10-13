// This submodule contains important routines for using a vector of integers as indices.

// General routines for verifying that a vector indeed represents a list of integers would be nice
// #include "ejovo_matrix_generic.h"
#include "matrix/matrix_index.h"
// A new typedef of "Index" is a type of TYPED(Vector)whose values are integers

// Low level function
MATRIX_TYPE TYPED(floor)(MATRIX_TYPE a) {
    return floor(a);
}

// Use your functional tools to simply cast __m to a floor
TYPED(Matrix) *TYPED(Matrix_as_index)(const TYPED(Matrix) *__m) {

    // Convert __m to an integer matrix with a cast to integer
    TYPED(Matrix) *ind = TYPED(Matrix_new)(__m->nrows, __m->ncols);
    for (size_t i = 0; i < TYPED(Matrix_size)(ind); i++) {
        ind->data[i] = TYPED(floor)(__m->data[i]);
    }

    return ind; // Ok this is neat but now I think that it actually has 0 utility...
}

// Take a supposed index matrix and scrub it -- making sure that all of the elements fall within
// the true bounds of __m
 TYPED(Vector)*TYPED(Matrix_scrub_index)(const TYPED(Matrix) *__m, const TYPED(Index) *__ind) {

    // The only bounds we care about are (size - 1) and 0.
    size_t len = TYPED(Matrix_size)(__m);

    int n_valid = 0;
    double val = 0;

    // iterate through the index, count how many are valid
    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__ind); !TYPED(MatIter_cmp)(it, TYPED(Matrix_end)(__ind)); it = TYPED(MatIter_next)(it)) {
        val = TYPED(MatIter_value)(it);
        if (val >= 0 && val <= (len - 1)) n_valid++;
    }

    TYPED(Vector)*out = TYPED(Vector_new)(n_valid);


    TYPED(MatIter) it = TYPED(Matrix_begin)(__ind);
    TYPED(MatIter) out_it = TYPED(Matrix_begin)(out);
    TYPED(MatIter) end = TYPED(Matrix_end)(__ind);

    for (; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it)) {
        val = TYPED(MatIter_value)(it);
        if (val >= 0 && val <= (len - 1)) {
            TYPED(MatIter_set)(out_it, floor(val)); // save the integer index
            out_it = TYPED(MatIter_next)(out_it);
        }
    }

    return out;
}

// Take a supposed index matrix and scrub it -- making sure that all of the elements fall within
// the appropriate columns
 TYPED(Vector)*TYPED(Matrix_scrub_col_index)(const TYPED(Matrix) *__m, const TYPED(Index) *__ind) {

    // The only bounds we care about are (size - 1) and 0.
    int n_valid = 0;
    double val = 0;

    // First let's check once if the indices are valid:
    // iterate through the index, count how many are valid
    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__ind); !TYPED(MatIter_cmp)(it, TYPED(Matrix_end)(__ind)); it = TYPED(MatIter_next)(it)) {
        val = TYPED(MatIter_value)(it);
        if (val >= 0 && val <= (__m->ncols - 1)) n_valid++;
    }

    TYPED(Vector)*out = TYPED(Vector_new)(n_valid);


    TYPED(MatIter) it = TYPED(Matrix_begin)(__ind);
    TYPED(MatIter) out_it = TYPED(Matrix_begin)(out);
    TYPED(MatIter) end = TYPED(Matrix_end)(__ind);

    for (; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it)) {
        val = TYPED(MatIter_value)(it);
        if (val >= 0 && val <= (__m->ncols - 1)) {
            TYPED(MatIter_set)(out_it, floor(val)); // save the integer index
            out_it = TYPED(MatIter_next)(out_it);
        }
    }

    return out;
}

 TYPED(Vector)*TYPED(Matrix_scrub_row_index)(const TYPED(Matrix) *__m, const TYPED(Index) *__ind) {

    // The only bounds we care about are (size - 1) and 0.
    int n_valid = 0;
    double val = 0;

    // First let's check once if the indices are valid:
    // iterate through the index, count how many are valid
    for (TYPED(MatIter) it = TYPED(Matrix_begin)(__ind); !TYPED(MatIter_cmp)(it, TYPED(Matrix_end)(__ind)); it = TYPED(MatIter_next)(it)) {
        val = TYPED(MatIter_value)(it);
        if (val >= 0 && val <= (__m->nrows - 1)) n_valid++;
    }

    TYPED(Vector)*out = TYPED(Vector_new)(n_valid);


    TYPED(MatIter) it = TYPED(Matrix_begin)(__ind);
    TYPED(MatIter) out_it = TYPED(Matrix_begin)(out);
    TYPED(MatIter) end = TYPED(Matrix_end)(__ind);

    for (; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it)) {
        val = TYPED(MatIter_value)(it);
        if (val >= 0 && val <= (__m->nrows - 1)) {
            TYPED(MatIter_set)(out_it, floor(val)); // save the integer index
            out_it = TYPED(MatIter_next)(out_it);
        }
    }

    return out;
}

// dont even scrub the indices, just extract the data!
 TYPED(Vector)*TYPED(matindex)(const TYPED(Matrix) *__m, const TYPED(Index) *__ind) {

    // first allocate a new matrix of size __ind
    TYPED(Vector)*out = TYPED(matalloc)(TYPED(Matrix_size)(__ind), 1);

    // now iterate through the indices
    TYPED(MatIter) it = TYPED(Matrix_begin)(__ind);
    TYPED(MatIter) out_it = TYPED(Matrix_begin)(out);
    TYPED(MatIter) end = TYPED(Matrix_end)(__ind);

    for (; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it), out_it = TYPED(MatIter_next)(out_it)) {
        TYPED(MatIter_set)(out_it, TYPED(matget)(__m, TYPED(MatIter_value)(it)));
    }

    return out;
}

 TYPED(Vector)*TYPED(Matrix_index)(const TYPED(Matrix) *__m, const TYPED(Index) *__ind) {

    // Using the indices described by __ind, return a newly allocated vector whose elements are the
    // ROW-MAJOR INDICES of a matrix.

    // let's first just scrub the indices
    TYPED(Vector)*valid = TYPED(Matrix_scrub_index)(__m, __ind);

    TYPED(Vector)*out = TYPED(matindex)(__m, valid);

    TYPED(Matrix_free)(valid);

    return out;
}

// Receiving a logical index that is the same shape as __m, return a TYPED(Vector)where
// the mask is true
 TYPED(Vector)*TYPED(Matrix_logical_index)(const TYPED(Matrix) *__m, const TYPED(Logical) *__log) {

    if (!TYPED(Matrix_is_logical)(__log)) return NULL;

    // How should I deal with the different cases? If a matrix is the same shape, size, etc..

    // if the sizes are different, bail
    if (TYPED(Matrix_size)(__m) != TYPED(Matrix_size)(__log)) return NULL;

    // Else, let's count the number in log
    int count = TYPED(sum)(__log);

    // and allocate a new vector
    TYPED(Vector)*out = TYPED(matalloc)(count, 1);

    TYPED(MatIter) out_it = TYPED(Matrix_begin)(out);
    TYPED(MatIter) it = TYPED(Matrix_begin)(__log);
    TYPED(MatIter) m_it = TYPED(Matrix_begin)(__m);

    TYPED(MatIter) end = TYPED(Matrix_end)(__log);

    for (; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it), m_it = TYPED(MatIter_next)(m_it)) {
        if (TYPED(MatIter_value)(it) == TYPED(TRUE)) {
            TYPED(MatIter_set)(out_it, TYPED(MatIter_value)(m_it));
            out_it = TYPED(MatIter_next)(out_it);
        }
    }

    return out;
}

// Return the indices where a predicate is satisfied
TYPED(Index) *TYPED(Matrix_where)(const TYPED(Matrix) *__m, TYPED(pred_fn) __fn) {

    // First let's get the logical matrix:
    TYPED(Logical) *log = TYPED(Matrix_as_logical)(__m, __fn);

    // And then let's allocate space for our new vector of indices

    TYPED(Index) *ind = TYPED(matalloc)(TYPED(sum)(log), 1);

    // Now let's iterate through our logical matrix. If the logical matrix is true,
    // add the index counter to ind
    // TYPED(MatIter) ind_it = TYPED(Matrix_begin)(ind);
    TYPED(MatIter) it = TYPED(Matrix_begin)(ind);
    // TYPED(MatIter) end = TYPED(Matrix_end)(log);


    for (size_t i = 0; i < TYPED(Matrix_size)(__m); i++) {
        if (TYPED(matget)(log, i) == TYPED(TRUE)) {
            TYPED(MatIter_set)(it, i);
            it = TYPED(MatIter_next)(it);
        }
    }

    TYPED(Matrix_free)(log);
    return ind;
}

// // Given a Logical matrix (1.0s and 0.0s), return a column vector whose elements are the indices
// // of the nonzero elements and whose length is the number of nozero elements, or sum(__log).
// TYPED(Index) *Logical_get_index(const Logical *__log) {

//     // Should I validate the index?

//     // Create a vector to store the indices, whose nrows is the number of elements in __log
//     TYPED(Index) *ind = TYPED(Vector_new)(TYPED(Vector_mask_count)(__log));

//     // Now let's iterate through our logical matrix. If the logical matrix is true,
//     // add the index counter to ind
//     // TYPED(MatIter) ind_it = TYPED(Matrix_begin)(ind);
//     TYPED(MatIter) it = TYPED(Matrix_begin)(ind);
//     // TYPED(MatIter) end = TYPED(Matrix_end)(log);


//     for (size_t i = 0; i < TYPED(Matrix_size)(__log); i++) {
//         if (TYPED(matget)(__log, i) == TRUE) {
//             TYPED(MatIter_set)(it, i);
//             it = TYPED(MatIter_next)(it);
//         }
//     }

//     return ind;
// }

// Return the indices where a predicate is satisfied
TYPED(Index) *TYPED(Matrix_where_lt)(const TYPED(Matrix) *__m, double __k) {

    // First let's get the logical matrix:
    TYPED(Logical) *logic = TYPED(Matrix_lt)(__m, __k);

    TYPED(Index) *ind = TYPED(Logical_get_index)(logic);

    TYPED(Matrix_free)(logic);

    return ind;
}

// Return the indices where a predicate is satisfied
TYPED(Index) *TYPED(Matrix_where_lteq)(const TYPED(Matrix) *__m, double __k) {

    // First let's get the logical matrix:
    TYPED(Logical) *logic = TYPED(Matrix_lteq)(__m, __k);

    TYPED(Index) *ind = TYPED(Logical_get_index)(logic);

    TYPED(Matrix_free)(logic);

    return ind;
}

// Return the indices where a predicate is satisfied
TYPED(Index) *TYPED(Matrix_where_gt)(const TYPED(Matrix) *__m, double __k) {

    // First let's get the logical matrix:
    TYPED(Logical) *logic = TYPED(Matrix_gt)(__m, __k);

    TYPED(Index) *ind = TYPED(Logical_get_index)(logic);

    TYPED(Matrix_free)(logic);

    return ind;
}

// Return the indices where a predicate is satisfied
TYPED(Index) *TYPED(Matrix_where_gteq)(const TYPED(Matrix) *__m, double __k) {

    // First let's get the logical matrix:
    TYPED(Logical) *logic = TYPED(Matrix_gteq)(__m, __k);

    TYPED(Index) *ind = TYPED(Logical_get_index)(logic);

    TYPED(Matrix_free)(logic);

    return ind;
}

TYPED(Matrix) *TYPED(matsetind)(TYPED(Matrix) *__m, const TYPED(Matrix) *__ind, const TYPED(Matrix) *__val) {

    // Loop through the indices

    TYPED(MatIter) it = TYPED(Matrix_begin)(__ind);
    TYPED(MatIter) val_it = TYPED(Matrix_begin)(__val);

    TYPED(MatIter) end = TYPED(Matrix_end)(__ind);
    TYPED(MatIter) val_end = TYPED(Matrix_end)(__val);

    for (; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it), val_it = TYPED(MatIter_next)(val_it)) {
        if (TYPED(MatIter_cmp)(val_it, val_end)) val_it = TYPED(Matrix_begin)(__val); // loop back the value if we have passed the end
        __m->data[(int) TYPED(MatIter_value)(it)] = TYPED(MatIter_value)(val_it);
    }

    return __m;
}

TYPED(Matrix) *TYPED(Matrix_set_index)(const TYPED(Matrix) *__m, const TYPED(Index) *__ind, const TYPED(Matrix) *__val) {

    // Duplicate __m
    TYPED(Matrix) *m = TYPED(Matrix_clone)(__m);
    return TYPED(matsetind)(m, __ind, __val);
}

TYPED(Matrix) *TYPED(Matrix_extract_rows)(const TYPED(Matrix) *__m, TYPED(Index) *__ind) {

    // First let's figure out the size of the resulting matrix.
    // Necessarily, the output will have __m->ncols cols whereas the number of
    // rows will depend on if the passed indices are legit or not

    int nrows = 0;
    TYPED(Index) *ind = NULL;

    bool ind_newly_allocated = false;

    if (TYPED(are_row_indices_valid)(__m, __ind)) {
        nrows = TYPED(Matrix_size)(__ind);
        ind = __ind;
    } else {

        // we need to allocate a new indices vector
        ind_newly_allocated = true;
        ind = TYPED(Matrix_scrub_row_index)(__m, __ind);
        nrows = TYPED(Matrix_size)(ind);
    }

    TYPED(Matrix) *out = TYPED(Matrix_new)(nrows, __m->ncols);

    // Now let's iterate through ind, copying the contents of the columns over to out.
    // This operation would be more efficient if we could just copy a certain block of memory
    // to another, although since the matrix is either row or column major order, we are forced
    // to use iteration in at least on of the cases. To keep this function more adaptive,
    // we opt to use the iterative route.

    TYPED(MatIter) it = TYPED(Vector_begin)(ind);
    const TYPED(MatIter) end = TYPED(Vector_end)(ind);

    for (int i = 0; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it), i++) {
        TYPED(Matrix_set_row_iter)(out, i, TYPED(Matrix_row_begin)(__m, TYPED(MatIter_value)(it))); // clean way to set all of the columns
    }

    if (ind_newly_allocated) TYPED(Matrix_free)(ind);

    return out;
}

TYPED(Matrix) *TYPED(Matrix_extract_cols)(const TYPED(Matrix) *__m, TYPED(Index) *__ind) {

    // First let's figure out the size of the resulting matrix.
    // Necessarily, the output will have __m->nrows rows whereas the number of
    // columns will depend on if the passed indices are legit or not

    int ncols = 0;
    TYPED(Index) *ind = NULL;

    bool ind_newly_allocated = false;

    if (TYPED(are_col_indices_valid)(__m, __ind)) {
        ncols = TYPED(Matrix_size)(__ind);
        ind = __ind;
    } else {

        // we need to allocate a new indices vector
        ind_newly_allocated = true;
        ind = TYPED(Matrix_scrub_col_index)(__m, __ind);
        ncols = TYPED(Matrix_size)(ind);
    }

    TYPED(Matrix) *out = TYPED(Matrix_new)(__m->nrows, ncols);

    // Now let's iterate through ind, copying the contents of the columns over to out.
    // This operation would be more efficient if we could just copy a certain block of memory
    // to another, although since the matrix is either row or column major order, we are forced
    // to use iteration in at least on of the cases. To keep this function more adaptive,
    // we opt to use the iterative route.

    TYPED(MatIter) it = TYPED(Vector_begin)(ind);
    const TYPED(MatIter) end = TYPED(Vector_end)(ind);

    for (int i = 0; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it), i++) {
        TYPED(Matrix_set_col_iter)(out, i, TYPED(Matrix_col_begin)(__m, TYPED(MatIter_value)(it))); // clean way to set all of the columns
    }

    if (ind_newly_allocated) TYPED(Matrix_free)(ind);

    return out;
}


/**================================================================================================
 *!              Utility functions for dealing with indices -- probably shouldnt be exported
 *================================================================================================**/

// Return true if all of the elements in __ind are valid column indices of __m
// static bool are_col_indices_valid(const TYPED(Matrix) *__m, const TYPED(Index) *__ind) {

//     // loop through the __index vector
//     TYPED(MatIter) it = TYPED(Matrix_begin)(__ind);
//     const TYPED(MatIter) end = TYPED(Matrix_begin)(__ind);

//     for(it; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it)) {

//         double val = TYPED(MatIter_value)(it);
//         // make sure the elements of __ind are positive, integers, and within __m's column range
//         if (val < 0 || !TYPED(is_int)(val) || val >= __m->ncols) return false;
//     }

//     return true;
// }

// Return true if all of the elements in __ind are valid column indices of __m
// static bool are_row_indices_valid(const TYPED(Matrix) *__m, const TYPED(Index) *__ind) {

//     // loop through the __index vector
//     TYPED(MatIter) it = TYPED(Matrix_begin)(__ind);
//     const TYPED(MatIter) end = TYPED(Matrix_begin)(__ind);

//     for(it; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it)) {

//         double val = TYPED(MatIter_value)(it);
//         // make sure the elements of __ind are positive, integers, and within __m's column range
//         if (val < 0 || !TYPED(is_int)(val) || val >= __m->nrows) return false;
//     }

//     return true;
// }

// I want to return the index of the max or min element.
int TYPED(MatIter_max_index)(TYPED(MatIter) begin, const TYPED(MatIter) end) {

    int index = 0;
    double max = TYPED(MatIter_value)(begin);
    TYPED(MatIter) it = TYPED(MatIter_next)(begin);

    for (size_t i = 1; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it), i++) {
    #ifdef MATRIX_COMPLEX
        if (cabs(TYPED(MatIter_value)(it)) > fabs(max)) {
    #else
        if (TYPED(MatIter_value)(it) > max) {
    #endif
            index = i;
            max = TYPED(MatIter_value)(it);
        }
    }

    return index;
}

// I want to return the index of the max or min element.
int TYPED(MatIter_min_index)(TYPED(MatIter) begin, const TYPED(MatIter) end) {

    int index = 0;
    double min = TYPED(MatIter_value)(begin);
    TYPED(MatIter) it = TYPED(MatIter_next)(begin);

    for (size_t i = 1; !TYPED(MatIter_cmp)(it, end); it = TYPED(MatIter_next)(it), i++) {
    #ifdef MATRIX_COMPLEX
        if (cabs(TYPED(MatIter_value)(it)) < fabs(min)) {
    #else
        if (TYPED(MatIter_value)(it) < min) {
    #endif
            index = i;
            min = TYPED(MatIter_value)(it);
        }
    }

    return index;
}

int TYPED(Matrix_row_min_index)(const TYPED(Matrix) *__m, size_t __i) {
    return TYPED(MatIter_min_index)(TYPED(Matrix_row_begin)(__m, __i), TYPED(Matrix_row_end)(__m, __i));
}

int TYPED(Matrix_row_max_index)(const TYPED(Matrix) *__m, size_t __i) {
    return TYPED(MatIter_max_index)(TYPED(Matrix_row_begin)(__m, __i), TYPED(Matrix_row_end)(__m, __i));
}

int TYPED(Matrix_row_max_index_from_col)(const TYPED(Matrix) *__m, size_t __i, size_t __j) {
    return TYPED(MatIter_max_index)(TYPED(Matrix_row_begin_from_col)(__m, __i, __j), TYPED(Matrix_row_end)(__m, __i));
}

int TYPED(Matrix_row_min_index_from_col)(const TYPED(Matrix) *__m, size_t __i, size_t __j) {
    return TYPED(MatIter_min_index)(TYPED(Matrix_row_begin_from_col)(__m, __i, __j), TYPED(Matrix_row_end)(__m, __i));
}


int TYPED(Matrix_col_min_index)(const TYPED(Matrix) *__m, size_t __i) {
    return TYPED(MatIter_min_index)(TYPED(Matrix_col_begin)(__m, __i), TYPED(Matrix_col_end)(__m, __i));
}

int TYPED(Matrix_col_max_index)(const TYPED(Matrix) *__m, size_t __i) {
    return TYPED(MatIter_max_index)(TYPED(Matrix_col_begin)(__m, __i), TYPED(Matrix_col_end)(__m, __i));
}

int TYPED(Matrix_col_max_index_from_row)(const TYPED(Matrix) *__m, size_t __j, size_t __i) {
    return TYPED(MatIter_max_index)(TYPED(Matrix_col_begin_from_row)(__m, __j, __i), TYPED(Matrix_col_end)(__m, __j));
}

// Find the max value of column j starting from row i
int TYPED(Matrix_col_min_index_from_row)(const TYPED(Matrix) *__m, size_t __j, size_t __i) {
    return TYPED(MatIter_min_index)(TYPED(Matrix_col_begin_from_row)(__m, __j, __i), TYPED(Matrix_col_end)(__m, __j));
}


// I want to return the index of the first occurence of some double