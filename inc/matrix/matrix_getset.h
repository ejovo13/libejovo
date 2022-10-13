#ifndef MATRIX_GETSET_H
#define MATRIX_GETSET_H

// Essential routines to get and set elements and columns and rows of matrices

#include "matrix.h"
#include "matrix_state.h"

/**================================================================================================
 *!                                        Set/Get Individual Elements
 *================================================================================================**/
static inline TYPED(Matrix) *TYPED(reshape)(TYPED(Matrix) *__m, size_t __nrow, size_t __ncol) {
    __m->nrows = __nrow;
    __m->ncols = __ncol;
    return __m;
}

static inline MATRIX_TYPE TYPED(matget)(const TYPED(Matrix) *__m, size_t __i) {
    return __m->data[__i];
}

// set value of the element at __m(__i, __j) without checking the indices
static inline void TYPED(matset)(TYPED(Matrix) *__m, size_t __i, size_t __j, MATRIX_TYPE __value) {
    __m->data[__i * __m->ncols + __j] = __value;
}

// Return element at __m[__i][__j] without checking bounds
static inline MATRIX_TYPE TYPED(matat)(const TYPED(Matrix) *__m, size_t __i, size_t __j) {
    return __m->data[__i * __m->ncols + __j];
}

// return a pointer to the element at __m(__i, __j) without checking the indices
static inline MATRIX_TYPE *TYPED(matacc)(const TYPED(Matrix) *__m, size_t __i, size_t __j) {
    return __m->data + (__i * __m->ncols + __j);
}

/**
 * Set the element that a pointer is pointing to to __value
 */
static inline void TYPED(setelement)(MATRIX_TYPE *__el, const MATRIX_TYPE __value) {
    *__el = __value;
}

// Swap __a and __b
static inline void TYPED(matswap)(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    MATRIX_TYPE temp = *__a;
    *(__a) = *(__b);
    *(__b) = temp;
}

static inline MATRIX_TYPE TYPED(Matrix_first)(const TYPED(Matrix) *__m) {
    return TYPED(matat)(__m, 0, 0);
}

static inline MATRIX_TYPE TYPED(Matrix_last)(const TYPED(Matrix) *__m) {
    return TYPED(matat)(__m, __m->nrows - 1, __m->ncols - 1);
}

static inline TYPED(MatIter) TYPED(Matrix_begin)(const TYPED(Matrix) *__m) {
    TYPED(MatIter) b = {.ptr = __m->data, .ptr_diff = 1};
    return b;
}

static inline TYPED(MatIter) TYPED(Matrix_end)(const TYPED(Matrix) *__m) {
    TYPED(MatIter) e = {.ptr = TYPED(matacc)(__m, __m->nrows - 1, __m->ncols), .ptr_diff = 1}; // want the elment justtt after the final one
    return e;
}


// set value of the element at __m(__i, __j) [zero indexed]
// return 0 if the bounds were respected, -1 elsewise
static inline int TYPED(Matrix_set)(TYPED(Matrix) * __m, size_t __i, size_t __j, MATRIX_TYPE __value) {

    if (TYPED(Matrix_valid_bounds)(__m, __i, __j)) {
        __m->data[__i*__m->ncols + __j] = __value;
        return 0;
    } else {
        fprintf(stderr, "**WARNING** Trying to access array element out of bounds. (set)\n");
        return 1;
    }
}

// return a pointer to the element at __m(__i, __j) checking the indices
// returns null if the bounds are not respected
static inline MATRIX_TYPE *TYPED(matacc_check)(const TYPED(Matrix) *__m, size_t __i, size_t __j) {

    if (TYPED(Matrix_valid_bounds)(__m, __i, __j)) {
        return __m->data + (__i*__m->ncols + __j);
    } else {
        fprintf(stderr, "**WARNING** Trying to access array element out of bounds. (access)\n");
        return NULL;
    }
}


// return a pointer to the element at __m(__i, __j) [zero indexed]
static inline MATRIX_TYPE *TYPED(Matrix_access)(const TYPED(Matrix) * __m, size_t __i, size_t __j) {
    return TYPED(matacc_check)(__m, __i, __j);
}


// return the value of the element at __m(__i, __j) [zero indexed]
// return -1 if bounds are not respected and prints an error to the screen
static inline MATRIX_TYPE TYPED(Matrix_at)(const TYPED(Matrix) *__m, size_t __i, size_t __j) {

    if (TYPED(Matrix_valid_bounds)(__m, __i, __j)) {

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
static inline void TYPED(matcpyele_unsafe)(TYPED(Matrix) *__dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, const TYPED(Matrix) *__src) {

    for (size_t i = __istart, irow = 0; i <= __iend; i++, irow++) {
        for (size_t j = __jstart, jcol = 0; j <= __jend; j++, jcol++) {
            TYPED(Matrix_set)(__dest, i, j, TYPED(Matrix_at)(__src, irow, jcol));
        }
    }
    // optimized for row-major access

}

// Copy the matrix __src into the submatrix of __dest prescribed by the start and end indices
static inline int TYPED(matcpyele)(TYPED(Matrix) * __dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, const TYPED(Matrix) * __src) {

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

    TYPED(matcpyele_unsafe)(__dest, __istart, __iend, __jstart, __jend, __src);


    return 0;
}


/**================================================================================================
 *!                                        Set/Get Rows/Cols
 *================================================================================================**/

// Set the first __n indices of row __i, starting at column __j
static inline void TYPED(matsetrow)(TYPED(Matrix) *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n) {

    MATRIX_TYPE *row_start = TYPED(matacc)(__A, __i, __j); // start of the row
    memcpy((void *) row_start, (void *) __src, sizeof(MATRIX_TYPE) * __n);

}

static inline void TYPED(matsetcol)(TYPED(Matrix) *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n) {

    MATRIX_TYPE *col_start = TYPED(matacc)(__A, __i, __j); // start of the col
    for (size_t i = 0; i < __n; i++) {
        *(col_start + (__A->nrows * i)) = __src[i];
    }
}
// /**================================================================================================
//  *!                                        Set/Get range of elements
//  *================================================================================================**/

// // Copy the matrix __src into the submatrix of __dest prescribed by the start and end indices
// extern inline int TYPED(matcpyele)(TYPED(Matrix) * __dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, TYPED(Matrix) * __src);

// // Copy the elements of __src into the submatrix of __dest prescribed by the start and end indices WITHOUT CHECKING THE BOUNDS
// extern inline void TYPED(matcpyele_unsafe)(TYPED(Matrix) *__dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, TYPED(Matrix) *__src);

// /**================================================================================================
//  *!                                        Set/Get Rows/Cols
//  *================================================================================================**/

// // Set the first __n indices of row __i, starting at column __j
// extern inline void TYPED(matsetrow)(TYPED(Matrix) *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n);

// extern inline void TYPED(matsetcol)(TYPED(Matrix) *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n);

// matsetrow_mult_k
// matsetrow_div_k
// matsetrow_sub_k
// matsetrow_add_k

// multiply the row of a matrix times the value __k
void TYPED(matsetrow_mult_k)(TYPED(MatIter) __r, const TYPED(MatIter) __row_end, MATRIX_TYPE __k);

// multiply the row of a matrix times the value __k
void TYPED(matsetrow_div_k)(TYPED(MatIter) __r, const TYPED(MatIter) __row_end, MATRIX_TYPE __k);
// multiply the row of a matrix times the value __k
void TYPED(matsetrow_add_k)(TYPED(MatIter) __r, const TYPED(MatIter) __row_end, MATRIX_TYPE __k);

// multiply the row of a matrix times the value __k
void TYPED(matsetrow_sub_k)(TYPED(MatIter) __r, const TYPED(MatIter) __row_end, MATRIX_TYPE __k);

int TYPED(Matrix_mult_row_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k);

int TYPED(Matrix_div_row_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k);
int TYPED(Matrix_add_row_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k);

int TYPED(Matrix_sub_row_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k);

// editing columns now
void TYPED(matsetcol_mult_k)(TYPED(MatIter) __c, const TYPED(MatIter) __col_end, MATRIX_TYPE __k);

// multiply the col of a matrix times the value __k
void TYPED(matsetcol_div_k)(TYPED(MatIter) __c, const TYPED(MatIter) __col_end, MATRIX_TYPE __k);
// multiply the col of a matrix times the value __k
void TYPED(matsetcol_add_k)(TYPED(MatIter) __c, const TYPED(MatIter) __col_end, MATRIX_TYPE __k);

// multiply the col of a matrix times the value __k
void TYPED(matsetcol_sub_k)(TYPED(MatIter) __c, const TYPED(MatIter) __col_end, MATRIX_TYPE __k);

int TYPED(Matrix_mult_col_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k);

int TYPED(Matrix_div_col_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k);
int TYPED(Matrix_add_col_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k);

int TYPED(Matrix_sub_col_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k);




// SETS THE iTH ROW OF __A USING A ROW VECTOR!!!! That is, a ONE by M matrix
int TYPED(Matrix_set_row)(TYPED(Matrix) *__A, size_t __i, const TYPED(Matrix) *__cow);

// SETS THE iTH ROW OF __A USING A ROW VECTOR!!!! That is, a ONE by M matrix
int TYPED(Matrix_set_col)(TYPED(Matrix) *__A, size_t __j, const TYPED(Matrix) *__col);

// It is remarkably faster to extract a specific row since we are just memcpy a certain period of bytes!
TYPED(Matrix) *TYPED(Matrix_get_col)(const TYPED(Matrix) *__A, size_t __j);

// On the other hand, matrow is quite slow since we have to access the elements with a for loop.
// As a design choice, I'd like to implement some sort of low level "row iterator" that will allow us
// to iterate allong the row of a TYPED(Matrix) (to access it later) without actually performing a copy
TYPED(Matrix) *TYPED(Matrix_get_row)(const TYPED(Matrix) *__A, size_t __i);

// I want to create a function that is going to multiply the row of a matrix, starting with it's row iterator.



/**================================================================================================
 *!                                        Set/Get Submatrices
 *================================================================================================**/

// Extract submatrix __A(__istart:__iend, __jstart:__jend)
// This allocates a completely new matrix
TYPED(Matrix) * TYPED(submat)(const TYPED(Matrix) * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

// Alternative spelling for object-oriented approach.
TYPED(Matrix) * TYPED(Matrix_submat)(const TYPED(Matrix) * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

TYPED(Matrix) * TYPED(Matrix_minor)(const TYPED(Matrix) * __A, size_t __irow, size_t __icol);

/**================================================================================================
 *!                                        Set/Get Matrices
 *================================================================================================**/

void TYPED(matfill)(TYPED(Matrix) *__A, const MATRIX_TYPE __value);

// fill matrix with a single value
void TYPED(Matrix_fill)(TYPED(Matrix) * __A, const MATRIX_TYPE value);

/**
 * Set all of the elements who fulfill a mask equal to the value
 */
void TYPED(Matrix_fill_mask)(TYPED(Matrix) *__A, TYPED(Mask) __mask, const MATRIX_TYPE __value);

TYPED(Matrix) *TYPED(Matrix_rcat)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

TYPED(Matrix) *TYPED(Matrix_ccat)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B);

#endif