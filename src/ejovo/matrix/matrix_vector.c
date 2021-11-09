// Function definitions for conceptualizing Matrices as column vectors

#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Constructors
 *================================================================================================**/

// Default to making a column vector
Vector *Vector_new(size_t __nrows) {
    return Matrix_new(__nrows, 1);
}

Vector *Vector_rand(size_t __nrows) {
    return Matrix_rand(__nrows, 1);
}

Vector *Vector_random(size_t __nrows, int __min, int __max) {
    return Matrix_random(__nrows, 1, __min, __max);
}

/**================================================================================================
 *!                                        Unary Vector Operators
 *================================================================================================**/

/**================================================================================================
 *!                                        Vector-Scalar Operators
 *================================================================================================**/

/**================================================================================================
 *!                                        Vector-Vector Operators
 *================================================================================================**/

// Take the dot product of __u and __v in place, storing the results in u!
// we are also just assuming that __u and __v are column (OR ROW) vectors of the same size
MATRIX_TYPE vecdot(const Vector *__u, const Vector *__v) {
    MATRIX_TYPE dot = 0;
    for (size_t i = 0; i < __u->nrows; i++) {
        for (size_t j = 0; j < __u->ncols; j++) {
            dot += (*matacc(__u, i, j)) * (*matacc(__v, i, j));
        }
    }
    return dot;
}

MATRIX_TYPE Vector_inner(const Vector *__u, const Vector *__v) {
    // perform the appropriate checks
    if (!Matrix_comp_add(__u, __v)) {
        perror("Vectors are not compatible to take the inner product");
        return -1;
    }

    return vecdot(__u, __v);
}

Vector *vecproject(const Vector *__v, const Vector *__u) {

    MATRIX_TYPE u_v = vecdot(__u, __v);
    MATRIX_TYPE u_u = vecdot(__u, __u);

    return Matrix_mult_scalar(__u, u_v / u_u);

}

// Take vector __v and project it ONTO __u
Vector *Vector_project_onto(const Vector *__v, const Vector *__u) {

    if (!Matrix_comp_add(__v, __u)) {
        perror("Vectors are not compatible to project onto");
        return NULL;
    }
    if (!Matrix_is_vec(__v) || !Matrix_is_vec(__u)) {
        perror("Operands must be row or column vectors");
        return NULL;
    }

    return vecproject(__v, __u);
}


/**================================================================================================
 *!                                        Normalization
 *================================================================================================**/

/**
 * Compute the p-norm of a vector
 *
 * The p-norm of a matrix is defined to be the pth root ( sum of |a_ij|^p )
 *
 */
MATRIX_TYPE vecpnorm(const Vector *__u, const int __p) {

    MATRIX_TYPE sum = 0;
    MATRIX_TYPE *a = NULL;

    for (size_t i = 0; i < __u->nrows; i++) {
        for (size_t j = 0; j < __u->ncols; j++) {
            a = matacc(__u, i, j);
            sum += pow(*a, __p);
        }
    }

    return pow(sum, 1.0 / __p);
}

// Euclidean norm
MATRIX_TYPE vecnorm(const Vector *__A) {

    MATRIX_TYPE sum = 0;
    MATRIX_TYPE *a = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            a = matacc(__A, i, j);
            sum += (*a) * (*a);
        }
    }

    return sqrt(sum);
}

void vecnormalize(Vector *__u) {

    MATRIX_TYPE norm = vecnorm(__u);
    matdivscalar(__u, norm);
}

// Return the norm of a vector (checking bounds?)
MATRIX_TYPE Vector_norm(const Vector *__u) {
    return vecnorm(__u);
}

MATRIX_TYPE Vector_pnorm(const Vector *__u, const size_t __p) {
    return vecpnorm(__u, __p);
}

// return a normalized version of this vector
Vector *Vector_normalize(const Vector *__u) {

    Vector *v = Matrix_clone(__u);

    vecnormalize(v);
    return v;
}

// Take a coliter and compute the pnorm
MATRIX_TYPE ColIter_norm(ColIter *__c) {




}

