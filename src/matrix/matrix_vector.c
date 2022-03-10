// Function definitions for conceptualizing Matrices as column vectors

#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Constructors
 *================================================================================================**/

// Default to making a column vector
Vector *Vector_new(size_t __nrows) {
    return Matrix_new(__nrows, 1);
}

Vector *Vector_from_iter(MatIter __begin, MatIter __end) {
    size_t len = MatIter_length(__begin, __end);
    Vector *v = Vector_new(len);

    MatIter_row_set_iter(Vector_begin(v), Vector_end(v), __begin);
    return v;
}

Vector *Vector_rand(size_t __nrows) {
    return Matrix_rand(__nrows, 1);
}

Vector *Vector_random(size_t __nrows, int __min, int __max) {
    return Matrix_random(__nrows, 1, __min, __max);
}

/**================================================================================================
 *!                                        State Functions
 *================================================================================================**/
size_t Vector_size(const Vector *__v) {
    if (Matrix_is_col(__v)) return __v->nrows;
    else return __v->ncols;
}

void Vector_set(Vector *__v, size_t __pos, MATRIX_TYPE __val) {
    if (Matrix_is_col(__v)) Matrix_set(__v, __pos, 0, __val); else Matrix_set(__v, 0, __pos, __val);
}

void Vector_set_first(Vector *__v, MATRIX_TYPE __val) {
    Vector_set(__v, 0, __val);
}

void Vector_set_last(Vector *__v, MATRIX_TYPE __val) {
    Vector_set(__v, Vector_size(__v) - 1, __val);
}

MATRIX_TYPE Vector_first(const Vector *__v) {
    return matat(__v, 0, 0);
}

MATRIX_TYPE Vector_last(const Vector *__v) {
    return Vector_at(__v, Vector_size(__v) - 1);
}

/**================================================================================================
 *!                                        Vector iterator functions
 *================================================================================================**/
MatIter Vector_begin(Vector *__v) {
    return MatIter_new(matacc(__v, 0, 0), 1);
}

MatIter Vector_end(Vector *__v) {
    return MatIter_new(Vector_access(__v, Vector_size(__v)), 1);
}

MATRIX_TYPE Vector_at(const Vector *__v, size_t __i) {
    if (Matrix_is_col(__v)) return matat(__v, __i, 0);
    else return matat(__v, 0, __i);
}

MATRIX_TYPE *Vector_access(const Vector *__v, size_t __i) {
    if (Matrix_is_col(__v)) return matacc(__v, __i, 0);
    else return matacc(__v, 0, __i);
}

// More abstract, functional pattern "map"
// apply a function to the objects of a
Vector *Vector_map(const Vector *__v, function __fn) {
    Vector *v_mapped = Matrix_clone(__v);
    for (int i = 0; i < Vector_size(__v); i++) {
        Vector_set(v_mapped, i, __fn(Vector_at(__v, i)));
    }
    return v_mapped;
}

MATRIX_TYPE Vector_sum(const Vector *__v) {
    MATRIX_TYPE sum = 0;
    for (size_t i = 0; i < Vector_size(__v); i++) {
        sum += Vector_at(__v, i);
    }
    return sum;
}

void Vector_print_as_row(const Vector *__v) {
    printf("| ");
    for (size_t i = 0; i < Vector_size(__v); i++) {
        printf("%4.4lf ", Vector_at(__v, i));
    }
    printf("|\n");
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

// Resizing/reorienting
// modify this vector in place so that it is a column vector (n rows, 1 col)
Vector *ascol(Vector *__v) {

    // Verify that __v is a vector
    if (!Matrix_is_vec(__v)) return NULL;

    const size_t size = Matrix_size(__v);

    __v->ncols = 1;
    __v->nrows = size;

    return __v;
}

// modify this vector in place so that it is a column vector (n rows, 1 col)
Vector *asrow(Vector *__v) {

    // Verify that __v is a vector
    if (!Matrix_is_vec(__v)) return NULL;

    const size_t size = Matrix_size(__v);

    __v->ncols = size;
    __v->nrows = 1;

    return __v;
}