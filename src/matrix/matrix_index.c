// This submodule contains important routines for using a vector of integers as indices.

// General routines for verifying that a vector indeed represents a list of integers would be nice
#include "ejovo_matrix.h"
// A new typedef of "Index" is a type of Vector whose values are integers

static bool is_int(double x) {
    return x == floor(x);
}


// Use your functional tools to simply cast __m to a floor
Vector *Matrix_as_index(const Matrix *__m) {
    return apply(map(__m, floor), fabs); // Ok this is neat but now I think that it actually has 0 utility...
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

// Take a supposed index matrix and scrub it -- making sure that all of the elements fall within
// the appropriate columns
Vector *Matrix_scrub_col_index(const Matrix *__m, const Index *__ind) {

    // The only bounds we care about are (size - 1) and 0.
    int n_valid = 0;
    double val = 0;

    // First let's check once if the indices are valid:
    // iterate through the index, count how many are valid
    for (MatIter it = Matrix_begin(__ind); !MatIter_cmp(it, Matrix_end(__ind)); it = MatIter_next(it)) {
        val = MatIter_value(it);
        if (val >= 0 && val <= (__m->ncols - 1)) n_valid++;
    }

    Vector *out = Vector_new(n_valid);


    MatIter it = Matrix_begin(__ind);
    MatIter out_it = Matrix_begin(out);
    MatIter end = Matrix_end(__ind);

    for (it; !MatIter_cmp(it, end); it = MatIter_next(it)) {
        val = MatIter_value(it);
        if (val >= 0 && val <= (__m->ncols - 1)) {
            MatIter_set(out_it, floor(val)); // save the integer index
            out_it = MatIter_next(out_it);
        }
    }

    return out;
}

Vector *Matrix_scrub_row_index(const Matrix *__m, const Index *__ind) {

    // The only bounds we care about are (size - 1) and 0.
    int n_valid = 0;
    double val = 0;

    // First let's check once if the indices are valid:
    // iterate through the index, count how many are valid
    for (MatIter it = Matrix_begin(__ind); !MatIter_cmp(it, Matrix_end(__ind)); it = MatIter_next(it)) {
        val = MatIter_value(it);
        if (val >= 0 && val <= (__m->nrows - 1)) n_valid++;
    }

    Vector *out = Vector_new(n_valid);


    MatIter it = Matrix_begin(__ind);
    MatIter out_it = Matrix_begin(out);
    MatIter end = Matrix_end(__ind);

    for (it; !MatIter_cmp(it, end); it = MatIter_next(it)) {
        val = MatIter_value(it);
        if (val >= 0 && val <= (__m->nrows - 1)) {
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
    Vector *out = matalloc(count, 1);

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
Index *Logical_get_index(const Logical *__log) {

    // Should I validate the index?

    // Create a vector to store the indices, whose nrows is the number of elements in __log
    Index *ind = Vector_new(Vector_mask_count(__log));

    // Now let's iterate through our logical matrix. If the logical matrix is true,
    // add the index counter to ind
    // MatIter ind_it = Matrix_begin(ind);
    MatIter it = Matrix_begin(ind);
    // MatIter end = Matrix_end(log);


    for (size_t i = 0; i < Matrix_size(__log); i++) {
        if (matget(__log, i) == TRUE) {
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

    Index *ind = Logical_get_index(logic);

    Matrix_free(logic);

    return ind;
}

// Return the indices where a predicate is satisfied
Index *Matrix_where_lteq(const Matrix *__m, double __k) {

    // First let's get the logical matrix:
    Logical *logic = Matrix_lteq(__m, __k);

    Index *ind = Logical_get_index(logic);

    Matrix_free(logic);

    return ind;
}

// Return the indices where a predicate is satisfied
Index *Matrix_where_gt(const Matrix *__m, double __k) {

    // First let's get the logical matrix:
    Logical *logic = Matrix_gt(__m, __k);

    Index *ind = Logical_get_index(logic);

    Matrix_free(logic);

    return ind;
}

// Return the indices where a predicate is satisfied
Index *Matrix_where_gteq(const Matrix *__m, double __k) {

    // First let's get the logical matrix:
    Logical *logic = Matrix_gteq(__m, __k);

    Index *ind = Logical_get_index(logic);

    Matrix_free(logic);

    return ind;
}

Matrix *matsetind(Matrix *__m, const Matrix *__ind, const Matrix *__val) {

    // Loop through the indices

    MatIter it = Matrix_begin(__ind);
    MatIter val_it = Matrix_begin(__val);

    MatIter end = Matrix_end(__ind);
    MatIter val_end = Matrix_end(__val);

    for (it; !MatIter_cmp(it, end); it = MatIter_next(it), val_it = MatIter_next(val_it)) {
        if (MatIter_cmp(val_it, val_end)) val_it = Matrix_begin(__val); // loop back the value if we have passed the end
        __m->data[(int) MatIter_value(it)] = MatIter_value(val_it);
    }

    return __m;
}

Matrix *Matrix_set_index(const Matrix *__m, const Index *__ind, const Matrix *__val) {

    // Duplicate __m
    Matrix *m = Matrix_clone(__m);
    return matsetind(m, __ind, __val);
}

Matrix *Matrix_extract_rows(const Matrix *__m, Index *__ind) {

    // First let's figure out the size of the resulting matrix.
    // Necessarily, the output will have __m->ncols cols whereas the number of
    // rows will depend on if the passed indices are legit or not

    int nrows = 0;
    Index *ind = NULL;

    bool ind_newly_allocated = false;

    if (are_row_indices_valid(__m, __ind)) {
        nrows = Matrix_size(__ind);
        ind = __ind;
    } else {

        // we need to allocate a new indices vector
        ind_newly_allocated = true;
        ind = Matrix_scrub_row_index(__m, __ind);
        nrows = Matrix_size(ind);
    }

    Matrix *out = Matrix_new(nrows, __m->ncols);

    // Now let's iterate through ind, copying the contents of the columns over to out.
    // This operation would be more efficient if we could just copy a certain block of memory
    // to another, although since the matrix is either row or column major order, we are forced
    // to use iteration in at least on of the cases. To keep this function more adaptive,
    // we opt to use the iterative route.

    MatIter it = Vector_begin(ind);
    const MatIter end = Vector_end(ind);

    for (int i = 0; !MatIter_cmp(it, end); it = MatIter_next(it), i++) {
        Matrix_set_row_iter(out, i, Matrix_row_begin(__m, MatIter_value(it))); // clean way to set all of the columns
    }

    if (ind_newly_allocated) Matrix_free(ind);

    return out;
}

Matrix *Matrix_extract_cols(const Matrix *__m, Index *__ind) {

    // First let's figure out the size of the resulting matrix.
    // Necessarily, the output will have __m->nrows rows whereas the number of
    // columns will depend on if the passed indices are legit or not

    int ncols = 0;
    Index *ind = NULL;

    bool ind_newly_allocated = false;

    if (are_col_indices_valid(__m, __ind)) {
        ncols = Matrix_size(__ind);
        ind = __ind;
    } else {

        // we need to allocate a new indices vector
        ind_newly_allocated = true;
        ind = Matrix_scrub_col_index(__m, __ind);
        ncols = Matrix_size(ind);
    }

    Matrix *out = Matrix_new(__m->nrows, ncols);

    // Now let's iterate through ind, copying the contents of the columns over to out.
    // This operation would be more efficient if we could just copy a certain block of memory
    // to another, although since the matrix is either row or column major order, we are forced
    // to use iteration in at least on of the cases. To keep this function more adaptive,
    // we opt to use the iterative route.

    MatIter it = Vector_begin(ind);
    const MatIter end = Vector_end(ind);

    for (int i = 0; !MatIter_cmp(it, end); it = MatIter_next(it), i++) {
        Matrix_set_col_iter(out, i, Matrix_col_begin(__m, MatIter_value(it))); // clean way to set all of the columns
    }

    if (ind_newly_allocated) Matrix_free(ind);

    return out;
}


/**================================================================================================
 *!              Utility functions for dealing with indices -- probably shouldnt be exported
 *================================================================================================**/

// Return true if all of the elements in __ind are valid column indices of __m
static bool are_col_indices_valid(const Matrix *__m, const Index *__ind) {

    // loop through the __index vector
    MatIter it = Matrix_begin(__ind);
    const MatIter end = Matrix_begin(__ind);

    for(it; !MatIter_cmp(it, end); it = MatIter_next(it)) {

        double val = MatIter_value(it);
        // make sure the elements of __ind are positive, integers, and within __m's column range
        if (val < 0 || !is_int(val) || val >= __m->ncols) return false;
    }

    return true;
}

// Return true if all of the elements in __ind are valid column indices of __m
static bool are_row_indices_valid(const Matrix *__m, const Index *__ind) {

    // loop through the __index vector
    MatIter it = Matrix_begin(__ind);
    const MatIter end = Matrix_begin(__ind);

    for(it; !MatIter_cmp(it, end); it = MatIter_next(it)) {

        double val = MatIter_value(it);
        // make sure the elements of __ind are positive, integers, and within __m's column range
        if (val < 0 || !is_int(val) || val >= __m->nrows) return false;
    }

    return true;
}

// I want to return the index of the max or min element.
int MatIter_max_index(MatIter begin, const MatIter end) {

    int index = 0;
    double max = MatIter_value(begin);
    MatIter it = MatIter_next(begin);

    for (size_t i = 1; !MatIter_cmp(it, end); it = MatIter_next(it), i++) {
        if (MatIter_value(it) > max) {
            index = i;
            max = MatIter_value(it);
        }
    }

    return index;
}

// I want to return the index of the max or min element.
int MatIter_min_index(MatIter begin, const MatIter end) {

    int index = 0;
    double min = MatIter_value(begin);
    MatIter it = MatIter_next(begin);

    for (size_t i = 1; !MatIter_cmp(it, end); it = MatIter_next(it), i++) {
        if (MatIter_value(it) < min) {
            index = i;
            min = MatIter_value(it);
        }
    }

    return index;
}

int Matrix_row_min_index(const Matrix *__m, size_t __i) {
    return MatIter_min_index(Matrix_row_begin(__m, __i), Matrix_row_end(__m, __i));
}

int Matrix_row_max_index(const Matrix *__m, size_t __i) {
    return MatIter_max_index(Matrix_row_begin(__m, __i), Matrix_row_end(__m, __i));
}

int Matrix_row_max_index_from_col(const Matrix *__m, size_t __i, size_t __j) {
    return MatIter_max_index(Matrix_row_begin_from_col(__m, __i, __j), Matrix_row_end(__m, __i));
}

int Matrix_row_min_index_from_col(const Matrix *__m, size_t __i, size_t __j) {
    return MatIter_min_index(Matrix_row_begin_from_col(__m, __i, __j), Matrix_row_end(__m, __i));
}


int Matrix_col_min_index(const Matrix *__m, size_t __i) {
    return MatIter_min_index(Matrix_col_begin(__m, __i), Matrix_col_end(__m, __i));
}

int Matrix_col_max_index(const Matrix *__m, size_t __i) {
    return MatIter_max_index(Matrix_col_begin(__m, __i), Matrix_col_end(__m, __i));
}

int Matrix_col_max_index_from_row(const Matrix *__m, size_t __j, size_t __i) {
    return MatIter_max_index(Matrix_col_begin_from_row(__m, __j, __i), Matrix_col_end(__m, __j));
}

// Find the max value of column j starting from row i
int Matrix_col_min_index_from_row(const Matrix *__m, size_t __j, size_t __i) {
    return MatIter_min_index(Matrix_col_begin_from_row(__m, __j, __i), Matrix_col_end(__m, __j));
}


// I want to return the index of the first occurence of some double