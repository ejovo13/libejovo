#pragma once

// Define a series of functions that deal with looping through all of the elements of a matrix,
// looping through all of the columns of a matrix, in essence this file deals with iteration
#include "matrix.h"

/**================================================================================================
 *!                                        Single functions
 *================================================================================================**/

/**================================================================================================
 *!                                        Single functions
 *================================================================================================**/

// series of functions used to add two elements that MATRIX_FN(access) pointers are pointing to
static inline void add_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) += (*__b);
}

// I'm going to want to use this for computing the LU decomposition
static inline void sub_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) -= (*__b);
}

static inline void mult_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) *= (*__b);
}

static inline void div_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) /= (*__b);
}

//* MATRIX_T times scalar

static inline void multscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) *= __k;
}

static inline void addscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) += __k;
}

static inline void divscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) /= __k;
}

static inline void subscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) -= __k;
}

/**================================================================================================
 *!                                        Foreach loops
 *================================================================================================**/

void MATRIX_FN(foreach)(MATRIX_T *__A, EDITOR __fnc);

void MATRIX_FN(foreach_2)(MATRIX_T *__A, const MATRIX_T *__B, EDITOR_2 __fnc);

void MATRIX_FN(foreach_k)(MATRIX_T *__A, EDITOR_K __fnc, MATRIX_TYPE __k);

/**================================================================================================
 *!                                        Single function + foreach loop
 *================================================================================================**/


// add a __B to __A, mutating __A in place, using a "foreach" construct
void MAT_FN(add_foreach)(MATRIX_T *__A, const MATRIX_T *__B);

void MAT_FN(sub_foreach)(MATRIX_T *__A, const MATRIX_T *__B);

void MAT_FN(mult_foreach)(MATRIX_T *__A, const MATRIX_T *__B);

void MAT_FN(div_foreach)(MATRIX_T *__A, const MATRIX_T *__B);

void MAT_FN(multscalar)(MATRIX_T *__A, const MATRIX_TYPE __k);

void MAT_FN(addscalar)(MATRIX_T *__A, const MATRIX_TYPE __k);

void MAT_FN(divscalar)(MATRIX_T *__A, const MATRIX_TYPE __k);

void MAT_FN(subscalar)(MATRIX_T *__A, const MATRIX_TYPE __k);

MATRIX_TYPE MAT_FN(sum)(const MATRIX_T *__A);

MATRIX_TYPE MAT_FN(min)(const MATRIX_T *__A);

MATRIX_TYPE MAT_FN(max)(const MATRIX_T *__A);


/**================================================================================================
 *!                                       MATRIX_T API foreach
 *================================================================================================**/

MATRIX_T *MATRIX_FN(mult_scalar)(const MATRIX_T *__A, const MATRIX_TYPE __k);

MATRIX_T *MATRIX_FN(add_scalar)(const MATRIX_T *__A, const MATRIX_TYPE __k);

MATRIX_T *MATRIX_FN(sub_scalar)(const MATRIX_T *__A, const MATRIX_TYPE __k);

MATRIX_T *MATRIX_FN(div_scalar)(const MATRIX_T *__A, const MATRIX_TYPE __k);


/**================================================================================================
 *!                                        MATRIX_T Mask functions
 *================================================================================================**/

/**
 * Perform an operation on a matrix when a given mask evaluates to true
 */
void MATRIX_FN(mask)(MATRIX_T *__A, Mask __mask, EDITOR __operator);
// __mask is only applied to matrix __A
void MATRIX_FN(mask_2)(MATRIX_T *__A, MATRIX_T *__B, Mask __mask, EDITOR_2 __operator);

void MATRIX_FN(mask_k)(MATRIX_T *__A, Mask __mask, EDITOR_K __operator, const MATRIX_TYPE __k);