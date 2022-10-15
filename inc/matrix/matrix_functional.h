#ifndef MATRIX_FUNCTIONAL_H
#define MATRIX_FUNCTIONAL_H

#include "matrix.h"

MATRIX_TYPE TYPED(Id)(MATRIX_TYPE x);

MATRIX_TYPE TYPED(x_squared)(MATRIX_TYPE x);

MATRIX_TYPE TYPED(x_cubed)(MATRIX_TYPE x);

// If the predicate is costly, we should consider using the Logical matrix counterpart that
// will filter using logical masks
 TYPED(Vector)*TYPED(filter)(const TYPED(Vector)*__v, TYPED(predicate_fn) __pred);

 TYPED(Vector)*TYPED(filter_if_not)(const TYPED(Vector)*__v, TYPED(predicate_fn) __pred);

 TYPED(Vector)*TYPED(filter_lt)(const TYPED(Vector)*__v, MATRIX_TYPE __cutoff);

 TYPED(Vector)*TYPED(filter_lteq)(const TYPED(Vector)*__v, MATRIX_TYPE __cutoff);

 TYPED(Vector)*TYPED(filter_gt)(const TYPED(Vector)*__v, MATRIX_TYPE __cutoff);


 TYPED(Vector)*TYPED(filter_gteq)(const TYPED(Vector)*__v, MATRIX_TYPE __cutoff);

// Apply a function that takes a MATRIX_TYPE and returns a MATRIX_TYPE to the contents of a matrix
TYPED(Matrix) *TYPED(map)(const TYPED(Matrix) *__m, TYPED(function) fn);

TYPED(Matrix) *TYPED(apply)(TYPED(Matrix) *__m, TYPED(function) fn);

// These functions should only operate on VECTORS
// Actually, I think I'm thinking about this wrong. These can operate on matrices but they
// will always return vectors because we can't preserve the size
MATRIX_TYPE TYPED(head)(const TYPED(Matrix) *__m);

TYPED(Matrix) *TYPED(take)(const TYPED(Matrix) *__m, int n_el);

 TYPED(Vector)*TYPED(tail)(const TYPED(Matrix) *__m);

MATRIX_TYPE TYPED(last)(const TYPED(Matrix) *__m);

 TYPED(Vector)*TYPED(init)(const TYPED(Matrix) *__m);

#endif