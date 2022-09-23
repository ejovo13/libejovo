#pragma once

// Function definitions for conceptualizing Matrices as column vectors

#include "matrix.h"

/**================================================================================================
 *!                                        Constructors
 *================================================================================================**/


Vector *vector(int __count, ...);

// Default to making a column vector
Vector *Vector_new(size_t __nrows);

Vector *Vector_ones(size_t __nrows);

Vector *Vector_from_iter(MatIter __begin, MatIter __end);

Vector *Vector_rand(size_t __nrows);

Vector *Vector_random(size_t __nrows, int __min, int __max);

Vector *Vector_from(const double* __arr, size_t __nrows);

Vector *Vector_clone(const Vector *__v);

Vector *Vector_from_matrix(const Matrix *__m);

Vector *Vector_as_col(const Vector *__v);

Vector *Vector_as_row(const Vector *__v);

void Vector_free(Vector *__v);

void Vector_reset(Vector **__v);



/**================================================================================================
 *!                                        Matrix to vec functions
 *================================================================================================**/
Vector *Matrix_as_col(const Matrix *__m);

Vector *Matrix_as_row(const Matrix *__m);






/**================================================================================================
 *!                                        State Functions
 *================================================================================================**/
size_t Vector_size(const Vector *__v);

void Vector_set(Vector *__v, size_t __pos, MATRIX_TYPE __val);

void Vector_set_first(Vector *__v, MATRIX_TYPE __val);

void Vector_set_last(Vector *__v, MATRIX_TYPE __val);

MATRIX_TYPE Vector_first(const Vector *__v);

MATRIX_TYPE Vector_last(const Vector *__v);

/**================================================================================================
 *!                                        Vector iterator functions
 *================================================================================================**/
MatIter Vector_begin(const Vector *__v);

MatIter Vector_end(const Vector *__v);

// Create a new vector iter starting at the ith position
MatIter Vector_iter(const Vector *__v, size_t i);

MATRIX_TYPE Vector_max(const Vector *__v);

MATRIX_TYPE Vector_at(const Vector *__v, size_t __i);

MATRIX_TYPE *Vector_access(const Vector *__v, size_t __i);

// More abstract, functional pattern "map"
// apply a function to the objects of a
Vector *Vector_map(const Vector *__v, function __fn);

MATRIX_TYPE Vector_sum(const Vector *__v);

void Vector_print_as_row(const Vector *__v);

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
MATRIX_TYPE vecdot(const Vector *__u, const Vector *__v);

MATRIX_TYPE Vector_inner(const Vector *__u, const Vector *__v);

Vector *vecproject(const Vector *__v, const Vector *__u);

// Take vector __v and project it ONTO __u
Vector *Vector_project_onto(const Vector *__v, const Vector *__u);


/**================================================================================================
 *!                                        Normalization
 *================================================================================================**/

// All of these functions should REALLY REALLY end up in the linear algebra section....

MATRIX_TYPE Vector_dot(const Vector *__u, const Vector *__v);

Vector *Vector_hadamard(const Vector *__u, const Vector *__v);

Matrix *Vector_outer(const Vector *__u, const Vector *__v);

// Return the orthogonal Projection matrix v * v^T
Matrix *Vector_orthogonal_projection(const Vector *__v);

/**
 * Compute the p-norm of a vector
 *
 * The p-norm of a matrix is defined to be the pth root ( sum of |a_ij|^p )
 *
 */
MATRIX_TYPE vecpnorm(const Vector *__u, const int __p);

// Euclidean norm
MATRIX_TYPE vecnorm(const Vector *__A);

void vecnormalize(Vector *__u);

// Return the norm of a vector (checking bounds?)
MATRIX_TYPE Vector_norm(const Vector *__u);

MATRIX_TYPE Vector_pnorm(const Vector *__u, const size_t __p);

// return a normalized version of this vector
Vector *Vector_normalize(const Vector *__u);

// Take a coliter and compute the pnorm
MATRIX_TYPE ColIter_norm(ColIter *__c);

Vector *ascol(Vector *__v);

Vector *asrow(Vector *__v);

MATRIX_TYPE Vector_distance(const Vector *__v, const Vector *__u);

Vector *Vector_difference(const Vector *__v, const Vector *__u);