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

// Low level routine that will modify a matrix in place
Matrix *as_stochastic(Matrix *__m) {

    apply(__m, fabs);

    // No I want to normalize the rows based on their sums!!
    double sum = 0;

    // So first thing I need to do is iterate the rows
    for (size_t i = 0; i < __m->nrows; i++) {

        // Get the sum of each row
        MatIter start = Matrix_row_begin(__m, i);
        MatIter end   = Matrix_row_end(__m, i);

        sum = MatIter_sum(start, end);

        // Now go and adjust the row
        MatIter_apply_div_k(start, end, sum);
    }

    return __m;
}

// This function should TECHNICALLY verify the fact that the matrix is square.
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

// Create a new Stochastic matrix whose elements come from a uniform distribution
Matrix *Stochastic_runif(size_t __n, double __a, double __b) {

    // first thing I need to do is create a new uniformly generated matrix, althought the
    // actual scale shouldnt really matter...
    Matrix *stoch = Matrix_runif(__n, __n, __a, __b);

    return as_stochastic(stoch);
}

Matrix *Stochastic_rnorm(size_t __n, double __mean, double __std) {

    Matrix *stoch = Matrix_rnorm(__n, __n, __mean, __std);

    return as_stochastic(stoch);
}

Matrix *Stochastic_rexp(size_t __n, double __rate) {

    Matrix *stoch = Matrix_rexp(__n, __n, __rate);

    return as_stochastic(stoch);
}

// Return a DSICRETE probability vector
Vector *Vector_prob_unif(size_t __n) {
    return Matrix_value(__n, 1, 1.0 / __n);
}