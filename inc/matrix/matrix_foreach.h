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

// series of functions used to add two elements that MATRIX_FN(access) pointers are pointing to
static inline void TYPED_FN(add_each)(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) += (*__b);
}

// I'm going to want to use this for computing the LU decomposition
static inline void TYPED_FN(sub_each)(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) -= (*__b);
}

static inline void TYPED_FN(mult_each)(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) *= (*__b);
}

static inline void TYPED_FN(div_each)(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) /= (*__b);
}

//* MATRIX_T times scalar

static inline void TYPED_FN(multscalar)(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) *= __k;
}

static inline void TYPED_FN(addscalar)(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) += __k;
}

static inline void TYPED_FN(divscalar)(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) /= __k;
}

static inline void TYPED_FN(subscalar)(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) -= __k;
}

/**================================================================================================
 *!                                        Foreach loops
 *================================================================================================**/

void MATRIX_FN(foreach)(MATRIX_T *__A, TYPED(EDITOR) __fnc);

void MATRIX_FN(foreach_2)(MATRIX_T *__A, const MATRIX_T *__B, TYPED(EDITOR_2) __fnc);

void MATRIX_FN(foreach_k)(MATRIX_T *__A, TYPED(EDITOR_K) __fnc, MATRIX_TYPE __k);

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
void MATRIX_FN(mask)(MATRIX_T *__A, TYPED(Mask) __mask, TYPED(EDITOR) __operator);
// __mask is only applied to matrix __A
void MATRIX_FN(mask_2)(MATRIX_T *__A, MATRIX_T *__B, TYPED(Mask) __mask, TYPED(EDITOR_2) __operator);

void MATRIX_FN(mask_k)(MATRIX_T *__A, TYPED(Mask) __mask, TYPED(EDITOR_K) __operator, const MATRIX_TYPE __k);

#endif