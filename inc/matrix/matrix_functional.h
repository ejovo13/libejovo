#pragma once

#include "matrix.h"

double Id(double x);

double x_squared(double x);

double x_cubed(double x);

// If the predicate is costly, we should consider using the Logical matrix counterpart that
// will filter using logical masks
Vector *filter(const Vector *__v, predicate_fn __pred);

Vector *filter_if_not(const Vector *__v, predicate_fn __pred);

Vector *filter_lt(const Vector *__v, double __cutoff);

Vector *filter_lteq(const Vector *__v, double __cutoff);

Vector *filter_gt(const Vector *__v, double __cutoff);


Vector *filter_gteq(const Vector *__v, double __cutoff);

// Apply a function that takes a double and returns a double to the contents of a matrix
Matrix *map(const Matrix *__m, function fn);

Matrix *apply(Matrix *__m, function fn);

// These functions should only operate on VECTORS
// Actually, I think I'm thinking about this wrong. These can operate on matrices but they
// will always return vectors because we can't preserve the size
MATRIX_TYPE head(const Matrix *__m);

Vector *tail(const Matrix *__m);

MATRIX_TYPE last(const Matrix *__m);

Vector *init (const Matrix *__m);
