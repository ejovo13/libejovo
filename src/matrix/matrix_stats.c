#include "ejovo_matrix.h"
#include "ejovo_rand.h"

// Basic statistic routines that will operate on either vectors or a pair of MatIters

MATRIX_TYPE MatIter_mean(const MatIter __begin, const MatIter __end) {
    MATRIX_TYPE sum = MatIter_sum(__begin, __end);
    return sum / MatIter_length(__begin, __end);
}

MATRIX_TYPE MatIter_sum_squared(const MatIter __begin, const MatIter __end) {

    MatIter iter = __begin;
    MATRIX_TYPE sum_squared = 0;

    while (! MatIter_cmp(iter, __end)) {
        sum_squared += MatIter_value(iter) * MatIter_value(iter);
        iter = MatIter_next(iter);
    }

    return sum_squared;
}

MATRIX_TYPE MatIter_mean_squared(const MatIter __begin, const MatIter __end) {
    MATRIX_TYPE sum_squared = MatIter_sum_squared(__begin, __end);
    return sum_squared / MatIter_length(__begin, __end);
}

MATRIX_TYPE MatIter_rms(const MatIter __begin, const MatIter __end) {
    MATRIX_TYPE mean_squared = MatIter_mean_squared(__begin, __end);
    return sqrt(mean_squared);
}

MATRIX_TYPE MatIter_var(const MatIter __begin, const MatIter __end) {

    // First thing that I need to do is create a new disposable vector from __begin and __end
    Vector *copy = Vector_from_iter(__begin, __end);

    // compute the average
    MATRIX_TYPE mean = MatIter_mean(__begin, __end);

    // subtract the average from our copy
    MatIter_row_sub_k(Vector_begin(copy), Vector_end(copy), mean);

    // now simply take the rms right??
    MATRIX_TYPE var = MatIter_mean_squared(Vector_begin(copy), Vector_end(copy));

    Matrix_free(copy);
    return var;
}

MATRIX_TYPE MatIter_std(const MatIter __begin, const MatIter __end) {
    return sqrt(MatIter_var(__begin, __end));
}

MATRIX_TYPE Vector_iter_sum(const Vector *__v) {
    return MatIter_sum(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_prod(const Vector *__v) {
    return MatIter_prod(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_mean(const Vector *__v) {
    return MatIter_mean(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_mean_squared(const Vector *__v) {
    return MatIter_mean_squared(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_rms(const Vector *__v) {
    return MatIter_rms(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_min(const Vector *__v) {
    return MatIter_min(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_max(const Vector *__v) {
    return MatIter_max(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_var(const Vector *__v) {
    return MatIter_var(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Vector_iter_std(const Vector *__v) {
    return MatIter_std(Vector_begin(__v), Vector_end(__v));
}

MATRIX_TYPE Matrix_iter_sum(const Matrix *__m) {
    return MatIter_sum(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_prod(const Matrix *__m) {
    return MatIter_prod(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_mean(const Matrix *__m) {
    return MatIter_mean(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_mean_squared(const Matrix *__m) {
    return MatIter_mean_squared(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_rms(const Matrix *__m) {
    return MatIter_rms(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_min(const Matrix *__m) {
    return MatIter_min(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_max(const Matrix *__m) {
    return MatIter_max(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_var(const Matrix *__m) {
    return MatIter_var(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE Matrix_iter_std(const Matrix *__m) {
    return MatIter_std(Matrix_begin(__m), Matrix_end(__m));
}

/**========================================================================
 *!                           Regular matrix stats routines
 *========================================================================**/
// typedef MATRIX_TYPE (* mat_iter_fn) (const MatIter, const MatIter);

MATRIX_TYPE Matrix_iterate(const Matrix *__m, mat_iter_fn fn) {
    return fn(Matrix_begin(__m), Matrix_end(__m));
}

MATRIX_TYPE mean(const Matrix *__m) {
    // return MatIter_mean(Matrix_begin(__m), Matrix_end(__m));
    return Matrix_iterate(__m, MatIter_mean);
}

MATRIX_TYPE sum(const Matrix *__m) {
    // return MatIter_sum(Matrix_begin(__m), Matrix_end(__m));
    // return Matrix_iterate(__m, MatIter_sum);
    MATRIX_TYPE somme = 0;
    MATRIX_TYPE *data = __m->data;
    const size_t n = Matrix_size(__m);
    for (int i = 0; i < n; i++) {
        somme += data[i];
    }
    return somme;
}

MATRIX_TYPE std(const Matrix *__m) {
    // return MatIter_std(Matrix_begin(__m), Matrix_end(__m));
    return Matrix_iterate(__m, MatIter_std);
}

MATRIX_TYPE var(const Matrix *__m) {
    // return MatIter_std(Matrix_begin(__m), Matrix_end(__m));
    return Matrix_iterate(__m, MatIter_var);
}

MATRIX_TYPE min(const Matrix *__m) {
    // return MatIter_std(Matrix_begin(__m), Matrix_end(__m));
    return Matrix_iterate(__m, MatIter_min);
}

MATRIX_TYPE max(const Matrix *__m) {
    // return MatIter_std(Matrix_begin(__m), Matrix_end(__m));
    return Matrix_iterate(__m, MatIter_max);
}

MATRIX_TYPE rms(const Matrix *__m) {
    return Matrix_iterate(__m, MatIter_rms);
}

MATRIX_TYPE mean_squared(const Matrix *__m) {
    return Matrix_iterate(__m, MatIter_mean_squared);
}

MATRIX_TYPE prod(const Matrix *__m) {
    return Matrix_iterate(__m, MatIter_prod);
}

// Implement the `cor` function to compute the correlation coefficient between two points
// I will also want to eventually add in my own data science and statistic routines just for good
// practice

// We are just assuming that both of these are vectors with the same size
// MATRIX_TYPE cor(const Matrix *__a, const Matrix *__b) {

//     if (! (Matrix_is_vec(__a) && Matrix_is_vec(__b))) return -1; // If they arent both vectors

//     // make sure their sizes are the same
//     if (Vector_size(__a) != Vector_size(__b)) return -2;

//     // First we need to find the average of __a and __b

//     MATRIX_TYPE mean_a = mean(__a);
//     MATRIX_TYPE mean_b = mean(__b);

//     // Now we need to compute The sum of x minus the mean and the sum
//     // of y minus its mean
//     Vector *a_min_mean = Matrix_sub_scalar(__a, mean_a);
//     Vector *b_min_mean = Matrix_sub_scalar(__b, mean_b);

//     Vector *num_arr = Matrix_hadamard(a_min_mean, b_min_mean);

//     MATRIX_TYPE num = sum(num_arr);
//     MATRIX_TYPE den = std(__a) * std(__b);

//     MATRIX_TYPE out = num / den;

//     Matrix_free(a_min_mean);
//     Matrix_free(b_min_mean);
//     Matrix_free(num_arr);

//     return out;
// }
MATRIX_TYPE cov(const Matrix *__x, const Matrix *__y) {


    if (! (Matrix_is_vec(__x) && Matrix_is_vec(__y))) return -1; // If they arent both vectors

    if (Vector_size(__x) != Vector_size(__y)) return -2;

    MATRIX_TYPE mean_x = mean(__x);
    MATRIX_TYPE mean_y = mean(__y);

    Vector *x_min_mean = Matrix_sub_scalar(__x, mean_x);
    Vector *y_min_mean = Matrix_sub_scalar(__y, mean_y);

    Vector *num_arr = Matrix_hadamard(x_min_mean, y_min_mean);

    MATRIX_TYPE out = sum(num_arr) / Vector_size(num_arr);

    Matrix_free(x_min_mean);
    Matrix_free(y_min_mean);
    Matrix_free(num_arr);

    return out;
}

// Attempt to compute the correlation coefficient by using standard scores
MATRIX_TYPE cor(const Matrix *__a, const Matrix *__b) {

    if (! (Matrix_is_vec(__a) && Matrix_is_vec(__b))) return -1; // If they arent both vectors

    // make sure their sizes are the same
    if (Vector_size(__a) != Vector_size(__b)) return -2;

    // Now we need to compute The sum of x minus the mean and the sum
    // of y minus its mean
    return cov(__a, __b) / (std(__a) * std(__b));
}

// Find the kth central moment
MATRIX_TYPE cmoment(const Vector *__v, int __k) {

    // Take the hadamard product of __v minus its mean.
    // Then take the sum and divide by n
    MATRIX_TYPE u_v = mean(__v);
    Vector *v_min_uv = Matrix_sub_scalar(__v, u_v);

    // take the kth hadamard exponential
    mathadexp(v_min_uv, __k);

    MATRIX_TYPE out = sum(v_min_uv) / Vector_size(__v);

    Matrix_free(v_min_uv);

    return out;
}

MATRIX_TYPE rmoment(const Vector *__v, int __k) {

    Vector *v = Matrix_clone(__v);

    mathadexp(v, __k);

    MATRIX_TYPE out = sum(v) / Vector_size(__v);

    Matrix_free(v);

    return out;
}

// Let's do a simple linear regression with respect to an x and y variable
// Return a matrix whose elements are the coefficients a_0, a_1, a_n for an nth
// degree polynomial
Vector *linear_regression(const Vector *__x, const Vector *__y) {

    // We will solve the linear regression problem via the Vandermonde matrix.

    Matrix *V = Matrix_vandermonde_reduced(__x, 1);
    Matrix *Vt = Matrix_transpose(V);
    Vector *y_hat = Matrix_multiply(Vt, __y);
    Matrix *lhs = Matrix_multiply(Vt, V);

    Matrix_reset(&V);
    Matrix_reset(&Vt);

    Vector *a = Matrix_solve_lu(lhs, y_hat);

    Matrix_reset(&y_hat);
    Matrix_reset(&lhs);

    return a;
}

Vector *logistical_regression(const Vector *__x, const Vector *__y) {

    Matrix *logx = map(__x, log);
    return linear_regression(logx, __y);
}


Matrix *runif(int n, double a, double b) {
    return runif_gen(n, a, b, DEFAULT_RNG);
}



Matrix *runif_gen(int n, double a, double b, RNG_FN rng_fn) {

    Matrix *out = Matrix_new(1, n);

    for (int i = 0; i < n; i++) {
        out->data[i] = unifd_rng(a, b, rng_fn);
    }

    return out;
}
