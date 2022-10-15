#ifndef MATRIX_STATS_H
#define MATRIX_STATS_H

#include "matrix.h"

// Basic statistic routines that will operate on either vectors or a pair of MatIters

static inline MATRIX_TYPE TYPED(log)(MATRIX_TYPE x) {
    return log(x);
}

MATRIX_TYPE TYPED(MatIter_mean)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end);

MATRIX_TYPE TYPED(MatIter_sum_squared)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end);

MATRIX_TYPE TYPED(MatIter_mean_squared)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end);

MATRIX_TYPE TYPED(MatIter_rms)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end);

MATRIX_TYPE TYPED(MatIter_var)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end);

MATRIX_TYPE TYPED(MatIter_std)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end);

MATRIX_TYPE TYPED(MatIter_sumabs)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end);

MATRIX_TYPE TYPED(Vector_iter_sum)(const TYPED(Vector)*__v);

MATRIX_TYPE TYPED(Vector_iter_prod)(const TYPED(Vector)*__v);

MATRIX_TYPE TYPED(Vector_iter_mean)(const TYPED(Vector)*__v);

MATRIX_TYPE TYPED(Vector_iter_mean_squared)(const TYPED(Vector)*__v);

MATRIX_TYPE TYPED(Vector_iter_rms)(const TYPED(Vector)*__v);

MATRIX_TYPE TYPED(Vector_iter_min)(const TYPED(Vector)*__v);

MATRIX_TYPE TYPED(Vector_iter_max)(const TYPED(Vector)*__v);

MATRIX_TYPE TYPED(Vector_iter_var)(const TYPED(Vector)*__v);

MATRIX_TYPE TYPED(Vector_iter_std)(const TYPED(Vector)*__v);

MATRIX_TYPE TYPED(Matrix_iter_sum)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(Matrix_iter_prod)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(Matrix_iter_mean)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(Matrix_iter_mean_squared)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(Matrix_iter_rms)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(Matrix_iter_min)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(Matrix_iter_max)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(Matrix_iter_var)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(Matrix_iter_std)(const TYPED(Matrix) *__m);

typedef MATRIX_TYPE (* TYPED(mat_iter_fn)) (const TYPED(MatIter), const TYPED(MatIter));

MATRIX_TYPE TYPED(Matrix_iterate)(const TYPED(Matrix) *__m, TYPED(mat_iter_fn) fn);

/**========================================================================
 *!                           Typed functions
 *========================================================================**/

MATRIX_TYPE TYPED(mean)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(sum)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(std)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(var)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(min)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(max)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(maxabs)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(sumabs)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(rms)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(mean_squared)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(cov)(const TYPED(Matrix) *__x, const TYPED(Matrix) *__y);

MATRIX_TYPE TYPED(prod)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(cor)(const TYPED(Matrix) *__x, const TYPED(Matrix) *__y);

// central moment
MATRIX_TYPE TYPED(cmoment)(const TYPED(Vector)*__v, int __k);

// raw moment
MATRIX_TYPE TYPED(rmoment)(const TYPED(Vector)*__v, int __k);

 TYPED(Vector)*TYPED(linear_regression)(const TYPED(Vector)*__x, const TYPED(Vector)*__y);

static inline MATRIX_TYPE TYPED(ejovo_log) (const MATRIX_TYPE x) {
    return log(x);
}

static inline MATRIX_TYPE TYPED(ejovo_fabs) (const MATRIX_TYPE x) {
    return fabs((double) x);
}

 TYPED(Vector)*TYPED(loglog_regression)(const TYPED(Vector)*__x, const TYPED(Vector)*__y);

 TYPED(Vector)*TYPED(least_squares)(const TYPED(Vector)*__x, const TYPED(Vector)*__y, int degree);

TYPED(Matrix) *TYPED(runif)(int n, MATRIX_TYPE a, MATRIX_TYPE b);

TYPED(Matrix) *TYPED(rnorm)(int n, MATRIX_TYPE mu, MATRIX_TYPE sigma);

TYPED(Matrix) *TYPED(rnorm_rng)(int n, MATRIX_TYPE mu, MATRIX_TYPE sigma, RNG_FN rng_fn);

TYPED(Matrix) *TYPED(runif_rng)(int n, MATRIX_TYPE a, MATRIX_TYPE b, RNG_FN rng_fn);

#endif