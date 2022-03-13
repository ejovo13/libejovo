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

Matrix *as_row_stochastic(Matrix *__m) {

    // I am not going to apply the absolute value function. Let that be applied in a higher level function.
    // This function will simply verify that the rows add up to one.
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

Matrix *as_col_stochastic(Matrix *__m) {

    double sum = 0;

    // So first thing I need to do is iterate the rows
    for (size_t i = 0; i < __m->ncols; i++) {

        // Get the sum of each row
        MatIter start = Matrix_col_begin(__m, i);
        MatIter end   = Matrix_col_end(__m, i);

        sum = MatIter_sum(start, end);

        // Now go and adjust the row
        MatIter_apply_div_k(start, end, sum);
    }

    return __m;
}

#define MAX_STOCHASTIC_ITERATIONS 1E4
#define STOCHASTIC_EPSILON 1E-10

Matrix *as_doubly_stochastic(Matrix *__m) {

    // I want every row and column to be equal to 1 within a certain margin.

    // I need a robust way to calculate the offset.
    size_t counter = 0;
    Vector *row_ones = Matrix_ones(__m->nrows, 1);
    Vector *col_ones = Matrix_ones(1, __m->ncols);
    Vector *row_sums = NULL;
    Vector *col_sums = NULL;
    MATRIX_TYPE row_err = 10;
    MATRIX_TYPE col_err = 10;
    // Vector *diff = NULL;

    do {

        if (row_err > STOCHASTIC_EPSILON) as_row_stochastic(__m);
        if (col_err > STOCHASTIC_EPSILON) as_col_stochastic(__m);

        row_sums = compute_row_sums(__m);
        col_sums = compute_col_sums(__m);

        row_err = Vector_distance(row_sums, row_ones);
        col_err = Vector_distance(col_sums, col_ones);

        Matrix_reset(&row_sums); // since the space has already been allocated
        Matrix_reset(&col_sums); // I think its better to modify row_sums and col_sums in place...

        counter ++;

    } while (
        // the distance between the col_sums and the row_sums is between a certain threshold.
        counter < MAX_STOCHASTIC_ITERATIONS &&
        (row_err > STOCHASTIC_EPSILON || col_err > STOCHASTIC_EPSILON)
    );

    return __m;
}






// Low level routine to modify a matrix in place and create a matrix that is doubly stochastic
// (whose rows and columns sum to 1)
Matrix *as_doubly_stochastic_DEPRECATED(Matrix *__m) {

    // If the matrix is not square, return NULL and don't modify __m
    if (!Matrix_is_square(__m)) return NULL;

    // I will use an algorithm that first normalizes col 1 so that the sum is one, and
    // then row 1 so that the sum of the elements __m(1, 2:end) sum up to 1 - __m(1, 1)
    // I will then repeat this iteratively, moving along the matrix in diagonal blocks.
    apply(__m, fabs);


    // iterate along the diagonals.
    for (size_t i = 0; i < __m->ncols; i++) {

        // printf("=== Processing i = %d\n", i);
        // For each iteration, there are 4 sums that I need to consider. The sums of above and below of the column,
        // and the row sums to the left and right of the pivot

        // First get the sum of the cols. When i = 0, we have made no normalization and we only want to
        // sum up the elements of the column
        MatIter cit_begin = Matrix_col_begin(__m, i);
        MatIter cit_pivot = Matrix_col_begin_from_row(__m, i, i);
        MatIter cit_end   = Matrix_col_end(__m, i);

        // printf("======= cit_begin: %lf\n", MatIter_value(cit_begin));
        // printf("======= cit_pivot: %lf\n", MatIter_value(cit_pivot));


        MatIter rit_begin = Matrix_row_begin(__m, i);
        MatIter rit_pivot = Matrix_row_begin_from_col(__m, i, i + 1); // Since I've normalized the first col's element, start at the next col
        MatIter rit_end   = Matrix_row_end(__m, i);

        // printf("======= rit_begin: %lf\n", MatIter_value(rit_begin));
        // printf("======= rit_pivot: %lf\n", MatIter_value(rit_pivot));

        double top_sum = MatIter_sum(cit_begin, cit_pivot);
        double bottom_sum = MatIter_sum(cit_pivot, cit_end);

        // printf("====== top_sum: %lf\n", top_sum);
        // printf("====== bottom_sum: %lf\n", bottom_sum);
        // normalize the column elements
        MatIter_apply_mult_k(cit_pivot, cit_end, (1 - top_sum) / bottom_sum);
        // Matrix_print(__m);

        double left_sum = MatIter_sum(rit_begin, rit_pivot);
        double right_sum = MatIter_sum(rit_pivot, rit_end);

        // printf("======= left_sum: %lf\n", left_sum);
        // printf("======= right_sum: %lf\n", right_sum);

        // normalize the row elements
        MatIter_apply_mult_k(rit_pivot, rit_end, (1 - left_sum) / right_sum);

        // printf("====== Resultant matrix:\n");
        // Matrix_print(__m);

        // printf("\n");

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

/**========================================================================
 *!                           Utility functions
 *========================================================================**/
Vector *compute_row_sums(const Matrix *__m) {

    Vector *out = Vector_new(__m->ncols);

    for (size_t i = 0; i < __m->ncols; i++) {
        // sum each of the rows, storing
        Vector_set(out, i, Matrix_row_sum(__m, i));
    }

    return out;
}

Vector *compute_col_sums(const Matrix *__m) {

    Vector *out = asrow(Vector_new(__m->ncols));

    for (size_t i = 0; i < __m->ncols; i++) {
        // sum each of the rows, storing
        Vector_set(out, i, Matrix_col_sum(__m, i));
    }

    return out;
}