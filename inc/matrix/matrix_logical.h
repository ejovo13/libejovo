#pragma once

// This module contains essential routines to deal with a "logical" Matrix data type that is represented
// by A matrix that is UNIQUELY ones and zeros

#include <stdbool.h>

#include "matrix.h"
#include "matrix_core.h"
#include "matrix_iter.h"
#include "matrix_foreach.h"
#include "matrix_getset.h"
#include "matrix_stats.h"
#include "matrix_state.h"
#include "matrix_functional.h"

extern double TRUE;
extern double FALSE;

typedef Matrix Logical;
typedef double (* pred_fn) (double);

// A Logical Matrix shall be typedef'd as a "Mask" to express intent
// This is used as a predicate function. Can be used to make a "true"
// matrix that is the same size as a passed matrix with
// Matrix_as_logical(m, true_fn); as Matrix_as_logical will accept a
// predicate as an argument
double true_fn(double d);

double NOT(double d);

double AND(double a, double b);

double OR(double a, double b);

// First routine that I should implement is having the notion of "if the vector is logical"
bool Matrix_is_logical(const Matrix *__log);


bool Vector_is_logical(const Vector *__log);

// I need to be able to create logical vectors now...
int Matrix_mask_count(const Matrix *__mask);

// Create a logical vector that is the same size as another matrix and set all of it's values to true.
int Vector_mask_count(const Vector *__mask);

// An alternative way to count the value is to count the non zero values


// Create a new logical matrix/vector from a current matrix and a predicate
Matrix *Matrix_as_logical(const Matrix *__m, pred_fn __fn);

Matrix *Matrix_as_true(const Matrix *__m);

Logical *Matrix_lt(const Matrix *__m, double __k);

// Return a Logical mask of all the values in __m that are <= __k
Logical *Matrix_lteq(const Matrix *__m, double __k);

// Return a Logical mask of all the values in __m that are > lt __k
Logical *Matrix_gt(const Matrix *__m, double __k);

// Return a Logical mask of all the values in __m that are >= __k
Logical *Matrix_gteq(const Matrix *__m, double __k);

// Wherever the mask is true, set __m to the __val
void matsetmask(Matrix *__m, const Matrix *__mask, MATRIX_TYPE __val);

void matsetpred(Matrix *__m, pred_fn __predicate, MATRIX_TYPE __val);

// Return a column vector of elements that correspond to a particular mask
Vector *Matrix_filter_mask(const Matrix *__m, const Matrix *__mask);

// return true if count == size of the mask
bool Logical_all(const Matrix *__mask);

// return true is any of the logical components are true
bool Logical_any(const Matrix *__mask);

// Return !__mask
Logical *Logical_not(const Matrix *__mask);