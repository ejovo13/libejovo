#pragma once

// Function definitions for conceptualizing Matrices as column vectors

#include "matrix.h"

/**================================================================================================
 *!                                        Constructors
 *================================================================================================**/

// Default to making a column vector
Vector *Vector_new(size_t __nrows);

Vector *Vector_rand(size_t __nrows);

Vector *Vector_random(size_t __nrows, int __min, int __max);

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
ColIter *Vector_col(const Vector *__v);

RowIter *Vector_row(const Vector *__v);

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

