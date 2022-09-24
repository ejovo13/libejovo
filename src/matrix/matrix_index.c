// This submodule contains important routines for using a vector of integers as indices.

// General routines for verifying that a vector indeed represents a list of integers would be nice
#include "ejovo_matrix_generic.h"
// #include "ejovo_matrix.h"
// A new typedef of "Index" is a type of Vector whose values are integers

// Use your functional tools to simply cast __m to a floor
Vector *MATRIX_FN(as_index)(const MATRIX_T *__m) {
    return TYPED_FN(apply)(TYPED_FN(map)(__m, floor), fabs); // Ok this is neat but now I think that it actually has 0 utility...
}

// Take a supposed index matrix and scrub it -- making sure that all of the elements fall within
// the true bounds of __m
Vector *MATRIX_FN(scrub_index)(const MATRIX_T *__m, const Index *__ind) {

    // The only bounds we care about are (size - 1) and 0.
    size_t len = MATRIX_FN(size)(__m);

    int n_valid = 0;
    double val = 0;

    // iterate through the index, count how many are valid
    for (MATITER_T it = MATRIX_FN(begin)(__ind); !MATITER_FN(cmp)(it, MATRIX_FN(end)(__ind)); it = MATITER_FN(next)(it)) {
        val = MATITER_FN(value)(it);
        if (val >= 0 && val <= (len - 1)) n_valid++;
    }

    Vector *out = VECTOR_FN(new)(n_valid);


    MATITER_T it = MATRIX_FN(begin)(__ind);
    MATITER_T out_it = MATRIX_FN(begin)(out);
    MATITER_T end = MATRIX_FN(end)(__ind);

    for (it; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it)) {
        val = MATITER_FN(value)(it);
        if (val >= 0 && val <= (len - 1)) {
            MATITER_FN(set)(out_it, floor(val)); // save the integer index
            out_it = MATITER_FN(next)(out_it);
        }
    }

    return out;
}

// Take a supposed index matrix and scrub it -- making sure that all of the elements fall within
// the appropriate columns
Vector *MATRIX_FN(scrub_col_index)(const MATRIX_T *__m, const Index *__ind) {

    // The only bounds we care about are (size - 1) and 0.
    int n_valid = 0;
    double val = 0;

    // First let's check once if the indices are valid:
    // iterate through the index, count how many are valid
    for (MATITER_T it = MATRIX_FN(begin)(__ind); !MATITER_FN(cmp)(it, MATRIX_FN(end)(__ind)); it = MATITER_FN(next)(it)) {
        val = MATITER_FN(value)(it);
        if (val >= 0 && val <= (__m->ncols - 1)) n_valid++;
    }

    Vector *out = VECTOR_FN(new)(n_valid);


    MATITER_T it = MATRIX_FN(begin)(__ind);
    MATITER_T out_it = MATRIX_FN(begin)(out);
    MATITER_T end = MATRIX_FN(end)(__ind);

    for (it; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it)) {
        val = MATITER_FN(value)(it);
        if (val >= 0 && val <= (__m->ncols - 1)) {
            MATITER_FN(set)(out_it, floor(val)); // save the integer index
            out_it = MATITER_FN(next)(out_it);
        }
    }

    return out;
}

Vector *MATRIX_FN(scrub_row_index)(const MATRIX_T *__m, const Index *__ind) {

    // The only bounds we care about are (size - 1) and 0.
    int n_valid = 0;
    double val = 0;

    // First let's check once if the indices are valid:
    // iterate through the index, count how many are valid
    for (MATITER_T it = MATRIX_FN(begin)(__ind); !MATITER_FN(cmp)(it, MATRIX_FN(end)(__ind)); it = MATITER_FN(next)(it)) {
        val = MATITER_FN(value)(it);
        if (val >= 0 && val <= (__m->nrows - 1)) n_valid++;
    }

    Vector *out = VECTOR_FN(new)(n_valid);


    MATITER_T it = MATRIX_FN(begin)(__ind);
    MATITER_T out_it = MATRIX_FN(begin)(out);
    MATITER_T end = MATRIX_FN(end)(__ind);

    for (it; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it)) {
        val = MATITER_FN(value)(it);
        if (val >= 0 && val <= (__m->nrows - 1)) {
            MATITER_FN(set)(out_it, floor(val)); // save the integer index
            out_it = MATITER_FN(next)(out_it);
        }
    }

    return out;
}

// dont even scrub the indices, just extract the data!
Vector *MAT_FN(index)(const MATRIX_T *__m, const Index *__ind) {

    // first allocate a new matrix of size __ind
    Vector *out = MAT_FN(alloc)(MATRIX_FN(size)(__ind), 1);

    // now iterate through the indices
    MATITER_T it = MATRIX_FN(begin)(__ind);
    MATITER_T out_it = MATRIX_FN(begin)(out);
    MATITER_T end = MATRIX_FN(end)(__ind);

    for (it; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it), out_it = MATITER_FN(next)(out_it)) {
        MATITER_FN(set)(out_it, MAT_FN(get)(__m, MATITER_FN(value)(it)));
    }

    return out;
}

Vector *MATRIX_FN(index)(const MATRIX_T *__m, const Index *__ind) {

    // Using the indices described by __ind, return a newly allocated vector whose elements are the
    // ROW-MAJOR INDICES of a matrix.

    // let's first just scrub the indices
    Vector *valid = MATRIX_FN(scrub_index)(__m, __ind);

    Vector *out = MAT_FN(index)(__m, valid);

    MATRIX_FN(free)(valid);

    return out;
}

// Receiving a logical index that is the same shape as __m, return a Vector where
// the mask is true
Vector *MATRIX_FN(logical_index)(const MATRIX_T *__m, const Logical *__log) {

    if (!MATRIX_FN(is_logical)(__log)) return NULL;

    // How should I deal with the different cases? If a matrix is the same shape, size, etc..

    // if the sizes are different, bail
    if (MATRIX_FN(size)(__m) != MATRIX_FN(size)(__log)) return NULL;

    // Else, let's count the number in log
    int count = TYPED_FN(sum)(__log);

    // and allocate a new vector
    Vector *out = MAT_FN(alloc)(count, 1);

    MATITER_T out_it = MATRIX_FN(begin)(out);
    MATITER_T it = MATRIX_FN(begin)(__log);
    MATITER_T m_it = MATRIX_FN(begin)(__m);

    MATITER_T end = MATRIX_FN(end)(__log);

    for (it; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it), m_it = MATITER_FN(next)(m_it)) {
        if (MATITER_FN(value)(it) == TYPED(TRUE)) {
            MATITER_FN(set)(out_it, MATITER_FN(value)(m_it));
            out_it = MATITER_FN(next)(out_it);
        }
    }

    return out;
}

// Return the indices where a predicate is satisfied
Index *MATRIX_FN(where)(const MATRIX_T *__m, pred_fn __fn) {

    // First let's get the logical matrix:
    Logical *log = MATRIX_FN(as_logical)(__m, __fn);

    // And then let's allocate space for our new vector of indices

    Index *ind = MAT_FN(alloc)(TYPED_FN(sum)(log), 1);

    // Now let's iterate through our logical matrix. If the logical matrix is true,
    // add the index counter to ind
    // MATITER_T ind_it = MATRIX_FN(begin)(ind);
    MATITER_T it = MATRIX_FN(begin)(ind);
    // MATITER_T end = MATRIX_FN(end)(log);


    for (size_t i = 0; i < MATRIX_FN(size)(__m); i++) {
        if (MAT_FN(get)(log, i) == TYPED(TRUE)) {
            MATITER_FN(set)(it, i);
            it = MATITER_FN(next)(it);
        }
    }

    MATRIX_FN(free)(log);
    return ind;
}

// // Given a Logical matrix (1.0s and 0.0s), return a column vector whose elements are the indices
// // of the nonzero elements and whose length is the number of nozero elements, or sum(__log).
// Index *Logical_get_index(const Logical *__log) {

//     // Should I validate the index?

//     // Create a vector to store the indices, whose nrows is the number of elements in __log
//     Index *ind = VECTOR_FN(new)(VECTOR_FN(mask_count)(__log));

//     // Now let's iterate through our logical matrix. If the logical matrix is true,
//     // add the index counter to ind
//     // MATITER_T ind_it = MATRIX_FN(begin)(ind);
//     MATITER_T it = MATRIX_FN(begin)(ind);
//     // MATITER_T end = MATRIX_FN(end)(log);


//     for (size_t i = 0; i < MATRIX_FN(size)(__log); i++) {
//         if (MAT_FN(get)(__log, i) == TRUE) {
//             MATITER_FN(set)(it, i);
//             it = MATITER_FN(next)(it);
//         }
//     }

//     return ind;
// }

// Return the indices where a predicate is satisfied
Index *MATRIX_FN(where_lt)(const MATRIX_T *__m, double __k) {

    // First let's get the logical matrix:
    Logical *logic = MATRIX_FN(lt)(__m, __k);

    Index *ind = Logical_get_index(logic);

    MATRIX_FN(free)(logic);

    return ind;
}

// Return the indices where a predicate is satisfied
Index *MATRIX_FN(where_lteq)(const MATRIX_T *__m, double __k) {

    // First let's get the logical matrix:
    Logical *logic = MATRIX_FN(lteq)(__m, __k);

    Index *ind = Logical_get_index(logic);

    MATRIX_FN(free)(logic);

    return ind;
}

// Return the indices where a predicate is satisfied
Index *MATRIX_FN(where_gt)(const MATRIX_T *__m, double __k) {

    // First let's get the logical matrix:
    Logical *logic = MATRIX_FN(gt)(__m, __k);

    Index *ind = Logical_get_index(logic);

    MATRIX_FN(free)(logic);

    return ind;
}

// Return the indices where a predicate is satisfied
Index *MATRIX_FN(where_gteq)(const MATRIX_T *__m, double __k) {

    // First let's get the logical matrix:
    Logical *logic = MATRIX_FN(gteq)(__m, __k);

    Index *ind = Logical_get_index(logic);

    MATRIX_FN(free)(logic);

    return ind;
}

MATRIX_T *MAT_FN(setind)(MATRIX_T *__m, const MATRIX_T *__ind, const MATRIX_T *__val) {

    // Loop through the indices

    MATITER_T it = MATRIX_FN(begin)(__ind);
    MATITER_T val_it = MATRIX_FN(begin)(__val);

    MATITER_T end = MATRIX_FN(end)(__ind);
    MATITER_T val_end = MATRIX_FN(end)(__val);

    for (it; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it), val_it = MATITER_FN(next)(val_it)) {
        if (MATITER_FN(cmp)(val_it, val_end)) val_it = MATRIX_FN(begin)(__val); // loop back the value if we have passed the end
        __m->data[(int) MATITER_FN(value)(it)] = MATITER_FN(value)(val_it);
    }

    return __m;
}

MATRIX_T *MATRIX_FN(set_index)(const MATRIX_T *__m, const Index *__ind, const MATRIX_T *__val) {

    // Duplicate __m
    MATRIX_T *m = MATRIX_FN(clone)(__m);
    return MAT_FN(setind)(m, __ind, __val);
}

MATRIX_T *MATRIX_FN(extract_rows)(const MATRIX_T *__m, Index *__ind) {

    // First let's figure out the size of the resulting matrix.
    // Necessarily, the output will have __m->ncols cols whereas the number of
    // rows will depend on if the passed indices are legit or not

    int nrows = 0;
    Index *ind = NULL;

    bool ind_newly_allocated = false;

    if (are_row_indices_valid(__m, __ind)) {
        nrows = MATRIX_FN(size)(__ind);
        ind = __ind;
    } else {

        // we need to allocate a new indices vector
        ind_newly_allocated = true;
        ind = MATRIX_FN(scrub_row_index)(__m, __ind);
        nrows = MATRIX_FN(size)(ind);
    }

    MATRIX_T *out = MATRIX_FN(new)(nrows, __m->ncols);

    // Now let's iterate through ind, copying the contents of the columns over to out.
    // This operation would be more efficient if we could just copy a certain block of memory
    // to another, although since the matrix is either row or column major order, we are forced
    // to use iteration in at least on of the cases. To keep this function more adaptive,
    // we opt to use the iterative route.

    MATITER_T it = VECTOR_FN(begin)(ind);
    const MATITER_T end = VECTOR_FN(end)(ind);

    for (int i = 0; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it), i++) {
        MATRIX_FN(set_row_iter)(out, i, MATRIX_FN(row_begin)(__m, MATITER_FN(value)(it))); // clean way to set all of the columns
    }

    if (ind_newly_allocated) MATRIX_FN(free)(ind);

    return out;
}

MATRIX_T *MATRIX_FN(extract_cols)(const MATRIX_T *__m, Index *__ind) {

    // First let's figure out the size of the resulting matrix.
    // Necessarily, the output will have __m->nrows rows whereas the number of
    // columns will depend on if the passed indices are legit or not

    int ncols = 0;
    Index *ind = NULL;

    bool ind_newly_allocated = false;

    if (are_col_indices_valid(__m, __ind)) {
        ncols = MATRIX_FN(size)(__ind);
        ind = __ind;
    } else {

        // we need to allocate a new indices vector
        ind_newly_allocated = true;
        ind = MATRIX_FN(scrub_col_index)(__m, __ind);
        ncols = MATRIX_FN(size)(ind);
    }

    MATRIX_T *out = MATRIX_FN(new)(__m->nrows, ncols);

    // Now let's iterate through ind, copying the contents of the columns over to out.
    // This operation would be more efficient if we could just copy a certain block of memory
    // to another, although since the matrix is either row or column major order, we are forced
    // to use iteration in at least on of the cases. To keep this function more adaptive,
    // we opt to use the iterative route.

    MATITER_T it = VECTOR_FN(begin)(ind);
    const MATITER_T end = VECTOR_FN(end)(ind);

    for (int i = 0; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it), i++) {
        MATRIX_FN(set_col_iter)(out, i, MATRIX_FN(col_begin)(__m, MATITER_FN(value)(it))); // clean way to set all of the columns
    }

    if (ind_newly_allocated) MATRIX_FN(free)(ind);

    return out;
}


/**================================================================================================
 *!              Utility functions for dealing with indices -- probably shouldnt be exported
 *================================================================================================**/

// Return true if all of the elements in __ind are valid column indices of __m
// static bool are_col_indices_valid(const MATRIX_T *__m, const Index *__ind) {

//     // loop through the __index vector
//     MATITER_T it = MATRIX_FN(begin)(__ind);
//     const MATITER_T end = MATRIX_FN(begin)(__ind);

//     for(it; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it)) {

//         double val = MATITER_FN(value)(it);
//         // make sure the elements of __ind are positive, integers, and within __m's column range
//         if (val < 0 || !is_int(val) || val >= __m->ncols) return false;
//     }

//     return true;
// }

// Return true if all of the elements in __ind are valid column indices of __m
// static bool are_row_indices_valid(const MATRIX_T *__m, const Index *__ind) {

//     // loop through the __index vector
//     MATITER_T it = MATRIX_FN(begin)(__ind);
//     const MATITER_T end = MATRIX_FN(begin)(__ind);

//     for(it; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it)) {

//         double val = MATITER_FN(value)(it);
//         // make sure the elements of __ind are positive, integers, and within __m's column range
//         if (val < 0 || !is_int(val) || val >= __m->nrows) return false;
//     }

//     return true;
// }

// I want to return the index of the max or min element.
int MATITER_FN(max_index)(MATITER_T begin, const MATITER_T end) {

    int index = 0;
    double max = MATITER_FN(value)(begin);
    MATITER_T it = MATITER_FN(next)(begin);

    for (size_t i = 1; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it), i++) {
        if (MATITER_FN(value)(it) > max) {
            index = i;
            max = MATITER_FN(value)(it);
        }
    }

    return index;
}

// I want to return the index of the max or min element.
int MATITER_FN(min_index)(MATITER_T begin, const MATITER_T end) {

    int index = 0;
    double min = MATITER_FN(value)(begin);
    MATITER_T it = MATITER_FN(next)(begin);

    for (size_t i = 1; !MATITER_FN(cmp)(it, end); it = MATITER_FN(next)(it), i++) {
        if (MATITER_FN(value)(it) < min) {
            index = i;
            min = MATITER_FN(value)(it);
        }
    }

    return index;
}

int MATRIX_FN(row_min_index)(const MATRIX_T *__m, size_t __i) {
    return MATITER_FN(min_index)(MATRIX_FN(row_begin)(__m, __i), MATRIX_FN(row_end)(__m, __i));
}

int MATRIX_FN(row_max_index)(const MATRIX_T *__m, size_t __i) {
    return MATITER_FN(max_index)(MATRIX_FN(row_begin)(__m, __i), MATRIX_FN(row_end)(__m, __i));
}

int MATRIX_FN(row_max_index_from_col)(const MATRIX_T *__m, size_t __i, size_t __j) {
    return MATITER_FN(max_index)(MATRIX_FN(row_begin_from_col)(__m, __i, __j), MATRIX_FN(row_end)(__m, __i));
}

int MATRIX_FN(row_min_index_from_col)(const MATRIX_T *__m, size_t __i, size_t __j) {
    return MATITER_FN(min_index)(MATRIX_FN(row_begin_from_col)(__m, __i, __j), MATRIX_FN(row_end)(__m, __i));
}


int MATRIX_FN(col_min_index)(const MATRIX_T *__m, size_t __i) {
    return MATITER_FN(min_index)(MATRIX_FN(col_begin)(__m, __i), MATRIX_FN(col_end)(__m, __i));
}

int MATRIX_FN(col_max_index)(const MATRIX_T *__m, size_t __i) {
    return MATITER_FN(max_index)(MATRIX_FN(col_begin)(__m, __i), MATRIX_FN(col_end)(__m, __i));
}

int MATRIX_FN(col_max_index_from_row)(const MATRIX_T *__m, size_t __j, size_t __i) {
    return MATITER_FN(max_index)(MATRIX_FN(col_begin_from_row)(__m, __j, __i), MATRIX_FN(col_end)(__m, __j));
}

// Find the max value of column j starting from row i
int MATRIX_FN(col_min_index_from_row)(const MATRIX_T *__m, size_t __j, size_t __i) {
    return MATITER_FN(min_index)(MATRIX_FN(col_begin_from_row)(__m, __j, __i), MATRIX_FN(col_end)(__m, __j));
}


// I want to return the index of the first occurence of some double