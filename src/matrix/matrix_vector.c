// Function definitions for conceptualizing Matrices as column vectors

#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Constructors
 *================================================================================================**/


Vector *vector(int __count, ...) {

    va_list ptr;
    va_start(ptr, __count);

    // allocate a new vector with the alloted elements;
    Vector *v = MAT_FN(alloc)(__count, 1);


    double next = va_arg(ptr, double);

    if (__count == 0) return NULL;


    for (int i = 0; i < __count; i++) {
        v->data[i] = next;
        next = va_arg(ptr, double);
    }

    return v;
}

// Default to making a column vector
Vector *VECTOR_FN(new)(size_t __nrows) {
    return MATRIX_FN(new)(__nrows, 1);
}

Vector *VECTOR_FN(ones)(size_t __nrows) {
    return MATRIX_FN(ones)(__nrows, 1);
}

Vector *VECTOR_FN(from_iter)(MATITER_T __begin, MATITER_T __end) {
    size_t len = MATITER_FN(length)(__begin, __end);
    Vector *v = VECTOR_FN(new)(len);

    MATITER_FN(row_set_iter)(VECTOR_FN(begin)(v), VECTOR_FN(end)(v), __begin);
    return v;
}

Vector *VECTOR_FN(from)(const double* __arr, size_t __nrows) {
    return MATRIX_FN(from)(__arr, __nrows, 1);
}

// Return a COLUMN vector whose elements are the row-major components of __m
Vector *VECTOR_FN(from_matrix)(const MATRIX_T *__m) {
    return VECTOR_FN(as_col)(__m);
}

Vector *VECTOR_FN(clone)(const Vector *__v) {
    return MATRIX_FN(clone)(__v);
}

Vector *VECTOR_FN(as_col)(const Vector *__v) {
    Vector *v = VECTOR_FN(clone)(__v);
    return ascol(v);
}

Vector *VECTOR_FN(as_row)(const Vector *__v) {
    Vector *v = VECTOR_FN(clone)(__v);
    return asrow(v);
}

Vector *VECTOR_FN(rand)(size_t __nrows) {
    return MATRIX_FN(rand)(__nrows, 1);
}

Vector *VECTOR_FN(random)(size_t __nrows, int __min, int __max) {
    return MATRIX_FN(random)(__nrows, 1, __min, __max);
}

void VECTOR_FN(free)(Vector *__v) {
    MATRIX_FN(free)(__v);
}

void VECTOR_FN(reset)(Vector **__v) {
    MATRIX_FN(reset)(__v);
}


/**================================================================================================
 *!                                        MATRIX_T to vec functions
 *================================================================================================**/
Vector *MATRIX_FN(as_col)(const MATRIX_T *__m) {
    return VECTOR_FN(as_col)(__m);
}

Vector *MATRIX_FN(as_row)(const MATRIX_T *__m) {
    return VECTOR_FN(as_row)(__m);
}


/**================================================================================================
 *!                                        State Functions
 *================================================================================================**/
size_t VECTOR_FN(size)(const Vector *__v) {
    if (MATRIX_FN(is_col)(__v)) return __v->nrows;
    else return __v->ncols;
}

void VECTOR_FN(set)(Vector *__v, size_t __pos, MATRIX_TYPE __val) {
    if (MATRIX_FN(is_col)(__v)) MATRIX_FN(set)(__v, __pos, 0, __val); else MATRIX_FN(set)(__v, 0, __pos, __val);
}

void VECTOR_FN(set_first)(Vector *__v, MATRIX_TYPE __val) {
    VECTOR_FN(set)(__v, 0, __val);
}

void VECTOR_FN(set_last)(Vector *__v, MATRIX_TYPE __val) {
    VECTOR_FN(set)(__v, VECTOR_FN(size)(__v) - 1, __val);
}

MATRIX_TYPE VECTOR_FN(first)(const Vector *__v) {
    return MAT_FN(at)(__v, 0, 0);
}

MATRIX_TYPE VECTOR_FN(last)(const Vector *__v) {
    return VECTOR_FN(at)(__v, VECTOR_FN(size)(__v) - 1);
}

/**================================================================================================
 *!                                        Vector iterator functions
 *================================================================================================**/
MATITER_T VECTOR_FN(begin)(const Vector *__v) {
    return MATITER_FN(new)(MAT_FN(acc)(__v, 0, 0), 1);
}

MATITER_T VECTOR_FN(end)(const Vector *__v) {
    return MATITER_FN(new)(VECTOR_FN(access)(__v, VECTOR_FN(size)(__v)), 1);
}

MATITER_T VECTOR_FN(iter)(const Vector *__v, size_t __i) {
    MATITER_T it = {.ptr = VECTOR_FN(access)(__v, __i), .ptr_diff = 1};
    return it;
}

MATRIX_TYPE VECTOR_FN(at)(const Vector *__v, size_t __i) {
    if (MATRIX_FN(is_col)(__v)) return MAT_FN(at)(__v, __i, 0);
    else return MAT_FN(at)(__v, 0, __i);
}

MATRIX_TYPE *VECTOR_FN(access)(const Vector *__v, size_t __i) {
    if (MATRIX_FN(is_col)(__v)) return MAT_FN(acc)(__v, __i, 0);
    else return MAT_FN(acc)(__v, 0, __i);
}

// More abstract, functional pattern "map"
// apply a function to the objects of a
Vector *VECTOR_FN(map)(const Vector *__v, function __fn) {
    Vector *v_mapped = MATRIX_FN(clone)(__v);
    for (int i = 0; i < VECTOR_FN(size)(__v); i++) {
        VECTOR_FN(set)(v_mapped, i, __fn(VECTOR_FN(at)(__v, i)));
    }
    return v_mapped;
}

MATRIX_TYPE VECTOR_FN(max)(const Vector *__v) {
    return MATRIX_FN(iter_max)(__v);
}

MATRIX_TYPE VECTOR_FN(sum)(const Vector *__v) {
    MATRIX_TYPE sum = 0;
    for (size_t i = 0; i < VECTOR_FN(size)(__v); i++) {
        sum += VECTOR_FN(at)(__v, i);
    }
    return sum;
}

void VECTOR_FN(print_as_row)(const Vector *__v) {
    printf("| ");
    for (size_t i = 0; i < VECTOR_FN(size)(__v); i++) {
        printf("%4.4lf ", VECTOR_FN(at)(__v, i));
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
            dot += (*MAT_FN(acc)(__u, i, j)) * (*MAT_FN(acc)(__v, i, j));
        }
    }
    return dot;
}

MATRIX_TYPE VECTOR_FN(dot)(const Vector *__u, const Vector *__v) {
    return VECTOR_FN(inner)(__u, __v);
}

Vector *VECTOR_FN(hadamard)(const Vector *__u, const Vector *__v) {

    // Create new matrix
    Vector *new = VECTOR_FN(clone)(__u);

    MATITER_T u_it = VECTOR_FN(begin)(__u);
    MATITER_T v_it = VECTOR_FN(begin)(__v);
    MATITER_T new_it = VECTOR_FN(begin)(new);

    const MATITER_T end = VECTOR_FN(end)(__u);

    for (u_it; !MATITER_FN(cmp)(u_it, end); u_it = MATITER_FN(next)(u_it), v_it = MATITER_FN(next)(v_it), new_it = MATITER_FN(next)(new_it)) {
        MATITER_FN(set)(new_it, MATITER_FN(value)(u_it) * MATITER_FN(value)(v_it));
    }

    return new;
}

MATRIX_TYPE VECTOR_FN(inner)(const Vector *__u, const Vector *__v) {
    // perform the appropriate checks
    if (!MATRIX_FN(comp_add)(__u, __v)) {
        perror("Vectors are not compatible to take the inner product");
        return -1;
    }

    return vecdot(__u, __v);
}

// Compute the outer product u * v_T
MATRIX_T *VECTOR_FN(outer)(const Vector *__u, const Vector *__v) {

    // This is really costly but fuck it I'm just gonna allocate two new vectors so I
    // dont have to footsy about with "is_col" logic

    // A more efficient implementation wouldn't worry about rows and
    // columns and would just copy u as the rows of the output
    // and then apply across the rows an iterator of __v.

    // But ima just do this:

    Vector *u = VECTOR_FN(as_col)(__u);
    Vector *v = VECTOR_FN(as_row)(__v);

    MATRIX_T *out = MATRIX_FN(multiply)(u, v);

    MATRIX_FN(reset)(&u);
    MATRIX_FN(reset)(&v);

    return out;
}

MATRIX_T *VECTOR_FN(orthogonal_projection)(const Vector *__v) {

    MATRIX_T *v_norm = VECTOR_FN(normalize)(__v);

    MATRIX_T *outer = VECTOR_FN(outer)(v_norm, v_norm);

    MATRIX_FN(reset)(&v_norm);

    return outer;
}

Vector *vecproject(const Vector *__v, const Vector *__u) {

    MATRIX_TYPE u_v = vecdot(__u, __v);
    MATRIX_TYPE u_u = vecdot(__u, __u);

    return MATRIX_FN(mult_scalar)(__u, u_v / u_u);

}

// Take vector __v and project it ONTO __u
Vector *VECTOR_FN(project_onto)(const Vector *__v, const Vector *__u) {

    if (!MATRIX_FN(comp_add)(__v, __u)) {
        perror("Vectors are not compatible to project onto");
        return NULL;
    }
    if (!MATRIX_FN(is_vec)(__v) || !MATRIX_FN(is_vec)(__u)) {
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
            a = MAT_FN(acc)(__u, i, j);
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
            a = MAT_FN(acc)(__A, i, j);
            sum += (*a) * (*a);
        }
    }

    return sqrt(sum);
}

void vecnormalize(Vector *__u) {

    MATRIX_TYPE norm = vecnorm(__u);
    MAT_FN(divscalar)(__u, norm);
}

// Return the norm of a vector (checking bounds?)
MATRIX_TYPE VECTOR_FN(norm)(const Vector *__u) {
    return vecnorm(__u);
}

MATRIX_TYPE VECTOR_FN(pnorm)(const Vector *__u, const size_t __p) {
    return vecpnorm(__u, __p);
}

// return a normalized version of this vector
Vector *VECTOR_FN(normalize)(const Vector *__u) {

    Vector *v = MATRIX_FN(clone)(__u);

    vecnormalize(v);
    return v;
}

// Take a coliter and compute the pnorm
MATRIX_TYPE ColIter_norm(ColIter *__c) {




}

// Resizing/reorienting
// modify this vector in place so that it is a column vector (n rows, 1 col)
Vector *ascol(Vector *__v) {

    const size_t size = MATRIX_FN(size)(__v);

    __v->ncols = 1;
    __v->nrows = size;

    return __v;
}

// modify this vector in place so that it is a column vector (n rows, 1 col)
Vector *asrow(Vector *__v) {

    const size_t size = MATRIX_FN(size)(__v);

    __v->ncols = size;
    __v->nrows = 1;

    return __v;
}


// Find the difference between vectors that are the same size.
Vector *VECTOR_FN(difference)(const Vector *__v, const Vector *__u) {
    if (MATRIX_FN(size)(__v) != MATRIX_FN(size)(__u));
    return MATITER_FN(difference)(VECTOR_FN(begin)(__v), VECTOR_FN(end)(__v), VECTOR_FN(begin)(__u));
}

// Find the EUCLIDEAN DISTANCE between two vectors. Returns -1 if the vectors are not the same size
MATRIX_TYPE VECTOR_FN(distance)(const Vector *__v, const Vector *__u) {
    Vector *diff = VECTOR_FN(difference)(__v, __u);

    MATRIX_TYPE dist = VECTOR_FN(norm)(diff);
    MATRIX_FN(reset)(&diff);

    return dist;
}






