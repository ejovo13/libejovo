#pragma once

// Essential routines to get and set elements and columns and rows of matrices

#include "matrix.h"
#include "matrix_state.h"

/**================================================================================================
 *!                                        Set/Get Individual Elements
 *================================================================================================**/
static inline MATRIX_T *reshape(MATRIX_T *__m, size_t __nrow, size_t __ncol) {
    __m->nrows = __nrow;
    __m->ncols = __ncol;
    return __m;
}

static inline MATRIX_TYPE MAT_FN(get)(const MATRIX_T *__m, size_t __i) {
    return __m->data[__i];
}

// set value of the element at __m(__i, __j) without checking the indices
static inline void MAT_FN(set)(MATRIX_T *__m, size_t __i, size_t __j, MATRIX_TYPE __value) {
    __m->data[__i * __m->ncols + __j] = __value;
}

// Return element at __m[__i][__j] without checking bounds
static inline MATRIX_TYPE MAT_FN(at)(const MATRIX_T *__m, size_t __i, size_t __j) {
    return __m->data[__i * __m->ncols + __j];
}

// return a pointer to the element at __m(__i, __j) without checking the indices
static inline MATRIX_TYPE *MAT_FN(acc)(const MATRIX_T *__m, size_t __i, size_t __j) {
    return __m->data + (__i * __m->ncols + __j);
}

/**
 * Set the element that a pointer is pointing to to __value
 */
static inline void setelement(MATRIX_TYPE *__el, const MATRIX_TYPE __value) {
    *__el = __value;
}

// Swap __a and __b
static inline void MAT_FN(swap)(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    MATRIX_TYPE temp = *__a;
    *(__a) = *(__b);
    *(__b) = temp;
}

static inline MATRIX_TYPE MATRIX_FN(first)(const MATRIX_T *__m) {
    return MAT_FN(at)(__m, 0, 0);
}

static inline MATRIX_TYPE MATRIX_FN(last)(const MATRIX_T *__m) {
    return MAT_FN(at)(__m, __m->nrows - 1, __m->ncols - 1);
}

static inline MATITER_T MATRIX_FN(begin)(const MATRIX_T *__m) {
    MATITER_T b = {.ptr = __m->data, .ptr_diff = 1};
    return b;
}

static inline MATITER_T MATRIX_FN(end)(const MATRIX_T *__m) {
    MATITER_T e = {.ptr = MAT_FN(acc)(__m, __m->nrows - 1, __m->ncols), .ptr_diff = 1}; // want the elment justtt after the final one
    return e;
}


// set value of the element at __m(__i, __j) [zero indexed]
// return 0 if the bounds were respected, -1 elsewise
static inline int MATRIX_FN(set)(MATRIX_T * __m, size_t __i, size_t __j, MATRIX_TYPE __value) {

    if (MATRIX_FN(valid_bounds)(__m, __i, __j)) {
        __m->data[__i*__m->ncols + __j] = __value;
        return 0;
    } else {
        fprintf(stderr, "**WARNING** Trying to access array element out of bounds. (set)\n");
        return 1;
    }
}

// return a pointer to the element at __m(__i, __j) checking the indices
// returns null if the bounds are not respected
static inline MATRIX_TYPE *MAT_FN(acc_check)(const MATRIX_T *__m, size_t __i, size_t __j) {

    if (MATRIX_FN(valid_bounds)(__m, __i, __j)) {
        return __m->data + (__i*__m->ncols + __j);
    } else {
        fprintf(stderr, "**WARNING** Trying to access array element out of bounds. (access)\n");
        return NULL;
    }
}


// return a pointer to the element at __m(__i, __j) [zero indexed]
static inline MATRIX_TYPE *MATRIX_FN(access)(const MATRIX_T * __m, size_t __i, size_t __j) {
    return MAT_FN(acc_check)(__m, __i, __j);
}


// return the value of the element at __m(__i, __j) [zero indexed]
// return -1 if bounds are not respected and prints an error to the screen
static inline MATRIX_TYPE MATRIX_FN(at)(const MATRIX_T *__m, size_t __i, size_t __j) {

    if (MATRIX_FN(valid_bounds)(__m, __i, __j)) {

        return __m->data[__i * __m->ncols + __j];

    } else {
        fprintf(stderr, "**WARNING** Trying to access array element out of bounds. (at)\n");

        // #if MATRIX_TYPE == Complex
            // return Complex_zero();
        // #else
        return -1;
        // #endif
    }
}



/**================================================================================================
 *!                                        Set/Get range of elements
 *================================================================================================**/
// Copy the elements of __src into the submatrix of __dest prescribed by the start and end indices WITHOUT CHECKING THE BOUNDS
static inline void MAT_FN(cpyele_unsafe)(MATRIX_T *__dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, const MATRIX_T *__src) {

    for (size_t i = __istart, irow = 0; i <= __iend; i++, irow++) {
        for (size_t j = __jstart, jcol = 0; j <= __jend; j++, jcol++) {
            MATRIX_FN(set)(__dest, i, j, MATRIX_FN(at)(__src, irow, jcol));
        }
    }
    // optimized for row-major access

}

// Copy the matrix __src into the submatrix of __dest prescribed by the start and end indices
static inline int MAT_FN(cpyele)(MATRIX_T * __dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, const MATRIX_T * __src) {

    // If the submatrix is not contained in __des
    if (__iend < __istart || __jend < __jstart || __iend >= __dest->nrows || __jend >= __dest->ncols) {
        perror("Selected submatrix is not contained within Parent Matrix\n");
        return -1;
    }

    // If the __src is not the same size as the selected submatrix
    if (__src->nrows != (__iend - __istart + 1) || __src->ncols != (__jend - __jstart + 1)) {
        perror("Selected submatrix not the same size as the src matrix to copy\n");
        return -2;
    }

    MAT_FN(cpyele_unsafe)(__dest, __istart, __iend, __jstart, __jend, __src);


    return 0;
}


/**================================================================================================
 *!                                        Set/Get Rows/Cols
 *================================================================================================**/

// Set the first __n indices of row __i, starting at column __j
static inline void MAT_FN(setrow)(MATRIX_T *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n) {

    MATRIX_TYPE *row_start = MAT_FN(acc)(__A, __i, __j); // start of the row
    memcpy((void *) row_start, (void *) __src, sizeof(MATRIX_TYPE) * __n);

}

static inline void MAT_FN(setcol)(MATRIX_T *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n) {

    MATRIX_TYPE *col_start = MAT_FN(acc)(__A, __i, __j); // start of the col
    for (size_t i = 0; i < __n; i++) {
        *(col_start + (__A->nrows * i)) = __src[i];
    }
}
// /**================================================================================================
//  *!                                        Set/Get range of elements
//  *================================================================================================**/

// // Copy the matrix __src into the submatrix of __dest prescribed by the start and end indices
// extern inline int MAT_FN(cpyele)(MATRIX_T * __dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, MATRIX_T * __src);

// // Copy the elements of __src into the submatrix of __dest prescribed by the start and end indices WITHOUT CHECKING THE BOUNDS
// extern inline void MAT_FN(cpyele_unsafe)(MATRIX_T *__dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, MATRIX_T *__src);

// /**================================================================================================
//  *!                                        Set/Get Rows/Cols
//  *================================================================================================**/

// // Set the first __n indices of row __i, starting at column __j
// extern inline void MAT_FN(setrow)(MATRIX_T *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n);

// extern inline void MAT_FN(setcol)(MATRIX_T *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n);

// matsetrow_mult_k
// matsetrow_div_k
// matsetrow_sub_k
// matsetrow_add_k

// multiply the row of a matrix times the value __k
void MAT_FN(setrow_mult_k)(MATRIX_T *__A, MATITER_T __r, const MATITER_T __row_end, MATRIX_TYPE __k);

// multiply the row of a matrix times the value __k
void MAT_FN(setrow_div_k)(MATRIX_T *__A, MATITER_T __r, const MATITER_T __row_end, MATRIX_TYPE __k);
// multiply the row of a matrix times the value __k
void MAT_FN(setrow_add_k)(MATRIX_T *__A, MATITER_T __r, const MATITER_T __row_end, MATRIX_TYPE __k);

// multiply the row of a matrix times the value __k
void MAT_FN(setrow_sub_k)(MATRIX_T *__A, MATITER_T __r, const MATITER_T __row_end, MATRIX_TYPE __k);

int MATRIX_FN(mult_row_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k);

int MATRIX_FN(div_row_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k);
int MATRIX_FN(add_row_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k);

int MATRIX_FN(sub_row_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k);

// editing columns now
void MAT_FN(setcol_mult_k)(MATRIX_T *__A, MATITER_T __c, const MATITER_T __col_end, MATRIX_TYPE __k);

// multiply the col of a matrix times the value __k
void MAT_FN(setcol_div_k)(MATRIX_T *__A, MATITER_T __c, const MATITER_T __col_end, MATRIX_TYPE __k);
// multiply the col of a matrix times the value __k
void MAT_FN(setcol_add_k)(MATRIX_T *__A, MATITER_T __c, const MATITER_T __col_end, MATRIX_TYPE __k);

// multiply the col of a matrix times the value __k
void MAT_FN(setcol_sub_k)(MATRIX_T *__A, MATITER_T __c, const MATITER_T __col_end, MATRIX_TYPE __k);

int MATRIX_FN(mult_col_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k);

int MATRIX_FN(div_col_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k);
int MATRIX_FN(add_col_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k);

int MATRIX_FN(sub_col_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k);




// SETS THE iTH ROW OF __A USING A ROW VECTOR!!!! That is, a ONE by M matrix
int MATRIX_FN(set_row)(MATRIX_T *__A, size_t __i, const MATRIX_T *__cow);

// SETS THE iTH ROW OF __A USING A ROW VECTOR!!!! That is, a ONE by M matrix
int MATRIX_FN(set_col)(MATRIX_T *__A, size_t __j, const MATRIX_T *__col);

// It is remarkably faster to extract a specific row since we are just memcpy a certain period of bytes!
MATRIX_T *MATRIX_FN(get_col)(const MATRIX_T *__A, size_t __j);

// On the other hand, matrow is quite slow since we have to access the elements with a for loop.
// As a design choice, I'd like to implement some sort of low level "row iterator" that will allow us
// to iterate allong the row of a MATRIX_T (to access it later) without actually performing a copy
MATRIX_T *MATRIX_FN(get_row)(const MATRIX_T *__A, size_t __i);

// I want to create a function that is going to multiply the row of a matrix, starting with it's row iterator.



/**================================================================================================
 *!                                        Set/Get Submatrices
 *================================================================================================**/

// Extract submatrix __A(__istart:__iend, __jstart:__jend)
// This allocates a completely new matrix
MATRIX_T * CAT(sub, MAT_T)(const MATRIX_T * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

// Alternative spelling for object-oriented approach.
MATRIX_T * MATRIX_FN(submat)(const MATRIX_T * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

MATRIX_T * MATRIX_FN(minor)(const MATRIX_T * __A, size_t __irow, size_t __icol);

/**================================================================================================
 *!                                        Set/Get Matrices
 *================================================================================================**/

void MAT_FN(fill)(MATRIX_T *__A, const MATRIX_TYPE __value);

// fill matrix with a single value
void MATRIX_FN(fill)(MATRIX_T * __A, const MATRIX_TYPE value);

/**
 * Set all of the elements who fulfill a mask equal to the value
 */
void MATRIX_FN(fill_mask)(MATRIX_T *__A, Mask __mask, const MATRIX_TYPE __value);

MATRIX_T *MATRIX_FN(rcat)(const MATRIX_T *__A, const MATRIX_T *__B);

MATRIX_T *MATRIX_FN(ccat)(const MATRIX_T *__A, const MATRIX_T *__B);