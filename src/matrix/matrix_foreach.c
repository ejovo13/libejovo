// Define a series of functions that deal with looping through all of the elements of a matrix,
// looping through all of the columns of a matrix, in essence this file deals with iteration
#include "ejovo_matrix_generic.h"
// #include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Foreach loops
 *================================================================================================**/

void MATRIX_FN(foreach)(MATRIX_T *__A, TYPED(EDITOR) __fnc) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            __fnc(MAT_FN(acc)(__A, i, j));
        }
    }
}

void MATRIX_FN(foreach_2)(MATRIX_T *__A, const MATRIX_T *__B, TYPED(EDITOR_2) __fnc) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            __fnc(MAT_FN(acc)(__A, i, j), MAT_FN(acc)(__B, i, j));
        }
    }
}

void MATRIX_FN(foreach_k)(MATRIX_T *__A, TYPED(EDITOR_K) __fnc, MATRIX_TYPE __k) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            __fnc(MAT_FN(acc)(__A, i, j), __k);
        }
    }
}

/**================================================================================================
 *!                                        Single function + foreach loop
 *================================================================================================**/


// add a __B to __A, mutating __A in place, using a "foreach" construct
void MAT_FN(add_foreach)(MATRIX_T *__A, const MATRIX_T *__B) {
    MATRIX_FN(foreach_2)(__A, __B, TYPED_FN(add_each));
}

void MAT_FN(sub_foreach)(MATRIX_T *__A, const MATRIX_T *__B) {
    MATRIX_FN(foreach_2)(__A, __B, TYPED_FN(sub_each));
}

void MAT_FN(mult_foreach)(MATRIX_T *__A, const MATRIX_T *__B) {
    MATRIX_FN(foreach_2)(__A, __B, TYPED_FN(mult_each));
}

void MAT_FN(div_foreach)(MATRIX_T *__A, const MATRIX_T *__B) {
    MATRIX_FN(foreach_2)(__A, __B, TYPED_FN(div_each));
}

void MAT_FN(multscalar)(MATRIX_T *__A, const MATRIX_TYPE __k) {
    MATRIX_FN(foreach_k)(__A, TYPED_FN(multscalar), __k);
}

void MAT_FN(addscalar)(MATRIX_T *__A, const MATRIX_TYPE __k) {
    MATRIX_FN(foreach_k)(__A, TYPED_FN(addscalar), __k);
}

void MAT_FN(divscalar)(MATRIX_T *__A, const MATRIX_TYPE __k) {
    MATRIX_FN(foreach_k)(__A, TYPED_FN(divscalar), __k);
}

void MAT_FN(subscalar)(MATRIX_T *__A, const MATRIX_TYPE __k) {
    MATRIX_FN(foreach_k)(__A, TYPED_FN(subscalar), __k);
}

MATRIX_TYPE MAT_FN(sum)(const MATRIX_T *__A) {

    MATRIX_TYPE sum = 0;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j <__A->ncols; j++) {
            sum += MAT_FN(at)(__A, i, j);
        }
    }

    return sum;
}

MATRIX_TYPE MAT_FN(min)(const MATRIX_T *__A) {

    MATRIX_TYPE min = MAT_FN(at)(__A, 0, 0);

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            if (MAT_FN(at)(__A, i, j) < min) min = MAT_FN(at)(__A, i, j);
        }
    }

    return min;
}

MATRIX_TYPE MAT_FN(max)(const MATRIX_T *__A) {

    MATRIX_TYPE max = MAT_FN(at)(__A, 0, 0);

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            if (MAT_FN(at)(__A, i, j) > max) max = MAT_FN(at)(__A, i, j);
        }
    }

    return max;
}


/**================================================================================================
 *!                                       MATRIX_T API foreach
 *================================================================================================**/

MATRIX_T *MATRIX_FN(mult_scalar)(const MATRIX_T *__A, const MATRIX_TYPE __k) {
    MATRIX_T *A = MATRIX_FN(clone)(__A);
    MAT_FN(multscalar)(A, __k);
    return A;
}

MATRIX_T *MATRIX_FN(add_scalar)(const MATRIX_T *__A, const MATRIX_TYPE __k) {
    MATRIX_T *A = MATRIX_FN(clone)(__A);
    MAT_FN(addscalar)(A, __k);
    return A;
}

MATRIX_T *MATRIX_FN(sub_scalar)(const MATRIX_T *__A, const MATRIX_TYPE __k) {
    MATRIX_T *A = MATRIX_FN(clone)(__A);
    MAT_FN(subscalar)(A, __k);
    return A;
}

MATRIX_T *MATRIX_FN(div_scalar)(const MATRIX_T *__A, const MATRIX_TYPE __k) {
    MATRIX_T *A = MATRIX_FN(clone)(__A);
    MAT_FN(divscalar)(A, __k);
    return A;
}


/**================================================================================================
 *!                                        MATRIX_T Mask functions
 *================================================================================================**/

/**
 * Perform an operation on a matrix when a given mask evaluates to true
 */
void MATRIX_FN(mask)(MATRIX_T *__A, TYPED(Mask) __mask, TYPED(EDITOR) __operator) {

    MATRIX_TYPE *el = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            el = MAT_FN(acc)(__A, i, j); // access the ith, jth element
            if (__mask(el)) __operator(el); // if the __mask is true, do something to __el
        }
    }
}
// __mask is only applied to matrix __A
void MATRIX_FN(mask_2)(MATRIX_T *__A, MATRIX_T *__B, TYPED(Mask) __mask, TYPED(EDITOR_2) __operator) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            a = MAT_FN(acc)(__A, i, j); // access the ith, jth element
            b = MAT_FN(acc)(__B, i, j); // access the ith, jth element
            if (__mask(a)) __operator(a, b); // if the __mask is true, do something to __el
        }
    }
}

void MATRIX_FN(mask_k)(MATRIX_T *__A, TYPED(Mask) __mask, TYPED(EDITOR_K) __operator, const MATRIX_TYPE __k) {

    MATRIX_TYPE *el = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            el = MAT_FN(acc)(__A, i, j); // access the ith, jth element
            if (__mask(el)) __operator(el, __k); // if the __mask is true, do something to __el
        }
    }
}