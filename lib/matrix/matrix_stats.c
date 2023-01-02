// #include "ejovo_matrix_generic.h"
#include "ejovo_matrix.h"
#include "ejovo_rand.h"

// Basic statistic routines that will operate on either vectors or a pair of MatIters

// Typed version of log
MATRIX_TYPE TYPED(MatIter_mean)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end) {
    MATRIX_TYPE sum = TYPED(MatIter_sum)(__begin, __end);
    return sum / TYPED(MatIter_length)(__begin, __end);
}

MATRIX_TYPE TYPED(MatIter_sumabs)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end) {

    TYPED(MatIter) iter = __begin;
    MATRIX_TYPE sumabs = 0;

    while (! TYPED(MatIter_cmp)(iter, __end)) {

#if defined MATRIX_COMPLEX
        sumabs += cabs(TYPED(MatIter_value)(iter));
#elif defined MATRIX_INT
        sumabs += abs(TYPED(MatIter_value)(iter));
#else
        sumabs += fabs(TYPED(MatIter_value)(iter));
#endif
// #elif defined MATRIX_
        iter = TYPED(MatIter_next)(iter);
    }

    return sumabs;

}

MATRIX_TYPE TYPED(MatIter_sum_squared)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end) {

    TYPED(MatIter) iter = __begin;
    MATRIX_TYPE sum_squared = 0;

    while (! TYPED(MatIter_cmp)(iter, __end)) {
        sum_squared += TYPED(MatIter_value)(iter) * TYPED(MatIter_value)(iter);
        iter = TYPED(MatIter_next)(iter);
    }

    return sum_squared;
}

MATRIX_TYPE TYPED(MatIter_mean_squared)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end) {
    MATRIX_TYPE sum_squared = TYPED(MatIter_sum_squared)(__begin, __end);
    return sum_squared / TYPED(MatIter_length)(__begin, __end);
}

MATRIX_TYPE TYPED(MatIter_rms)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end) {
    MATRIX_TYPE mean_squared = TYPED(MatIter_mean_squared)(__begin, __end);
    return sqrt(mean_squared);
}

MATRIX_TYPE TYPED(MatIter_var)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end) {

    // First thing that I need to do is create a new disposable vector from __begin and __end
    TYPED(Vector) *copy = TYPED(Vector_from_iter)(__begin, __end);

    // compute the average
    MATRIX_TYPE mean = TYPED(MatIter_mean)(__begin, __end);

    // subtract the average from our copy
    TYPED(MatIter_row_sub_k)(TYPED(Vector_begin)(copy), TYPED(Vector_end)(copy), mean);

    // now simply take the rms right??
    MATRIX_TYPE var = TYPED(MatIter_mean_squared)(TYPED(Vector_begin)(copy), TYPED(Vector_end)(copy));

    TYPED(Matrix_free)(copy);
    return var;
}

MATRIX_TYPE TYPED(MatIter_std)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end) {
    return sqrt(TYPED(MatIter_var)(__begin, __end));
}

MATRIX_TYPE TYPED(Vector_iter_sum)(const TYPED(Vector)*__v) {
    return TYPED(MatIter_sum)(TYPED(Vector_begin)(__v), TYPED(Vector_end)(__v));
}

MATRIX_TYPE TYPED(Vector_iter_prod)(const TYPED(Vector)*__v) {
    return TYPED(MatIter_prod)(TYPED(Vector_begin)(__v), TYPED(Vector_end)(__v));
}

MATRIX_TYPE TYPED(Vector_iter_mean)(const TYPED(Vector)*__v) {
    return TYPED(MatIter_mean)(TYPED(Vector_begin)(__v), TYPED(Vector_end)(__v));
}

MATRIX_TYPE TYPED(Vector_iter_mean_squared)(const TYPED(Vector)*__v) {
    return TYPED(MatIter_mean_squared)(TYPED(Vector_begin)(__v), TYPED(Vector_end)(__v));
}

MATRIX_TYPE TYPED(Vector_iter_rms)(const TYPED(Vector)*__v) {
    return TYPED(MatIter_rms)(TYPED(Vector_begin)(__v), TYPED(Vector_end)(__v));
}

MATRIX_TYPE TYPED(Vector_iter_min)(const TYPED(Vector)*__v) {
    return TYPED(MatIter_min)(TYPED(Vector_begin)(__v), TYPED(Vector_end)(__v));
}

MATRIX_TYPE TYPED(Vector_iter_max)(const TYPED(Vector)*__v) {
    return TYPED(MatIter_max)(TYPED(Vector_begin)(__v), TYPED(Vector_end)(__v));
}

MATRIX_TYPE TYPED(Vector_iter_var)(const TYPED(Vector)*__v) {
    return TYPED(MatIter_var)(TYPED(Vector_begin)(__v), TYPED(Vector_end)(__v));
}

MATRIX_TYPE TYPED(Vector_iter_std)(const TYPED(Vector)*__v) {
    return TYPED(MatIter_std)(TYPED(Vector_begin)(__v), TYPED(Vector_end)(__v));
}

MATRIX_TYPE TYPED(Matrix_iter_sum)(const TYPED(Matrix) *__m) {
    return TYPED(MatIter_sum)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
}

MATRIX_TYPE TYPED(Matrix_iter_prod)(const TYPED(Matrix) *__m) {
    return TYPED(MatIter_prod)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
}

MATRIX_TYPE TYPED(Matrix_iter_mean)(const TYPED(Matrix) *__m) {
    return TYPED(MatIter_mean)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
}

MATRIX_TYPE TYPED(Matrix_iter_mean_squared)(const TYPED(Matrix) *__m) {
    return TYPED(MatIter_mean_squared)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
}

MATRIX_TYPE TYPED(Matrix_iter_rms)(const TYPED(Matrix) *__m) {
    return TYPED(MatIter_rms)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
}

MATRIX_TYPE TYPED(Matrix_iter_min)(const TYPED(Matrix) *__m) {
    return TYPED(MatIter_min)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
}

MATRIX_TYPE TYPED(Matrix_iter_max)(const TYPED(Matrix) *__m) {
    return TYPED(MatIter_max)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
}

MATRIX_TYPE TYPED(Matrix_iter_var)(const TYPED(Matrix) *__m) {
    return TYPED(MatIter_var)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
}

MATRIX_TYPE TYPED(Matrix_iter_std)(const TYPED(Matrix) *__m) {
    return TYPED(MatIter_std)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
}

/**========================================================================
 *!                           Regular matrix stats routines
 *========================================================================**/
// typedef MATRIX_TYPE (* mat_iter_fn) (const MatIter, const MatIter);

MATRIX_TYPE TYPED(Matrix_iterate)(const TYPED(Matrix) *__m, TYPED(mat_iter_fn) fn) {
    return fn(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
}

MATRIX_TYPE TYPED(mean)(const TYPED(Matrix) *__m) {
    // return TYPED(MatIter_mean)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
    return TYPED(Matrix_iterate)(__m, TYPED(MatIter_mean));
}

MATRIX_TYPE TYPED(sum)(const TYPED(Matrix) *__m) {
    // return TYPED(MatIter_sum)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
    // return TYPED(Matrix_iterate)(__m, TYPED(MatIter_sum));
    MATRIX_TYPE somme = 0;
    MATRIX_TYPE *data = __m->data;
    const size_t n = TYPED(Matrix_size)(__m);
    for (size_t i = 0; i < n; i++) {
        somme += data[i];
    }
    return somme;
}

MATRIX_TYPE TYPED(std)(const TYPED(Matrix) *__m) {
    // return TYPED(MatIter_std)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
    return TYPED(Matrix_iterate)(__m, TYPED(MatIter_std));
}

MATRIX_TYPE TYPED(var)(const TYPED(Matrix) *__m) {
    // return TYPED(MatIter_std)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
    return TYPED(Matrix_iterate)(__m, TYPED(MatIter_var));
}

MATRIX_TYPE TYPED(min)(const TYPED(Matrix) *__m) {
    // return TYPED(MatIter_std)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
    return TYPED(Matrix_iterate)(__m, TYPED(MatIter_min));
}

MATRIX_TYPE TYPED(max)(const TYPED(Matrix) *__m) {
    // return TYPED(MatIter_std)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
    return TYPED(Matrix_iterate)(__m, TYPED(MatIter_max));
}

MATRIX_TYPE TYPED(maxabs)(const TYPED(Matrix) *__m) {
    return TYPED(Matrix_iterate)(__m, TYPED(MatIter_maxabs));
}

MATRIX_TYPE TYPED(sumabs)(const TYPED(Matrix) *__m) {
    return TYPED(Matrix_iterate)(__m, TYPED(MatIter_sumabs));
}

MATRIX_TYPE TYPED(rms)(const TYPED(Matrix) *__m) {
    return TYPED(Matrix_iterate)(__m, TYPED(MatIter_rms));
}

MATRIX_TYPE TYPED(mean_squared)(const TYPED(Matrix) *__m) {
    return TYPED(Matrix_iterate)(__m, TYPED(MatIter_mean_squared));
}

MATRIX_TYPE TYPED(prod)(const TYPED(Matrix) *__m) {
    return TYPED(Matrix_iterate)(__m, TYPED(MatIter_prod));
}

// Implement the `cor` function to compute the correlation coefficient between two points
// I will also want to eventually add in my own data science and statistic routines just for good
// practice

// We are just assuming that both of these are vectors with the same size
// MATRIX_TYPE cor(const TYPED(Matrix) *__a, const TYPED(Matrix) *__b) {

//     if (! (TYPED(Matrix_is_vec)(__a) && TYPED(Matrix_is_vec)(__b))) return -1; // If they arent both vectors

//     // make sure their sizes are the same
//     if (TYPED(Vector_size)(__a) != TYPED(Vector_size)(__b)) return -2;

//     // First we need to find the average of __a and __b

//     MATRIX_TYPE mean_a = TYPED(mean)(__a);
//     MATRIX_TYPE mean_b = TYPED(mean)(__b);

//     // Now we need to compute The sum of x minus the mean and the sum
//     // of y minus its mean
//     TYPED(Vector)*a_min_mean = TYPED(Matrix_sub_scalar)(__a, mean_a);
//     TYPED(Vector)*b_min_mean = TYPED(Matrix_sub_scalar)(__b, mean_b);

//     TYPED(Vector)*num_arr = TYPED(Matrix_hadamard)(a_min_mean, b_min_mean);

//     MATRIX_TYPE num = TYPED(sum)(num_arr);
//     MATRIX_TYPE den = std(__a) * std(__b);

//     MATRIX_TYPE out = num / den;

//     TYPED(Matrix_free)(a_min_mean);
//     TYPED(Matrix_free)(b_min_mean);
//     TYPED(Matrix_free)(num_arr);

//     return out;
// }
MATRIX_TYPE TYPED(cov)(const TYPED(Matrix) *__x, const TYPED(Matrix) *__y) {


    if (! (TYPED(Matrix_is_vec)(__x) && TYPED(Matrix_is_vec)(__y))) return -1; // If they arent both vectors

    if (TYPED(Vector_size)(__x) != TYPED(Vector_size)(__y)) return -2;

    MATRIX_TYPE mean_x = TYPED(mean)(__x);
    MATRIX_TYPE mean_y = TYPED(mean)(__y);

    TYPED(Vector)*x_min_mean = TYPED(Matrix_sub_scalar)(__x, mean_x);
    TYPED(Vector)*y_min_mean = TYPED(Matrix_sub_scalar)(__y, mean_y);

    TYPED(Vector)*num_arr = TYPED(Matrix_hadamard)(x_min_mean, y_min_mean);

    MATRIX_TYPE out = TYPED(sum)(num_arr) / TYPED(Vector_size)(num_arr);

    TYPED(Matrix_free)(x_min_mean);
    TYPED(Matrix_free)(y_min_mean);
    TYPED(Matrix_free)(num_arr);

    return out;
}

// Attempt to compute the correlation coefficient by using standard scores
MATRIX_TYPE TYPED(cor)(const TYPED(Matrix) *__a, const TYPED(Matrix) *__b) {

    if (! (TYPED(Matrix_is_vec)(__a) && TYPED(Matrix_is_vec)(__b))) return -1; // If they arent both vectors

    // make sure their sizes are the same
    if (TYPED(Vector_size)(__a) != TYPED(Vector_size)(__b)) return -2;

    // Now we need to compute The sum of x minus the mean and the sum
    // of y minus its mean
    return TYPED(cov)(__a, __b) / (TYPED(std)(__a) * TYPED(std)(__b));
}

// Find the kth central moment
MATRIX_TYPE TYPED(cmoment)(const TYPED(Vector)*__v, int __k) {

    // Take the hadamard product of __v minus its mean.
    // Then take the sum and divide by n
    MATRIX_TYPE u_v = TYPED(mean)(__v);
    TYPED(Vector)*v_min_uv = TYPED(Matrix_sub_scalar)(__v, u_v);

    // take the kth hadamard exponential
    TYPED(mathadexp)(v_min_uv, __k);

    MATRIX_TYPE out = TYPED(sum)(v_min_uv) / TYPED(Vector_size)(__v);

    TYPED(Matrix_free)(v_min_uv);

    return out;
}

MATRIX_TYPE TYPED(rmoment)(const TYPED(Vector)*__v, int __k) {

    TYPED(Vector)*v = TYPED(Matrix_clone)(__v);

    TYPED(mathadexp)(v, __k);

    MATRIX_TYPE out = TYPED(sum)(v) / TYPED(Vector_size)(__v);

    TYPED(Matrix_free)(v);

    return out;
}

// Let's do a simple linear regression with respect to an x and y variable
// Return a matrix whose elements are the coefficients a_0, a_1, a_n for an nth
// degree polynomial
 TYPED(Vector)*TYPED(linear_regression)(const TYPED(Vector)*__x, const TYPED(Vector)*__y) {
    return TYPED(least_squares)(__x, __y, 1);
}

 TYPED(Vector)*TYPED(least_squares)(const TYPED(Vector)*__x, const TYPED(Vector)*__y, int degree) {

    TYPED(Matrix) *V = TYPED(Matrix_vandermonde_reduced)(__x, degree);
    TYPED(Matrix) *Vt = TYPED(Matrix_transpose)(V);
    TYPED(Vector)*y_hat = TYPED(Matrix_multiply)(Vt, __y);
    TYPED(Matrix) *lhs = TYPED(Matrix_multiply)(Vt, V);

    TYPED(Matrix_reset)(&V);
    TYPED(Matrix_reset)(&Vt);

    TYPED(Vector)*a = TYPED(Matrix_solve_lu)(lhs, y_hat);

    TYPED(Matrix_reset)(&y_hat);
    TYPED(Matrix_reset)(&lhs);

    return a;

}

 TYPED(Vector)*TYPED(loglog_regression)(const TYPED(Vector)*__x, const TYPED(Vector)*__y) {

    TYPED(Matrix) *logx = TYPED(map)(__x, TYPED(ejovo_log));
    TYPED(Matrix) *logy = TYPED(map)(__y, TYPED(ejovo_log));
    TYPED(Vector)*out = TYPED(linear_regression)(logx, logy);

    TYPED(Matrix_free)(logx);
    TYPED(Matrix_free)(logy);

    return out;
}


TYPED(Matrix) *TYPED(runif)(int n, MATRIX_TYPE a, MATRIX_TYPE b) {
    return TYPED(runif_rng)(n, a, b, DEFAULT_RNG);
}

TYPED(Matrix) *TYPED(rnorm)(int n, MATRIX_TYPE mu, MATRIX_TYPE sigma) {
    return TYPED(rnorm_rng)(n, mu, sigma, DEFAULT_RNG);
}

TYPED(Matrix) *TYPED(rnorm_rng)(int n, MATRIX_TYPE mu, MATRIX_TYPE sigma, RNG_FN rng_fn) {

    TYPED(Matrix) *out = TYPED(Matrix_new)(1, n);

    for (int i = 0; i < n; i++) {
    #ifdef MATRIX_COMPLEX
        out->data[i] = normc_rng(mu, sigma, rng_fn);
    #else
        out->data[i] = normd_rng(mu, sigma, rng_fn);
    #endif

    }

    return out;

}

TYPED(Matrix) *TYPED(runif_rng)(int n, MATRIX_TYPE a, MATRIX_TYPE b, RNG_FN rng_fn) {

    TYPED(Matrix) *out = TYPED(Matrix_new)(1, n);

    for (int i = 0; i < n; i++) {
    #ifdef MATRIX_COMPLEX
        out->data[i] = unifc_rng(a, b, rng_fn);
    #else
        out->data[i] = unifd_rng(a, b, rng_fn);
    #endif

    }

    return out;
}
