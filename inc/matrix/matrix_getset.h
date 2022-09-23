#pragma once

// Essential routines to get and set elements and columns and rows of matrices

#include "matrix.h"
#include "matrix_state.h"

/**================================================================================================
 *!                                        Set/Get Individual Elements
 *================================================================================================**/


static inline MATRIX_TYPE matget(const Matrix *__m, size_t __i) {
    return __m->data[__i];
}

// set value of the element at __m(__i, __j) without checking the indices
static inline void matset(Matrix *__m, size_t __i, size_t __j, MATRIX_TYPE __value) {
    __m->data[__i * __m->ncols + __j] = __value;
}

// Return element at __m[__i][__j] without checking bounds
static inline MATRIX_TYPE matat(const Matrix *__m, size_t __i, size_t __j) {
    return __m->data[__i * __m->ncols + __j];
}

// return a pointer to the element at __m(__i, __j) without checking the indices
static inline MATRIX_TYPE *matacc(const Matrix *__m, size_t __i, size_t __j) {
    return __m->data + (__i * __m->ncols + __j);
}

/**
 * Set the element that a pointer is pointing to to __value
 */
static inline void setelement(MATRIX_TYPE *__el, const MATRIX_TYPE __value) {
    *__el = __value;
}

// Swap __a and __b
static inline void matswap(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    MATRIX_TYPE temp = *__a;
    *(__a) = *(__b);
    *(__b) = temp;
}

static inline MATRIX_TYPE Matrix_first(const Matrix *__m) {
    return matat(__m, 0, 0);
}

static inline MATRIX_TYPE Matrix_last(const Matrix *__m) {
    return matat(__m, __m->nrows - 1, __m->ncols - 1);
}

static inline MatIter Matrix_begin(const Matrix *__m) {
    MatIter b = {.ptr = __m->data, .ptr_diff = 1};
    return b;
}

static inline MatIter Matrix_end(const Matrix *__m) {
    MatIter e = {.ptr = matacc(__m, __m->nrows - 1, __m->ncols), .ptr_diff = 1}; // want the elment justtt after the final one
    return e;
}


// set value of the element at __m(__i, __j) [zero indexed]
// return 0 if the bounds were respected, -1 elsewise
static inline int Matrix_set(Matrix * __m, size_t __i, size_t __j, MATRIX_TYPE __value) {

    if (Matrix_valid_bounds(__m, __i, __j)) {
        __m->data[__i*__m->ncols + __j] = __value;
        return 0;
    } else {
        fprintf(stderr, "**WARNING** Trying to access array element out of bounds. (set)\n");
        return 1;
    }
}

// return a pointer to the element at __m(__i, __j) checking the indices
// returns null if the bounds are not respected
static inline MATRIX_TYPE *matacc_check(const Matrix *__m, size_t __i, size_t __j) {

    if (Matrix_valid_bounds(__m, __i, __j)) {
        return __m->data + (__i*__m->ncols + __j);
    } else {
        fprintf(stderr, "**WARNING** Trying to access array element out of bounds. (access)\n");
        return NULL;
    }
}


// return a pointer to the element at __m(__i, __j) [zero indexed]
static inline MATRIX_TYPE *Matrix_access(const Matrix * __m, size_t __i, size_t __j) {
    return matacc_check(__m, __i, __j);
}


// return the value of the element at __m(__i, __j) [zero indexed]
// return -1 if bounds are not respected and prints an error to the screen
static inline MATRIX_TYPE Matrix_at(const Matrix *__m, size_t __i, size_t __j) {

    if (Matrix_valid_bounds(__m, __i, __j)) {

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
static inline void matcpyele_unsafe(Matrix *__dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, const Matrix *__src) {

    for (size_t i = __istart, irow = 0; i <= __iend; i++, irow++) {
        for (size_t j = __jstart, jcol = 0; j <= __jend; j++, jcol++) {
            Matrix_set(__dest, i, j, Matrix_at(__src, irow, jcol));
        }
    }
    // optimized for row-major access

}

// Copy the matrix __src into the submatrix of __dest prescribed by the start and end indices
static inline int matcpyele(Matrix * __dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, const Matrix * __src) {

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

    matcpyele_unsafe(__dest, __istart, __iend, __jstart, __jend, __src);


    return 0;
}


/**================================================================================================
 *!                                        Set/Get Rows/Cols
 *================================================================================================**/

// Set the first __n indices of row __i, starting at column __j
static inline void matsetrow(Matrix *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n) {

    MATRIX_TYPE *row_start = matacc(__A, __i, __j); // start of the row
    memcpy((void *) row_start, (void *) __src, sizeof(MATRIX_TYPE) * __n);

}

static inline void matsetcol(Matrix *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n) {

    MATRIX_TYPE *col_start = matacc(__A, __i, __j); // start of the col
    for (size_t i = 0; i < __n; i++) {
        *(col_start + (__A->nrows * i)) = __src[i];
    }
}
// /**================================================================================================
//  *!                                        Set/Get range of elements
//  *================================================================================================**/

// // Copy the matrix __src into the submatrix of __dest prescribed by the start and end indices
// extern inline int matcpyele(Matrix * __dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, Matrix * __src);

// // Copy the elements of __src into the submatrix of __dest prescribed by the start and end indices WITHOUT CHECKING THE BOUNDS
// extern inline void matcpyele_unsafe(Matrix *__dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, Matrix *__src);

// /**================================================================================================
//  *!                                        Set/Get Rows/Cols
//  *================================================================================================**/

// // Set the first __n indices of row __i, starting at column __j
// extern inline void matsetrow(Matrix *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n);

// extern inline void matsetcol(Matrix *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n);

// matsetrow_mult_k
// matsetrow_div_k
// matsetrow_sub_k
// matsetrow_add_k

// multiply the row of a matrix times the value __k
void matsetrow_mult_k(Matrix *__A, MatIter __r, const MatIter __row_end, MATRIX_TYPE __k);

// multiply the row of a matrix times the value __k
void matsetrow_div_k(Matrix *__A, MatIter __r, const MatIter __row_end, MATRIX_TYPE __k);
// multiply the row of a matrix times the value __k
void matsetrow_add_k(Matrix *__A, MatIter __r, const MatIter __row_end, MATRIX_TYPE __k);

// multiply the row of a matrix times the value __k
void matsetrow_sub_k(Matrix *__A, MatIter __r, const MatIter __row_end, MATRIX_TYPE __k);

int Matrix_mult_row_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);

int Matrix_div_row_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);
int Matrix_add_row_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);

int Matrix_sub_row_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);

// editing columns now
void matsetcol_mult_k(Matrix *__A, MatIter __c, const MatIter __col_end, MATRIX_TYPE __k);

// multiply the col of a matrix times the value __k
void matsetcol_div_k(Matrix *__A, MatIter __c, const MatIter __col_end, MATRIX_TYPE __k);
// multiply the col of a matrix times the value __k
void matsetcol_add_k(Matrix *__A, MatIter __c, const MatIter __col_end, MATRIX_TYPE __k);

// multiply the col of a matrix times the value __k
void matsetcol_sub_k(Matrix *__A, MatIter __c, const MatIter __col_end, MATRIX_TYPE __k);

int Matrix_mult_col_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);

int Matrix_div_col_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);
int Matrix_add_col_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);

int Matrix_sub_col_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k);




// SETS THE iTH ROW OF __A USING A ROW VECTOR!!!! That is, a ONE by M matrix
int Matrix_set_row(Matrix *__A, size_t __i, const Matrix *__cow);

// SETS THE iTH ROW OF __A USING A ROW VECTOR!!!! That is, a ONE by M matrix
int Matrix_set_col(Matrix *__A, size_t __j, const Matrix *__col);

// It is remarkably faster to extract a specific row since we are just memcpy a certain period of bytes!
Matrix *Matrix_get_col(const Matrix *__A, size_t __j);

// On the other hand, matrow is quite slow since we have to access the elements with a for loop.
// As a design choice, I'd like to implement some sort of low level "row iterator" that will allow us
// to iterate allong the row of a Matrix (to access it later) without actually performing a copy
Matrix *Matrix_get_row(const Matrix *__A, size_t __i);

// I want to create a function that is going to multiply the row of a matrix, starting with it's row iterator.








/**================================================================================================
 *!                                        Set/Get Submatrices
 *================================================================================================**/

// Extract submatrix __A(__istart:__iend, __jstart:__jend)
// This allocates a completely new matrix
Matrix * submat(const Matrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

// Alternative spelling for object-oriented approach.
Matrix * Matrix_submat(const Matrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend);

Matrix * Matrix_minor(const Matrix * __A, size_t __irow, size_t __icol);

/**================================================================================================
 *!                                        Set/Get Matrices
 *================================================================================================**/

void matfill(Matrix *__A, const MATRIX_TYPE __value);

// fill matrix with a single value
void Matrix_fill(Matrix * __A, const MATRIX_TYPE value);

/**
 * Set all of the elements who fulfill a mask equal to the value
 */
void Matrix_fill_mask(Matrix *__A, Mask __mask, const MATRIX_TYPE __value);

Matrix *Matrix_rcat(const Matrix *__A, const Matrix *__B);

Matrix *Matrix_ccat(const Matrix *__A, const Matrix *__B);