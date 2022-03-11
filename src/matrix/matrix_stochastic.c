#include "ejovo_matrix.h"

// I want a function that will return a stochastic matrix.

// I also need a Matrix interface to the runif, rnorm functions


Matrix *Matrix_runif(size_t __m, size_t __n, double __a, double __b) {

    Matrix *m = Vector_runif(__m * __n, __a, __b);

    m->nrows = __m;
    m->ncols = __n;

    return m;
}

Matrix *Matrix_rnorm(size_t __m, size_t __n, double __mean, double __std) {

    Matrix *m = Vector_rnorm(__m * __n, __mean, __std);

    m->nrows = __m;
    m->ncols = __n;

    return m;
}


Matrix *Matrix_rexp(size_t __m, size_t __n, double __rate) {

    Matrix *m = Vector_rexp(__m * __n, __rate);

    m->nrows = __m;
    m->ncols = __n;

    return m;
}

// This function should TECHNICALLY verify the fact
Matrix *Matrix_as_stochastic(const Matrix *__m) {

    // first thing I should do is apply the absolute value function to the matrix

    Matrix *m_pos = map(__m, abs);

    // No I want to normalize the rows based on their sums!!
    double sum = 0;

    // So first thing I need to do is iterate the rows
    for (size_t i = 0; i < __m->nrows; i++) {

        // Get the sum of each row
        MatIter start = Matrix_row_begin(m_pos, i);
        MatIter end   = Matrix_row_end(m_pos, i);

        sum = MatIter_sum(start, end);

        // Now go and adjust the row
        MatIter_apply_div_k(start, end, sum);
    }

    return m_pos;
}