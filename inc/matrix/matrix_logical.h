#ifndef MATRIX_LOGICAL_H
#define MATRIX_LOGICAL_H

// This module contains essential routines to deal with a "logical" TYPED(Matrix) data type that is represented
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

extern MATRIX_TYPE TYPED(TRUE);
extern MATRIX_TYPE TYPED(FALSE);

typedef TYPED(Matrix) TYPED(Logical);
typedef MATRIX_TYPE (* TYPED(pred_fn)) (MATRIX_TYPE);

// A Logical TYPED(Matrix) shall be typedef'd as a "Mask" to express intent
// This is used as a predicate function. Can be used to make a "true"
// matrix that is the same size as a passed matrix with
// TYPED(Matrix_as_logical)(m, true_fn); as TYPED(Matrix_as_logical) will accept a
// predicate as an argument
MATRIX_TYPE TYPED(true_fn)(MATRIX_TYPE d);

MATRIX_TYPE TYPED(NOT)(MATRIX_TYPE d);

MATRIX_TYPE TYPED(AND)(MATRIX_TYPE a, MATRIX_TYPE b);

MATRIX_TYPE TYPED(OR)(MATRIX_TYPE a, MATRIX_TYPE b);

// First routine that I should implement is having the notion of "if the vector is logical"
bool TYPED(Matrix_is_logical)(const TYPED(Matrix) *__log);


bool TYPED(Vector_is_logical)(const TYPED(Vector)*__log);

// I need to be able to create logical vectors now...
int TYPED(Matrix_mask_count)(const TYPED(Matrix) *__mask);

// Create a logical vector that is the same size as another matrix and set all of it's values to true.
int TYPED(Vector_mask_count)(const TYPED(Vector)*__mask);

// An alternative way to count the value is to count the non zero values


// Create a new logical matrix/vector from a current matrix and a predicate
TYPED(Matrix) *TYPED(Matrix_as_logical)(const TYPED(Matrix) *__m, TYPED(pred_fn) __fn);

TYPED(Matrix) *TYPED(Matrix_as_true)(const TYPED(Matrix) *__m);

TYPED(Logical) *TYPED(Matrix_lt)(const TYPED(Matrix) *__m, MATRIX_TYPE __k);

// Return a Logical mask of all the values in __m that are <= __k
TYPED(Logical) *TYPED(Matrix_lteq)(const TYPED(Matrix) *__m, MATRIX_TYPE __k);

// Return a Logical mask of all the values in __m that are > lt __k
TYPED(Logical) *TYPED(Matrix_gt)(const TYPED(Matrix) *__m, MATRIX_TYPE __k);

// Return a Logical mask of all the values in __m that are >= __k
TYPED(Logical) *TYPED(Matrix_gteq)(const TYPED(Matrix) *__m, MATRIX_TYPE __k);

// Wherever the mask is true, set __m to the __val
void TYPED(matsetmask)(TYPED(Matrix) *__m, const TYPED(Matrix) *__mask, MATRIX_TYPE __val);

void TYPED(matsetpred)(TYPED(Matrix) *__m, TYPED(pred_fn) __predicate, MATRIX_TYPE __val);

// Return a column vector of elements that correspond to a particular mask
 TYPED(Vector)*TYPED(Matrix_filter_mask)(const TYPED(Matrix) *__m, const TYPED(Matrix) *__mask);

// return true if count == size of the mask
bool TYPED(Logical_all)(const TYPED(Matrix) *__mask);

// return true is any of the logical components are true
bool TYPED(Logical_any)(const TYPED(Matrix) *__mask);

// Return !__mask
TYPED(Logical) *TYPED(Logical_not)(const TYPED(Matrix) *__mask);

#endif