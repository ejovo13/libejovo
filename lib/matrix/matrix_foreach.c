// Define a series of functions that deal with looping through all of the elements of a matrix,
// looping through all of the columns of a matrix, in essence this file deals with iteration
// #include "ejovo_matrix_generic.h"
#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Foreach loops
 *================================================================================================**/

void TYPED(Matrix_foreach)(TYPED(Matrix) *__A, TYPED(EDITOR) __fnc) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            __fnc(TYPED(matacc)(__A, i, j));
        }
    }
}

void TYPED(Matrix_foreach_2)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B, TYPED(EDITOR_2) __fnc) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            __fnc(TYPED(matacc)(__A, i, j), TYPED(matacc)(__B, i, j));
        }
    }
}

void TYPED(Matrix_foreach_k)(TYPED(Matrix) *__A, TYPED(EDITOR_K) __fnc, MATRIX_TYPE __k) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            __fnc(TYPED(matacc)(__A, i, j), __k);
        }
    }
}

/**================================================================================================
 *!                                        Single function + foreach loop
 *================================================================================================**/


// add a __B to __A, mutating __A in place, using a "foreach" construct
void TYPED(matadd_foreach)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {
    TYPED(Matrix_foreach_2)(__A, __B, TYPED(add_each));
}

void TYPED(matsub_foreach)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {
    TYPED(Matrix_foreach_2)(__A, __B, TYPED(sub_each));
}

void TYPED(matmult_foreach)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {
    TYPED(Matrix_foreach_2)(__A, __B, TYPED(mult_each));
}

void TYPED(matdiv_foreach)(TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {
    TYPED(Matrix_foreach_2)(__A, __B, TYPED(div_each));
}

void TYPED(matmultscalar)(TYPED(Matrix) *__A, const MATRIX_TYPE __k) {
    TYPED(Matrix_foreach_k)(__A, TYPED(multscalar), __k);
}

void TYPED(mataddscalar)(TYPED(Matrix) *__A, const MATRIX_TYPE __k) {
    TYPED(Matrix_foreach_k)(__A, TYPED(addscalar), __k);
}

void TYPED(matdivscalar)(TYPED(Matrix) *__A, const MATRIX_TYPE __k) {
    TYPED(Matrix_foreach_k)(__A, TYPED(divscalar), __k);
}

void TYPED(matsubscalar)(TYPED(Matrix) *__A, const MATRIX_TYPE __k) {
    TYPED(Matrix_foreach_k)(__A, TYPED(subscalar), __k);
}

MATRIX_TYPE TYPED(matsum)(const TYPED(Matrix) *__A) {

    MATRIX_TYPE sum = 0;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j <__A->ncols; j++) {
            sum += TYPED(matat)(__A, i, j);
        }
    }

    return sum;
}

MATRIX_TYPE TYPED(matmin)(const TYPED(Matrix) *__A) {

    MATRIX_TYPE min = TYPED(matat)(__A, 0, 0);

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
        #ifdef MATRIX_COMPLEX
            if (cabs(TYPED(matat)(__A, i, j)) < cabs(min)) min = TYPED(matat)(__A, i, j);
        #else
            if (TYPED(matat)(__A, i, j) < min) min = TYPED(matat)(__A, i, j);
        #endif
        }
    }

    return min;
}

MATRIX_TYPE TYPED(matmax)(const TYPED(Matrix) *__A) {

    MATRIX_TYPE max = TYPED(matat)(__A, 0, 0);

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
        #ifdef MATRIX_COMPLEX
            if (cabs(TYPED(matat)(__A, i, j)) > cabs(max)) max = TYPED(matat)(__A, i, j);
        #else
            if (TYPED(matat)(__A, i, j) > max) max = TYPED(matat)(__A, i, j);
        #endif
        }
    }

    return max;
}


/**================================================================================================
 *!                                       TYPED(Matrix) API foreach
 *================================================================================================**/

TYPED(Matrix) *TYPED(Matrix_mult_scalar)(const TYPED(Matrix) *__A, const MATRIX_TYPE __k) {
    TYPED(Matrix) *A = TYPED(Matrix_clone)(__A);
    TYPED(matmultscalar)(A, __k);
    return A;
}

TYPED(Matrix) *TYPED(Matrix_add_scalar)(const TYPED(Matrix) *__A, const MATRIX_TYPE __k) {
    TYPED(Matrix) *A = TYPED(Matrix_clone)(__A);
    TYPED(mataddscalar)(A, __k);
    return A;
}

TYPED(Matrix) *TYPED(Matrix_sub_scalar)(const TYPED(Matrix) *__A, const MATRIX_TYPE __k) {
    TYPED(Matrix) *A = TYPED(Matrix_clone)(__A);
    TYPED(matsubscalar)(A, __k);
    return A;
}

TYPED(Matrix) *TYPED(Matrix_div_scalar)(const TYPED(Matrix) *__A, const MATRIX_TYPE __k) {
    TYPED(Matrix) *A = TYPED(Matrix_clone)(__A);
    TYPED(matdivscalar)(A, __k);
    return A;
}


/**================================================================================================
 *!                                        TYPED(Matrix) Mask functions
 *================================================================================================**/

/**
 * Perform an operation on a matrix when a given mask evaluates to true
 */
void TYPED(Matrix_mask)(TYPED(Matrix) *__A, TYPED(Mask) __mask, TYPED(EDITOR) __operator) {

    MATRIX_TYPE *el = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            el = TYPED(matacc)(__A, i, j); // access the ith, jth element
            if (__mask(el)) __operator(el); // if the __mask is true, do something to __el
        }
    }
}
// __mask is only applied to matrix __A
void TYPED(Matrix_mask_2)(TYPED(Matrix) *__A, TYPED(Matrix) *__B, TYPED(Mask) __mask, TYPED(EDITOR_2) __operator) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            a = TYPED(matacc)(__A, i, j); // access the ith, jth element
            b = TYPED(matacc)(__B, i, j); // access the ith, jth element
            if (__mask(a)) __operator(a, b); // if the __mask is true, do something to __el
        }
    }
}

void TYPED(Matrix_mask_k)(TYPED(Matrix) *__A, TYPED(Mask) __mask, TYPED(EDITOR_K) __operator, const MATRIX_TYPE __k) {

    MATRIX_TYPE *el = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            el = TYPED(matacc)(__A, i, j); // access the ith, jth element
            if (__mask(el)) __operator(el, __k); // if the __mask is true, do something to __el
        }
    }
}