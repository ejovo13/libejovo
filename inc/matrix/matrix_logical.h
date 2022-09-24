#pragma once

// This module contains essential routines to deal with a "logical" MATRIX_T data type that is represented
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

typedef MATRIX_T Logical;
typedef double (* pred_fn) (double);

// A Logical MATRIX_T shall be typedef'd as a "Mask" to express intent
// This is used as a predicate function. Can be used to make a "true"
// matrix that is the same size as a passed matrix with
// MATRIX_FN(as_logical)(m, true_fn); as MATRIX_FN(as_logical) will accept a
// predicate as an argument
double true_fn(double d);

double NOT(double d);

double AND(double a, double b);

double OR(double a, double b);

// First routine that I should implement is having the notion of "if the vector is logical"
bool MATRIX_FN(is_logical)(const MATRIX_T *__log);


bool VECTOR_FN(is_logical)(const Vector *__log);

// I need to be able to create logical vectors now...
int MATRIX_FN(mask_count)(const MATRIX_T *__mask);

// Create a logical vector that is the same size as another matrix and set all of it's values to true.
int VECTOR_FN(mask_count)(const Vector *__mask);

// An alternative way to count the value is to count the non zero values


// Create a new logical matrix/vector from a current matrix and a predicate
MATRIX_T *MATRIX_FN(as_logical)(const MATRIX_T *__m, pred_fn __fn);

MATRIX_T *MATRIX_FN(as_true)(const MATRIX_T *__m);

Logical *MATRIX_FN(lt)(const MATRIX_T *__m, double __k);

// Return a Logical mask of all the values in __m that are <= __k
Logical *MATRIX_FN(lteq)(const MATRIX_T *__m, double __k);

// Return a Logical mask of all the values in __m that are > lt __k
Logical *MATRIX_FN(gt)(const MATRIX_T *__m, double __k);

// Return a Logical mask of all the values in __m that are >= __k
Logical *MATRIX_FN(gteq)(const MATRIX_T *__m, double __k);

// Wherever the mask is true, set __m to the __val
void MAT_FN(setmask)(MATRIX_T *__m, const MATRIX_T *__mask, MATRIX_TYPE __val);

void MAT_FN(setpred)(MATRIX_T *__m, pred_fn __predicate, MATRIX_TYPE __val);

// Return a column vector of elements that correspond to a particular mask
Vector *MATRIX_FN(filter_mask)(const MATRIX_T *__m, const MATRIX_T *__mask);

// return true if count == size of the mask
bool Logical_all(const MATRIX_T *__mask);

// return true is any of the logical components are true
bool Logical_any(const MATRIX_T *__mask);

// Return !__mask
Logical *Logical_not(const MATRIX_T *__mask);