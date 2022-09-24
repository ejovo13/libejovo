#include "ejovo_matrix_generic.h"
// #include "ejovo_matrix.h"
#include "ejovo_rand.h"

// Basic statistic routines that will operate on either vectors or a pair of MatIters

// Typed version of log
MATRIX_TYPE MATITER_FN(mean)(const MATITER_T __begin, const MATITER_T __end) {
    MATRIX_TYPE sum = MATITER_FN(sum)(__begin, __end);
    return sum / MATITER_FN(length)(__begin, __end);
}

MATRIX_TYPE MATITER_FN(sum_squared)(const MATITER_T __begin, const MATITER_T __end) {

    MATITER_T iter = __begin;
    MATRIX_TYPE sum_squared = 0;

    while (! MATITER_FN(cmp)(iter, __end)) {
        sum_squared += MATITER_FN(value)(iter) * MATITER_FN(value)(iter);
        iter = MATITER_FN(next)(iter);
    }

    return sum_squared;
}

MATRIX_TYPE MATITER_FN(mean_squared)(const MATITER_T __begin, const MATITER_T __end) {
    MATRIX_TYPE sum_squared = MATITER_FN(sum_squared)(__begin, __end);
    return sum_squared / MATITER_FN(length)(__begin, __end);
}

MATRIX_TYPE MATITER_FN(rms)(const MATITER_T __begin, const MATITER_T __end) {
    MATRIX_TYPE mean_squared = MATITER_FN(mean_squared)(__begin, __end);
    return sqrt(mean_squared);
}

MATRIX_TYPE MATITER_FN(var)(const MATITER_T __begin, const MATITER_T __end) {

    // First thing that I need to do is create a new disposable vector from __begin and __end
    Vector *copy = VECTOR_FN(from_iter)(__begin, __end);

    // compute the average
    MATRIX_TYPE mean = MATITER_FN(mean)(__begin, __end);

    // subtract the average from our copy
    MATITER_FN(row_sub_k)(VECTOR_FN(begin)(copy), VECTOR_FN(end)(copy), mean);

    // now simply take the rms right??
    MATRIX_TYPE var = MATITER_FN(mean_squared)(VECTOR_FN(begin)(copy), VECTOR_FN(end)(copy));

    MATRIX_FN(free)(copy);
    return var;
}

MATRIX_TYPE MATITER_FN(std)(const MATITER_T __begin, const MATITER_T __end) {
    return sqrt(MATITER_FN(var)(__begin, __end));
}

MATRIX_TYPE VECTOR_FN(iter_sum)(const Vector *__v) {
    return MATITER_FN(sum)(VECTOR_FN(begin)(__v), VECTOR_FN(end)(__v));
}

MATRIX_TYPE VECTOR_FN(iter_prod)(const Vector *__v) {
    return MATITER_FN(prod)(VECTOR_FN(begin)(__v), VECTOR_FN(end)(__v));
}

MATRIX_TYPE VECTOR_FN(iter_mean)(const Vector *__v) {
    return MATITER_FN(mean)(VECTOR_FN(begin)(__v), VECTOR_FN(end)(__v));
}

MATRIX_TYPE VECTOR_FN(iter_mean_squared)(const Vector *__v) {
    return MATITER_FN(mean_squared)(VECTOR_FN(begin)(__v), VECTOR_FN(end)(__v));
}

MATRIX_TYPE VECTOR_FN(iter_rms)(const Vector *__v) {
    return MATITER_FN(rms)(VECTOR_FN(begin)(__v), VECTOR_FN(end)(__v));
}

MATRIX_TYPE VECTOR_FN(iter_min)(const Vector *__v) {
    return MATITER_FN(min)(VECTOR_FN(begin)(__v), VECTOR_FN(end)(__v));
}

MATRIX_TYPE VECTOR_FN(iter_max)(const Vector *__v) {
    return MATITER_FN(max)(VECTOR_FN(begin)(__v), VECTOR_FN(end)(__v));
}

MATRIX_TYPE VECTOR_FN(iter_var)(const Vector *__v) {
    return MATITER_FN(var)(VECTOR_FN(begin)(__v), VECTOR_FN(end)(__v));
}

MATRIX_TYPE VECTOR_FN(iter_std)(const Vector *__v) {
    return MATITER_FN(std)(VECTOR_FN(begin)(__v), VECTOR_FN(end)(__v));
}

MATRIX_TYPE MATRIX_FN(iter_sum)(const MATRIX_T *__m) {
    return MATITER_FN(sum)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
}

MATRIX_TYPE MATRIX_FN(iter_prod)(const MATRIX_T *__m) {
    return MATITER_FN(prod)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
}

MATRIX_TYPE MATRIX_FN(iter_mean)(const MATRIX_T *__m) {
    return MATITER_FN(mean)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
}

MATRIX_TYPE MATRIX_FN(iter_mean_squared)(const MATRIX_T *__m) {
    return MATITER_FN(mean_squared)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
}

MATRIX_TYPE MATRIX_FN(iter_rms)(const MATRIX_T *__m) {
    return MATITER_FN(rms)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
}

MATRIX_TYPE MATRIX_FN(iter_min)(const MATRIX_T *__m) {
    return MATITER_FN(min)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
}

MATRIX_TYPE MATRIX_FN(iter_max)(const MATRIX_T *__m) {
    return MATITER_FN(max)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
}

MATRIX_TYPE MATRIX_FN(iter_var)(const MATRIX_T *__m) {
    return MATITER_FN(var)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
}

MATRIX_TYPE MATRIX_FN(iter_std)(const MATRIX_T *__m) {
    return MATITER_FN(std)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
}

/**========================================================================
 *!                           Regular matrix stats routines
 *========================================================================**/
// typedef MATRIX_TYPE (* mat_iter_fn) (const MatIter, const MatIter);

MATRIX_TYPE MATRIX_FN(iterate)(const MATRIX_T *__m, mat_iter_fn fn) {
    return fn(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
}

MATRIX_TYPE TYPED_FN(mean)(const MATRIX_T *__m) {
    // return MATITER_FN(mean)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
    return MATRIX_FN(iterate)(__m, MATITER_FN(mean));
}

MATRIX_TYPE TYPED_FN(sum)(const MATRIX_T *__m) {
    // return MATITER_FN(sum)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
    // return MATRIX_FN(iterate)(__m, MATITER_FN(sum));
    MATRIX_TYPE somme = 0;
    MATRIX_TYPE *data = __m->data;
    const size_t n = MATRIX_FN(size)(__m);
    for (int i = 0; i < n; i++) {
        somme += data[i];
    }
    return somme;
}

MATRIX_TYPE TYPED_FN(std)(const MATRIX_T *__m) {
    // return MATITER_FN(std)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
    return MATRIX_FN(iterate)(__m, MATITER_FN(std));
}

MATRIX_TYPE TYPED_FN(var)(const MATRIX_T *__m) {
    // return MATITER_FN(std)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
    return MATRIX_FN(iterate)(__m, MATITER_FN(var));
}

MATRIX_TYPE TYPED_FN(min)(const MATRIX_T *__m) {
    // return MATITER_FN(std)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
    return MATRIX_FN(iterate)(__m, MATITER_FN(min));
}

MATRIX_TYPE TYPED_FN(max)(const MATRIX_T *__m) {
    // return MATITER_FN(std)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
    return MATRIX_FN(iterate)(__m, MATITER_FN(max));
}

MATRIX_TYPE TYPED_FN(rms)(const MATRIX_T *__m) {
    return MATRIX_FN(iterate)(__m, MATITER_FN(rms));
}

MATRIX_TYPE TYPED_FN(mean_squared)(const MATRIX_T *__m) {
    return MATRIX_FN(iterate)(__m, MATITER_FN(mean_squared));
}

MATRIX_TYPE TYPED_FN(prod)(const MATRIX_T *__m) {
    return MATRIX_FN(iterate)(__m, MATITER_FN(prod));
}

// Implement the `cor` function to compute the correlation coefficient between two points
// I will also want to eventually add in my own data science and statistic routines just for good
// practice

// We are just assuming that both of these are vectors with the same size
// MATRIX_TYPE cor(const MATRIX_T *__a, const MATRIX_T *__b) {

//     if (! (MATRIX_FN(is_vec)(__a) && MATRIX_FN(is_vec)(__b))) return -1; // If they arent both vectors

//     // make sure their sizes are the same
//     if (VECTOR_FN(size)(__a) != VECTOR_FN(size)(__b)) return -2;

//     // First we need to find the average of __a and __b

//     MATRIX_TYPE mean_a = TYPED_FN(mean)(__a);
//     MATRIX_TYPE mean_b = TYPED_FN(mean)(__b);

//     // Now we need to compute The sum of x minus the mean and the sum
//     // of y minus its mean
//     Vector *a_min_mean = MATRIX_FN(sub_scalar)(__a, mean_a);
//     Vector *b_min_mean = MATRIX_FN(sub_scalar)(__b, mean_b);

//     Vector *num_arr = MATRIX_FN(hadamard)(a_min_mean, b_min_mean);

//     MATRIX_TYPE num = TYPED_FN(sum)(num_arr);
//     MATRIX_TYPE den = std(__a) * std(__b);

//     MATRIX_TYPE out = num / den;

//     MATRIX_FN(free)(a_min_mean);
//     MATRIX_FN(free)(b_min_mean);
//     MATRIX_FN(free)(num_arr);

//     return out;
// }
MATRIX_TYPE TYPED_FN(cov)(const MATRIX_T *__x, const MATRIX_T *__y) {


    if (! (MATRIX_FN(is_vec)(__x) && MATRIX_FN(is_vec)(__y))) return -1; // If they arent both vectors

    if (VECTOR_FN(size)(__x) != VECTOR_FN(size)(__y)) return -2;

    MATRIX_TYPE mean_x = TYPED_FN(mean)(__x);
    MATRIX_TYPE mean_y = TYPED_FN(mean)(__y);

    Vector *x_min_mean = MATRIX_FN(sub_scalar)(__x, mean_x);
    Vector *y_min_mean = MATRIX_FN(sub_scalar)(__y, mean_y);

    Vector *num_arr = MATRIX_FN(hadamard)(x_min_mean, y_min_mean);

    MATRIX_TYPE out = TYPED_FN(sum)(num_arr) / VECTOR_FN(size)(num_arr);

    MATRIX_FN(free)(x_min_mean);
    MATRIX_FN(free)(y_min_mean);
    MATRIX_FN(free)(num_arr);

    return out;
}

// Attempt to compute the correlation coefficient by using standard scores
MATRIX_TYPE TYPED_FN(cor)(const MATRIX_T *__a, const MATRIX_T *__b) {

    if (! (MATRIX_FN(is_vec)(__a) && MATRIX_FN(is_vec)(__b))) return -1; // If they arent both vectors

    // make sure their sizes are the same
    if (VECTOR_FN(size)(__a) != VECTOR_FN(size)(__b)) return -2;

    // Now we need to compute The sum of x minus the mean and the sum
    // of y minus its mean
    return TYPED_FN(cov)(__a, __b) / (TYPED_FN(std)(__a) * TYPED_FN(std)(__b));
}

// Find the kth central moment
MATRIX_TYPE TYPED_FN(cmoment)(const Vector *__v, int __k) {

    // Take the hadamard product of __v minus its mean.
    // Then take the sum and divide by n
    MATRIX_TYPE u_v = TYPED_FN(mean)(__v);
    Vector *v_min_uv = MATRIX_FN(sub_scalar)(__v, u_v);

    // take the kth hadamard exponential
    MAT_FN(hadexp)(v_min_uv, __k);

    MATRIX_TYPE out = TYPED_FN(sum)(v_min_uv) / VECTOR_FN(size)(__v);

    MATRIX_FN(free)(v_min_uv);

    return out;
}

MATRIX_TYPE TYPED_FN(rmoment)(const Vector *__v, int __k) {

    Vector *v = MATRIX_FN(clone)(__v);

    MAT_FN(hadexp)(v, __k);

    MATRIX_TYPE out = TYPED_FN(sum)(v) / VECTOR_FN(size)(__v);

    MATRIX_FN(free)(v);

    return out;
}

// Let's do a simple linear regression with respect to an x and y variable
// Return a matrix whose elements are the coefficients a_0, a_1, a_n for an nth
// degree polynomial
Vector *TYPED_FN(linear_regression)(const Vector *__x, const Vector *__y) {
    return TYPED_FN(least_squares)(__x, __y, 1);
}

Vector *TYPED_FN(least_squares)(const Vector *__x, const Vector *__y, int degree) {

    MATRIX_T *V = MATRIX_FN(vandermonde_reduced)(__x, degree);
    MATRIX_T *Vt = MATRIX_FN(transpose)(V);
    Vector *y_hat = MATRIX_FN(multiply)(Vt, __y);
    MATRIX_T *lhs = MATRIX_FN(multiply)(Vt, V);

    MATRIX_FN(reset)(&V);
    MATRIX_FN(reset)(&Vt);

    Vector *a = MATRIX_FN(solve_lu)(lhs, y_hat);

    MATRIX_FN(reset)(&y_hat);
    MATRIX_FN(reset)(&lhs);

    return a;

}

Vector *TYPED_FN(loglog_regression)(const Vector *__x, const Vector *__y) {

    MATRIX_T *logx = TYPED_FN(map)(__x, log);
    MATRIX_T *logy = TYPED_FN(map)(__y, log);
    Vector *out = TYPED_FN(linear_regression)(logx, logy);

    MATRIX_FN(free)(logx);
    MATRIX_FN(free)(logy);

    return out;
}


MATRIX_T *TYPED_FN(runif)(int n, double a, double b) {
    return TYPED_FN(runif_gen)(n, a, b, DEFAULT_RNG);
}



MATRIX_T *TYPED_FN(runif_gen)(int n, double a, double b, RNG_FN rng_fn) {

    MATRIX_T *out = MATRIX_FN(new)(1, n);

    for (int i = 0; i < n; i++) {
        out->data[i] = unifd_rng(a, b, rng_fn);
    }

    return out;
}
