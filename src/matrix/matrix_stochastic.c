// #include "ejovo_matrix_generic.h"
#include "ejovo_matrix.h"

// I want a function that will return a stochastic matrix.

// I also need a TYPED(Matrix) interface to the runif, rnorm functions


TYPED(Matrix) *TYPED(Matrix_runif)(size_t __m, size_t __n, MATRIX_TYPE __a, MATRIX_TYPE __b) {

    TYPED(Matrix) *m = TYPED(runif)(__m * __n, __a, __b);

    m->nrows = __m;
    m->ncols = __n;

    return m;
}

TYPED(Matrix) *TYPED(Matrix_rnorm)(size_t __m, size_t __n, MATRIX_TYPE __mean, MATRIX_TYPE __std) {

    TYPED(Matrix) *m = TYPED(rnorm)(__m * __n, __mean, __std);

    m->nrows = __m;
    m->ncols = __n;

    return m;
}


TYPED(Matrix) *TYPED(Matrix_rexp)(size_t __m, size_t __n, double __rate) {

    TYPED(Matrix) *m = TYPED(Vector_rexp)(__m * __n, __rate);

    m->nrows = __m;
    m->ncols = __n;

    return m;
}

// Low level routine that will modify a matrix in place
TYPED(Matrix) *TYPED(as_stochastic)(TYPED(Matrix) *__m) {

    TYPED(apply)(__m, TYPED(ejovo_fabs));

    // No I want to normalize the rows based on their sums!!
    double sum = 0;

    // So first thing I need to do is iterate the rows
    for (size_t i = 0; i < __m->nrows; i++) {

        // Get the sum of each row
        TYPED(MatIter) start = TYPED(Matrix_row_begin)(__m, i);
        TYPED(MatIter) end   = TYPED(Matrix_row_end)(__m, i);

        sum = TYPED(MatIter_sum)(start, end);

        // Now go and adjust the row
        TYPED(MatIter_apply_div_k)(start, end, sum);
    }

    return __m;
}

TYPED(Matrix) *TYPED(as_row_stochastic)(TYPED(Matrix) *__m) {

    // I am not going to apply the absolute value function. Let that be applied in a higher level function.
    // This function will simply verify that the rows add up to one.
    double sum = 0;

    // So first thing I need to do is iterate the rows
    for (size_t i = 0; i < __m->nrows; i++) {

        // Get the sum of each row
        TYPED(MatIter) start = TYPED(Matrix_row_begin)(__m, i);
        TYPED(MatIter) end   = TYPED(Matrix_row_end)(__m, i);

        sum = TYPED(MatIter_sum)(start, end);

        // Now go and adjust the row
        TYPED(MatIter_apply_div_k)(start, end, sum);
    }

    return __m;

}

TYPED(Matrix) *TYPED(as_col_stochastic)(TYPED(Matrix) *__m) {

    double sum = 0;

    // So first thing I need to do is iterate the rows
    for (size_t i = 0; i < __m->ncols; i++) {

        // Get the sum of each row
        TYPED(MatIter) start = TYPED(Matrix_col_begin)(__m, i);
        TYPED(MatIter) end   = TYPED(Matrix_col_end)(__m, i);

        sum = TYPED(MatIter_sum)(start, end);

        // Now go and adjust the row
        TYPED(MatIter_apply_div_k)(start, end, sum);
    }

    return __m;
}

#define MAX_STOCHASTIC_ITERATIONS 1E4
#define STOCHASTIC_EPSILON 1E-10

TYPED(Matrix) *TYPED(as_doubly_stochastic)(TYPED(Matrix) *__m) {

    // I want every row and column to be equal to 1 within a certain margin.

    // I need a robust way to calculate the offset.
    size_t counter = 0;
    TYPED(Vector)*row_ones = TYPED(Matrix_ones)(__m->nrows, 1);
    TYPED(Vector)*col_ones = TYPED(Matrix_ones)(1, __m->ncols);
    TYPED(Vector)*row_sums = NULL;
    TYPED(Vector)*col_sums = NULL;
    MATRIX_TYPE row_err = 10;
    MATRIX_TYPE col_err = 10;
    // TYPED(Vector)*diff = NULL;

    do {

    #ifdef MATRIX_COMPLEX
        if (cabs(row_err) > STOCHASTIC_EPSILON) TYPED(as_row_stochastic)(__m);
        if (cabs(col_err) > STOCHASTIC_EPSILON) TYPED(as_col_stochastic)(__m);
    #else
        if (row_err > STOCHASTIC_EPSILON) TYPED(as_row_stochastic)(__m);
        if (col_err > STOCHASTIC_EPSILON) TYPED(as_col_stochastic)(__m);
    #endif


        row_sums = TYPED(compute_row_sums)(__m);
        col_sums = TYPED(compute_col_sums)(__m);

        row_err = TYPED(Vector_distance)(row_sums, row_ones);
        col_err = TYPED(Vector_distance)(col_sums, col_ones);

        TYPED(Matrix_reset)(&row_sums); // since the space has already been allocated
        TYPED(Matrix_reset)(&col_sums); // I think its better to modify row_sums and col_sums in place...

        counter ++;

    } while (
        // the distance between the col_sums and the row_sums is between a certain threshold.
        counter < MAX_STOCHASTIC_ITERATIONS &&
    #ifdef MATRIX_COMPLEX
        (cabs(row_err) > STOCHASTIC_EPSILON || cabs(col_err) > STOCHASTIC_EPSILON)
    #else
        (row_err > STOCHASTIC_EPSILON || col_err > STOCHASTIC_EPSILON)
    #endif
    );

    // printf("Exiting 'as_doubly_stochastic' with row_err: %lf, col_err: %lf, niter: %d\n", row_err, col_err, counter);
    printf("Exiting 'as_doubly_stochastic' with row_err: ");
    TYPED(print_el)(row_err);
    printf(", col_err: ");
    TYPED(print_el)(col_err);
    printf(", niter: %lu\n", counter);

    return __m;
}






// Low level routine to modify a matrix in place and create a matrix that is doubly stochastic
// (whose rows and columns sum to 1)
TYPED(Matrix) *TYPED(as_doubly_stochastic_DEPRECATED)(TYPED(Matrix) *__m) {

    // If the matrix is not square, return NULL and don't modify __m
    if (!TYPED(Matrix_is_square)(__m)) return NULL;

    // I will use an algorithm that first normalizes col 1 so that the sum is one, and
    // then row 1 so that the sum of the elements __m(1, 2:end) sum up to 1 - __m(1, 1)
    // I will then repeat this iteratively, moving along the matrix in diagonal blocks.
    TYPED(apply)(__m, TYPED(ejovo_fabs));


    // iterate along the diagonals.
    for (size_t i = 0; i < __m->ncols; i++) {

        // printf("=== Processing i = %d\n", i);
        // For each iteration, there are 4 sums that I need to consider. The sums of above and below of the column,
        // and the row sums to the left and right of the pivot

        // First get the sum of the cols. When i = 0, we have made no normalization and we only want to
        // sum up the elements of the column
        TYPED(MatIter) cit_begin = TYPED(Matrix_col_begin)(__m, i);
        TYPED(MatIter) cit_pivot = TYPED(Matrix_col_begin_from_row)(__m, i, i);
        TYPED(MatIter) cit_end   = TYPED(Matrix_col_end)(__m, i);

        // printf("======= cit_begin: %lf\n", TYPED(MatIter_value)(cit_begin));
        // printf("======= cit_pivot: %lf\n", TYPED(MatIter_value)(cit_pivot));


        TYPED(MatIter) rit_begin = TYPED(Matrix_row_begin)(__m, i);
        TYPED(MatIter) rit_pivot = TYPED(Matrix_row_begin_from_col)(__m, i, i + 1); // Since I've normalized the first col's element, start at the next col
        TYPED(MatIter) rit_end   = TYPED(Matrix_row_end)(__m, i);

        // printf("======= rit_begin: %lf\n", TYPED(MatIter_value)(rit_begin));
        // printf("======= rit_pivot: %lf\n", TYPED(MatIter_value)(rit_pivot));

        double top_sum = TYPED(MatIter_sum)(cit_begin, cit_pivot);
        double bottom_sum = TYPED(MatIter_sum)(cit_pivot, cit_end);

        // printf("====== top_sum: %lf\n", top_sum);
        // printf("====== bottom_sum: %lf\n", bottom_sum);
        // normalize the column elements
        TYPED(MatIter_apply_mult_k)(cit_pivot, cit_end, (1 - top_sum) / bottom_sum);
        // TYPED(Matrix_print)(__m);

        double left_sum = TYPED(MatIter_sum)(rit_begin, rit_pivot);
        double right_sum = TYPED(MatIter_sum)(rit_pivot, rit_end);

        // printf("======= left_sum: %lf\n", left_sum);
        // printf("======= right_sum: %lf\n", right_sum);

        // normalize the row elements
        TYPED(MatIter_apply_mult_k)(rit_pivot, rit_end, (1 - left_sum) / right_sum);

        // printf("====== Resultant matrix:\n");
        // TYPED(Matrix_print)(__m);

        // printf("\n");

    }

    return __m;
}





// This function should TECHNICALLY verify the fact that the matrix is square.
TYPED(Matrix) *TYPED(Matrix_as_stochastic)(const TYPED(Matrix) *__m) {

    // first thing I should do is apply the absolute value function to the matrix

    TYPED(Matrix) *m_pos = TYPED(map)(__m, TYPED(ejovo_fabs));

    // No I want to normalize the rows based on their sums!!
    double sum = 0;

    // So first thing I need to do is iterate the rows
    for (size_t i = 0; i < __m->nrows; i++) {

        // Get the sum of each row
        TYPED(MatIter) start = TYPED(Matrix_row_begin)(m_pos, i);
        TYPED(MatIter) end   = TYPED(Matrix_row_end)(m_pos, i);

        sum = TYPED(MatIter_sum)(start, end);

        // Now go and adjust the row
        TYPED(MatIter_apply_div_k)(start, end, sum);
    }

    return m_pos;
}

// Create a new Stochastic matrix whose elements come from a uniform distribution
TYPED(Matrix) *TYPED(Stochastic_runif)(size_t __n, double __a, double __b) {

    // first thing I need to do is create a new uniformly generated matrix, althought the
    // actual scale shouldnt really matter...
    TYPED(Matrix) *stoch = TYPED(Matrix_runif)(__n, __n, __a, __b);

    return TYPED(as_stochastic)(stoch);
}

TYPED(Matrix) *TYPED(Stochastic_rnorm)(size_t __n, double __mean, double __std) {

    TYPED(Matrix) *stoch = TYPED(Matrix_rnorm)(__n, __n, __mean, __std);

    return TYPED(as_stochastic)(stoch);
}

TYPED(Matrix) *TYPED(Stochastic_rexp)(size_t __n, double __rate) {

    TYPED(Matrix) *stoch = TYPED(Matrix_rexp)(__n, __n, __rate);

    return TYPED(as_stochastic)(stoch);
}

// Return a DSICRETE probability vector
 TYPED(Vector)*TYPED(Vector_prob_unif)(size_t __n) {
    return TYPED(Matrix_value)(__n, 1, 1.0 / __n);
}

/**========================================================================
 *!                           Utility functions
 *========================================================================**/
 TYPED(Vector)*TYPED(compute_row_sums)(const TYPED(Matrix) *__m) {

    TYPED(Vector)*out = TYPED(Vector_new)(__m->ncols);

    for (size_t i = 0; i < __m->ncols; i++) {
        // sum each of the rows, storing
        TYPED(Vector_set)(out, i, TYPED(Matrix_row_sum)(__m, i));
    }

    return out;
}

 TYPED(Vector)*TYPED(compute_col_sums)(const TYPED(Matrix) *__m) {

    TYPED(Vector)*out = TYPED(asrow)(TYPED(Vector_new)(__m->nrows));

    for (size_t i = 0; i < __m->nrows; i++) {
        // sum each of the cols, storing
        TYPED(Vector_set)(out, i, TYPED(Matrix_col_sum)(__m, i));
    }

    return out;
}