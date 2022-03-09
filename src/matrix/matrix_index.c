// This submodule contains important routines for using a vector of integers as indices.

// General routines for verifying that a vector indeed represents a list of integers would be nice
#include "matrix_index.h"
// A new typedef of "Index" is a type of Vector whose values are integers

static bool is_int(double x) {
    return x == floor(x);
}


// Use your functional tools to simply cast __m to a floor
Vector *Matrix_as_index(const Matrix *__m) {
    return map(__m, floor); // Ok this is neat but now I think that it actually has 0 utility...
}

// Take a supposed index matrix and scrub it -- making sure that all of the elements fall within
// the true bounds of __m
Vector *Matrix_scrub_index(const Matrix *__m, const Index *__ind) {

    // The only bounds we care about are (size - 1) and 0.
    size_t len = Matrix_size(__m);

    int n_valid = 0;
    double val = 0;

    // iterate through the index, count how many are valid
    for (MatIter it = Matrix_begin(__ind); !MatIter_cmp(it, Matrix_end(__ind)); it = MatIter_next(it)) {
        val = MatIter_value(it);
        if (val >= 0 && val <= (len - 1)) n_valid++;
    }

    Vector *out = Vector_new(n_valid);


    MatIter it = Matrix_begin(__ind);
    MatIter out_it = Matrix_begin(out);
    MatIter end = Matrix_end(__ind);

    for (it; !MatIter_cmp(it, end); it = MatIter_next(it)) {
        val = MatIter_value(it);
        if (val >= 0 && val <= (len - 1)) {
            MatIter_set(out_it, floor(val)); // save the integer index
            out_it = MatIter_next(out_it);
        }
    }

    return out;
}

// dont even scrub the indices, just extract the data!
Vector *matindex(const Matrix *__m, const Index *__ind) {

    // first allocate a new matrix of size __ind
    Vector *out = matalloc(Matrix_size(__ind), 1);

    // now iterate through the indices
    MatIter it = Matrix_begin(__ind);
    MatIter out_it = Matrix_begin(out);
    MatIter end = Matrix_end(__ind);

    for (it; !MatIter_cmp(it, end); it = MatIter_next(it), out_it = MatIter_next(out_it)) {
        MatIter_set(out_it, matget(__m, MatIter_value(it)));
    }

    return out;
}

Vector *Matrix_index(const Matrix *__m, const Index *__ind) {

    // Using the indices described by __ind, return a newly allocated vector whose elements are the
    // ROW-MAJOR INDICES of a matrix.

    // let's first just scrub the indices
    Vector *valid = Matrix_scrub_index(__m, __ind);

    Vector *out = matindex(__m, valid);

    Matrix_free(valid);

    return out;
}

// Receiving a logical index that is the same shape as __m, return a Vector where
// the mask is true
Vector *Matrix_logical_index(const Matrix *__m, const Logical *__log) {

    if (!Matrix_is_logical(__log)) return NULL;

    // How should I deal with the different cases? If a matrix is the same shape, size, etc..

    // if the sizes are different, bail
    if (Matrix_size(__m) != Matrix_size(__log)) return NULL;

    // Else, let's count the number in log
    int count = sum(__log);

    // and allocate a new vector
    Vector *out = matalloc(Matrix_size(__m), 1);

    MatIter out_it = Matrix_begin(out);
    MatIter it = Matrix_begin(__log);
    MatIter m_it = Matrix_begin(__m);

    MatIter end = Matrix_end(__log);

    for (it; !MatIter_cmp(it, end); it = MatIter_next(it), m_it = MatIter_next(m_it)) {
        if (MatIter_value(it) == TRUE) {
            MatIter_set(out_it, MatIter_value(m_it));
            out_it = MatIter_next(out_it);
        }
    }

    return out;
}

// Return the indices where a predicate is satisfied
Index *Matrix_where(const Matrix *__m, pred_fn __fn) {

    // First let's get the logical matrix:
    Logical *log = Matrix_as_logical(__m, __fn);

    // And then let's allocate space for our new vector of indices

    Index *ind = matalloc(sum(log), 1);

    // Now let's iterate through our logical matrix. If the logical matrix is true,
    // add the index counter to ind
    // MatIter ind_it = Matrix_begin(ind);
    MatIter it = Matrix_begin(ind);
    // MatIter end = Matrix_end(log);


    for (size_t i = 0; i < Matrix_size(__m); i++) {
        if (matget(log, i) == TRUE) {
            MatIter_set(it, i);
            it = MatIter_next(it);
        }
    }

    Matrix_free(log);
    return ind;
}

// Given a Logical matrix (1.0s and 0.0s), return a column vector whose elements are the indices
// of the nonzero elements and whose length is the number of nozero elements, or sum(__log).
Index *Logical_index(const Logical *__log) {

    // Should I validate the index?

    // Create a vector to store the indices, whose nrows is the number of elements in __log
    Index *ind = Vector_new(Vector_mask_count(__log));

    // Now let's iterate through our logical matrix. If the logical matrix is true,
    // add the index counter to ind
    // MatIter ind_it = Matrix_begin(ind);
    MatIter it = Matrix_begin(ind);
    // MatIter end = Matrix_end(log);


    for (size_t i = 0; i < Matrix_size(__log); i++) {
        if (matget(log, i) == TRUE) {
            MatIter_set(it, i);
            it = MatIter_next(it);
        }
    }

    return ind;
}

// Return the indices where a predicate is satisfied
Index *Matrix_where_lt(const Matrix *__m, double __k) {

    // First let's get the logical matrix:
    Logical *logic = Matrix_lt(__m, __k);

    Index *ind = Logical_index(logic);

    Matrix_free(logic);

    return ind;
}

// Return the indices where a predicate is satisfied
Index *Matrix_where_lteq(const Matrix *__m, double __k) {

    // First let's get the logical matrix:
    Logical *logic = Matrix_lteq(__m, __k);

    Index *ind = Logical_index(logic);

    Matrix_free(logic);

    return ind;
}

// Return the indices where a predicate is satisfied
Index *Matrix_where_gt(const Matrix *__m, double __k) {

    // First let's get the logical matrix:
    Logical *logic = Matrix_gt(__m, __k);

    Index *ind = Logical_index(logic);

    Matrix_free(logic);

    return ind;
}

// Return the indices where a predicate is satisfied
Index *Matrix_where_gteq(const Matrix *__m, double __k) {

    // First let's get the logical matrix:
    Logical *logic = Matrix_gteq(__m, __k);

    Index *ind = Logical_index(logic);

    Matrix_free(logic);

    return ind;
}
