#pragma once

#include "matrix.h"
#include "matrix_core.h"
#include "matrix_vector.h"
#include "matrix_state.h"
#include "matrix_vector.h"
#include "matrix_iter.h"
#include "matrix_getset.h"

double ID(double x);

// If the predicate is costly, we should consider using the Logical matrix counterpart that
// will filter using logical masks
Vector *filter(const Vector *__v, predicate_fn __pred);

Vector *filter_if_not(const Vector *__v, predicate_fn __pred);

// Apply a function that takes a double and returns a double to the contents of a matrix
Matrix *map(const Matrix *__m, function fn);

// These functions should only operate on VECTORS
// Actually, I think I'm thinking about this wrong. These can operate on matrices but they
// will always return vectors because we can't preserve the size
MATRIX_TYPE head(const Matrix *__m);

Vector *tail(const Matrix *__m);

MATRIX_TYPE last(const Matrix *__m);

Vector *init (const Matrix *__m);
