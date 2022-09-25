#ifndef MATRIX_FOREACH_H
#define MATRIX_FOREACH_H
// Define a series of functions that deal with looping through all of the elements of a matrix,
// looping through all of the columns of a matrix, in essence this file deals with iteration
#include "matrix.h"

/**================================================================================================
 *!                                        Single functions
 *================================================================================================**/

/**================================================================================================
 *!                                        Single functions
 *================================================================================================**/

// series of functions used to add two elements that TYPED(Matrix_access) pointers are pointing to
static inline void TYPED(add_each)(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) += (*__b);
}

// I'm going to want to use this for computing the LU decomposition
static inline void TYPED(sub_each)(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) -= (*__b);
}

static inline void TYPED(mult_each)(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) *= (*__b);
}

static inline void TYPED(div_each)(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) /= (*__b);
}

//* TYPED(Matrix) times scalar

static inline void TYPED(multscalar)(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) *= __k;
}

static inline void TYPED(addscalar)(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) += __k;
}

static inline void TYPED(divscalar)(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) /= __k;
}

static inline void TYPED(subscalar)(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) -= __k;
}

/**================================================================================================
 *!                                        Foreach loops
 *================================================================================================**/

void TYPED(Matrix_foreach)(TYPED(Matrix) *__A, TYPED(EDITOR) __fnc);

void TYPED(Matrix_foreach_2)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B, TYPED(EDITOR_2) __fnc);

void TYPED(Matrix_foreach_k)(TYPED(Matrix) *__A, TYPED(EDITOR_K) __fnc, MATRIX_TYPE __k);

/**================================================================================================
 *!                                        Single function + foreach loop
 *================================================================================================**/


// add a __B to __A, mutating __A in place, using a "foreach" construct
void TYPED(matadd_foreach)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

void TYPED(matsub_foreach)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

void TYPED(matmult_foreach)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

void TYPED(matdiv_foreach)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

void TYPED(matmultscalar)(TYPED(Matrix) *__A, const MATRIX_TYPE __k);

void TYPED(mataddscalar)(TYPED(Matrix) *__A, const MATRIX_TYPE __k);

void TYPED(matdivscalar)(TYPED(Matrix) *__A, const MATRIX_TYPE __k);

void TYPED(matsubscalar)(TYPED(Matrix) *__A, const MATRIX_TYPE __k);

MATRIX_TYPE TYPED(matsum)(const TYPED(Matrix) *__A);

MATRIX_TYPE TYPED(matmin)(const TYPED(Matrix) *__A);

MATRIX_TYPE TYPED(matmax)(const TYPED(Matrix) *__A);


/**================================================================================================
 *!                                       TYPED(Matrix) API foreach
 *================================================================================================**/

TYPED(Matrix) *TYPED(Matrix_mult_scalar)(const TYPED(Matrix) *__A, const MATRIX_TYPE __k);

TYPED(Matrix) *TYPED(Matrix_add_scalar)(const TYPED(Matrix) *__A, const MATRIX_TYPE __k);

TYPED(Matrix) *TYPED(Matrix_sub_scalar)(const TYPED(Matrix) *__A, const MATRIX_TYPE __k);

TYPED(Matrix) *TYPED(Matrix_div_scalar)(const TYPED(Matrix) *__A, const MATRIX_TYPE __k);


/**================================================================================================
 *!                                        TYPED(Matrix) Mask functions
 *================================================================================================**/

/**
 * Perform an operation on a matrix when a given mask evaluates to true
 */
void TYPED(Matrix_mask)(TYPED(Matrix) *__A, TYPED(Mask) __mask, TYPED(EDITOR) __operator);
// __mask is only applied to matrix __A
void TYPED(Matrix_mask_2)(TYPED(Matrix) *__A, TYPED(Matrix) *__B, TYPED(Mask) __mask, TYPED(EDITOR_2) __operator);

void TYPED(Matrix_mask_k)(TYPED(Matrix) *__A, TYPED(Mask) __mask, TYPED(EDITOR_K) __operator, const MATRIX_TYPE __k);

#endif