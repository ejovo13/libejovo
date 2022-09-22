// Function definitions for conceptualizing Matrices as column vectors

#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Constructors
 *================================================================================================**/


Vector *vector(int __count, ...) {

    va_list ptr;
    va_start(ptr, __count);

    // allocate a new vector with the alloted elements;
    Vector *v = matalloc(__count, 1);


    double next = va_arg(ptr, double);

    if (__count == 0) return NULL;


    for (int i = 0; i < __count; i++) {
        v->data[i] = next;
        next = va_arg(ptr, double);
    }

    return v;
}

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


Vector *Vector_from(const double* __arr, size_t __nrows) {
    return Matrix_from(__arr, __nrows, 1);
}

// Return a COLUMN vector whose elements are the row-major components of __m
Vector *Vector_from_matrix(const Matrix *__m) {
    return Vector_as_col(__m);
}

Vector *Vector_clone(const Vector *__v) {
    return Matrix_clone(__v);
}

Vector *Vector_as_col(const Vector *__v) {
    Vector *v = Vector_clone(__v);
    return ascol(v);
}

Vector *Vector_as_row(const Vector *__v) {
    Vector *v = Vector_clone(__v);
    return asrow(v);
}

Vector *Vector_rand(size_t __nrows) {
    return Matrix_rand(__nrows, 1);
}

Vector *Vector_random(size_t __nrows, int __min, int __max) {
    return Matrix_random(__nrows, 1, __min, __max);
}

void Vector_free(Vector *__v) {
    Matrix_free(__v);
}

void Vector_reset(Vector **__v) {
    Matrix_reset(__v);
}


/**================================================================================================
 *!                                        Matrix to vec functions
 *================================================================================================**/
Vector *Matrix_as_col(const Matrix *__m) {
    return Vector_as_col(__m);
}

Vector *Matrix_as_row(const Matrix *__m) {
    return Vector_as_row(__m);
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
MatIter Vector_begin(const Vector *__v) {
    return MatIter_new(matacc(__v, 0, 0), 1);
}

MatIter Vector_end(const Vector *__v) {
    return MatIter_new(Vector_access(__v, Vector_size(__v)), 1);
}

MatIter Vector_iter(const Vector *__v, size_t __i) {
    MatIter it = {.ptr = Vector_access(__v, __i), .ptr_diff = 1};
    return it;
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

MATRIX_TYPE Vector_max(const Vector *__v) {
    return Matrix_iter_max(__v);
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

MATRIX_TYPE Vector_dot(const Vector *__u, const Vector *__v) {
    return Vector_inner(__u, __v);
}

Vector *Vector_hadamard(const Vector *__u, const Vector *__v) {

    // Create new matrix
    Vector *new = Vector_clone(__u);

    MatIter u_it = Vector_begin(__u);
    MatIter v_it = Vector_begin(__v);
    MatIter new_it = Vector_begin(new);

    const MatIter end = Vector_end(__u);

    for (u_it; !MatIter_cmp(u_it, end); u_it = MatIter_next(u_it), v_it = MatIter_next(v_it), new_it = MatIter_next(new_it)) {
        MatIter_set(new_it, MatIter_value(u_it) * MatIter_value(v_it));
    }

    return new;
}

MATRIX_TYPE Vector_inner(const Vector *__u, const Vector *__v) {
    // perform the appropriate checks
    if (!Matrix_comp_add(__u, __v)) {
        perror("Vectors are not compatible to take the inner product");
        return -1;
    }

    return vecdot(__u, __v);
}

// Compute the outer product u * v_T
Matrix *Vector_outer(const Vector *__u, const Vector *__v) {

    // This is really costly but fuck it I'm just gonna allocate two new vectors so I
    // dont have to footsy about with "is_col" logic

    // A more efficient implementation wouldn't worry about rows and
    // columns and would just copy u as the rows of the output
    // and then apply across the rows an iterator of __v.

    // But ima just do this:

    Vector *u = Vector_as_col(__u);
    Vector *v = Vector_as_row(__v);

    Matrix *out = Matrix_multiply(u, v);

    Matrix_reset(&u);
    Matrix_reset(&v);

    return out;
}

Matrix *Vector_orthogonal_projection(const Vector *__v) {

    Matrix *v_norm = Vector_normalize(__v);

    Matrix *outer = Vector_outer(v_norm, v_norm);

    Matrix_reset(&v_norm);

    return outer;
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

    const size_t size = Matrix_size(__v);

    __v->ncols = 1;
    __v->nrows = size;

    return __v;
}

// modify this vector in place so that it is a column vector (n rows, 1 col)
Vector *asrow(Vector *__v) {

    const size_t size = Matrix_size(__v);

    __v->ncols = size;
    __v->nrows = 1;

    return __v;
}