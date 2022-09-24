#ifndef MATRIX_VECTOR_H
#define MATRIX_VECTOR_H

// Function definitions for conceptualizing Matrices as column vectors

#include "matrix.h"

/**================================================================================================
 *!                                        Constructors
 *================================================================================================**/


Vector *TYPED_FN(vector)(int __count, ...);

// Default to making a column vector
Vector *VECTOR_FN(new)(size_t __nrows);

Vector *VECTOR_FN(ones)(size_t __nrows);

Vector *VECTOR_FN(from_iter)(MATITER_T __begin, MATITER_T __end);

Vector *VECTOR_FN(rand)(size_t __nrows);

Vector *VECTOR_FN(random)(size_t __nrows, int __min, int __max);

Vector *VECTOR_FN(from)(const double* __arr, size_t __nrows);

Vector *VECTOR_FN(clone)(const Vector *__v);

Vector *VECTOR_FN(from_matrix)(const MATRIX_T *__m);

Vector *VECTOR_FN(as_col)(const Vector *__v);

Vector *VECTOR_FN(as_row)(const Vector *__v);

void VECTOR_FN(free)(Vector *__v);

void VECTOR_FN(reset)(Vector **__v);



/**================================================================================================
 *!                                        MATRIX_T to vec functions
 *================================================================================================**/
Vector *MATRIX_FN(as_col)(const MATRIX_T *__m);

Vector *MATRIX_FN(as_row)(const MATRIX_T *__m);






/**================================================================================================
 *!                                        State Functions
 *================================================================================================**/
size_t VECTOR_FN(size)(const Vector *__v);

void VECTOR_FN(set)(Vector *__v, size_t __pos, MATRIX_TYPE __val);

void VECTOR_FN(set_first)(Vector *__v, MATRIX_TYPE __val);

void VECTOR_FN(set_last)(Vector *__v, MATRIX_TYPE __val);

MATRIX_TYPE VECTOR_FN(first)(const Vector *__v);

MATRIX_TYPE VECTOR_FN(last)(const Vector *__v);

/**================================================================================================
 *!                                        Vector iterator functions
 *================================================================================================**/
MATITER_T VECTOR_FN(begin)(const Vector *__v);

MATITER_T VECTOR_FN(end)(const Vector *__v);

// Create a new vector iter starting at the ith position
MATITER_T VECTOR_FN(iter)(const Vector *__v, size_t i);

MATRIX_TYPE VECTOR_FN(max)(const Vector *__v);

MATRIX_TYPE VECTOR_FN(at)(const Vector *__v, size_t __i);

MATRIX_TYPE *VECTOR_FN(access)(const Vector *__v, size_t __i);

// More abstract, functional pattern "map"
// apply a function to the objects of a
Vector *VECTOR_FN(map)(const Vector *__v, TYPED(function) __fn);

MATRIX_TYPE VECTOR_FN(sum)(const Vector *__v);

void VECTOR_FN(print_as_row)(const Vector *__v);

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
MATRIX_TYPE TYPED_FN(vecdot)(const Vector *__u, const Vector *__v);

MATRIX_TYPE VECTOR_FN(inner)(const Vector *__u, const Vector *__v);

Vector *TYPED_FN(vecproject)(const Vector *__v, const Vector *__u);

// Take vector __v and project it ONTO __u
Vector *VECTOR_FN(project_onto)(const Vector *__v, const Vector *__u);


/**================================================================================================
 *!                                        Normalization
 *================================================================================================**/

// All of these functions should REALLY REALLY end up in the linear algebra section....

MATRIX_TYPE VECTOR_FN(dot)(const Vector *__u, const Vector *__v);

Vector *VECTOR_FN(hadamard)(const Vector *__u, const Vector *__v);

MATRIX_T *VECTOR_FN(outer)(const Vector *__u, const Vector *__v);

// Return the orthogonal Projection matrix v * v^T
MATRIX_T *VECTOR_FN(orthogonal_projection)(const Vector *__v);

/**
 * Compute the p-norm of a vector
 *
 * The p-norm of a matrix is defined to be the pth root ( sum of |a_ij|^p )
 *
 */
MATRIX_TYPE TYPED_FN(vecpnorm)(const Vector *__u, const int __p);

// Euclidean norm
MATRIX_TYPE TYPED_FN(vecnorm)(const Vector *__A);

void TYPED_FN(vecnormalize)(Vector *__u);

// Return the norm of a vector (checking bounds?)
MATRIX_TYPE VECTOR_FN(norm)(const Vector *__u);

MATRIX_TYPE VECTOR_FN(pnorm)(const Vector *__u, const size_t __p);

// return a normalized version of this vector
Vector *VECTOR_FN(normalize)(const Vector *__u);

// Take a coliter and compute the pnorm
MATRIX_TYPE TYPED_FN(ColIter_norm)(TYPED(ColIter) *__c);

Vector *TYPED_FN(ascol)(Vector *__v);

Vector *TYPED_FN(asrow)(Vector *__v);

MATRIX_TYPE VECTOR_FN(distance)(const Vector *__v, const Vector *__u);

Vector *VECTOR_FN(difference)(const Vector *__v, const Vector *__u);

#endif