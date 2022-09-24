#ifndef MATRIX_FUNCTIONAL_H
#define MATRIX_FUNCTIONAL_H

#include "matrix.h"

MATRIX_TYPE TYPED_FN(Id)(MATRIX_TYPE x);

MATRIX_TYPE TYPED_FN(x_squared)(MATRIX_TYPE x);

MATRIX_TYPE TYPED_FN(x_cubed)(MATRIX_TYPE x);

// If the predicate is costly, we should consider using the Logical matrix counterpart that
// will filter using logical masks
Vector *TYPED_FN(filter)(const Vector *__v, TYPED(predicate_fn) __pred);

Vector *TYPED_FN(filter_if_not)(const Vector *__v, TYPED(predicate_fn) __pred);

Vector *TYPED_FN(filter_lt)(const Vector *__v, MATRIX_TYPE __cutoff);

Vector *TYPED_FN(filter_lteq)(const Vector *__v, MATRIX_TYPE __cutoff);

Vector *TYPED_FN(filter_gt)(const Vector *__v, MATRIX_TYPE __cutoff);


Vector *TYPED_FN(filter_gteq)(const Vector *__v, MATRIX_TYPE __cutoff);

// Apply a function that takes a MATRIX_TYPE and returns a MATRIX_TYPE to the contents of a matrix
MATRIX_T *TYPED_FN(map)(const MATRIX_T *__m, TYPED(function) fn);

MATRIX_T *TYPED_FN(apply)(MATRIX_T *__m, TYPED(function) fn);

// These functions should only operate on VECTORS
// Actually, I think I'm thinking about this wrong. These can operate on matrices but they
// will always return vectors because we can't preserve the size
MATRIX_TYPE TYPED_FN(head)(const MATRIX_T *__m);

Vector *TYPED_FN(tail)(const MATRIX_T *__m);

MATRIX_TYPE TYPED_FN(last)(const MATRIX_T *__m);

Vector *TYPED_FN(init)(const MATRIX_T *__m);

#endif