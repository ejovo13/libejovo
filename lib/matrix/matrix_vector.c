// Function definitions for conceptualizing Matrices as column vectors

// #include "ejovo_matrix_generic.h"
#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Constructors
 *================================================================================================**/

#ifdef MATRIX_DOUBLE

 TYPED(Vector)*TYPED(vector)(int __count, ...) {

    va_list ptr;
    va_start(ptr, __count);

    // allocate a new vector with the alloted elements;
    TYPED(Vector)*v = TYPED(matalloc)(__count, 1);


    MATRIX_TYPE next = va_arg(ptr, MATRIX_TYPE);

    if (__count == 0) return NULL;


    for (int i = 0; i < __count; i++) {
        v->data[i] = next;
        next = va_arg(ptr, MATRIX_TYPE);
    }

    return v;
}

#endif

// Default to making a column vector
 TYPED(Vector)*TYPED(Vector_new)(size_t __nrows) {
    return TYPED(Matrix_new)(__nrows, 1);
}

 TYPED(Vector)*TYPED(Vector_ones)(size_t __nrows) {
    return TYPED(Matrix_ones)(__nrows, 1);
}

 TYPED(Vector)*TYPED(Vector_from_iter)(TYPED(MatIter) __begin, TYPED(MatIter) __end) {
    size_t len = TYPED(MatIter_length)(__begin, __end);
    TYPED(Vector)*v = TYPED(Vector_new)(len);

    TYPED(MatIter_row_set_iter)(TYPED(Vector_begin)(v), TYPED(Vector_end)(v), __begin);
    return v;
}

 TYPED(Vector)*TYPED(Vector_from)(const MATRIX_TYPE* __arr, size_t __nrows) {
    return TYPED(Matrix_from)(__arr, __nrows, 1);
}

// Return a COLUMN vector whose elements are the row-major components of __m
 TYPED(Vector)*TYPED(Vector_from_matrix)(const TYPED(Matrix) *__m) {
    return TYPED(Vector_as_col)(__m);
}

 TYPED(Vector)*TYPED(Vector_clone)(const TYPED(Vector)*__v) {
    return TYPED(Matrix_clone)(__v);
}

 TYPED(Vector)*TYPED(Vector_as_col)(const TYPED(Vector)*__v) {
    TYPED(Vector)*v = TYPED(Vector_clone)(__v);
    return TYPED(ascol)(v);
}

 TYPED(Vector)*TYPED(Vector_as_row)(const TYPED(Vector)*__v) {
    TYPED(Vector)*v = TYPED(Vector_clone)(__v);
    return TYPED(asrow)(v);
}

 TYPED(Vector)*TYPED(Vector_rand)(size_t __nrows) {
    return TYPED(Matrix_rand)(__nrows, 1);
}

 TYPED(Vector)*TYPED(Vector_random)(size_t __nrows, int __min, int __max) {
    return TYPED(Matrix_random)(__nrows, 1, __min, __max);
}

void TYPED(Vector_free)( TYPED(Vector)*__v) {
    TYPED(Matrix_free)(__v);
}

void TYPED(Vector_reset)( TYPED(Vector)**__v) {
    TYPED(Matrix_reset)(__v);
}


/**================================================================================================
 *!                                        TYPED(Matrix) to vec functions
 *================================================================================================**/
 TYPED(Vector)*TYPED(Matrix_as_col)(const TYPED(Matrix) *__m) {
    return TYPED(Vector_as_col)(__m);
}

 TYPED(Vector)*TYPED(Matrix_as_row)(const TYPED(Matrix) *__m) {
    return TYPED(Vector_as_row)(__m);
}


/**================================================================================================
 *!                                        State Functions
 *================================================================================================**/
size_t TYPED(Vector_size)(const TYPED(Vector)*__v) {
    if (TYPED(Matrix_is_col)(__v)) return __v->nrows;
    else return __v->ncols;
}

void TYPED(Vector_set)( TYPED(Vector)*__v, size_t __pos, MATRIX_TYPE __val) {
    if (TYPED(Matrix_is_col)(__v)) TYPED(Matrix_set)(__v, __pos, 0, __val); else TYPED(Matrix_set)(__v, 0, __pos, __val);
}

void TYPED(Vector_set_first)( TYPED(Vector)*__v, MATRIX_TYPE __val) {
    TYPED(Vector_set)(__v, 0, __val);
}

void TYPED(Vector_set_last)( TYPED(Vector)*__v, MATRIX_TYPE __val) {
    TYPED(Vector_set)(__v, TYPED(Vector_size)(__v) - 1, __val);
}

MATRIX_TYPE TYPED(Vector_first)(const TYPED(Vector)*__v) {
    return TYPED(matat)(__v, 0, 0);
}

MATRIX_TYPE TYPED(Vector_last)(const TYPED(Vector)*__v) {
    return TYPED(Vector_at)(__v, TYPED(Vector_size)(__v) - 1);
}

/**================================================================================================
 *!                                        TYPED(Vector)iterator functions
 *================================================================================================**/
TYPED(MatIter) TYPED(Vector_begin)(const TYPED(Vector)*__v) {
    return TYPED(MatIter_new)(TYPED(matacc)(__v, 0, 0), 1);
}

TYPED(MatIter) TYPED(Vector_end)(const TYPED(Vector)*__v) {
    return TYPED(MatIter_new)(TYPED(Vector_access)(__v, TYPED(Vector_size)(__v)), 1);
}

TYPED(MatIter) TYPED(Vector_iter)(const TYPED(Vector)*__v, size_t __i) {
    TYPED(MatIter) it = {.ptr = TYPED(Vector_access)(__v, __i), .ptr_diff = 1};
    return it;
}

MATRIX_TYPE TYPED(Vector_at)(const TYPED(Vector)*__v, size_t __i) {
    if (TYPED(Matrix_is_col)(__v)) return TYPED(matat)(__v, __i, 0);
    else return TYPED(matat)(__v, 0, __i);
}

MATRIX_TYPE *TYPED(Vector_access)(const TYPED(Vector)*__v, size_t __i) {
    if (TYPED(Matrix_is_col)(__v)) return TYPED(matacc)(__v, __i, 0);
    else return TYPED(matacc)(__v, 0, __i);
}

// More abstract, functional pattern "map"
// apply a function to the objects of a
 TYPED(Vector)*TYPED(Vector_map)(const TYPED(Vector)*__v, TYPED(function) __fn) {
    TYPED(Vector)*v_mapped = TYPED(Matrix_clone)(__v);
    for (size_t i = 0; i < TYPED(Vector_size)(__v); i++) {
        TYPED(Vector_set)(v_mapped, i, __fn(TYPED(Vector_at)(__v, i)));
    }
    return v_mapped;
}

MATRIX_TYPE TYPED(Vector_max)(const TYPED(Vector)*__v) {
    return TYPED(Matrix_iter_max)(__v);
}

MATRIX_TYPE TYPED(Vector_sum)(const TYPED(Vector)*__v) {
    MATRIX_TYPE sum = 0;
    for (size_t i = 0; i < TYPED(Vector_size)(__v); i++) {
        sum += TYPED(Vector_at)(__v, i);
    }
    return sum;
}

void TYPED(Vector_print_as_row)(const TYPED(Vector)*__v) {
    printf("| ");
    for (size_t i = 0; i < TYPED(Vector_size)(__v); i++) {
        // printf("%4.4lf ", TYPED(Vector_at)(__v, i));
        TYPED(print_el)(__v->data[i]);
    }
    printf("|\n");
}

/**================================================================================================
 *!                                        Unary TYPED(Vector)Operators
 *================================================================================================**/

/**================================================================================================
 *!                                        Vector-Scalar Operators
 *================================================================================================**/

/**================================================================================================
 *!                                        Vector- TYPED(Vector)Operators
 *================================================================================================**/

// Take the dot product of __u and __v in place, storing the results in u!
// we are also just assuming that __u and __v are column (OR ROW) vectors of the same size
MATRIX_TYPE TYPED(vecdot)(const TYPED(Vector)*__u, const TYPED(Vector)*__v) {
    MATRIX_TYPE dot = 0;
    for (size_t i = 0; i < __u->nrows; i++) {
        for (size_t j = 0; j < __u->ncols; j++) {
            dot += (*TYPED(matacc)(__u, i, j)) * (*TYPED(matacc)(__v, i, j));
        }
    }
    return dot;
}

MATRIX_TYPE TYPED(Vector_dot)(const TYPED(Vector)*__u, const TYPED(Vector)*__v) {
    return TYPED(Vector_inner)(__u, __v);
}

 TYPED(Vector)*TYPED(Vector_hadamard)(const TYPED(Vector)*__u, const TYPED(Vector)*__v) {

    // Create new matrix
    TYPED(Vector)*new = TYPED(Vector_clone)(__u);

    TYPED(MatIter) u_it = TYPED(Vector_begin)(__u);
    TYPED(MatIter) v_it = TYPED(Vector_begin)(__v);
    TYPED(MatIter) new_it = TYPED(Vector_begin)(new);

    const TYPED(MatIter) end = TYPED(Vector_end)(__u);

    for (; !TYPED(MatIter_cmp)(u_it, end); u_it = TYPED(MatIter_next)(u_it), v_it = TYPED(MatIter_next)(v_it), new_it = TYPED(MatIter_next)(new_it)) {
        TYPED(MatIter_set)(new_it, TYPED(MatIter_value)(u_it) * TYPED(MatIter_value)(v_it));
    }

    return new;
}

MATRIX_TYPE TYPED(Vector_inner)(const TYPED(Vector)*__u, const TYPED(Vector)*__v) {
    // perform the appropriate checks
    if (!TYPED(Matrix_comp_add)(__u, __v)) {
        perror("Vectors are not compatible to take the inner product");
        return -1;
    }

    return TYPED(vecdot)(__u, __v);
}

// Compute the outer product u * v_T
TYPED(Matrix) *TYPED(Vector_outer)(const TYPED(Vector)*__u, const TYPED(Vector)*__v) {

    // This is really costly but fuck it I'm just gonna allocate two new vectors so I
    // dont have to footsy about with "is_col" logic

    // A more efficient implementation wouldn't worry about rows and
    // columns and would just copy u as the rows of the output
    // and then apply across the rows an iterator of __v.

    // But ima just do this:

    TYPED(Vector)*u = TYPED(Vector_as_col)(__u);
    TYPED(Vector)*v = TYPED(Vector_as_row)(__v);

    TYPED(Matrix) *out = TYPED(Matrix_multiply)(u, v);

    TYPED(Matrix_reset)(&u);
    TYPED(Matrix_reset)(&v);

    return out;
}

TYPED(Matrix) *TYPED(Vector_orthogonal_projection)(const TYPED(Vector)*__v) {

    TYPED(Matrix) *v_norm = TYPED(Vector_normalize)(__v);

    TYPED(Matrix) *outer = TYPED(Vector_outer)(v_norm, v_norm);

    TYPED(Matrix_reset)(&v_norm);

    return outer;
}

 TYPED(Vector)*TYPED(vecproject)(const TYPED(Vector)*__v, const TYPED(Vector)*__u) {

    MATRIX_TYPE u_v = TYPED(vecdot)(__u, __v);
    MATRIX_TYPE u_u = TYPED(vecdot)(__u, __u);

    return TYPED(Matrix_mult_scalar)(__u, u_v / u_u);

}

// Take vector __v and project it ONTO __u
 TYPED(Vector)*TYPED(Vector_project_onto)(const TYPED(Vector)*__v, const TYPED(Vector)*__u) {

    if (!TYPED(Matrix_comp_add)(__v, __u)) {
        perror("Vectors are not compatible to project onto");
        return NULL;
    }
    if (!TYPED(Matrix_is_vec)(__v) || !TYPED(Matrix_is_vec)(__u)) {
        perror("Operands must be row or column vectors");
        return NULL;
    }

    return TYPED(vecproject)(__v, __u);
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
MATRIX_TYPE TYPED(vecpnorm)(const TYPED(Vector)*__u, const int __p) {

    MATRIX_TYPE sum = 0;
    MATRIX_TYPE *a = NULL;

    for (size_t i = 0; i < __u->nrows; i++) {
        for (size_t j = 0; j < __u->ncols; j++) {
            a = TYPED(matacc)(__u, i, j);
            sum += pow(*a, __p);
        }
    }

    return pow(sum, 1.0 / __p);
}

// Euclidean norm
// MATRIX_TYPE TYPED(vecnorm)(const TYPED(Vector)*__A) {

//     MATRIX_TYPE sum = 0;

//     const size_t n = TYPED(Matrix_size)(__A);

//     for (size_t i = 0; i < n; i++) {
//         sum += __A->data[i] * __A->data[i];
//     }

//     // for (size_t i = 0; i < __A->nrows; i++) {
//     //     for (size_t j = 0; j < __A->ncols; j++) {
//     //         a = TYPED(matacc)(__A, i, j);
//     //         sum += (*a) * (*a);
//     //     }
//     // }

//     return sqrt(sum);
// }

void TYPED(vecnormalize)( TYPED(Vector)*__u) {

    MATRIX_TYPE norm = TYPED(vecnorm)(__u);
    TYPED(matdivscalar)(__u, norm);
}

// Return the norm of a vector (checking bounds?)
MATRIX_TYPE TYPED(Vector_norm)(const TYPED(Vector)*__u) {
    return TYPED(vecnorm)(__u);
}

MATRIX_TYPE TYPED(Vector_pnorm)(const TYPED(Vector)*__u, const size_t __p) {
    return TYPED(vecpnorm)(__u, __p);
}

// return a normalized version of this vector
 TYPED(Vector)*TYPED(Vector_normalize)(const TYPED(Vector)*__u) {

    TYPED(Vector)*v = TYPED(Matrix_clone)(__u);

    TYPED(vecnormalize)(v);
    return v;
}

// // Take a coliter and compute the pnorm
// MATRIX_TYPE TYPED(ColIter_norm)(TYPED(ColIter) *__c) {
    




// }

// Resizing/reorienting
// modify this vector in place so that it is a column vector (n rows, 1 col)
 TYPED(Vector)*TYPED(ascol)( TYPED(Vector)*__v) {

    const size_t size = TYPED(Matrix_size)(__v);

    __v->ncols = 1;
    __v->nrows = size;

    return __v;
}

// modify this vector in place so that it is a column vector (n rows, 1 col)
 TYPED(Vector)*TYPED(asrow)( TYPED(Vector)*__v) {

    const size_t size = TYPED(Matrix_size)(__v);

    __v->ncols = size;
    __v->nrows = 1;

    return __v;
}


// Find the difference between vectors that are the same size.
 TYPED(Vector)*TYPED(Vector_difference)(const TYPED(Vector)*__v, const TYPED(Vector)*__u) {
    assert(TYPED(Matrix_size)(__v) == TYPED(Matrix_size)(__u));
    return TYPED(MatIter_difference)(TYPED(Vector_begin)(__v), TYPED(Vector_end)(__v), TYPED(Vector_begin)(__u));
}

// Find the EUCLIDEAN DISTANCE between two vectors. Returns -1 if the vectors are not the same size
MATRIX_TYPE TYPED(Vector_distance)(const TYPED(Vector)*__v, const TYPED(Vector)*__u) {
    TYPED(Vector)*diff = TYPED(Vector_difference)(__v, __u);

    MATRIX_TYPE dist = TYPED(Vector_norm)(diff);
    TYPED(Matrix_reset)(&diff);

    return dist;
}






