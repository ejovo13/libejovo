#ifndef MATRIX_VECTOR_H
#define MATRIX_VECTOR_H

// Function definitions for conceptualizing Matrices as column vectors

#include "matrix.h"

/**================================================================================================
 *!                                        Constructors
 *================================================================================================**/


 TYPED(Vector)*TYPED(vector)(int __count, ...);

// Default to making a column vector
 TYPED(Vector)*TYPED(Vector_new)(size_t __nrows);

 TYPED(Vector)*TYPED(Vector_ones)(size_t __nrows);

 TYPED(Vector)*TYPED(Vector_from_iter)(TYPED(MatIter) __begin, TYPED(MatIter) __end);

 TYPED(Vector)*TYPED(Vector_rand)(size_t __nrows);

 TYPED(Vector)*TYPED(Vector_random)(size_t __nrows, int __min, int __max);

 TYPED(Vector)*TYPED(Vector_from)(const MATRIX_TYPE* __arr, size_t __nrows);

 TYPED(Vector)*TYPED(Vector_clone)(const TYPED(Vector)*__v);

 TYPED(Vector)*TYPED(Vector_from_matrix)(const TYPED(Matrix) *__m);

 TYPED(Vector)*TYPED(Vector_as_col)(const TYPED(Vector)*__v);

 TYPED(Vector)*TYPED(Vector_as_row)(const TYPED(Vector)*__v);

void TYPED(Vector_free)( TYPED(Vector)*__v);

void TYPED(Vector_reset)( TYPED(Vector)**__v);



/**================================================================================================
 *!                                        TYPED(Matrix) to vec functions
 *================================================================================================**/
 TYPED(Vector)*TYPED(Matrix_as_col)(const TYPED(Matrix) *__m);

 TYPED(Vector)*TYPED(Matrix_as_row)(const TYPED(Matrix) *__m);






/**================================================================================================
 *!                                        State Functions
 *================================================================================================**/
size_t TYPED(Vector_size)(const TYPED(Vector)*__v);

void TYPED(Vector_set)( TYPED(Vector)*__v, size_t __pos, MATRIX_TYPE __val);

void TYPED(Vector_set_first)( TYPED(Vector)*__v, MATRIX_TYPE __val);

void TYPED(Vector_set_last)( TYPED(Vector)*__v, MATRIX_TYPE __val);

MATRIX_TYPE TYPED(Vector_first)(const TYPED(Vector)*__v);

MATRIX_TYPE TYPED(Vector_last)(const TYPED(Vector)*__v);

/**================================================================================================
 *!                                        TYPED(Vector)iterator functions
 *================================================================================================**/
TYPED(MatIter) TYPED(Vector_begin)(const TYPED(Vector)*__v);

TYPED(MatIter) TYPED(Vector_end)(const TYPED(Vector)*__v);

// Create a new vector iter starting at the ith position
TYPED(MatIter) TYPED(Vector_iter)(const TYPED(Vector)*__v, size_t i);

MATRIX_TYPE TYPED(Vector_max)(const TYPED(Vector)*__v);

MATRIX_TYPE TYPED(Vector_at)(const TYPED(Vector)*__v, size_t __i);

static inline MATRIX_TYPE TYPED(vecat)(const TYPED(Vector)*__v, size_t i) {
    return __v->data[i];
}

static inline MATRIX_TYPE *TYPED(vecacc)(const TYPED(Vector)*__v, size_t i) {
    return &__v->data[i];
}

static inline void TYPED(vecset)(const TYPED(Vector)*__v, size_t i, MATRIX_TYPE k) {
    __v->data[i] = k;
}

static inline MATRIX_TYPE *TYPED(vecptr)(const TYPED(Vector)*__v, size_t i) {
    return &__v->data[i];
}





MATRIX_TYPE *TYPED(Vector_access)(const TYPED(Vector)*__v, size_t __i);

// More abstract, functional pattern "map"
// apply a function to the objects of a
 TYPED(Vector)*TYPED(Vector_map)(const TYPED(Vector)*__v, TYPED(function) __fn);

MATRIX_TYPE TYPED(Vector_sum)(const TYPED(Vector)*__v);

void TYPED(Vector_print_as_row)(const TYPED(Vector)*__v);

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
MATRIX_TYPE TYPED(vecdot)(const TYPED(Vector)*__u, const TYPED(Vector)*__v);

MATRIX_TYPE TYPED(Vector_inner)(const TYPED(Vector)*__u, const TYPED(Vector)*__v);

 TYPED(Vector)*TYPED(vecproject)(const TYPED(Vector)*__v, const TYPED(Vector)*__u);

// Take vector __v and project it ONTO __u
 TYPED(Vector)*TYPED(Vector_project_onto)(const TYPED(Vector)*__v, const TYPED(Vector)*__u);


/**================================================================================================
 *!                                        Normalization
 *================================================================================================**/

// All of these functions should REALLY REALLY end up in the linear algebra section....

MATRIX_TYPE TYPED(Vector_dot)(const TYPED(Vector)*__u, const TYPED(Vector)*__v);

 TYPED(Vector)*TYPED(Vector_hadamard)(const TYPED(Vector)*__u, const TYPED(Vector)*__v);

TYPED(Matrix) *TYPED(Vector_outer)(const TYPED(Vector)*__u, const TYPED(Vector)*__v);

// Return the orthogonal Projection matrix v * v^T
TYPED(Matrix) *TYPED(Vector_orthogonal_projection)(const TYPED(Vector)*__v);

/**
 * Compute the p-norm of a vector
 *
 * The p-norm of a matrix is defined to be the pth root ( sum of |a_ij|^p )
 *
 */
MATRIX_TYPE TYPED(vecpnorm)(const TYPED(Vector)*__u, const int __p);

// Euclidean norm
// MATRIX_TYPE TYPED(vecnorm)(const TYPED(Vector)*__A);

static inline MATRIX_TYPE TYPED(vecnorm)(const TYPED(Vector)*__A) {

    MATRIX_TYPE sum = 0;

    const size_t n = TYPED(Matrix_size)(__A);

    for (size_t i = 0; i < n; i++) {
        sum += __A->data[i] * __A->data[i];
    }

    // for (size_t i = 0; i < __A->nrows; i++) {
    //     for (size_t j = 0; j < __A->ncols; j++) {
    //         a = TYPED(matacc)(__A, i, j);
    //         sum += (*a) * (*a);
    //     }
    // }

    return sqrt(sum);
}

void TYPED(vecnormalize)( TYPED(Vector)*__u);

// Return the norm of a vector (checking bounds?)
MATRIX_TYPE TYPED(Vector_norm)(const TYPED(Vector)*__u);

MATRIX_TYPE TYPED(Vector_pnorm)(const TYPED(Vector)*__u, const size_t __p);

// return a normalized version of this vector
 TYPED(Vector)*TYPED(Vector_normalize)(const TYPED(Vector)*__u);

// Take a coliter and compute the pnorm
// MATRIX_TYPE TYPED(ColIter_norm)(TYPED(ColIter) *__c);

 TYPED(Vector)*TYPED(ascol)( TYPED(Vector)*__v);

 TYPED(Vector)*TYPED(asrow)( TYPED(Vector)*__v);

MATRIX_TYPE TYPED(Vector_distance)(const TYPED(Vector)*__v, const TYPED(Vector)*__u);

 TYPED(Vector)*TYPED(Vector_difference)(const TYPED(Vector)*__v, const TYPED(Vector)*__u);

#endif