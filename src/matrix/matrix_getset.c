// Essential routines to get and set elements and columns and rows of matrices

// #include "ejovo_matrix_generic.h"
#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Set/Get Individual Elements
 *================================================================================================**/

// return the value of the element at __m(__i, __j) [zero indexed]
// return -1 if bounds are not respected and prints an error to the screen
// inline MATRIX_TYPE TYPED(Matrix_at)(const TYPED(Matrix) *__m, size_t __i, size_t __j) {

//     if (TYPED(Matrix_valid_bounds)(__m, __i, __j)) {

//         return __m->data[__i * __m->ncols + __j];

//     } else {
//         fprintf(stderr, "**WARNING** Trying to access array element out of bounds. (at)\n");

//         // #if MATRIX_TYPE == Complex
//             // return Complex_zero();
//         // #else
//         return -1;
//         // #endif
//     }
// }

// inline MATRIX_TYPE TYPED(matget)(const TYPED(Matrix) *__m, size_t __i) {
//     return __m->data[__i];
// }

// inline MATRIX_TYPE TYPED(Matrix_first)(const TYPED(Matrix) *__m) {
//     return TYPED(matat)(__m, 0, 0);
// }

// inline MATRIX_TYPE TYPED(Matrix_last)(const TYPED(Matrix) *__m) {
//     return TYPED(matat)(__m, __m->nrows - 1, __m->ncols - 1);
// }



// inline TYPED(MatIter) TYPED(Matrix_end)(const TYPED(Matrix) *__m) {
//     TYPED(MatIter) e = {.ptr = TYPED(matacc)(__m, __m->nrows - 1, __m->ncols), .ptr_diff = 1}; // want the elment justtt after the final one
//     return e;
// }

// // Return element at __m[__i][__j] without checking bounds
// inline MATRIX_TYPE TYPED(matat)(const TYPED(Matrix) *__m, size_t __i, size_t __j) {
//     return __m->data[__i * __m->ncols + __j];
// }

// // set value of the element at __m(__i, __j) [zero indexed]
// // return 0 if the bounds were respected, -1 elsewise
// inline int TYPED(Matrix_set)(TYPED(Matrix) * __m, size_t __i, size_t __j, MATRIX_TYPE __value) {

//     if (TYPED(Matrix_valid_bounds)(__m, __i, __j)) {
//         __m->data[__i*__m->ncols + __j] = __value;
//         return 0;
//     } else {
//         fprintf(stderr, "**WARNING** Trying to access array element out of bounds. (set)\n");
//         return 1;
//     }
// }

// // set value of the element at __m(__i, __j) without checking the indices
// inline void TYPED(matset)(TYPED(Matrix) *__m, size_t __i, size_t __j, MATRIX_TYPE __value) {
//     __m->data[__i * __m->ncols + __j] = __value;
// }

// // return a pointer to the element at __m(__i, __j) [zero indexed]
// inline MATRIX_TYPE *TYPED(Matrix_access)(const TYPED(Matrix) * __m, size_t __i, size_t __j) {
//     return TYPED(matacc_check)(__m, __i, __j);
// }

// // return a pointer to the element at __m(__i, __j) without checking the indices
// inline MATRIX_TYPE *TYPED(matacc)(const TYPED(Matrix) *__m, size_t __i, size_t __j) {
//     return __m->data + (__i * __m->ncols + __j);
// }

// // return a pointer to the element at __m(__i, __j) checking the indices
// // returns null if the bounds are not respected
// inline MATRIX_TYPE *TYPED(matacc_check)(const TYPED(Matrix) *__m, size_t __i, size_t __j) {

//     if (TYPED(Matrix_valid_bounds)(__m, __i, __j)) {
//         return __m->data + (__i*__m->ncols + __j);
//     } else {
//         fprintf(stderr, "**WARNING** Trying to access array element out of bounds. (access)\n");
//         return NULL;
//     }
// }
// /**
//  * Set the element that a pointer is pointing to to __value
//  */
// inline void setelement(MATRIX_TYPE *__el, const MATRIX_TYPE __value) {
//     *__el = __value;
// }

// // Swap __a and __b
// inline void TYPED(matswap)(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
//     MATRIX_TYPE temp = *__a;
//     *(__a) = *(__b);
//     *(__b) = temp;
// }

// /**================================================================================================
//  *!                                        Set/Get range of elements
//  *================================================================================================**/

// // Copy the matrix __src into the submatrix of __dest prescribed by the start and end indices
// inline int TYPED(matcpyele)(TYPED(Matrix) * __dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, TYPED(Matrix) * __src) {

//     // If the submatrix is not contained in __des
//     if (__iend < __istart || __jend < __jstart || __iend >= __dest->nrows || __jend >= __dest->ncols) {
//         perror("Selected submatrix is not contained within Parent Matrix\n");
//         return -1;
//     }

//     // If the __src is not the same size as the selected submatrix
//     if (__src->nrows != (__iend - __istart + 1) || __src->ncols != (__jend - __jstart + 1)) {
//         perror("Selected submatrix not the same size as the src matrix to copy\n");
//         return -2;
//     }

//     TYPED(matcpyele_unsafe)(__dest, __istart, __iend, __jstart, __jend, __src);


//     return 0;
// }

// // Copy the elements of __src into the submatrix of __dest prescribed by the start and end indices WITHOUT CHECKING THE BOUNDS
// inline void TYPED(matcpyele_unsafe)(TYPED(Matrix) *__dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, TYPED(Matrix) *__src) {

//     for (size_t i = __istart, irow = 0; i <= __iend; i++, irow++) {
//         for (size_t j = __jstart, jcol = 0; j <= __jend; j++, jcol++) {
//             TYPED(Matrix_set)(__dest, i, j, TYPED(Matrix_at)(__src, irow, jcol));
//         }
//     }
//     // optimized for row-major access

// }

// /**================================================================================================
//  *!                                        Set/Get Rows/Cols
//  *================================================================================================**/

// // Set the first __n indices of row __i, starting at column __j
// inline void TYPED(matsetrow)(TYPED(Matrix) *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n) {

//     MATRIX_TYPE *row_start = TYPED(matacc)(__A, __i, __j); // start of the row
//     memcpy((void *) row_start, (void *) __src, sizeof(MATRIX_TYPE) * __n);

// }

// inline void TYPED(matsetcol)(TYPED(Matrix) *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n) {

//     MATRIX_TYPE *col_start = TYPED(matacc)(__A, __i, __j); // start of the col
//     for (size_t i = 0; i < __n; i++) {
//         *(col_start + (__A->nrows * i)) = __src[i];
//     }
// }

// matsetrow_mult_k
// matsetrow_div_k
// matsetrow_sub_k
// matsetrow_add_k

// multiply the row of a matrix times the value __k
void TYPED(matsetrow_mult_k)(TYPED(MatIter) __r, const TYPED(MatIter) __row_end, MATRIX_TYPE __k) {

    while(! TYPED(MatIter_cmp)(__r, __row_end)) { // while we haven't reached the end,
        TYPED(multscalar)(__r.ptr, __k);
        __r = TYPED(MatIter_next)(__r);
    }

}

// multiply the row of a matrix times the value __k
void TYPED(matsetrow_div_k)(TYPED(MatIter) __r, const TYPED(MatIter) __row_end, MATRIX_TYPE __k) {

    while(! TYPED(MatIter_cmp)(__r, __row_end)) { // while we haven't reached the end,
        TYPED(divscalar)(__r.ptr, __k);
        __r = TYPED(MatIter_next)(__r);
    }

}
// multiply the row of a matrix times the value __k
void TYPED(matsetrow_add_k)(TYPED(MatIter) __r, const TYPED(MatIter) __row_end, MATRIX_TYPE __k) {

    while(! TYPED(MatIter_cmp)(__r, __row_end)) { // while we haven't reached the end,
        TYPED(addscalar)(__r.ptr, __k);
        __r = TYPED(MatIter_next)(__r);
    }

}

// multiply the row of a matrix times the value __k
void TYPED(matsetrow_sub_k)(TYPED(MatIter) __r, const TYPED(MatIter) __row_end, MATRIX_TYPE __k) {

    while(! TYPED(MatIter_cmp)(__r, __row_end)) { // while we haven't reached the end,
        TYPED(subscalar)(__r.ptr, __k);
        __r = TYPED(MatIter_next)(__r);
    }

}

int TYPED(Matrix_mult_row_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k) {

    const TYPED(MatIter) row_end = TYPED(Matrix_row_end)(__A, __i);
    TYPED(MatIter) row_begin = TYPED(Matrix_row_begin)(__A, __i);

    TYPED(matsetrow_mult_k)(row_begin, row_end, __k);
    return EXIT_SUCCESS;

}

int TYPED(Matrix_div_row_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k) {

    const TYPED(MatIter) row_end = TYPED(Matrix_row_end)(__A, __i);
    TYPED(MatIter) row_begin = TYPED(Matrix_row_begin)(__A, __i);

    TYPED(matsetrow_div_k)(row_begin, row_end, __k);
    return EXIT_SUCCESS;

}
int TYPED(Matrix_add_row_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k) {


    const TYPED(MatIter) row_end = TYPED(Matrix_row_end)(__A, __i);
    TYPED(MatIter) row_begin = TYPED(Matrix_row_begin)(__A, __i);

    TYPED(matsetrow_add_k)(row_begin, row_end, __k);
    return EXIT_SUCCESS;

}

int TYPED(Matrix_sub_row_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k) {

    const TYPED(MatIter) row_end = TYPED(Matrix_row_end)(__A, __i);
    TYPED(MatIter) row_begin = TYPED(Matrix_row_begin)(__A, __i);

    TYPED(matsetrow_sub_k)(row_begin, row_end, __k);
    return EXIT_SUCCESS;

}

// editing columns now
void TYPED(matsetcol_mult_k)(TYPED(MatIter) __c, const TYPED(MatIter) __col_end, MATRIX_TYPE __k) {

    while(! TYPED(MatIter_cmp)(__c, __col_end)) { // while we haven't reached the end,
        TYPED(multscalar)(__c.ptr, __k);
        TYPED(MatIter_next)(__c);
    }

}

// multiply the col of a matrix times the value __k
void TYPED(matsetcol_div_k)(TYPED(MatIter) __c, const TYPED(MatIter) __col_end, MATRIX_TYPE __k) {

    while(! TYPED(MatIter_cmp)(__c, __col_end)) { // while we haven't reached the end,
        TYPED(divscalar)(__c.ptr, __k);
        TYPED(MatIter_next)(__c);
    }

}
// multiply the col of a matrix times the value __k
void TYPED(matsetcol_add_k)(TYPED(MatIter) __c, const TYPED(MatIter) __col_end, MATRIX_TYPE __k) {

    while(! TYPED(MatIter_cmp)(__c, __col_end)) { // while we haven't reached the end,
        TYPED(addscalar)(__c.ptr, __k);
        TYPED(MatIter_next)(__c);
    }

}

// multiply the col of a matrix times the value __k
void TYPED(matsetcol_sub_k)(TYPED(MatIter) __c, const TYPED(MatIter) __col_end, MATRIX_TYPE __k) {

    while(! TYPED(MatIter_cmp)(__c, __col_end)) { // while we haven't reached the end,
        TYPED(subscalar)(__c.ptr, __k);
        TYPED(MatIter_next)(__c);
    }

}

int TYPED(Matrix_mult_col_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k) {

    const TYPED(MatIter) col_end = TYPED(Matrix_col_end)(__A, __i);
    TYPED(MatIter) col_begin = TYPED(Matrix_col_begin)(__A, __i);

    TYPED(matsetcol_mult_k)(col_begin, col_end, __k);
    return EXIT_SUCCESS;

}

int TYPED(Matrix_div_col_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k) {

    const TYPED(MatIter) col_end = TYPED(Matrix_col_end)(__A, __i);
    TYPED(MatIter) col_begin = TYPED(Matrix_col_begin)(__A, __i);

    TYPED(matsetcol_div_k)(col_begin, col_end, __k);
    return EXIT_SUCCESS;

}
int TYPED(Matrix_add_col_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k) {


    const TYPED(MatIter) col_end = TYPED(Matrix_col_end)(__A, __i);
    TYPED(MatIter) col_begin = TYPED(Matrix_col_begin)(__A, __i);

    TYPED(matsetcol_add_k)(col_begin, col_end, __k);
    return EXIT_SUCCESS;

}

int TYPED(Matrix_sub_col_k)(TYPED(Matrix) *__A, const size_t __i, const MATRIX_TYPE __k) {

    const TYPED(MatIter) col_end = TYPED(Matrix_col_end)(__A, __i);
    TYPED(MatIter) col_begin = TYPED(Matrix_col_begin)(__A, __i);

    TYPED(matsetcol_sub_k)(col_begin, col_end, __k);
    return EXIT_SUCCESS;

}




// SETS THE iTH ROW OF __A USING A ROW VECTOR!!!! That is, a ONE by M matrix
int TYPED(Matrix_set_row)(TYPED(Matrix) *__A, size_t __i, const TYPED(Matrix) *__cow) {

    // Check that the __cow matrix is actually a row matrix and that the number of columns match
    if (!TYPED(Matrix_is_row)(__cow)) {
        perror("TYPED(Matrix) is not a row vector");
        return EXIT_FAILURE;
    }
    if (__cow->ncols != __A->ncols) {
        perror("TYPED(Matrix) does not have the same number of cols");
        return EXIT_FAILURE;
    }

    TYPED(matsetrow)(__A, __i, 0, __cow->data, __cow->ncols);
    return EXIT_SUCCESS;

}

// SETS THE iTH ROW OF __A USING A ROW VECTOR!!!! That is, a ONE by M matrix
int TYPED(Matrix_set_col)(TYPED(Matrix) *__A, size_t __j, const TYPED(Matrix) *__col) {

    // Check that the __row matrix is actually a row matrix and that the number of columns match
    if (!TYPED(Matrix_is_col)(__col)) {
        perror("TYPED(Matrix) is not a col vector");
        return EXIT_FAILURE;
    }
    if (__col->nrows != __A->nrows) {
        perror("TYPED(Matrix) does not have the same number of rows");
        return EXIT_FAILURE;
    }

    TYPED(matsetcol)(__A, 0, __j, __col->data, __col->nrows);
    return EXIT_SUCCESS;

}

// It is remarkably faster to extract a specific row since we are just memcpy a certain period of bytes!
TYPED(Matrix) *TYPED(Matrix_get_col)(const TYPED(Matrix) *__A, size_t __j) {
    // don't even check bounds or anything just copy that shit!
    if (__j >= __A->ncols) {
        perror("jth column doesnt exist, returning NULL pointer");
        return NULL;
    }
    // so we want to copy __A->nrow elements.
    TYPED(Matrix) *x = TYPED(matalloc)(__A->nrows, 1);
    // iterate through the proper positions
    for (size_t i = 0; i < __A->nrows; i++) {
        TYPED(matset)(x, i, 0, TYPED(matat)(__A, i, __j));
    }

    return x;

}

// On the other hand, matrow is quite slow since we have to access the elements with a for loop.
// As a design choice, I'd like to implement some sort of low level "row iterator" that will allow us
// to iterate allong the row of a TYPED(Matrix) (to access it later) without actually performing a copy
TYPED(Matrix) *TYPED(Matrix_get_row)(const TYPED(Matrix) *__A, size_t __i) {

    if (__i >= __A->nrows) {
        perror("ith row doesnt exist, returning NULL pointer");
        return NULL;
    }

    // printf("Trying to set row\n");
    TYPED(Matrix) *row = TYPED(matalloc)(1, __A->ncols);
    TYPED(matsetrow)(row, 0, 0, TYPED(matacc)(__A, __i, 0), __A->ncols);
    return row;

}

// I want to create a function that is going to multiply the row of a matrix, starting with it's row iterator.








/**================================================================================================
 *!                                        Set/Get Submatrices
 *================================================================================================**/

// Extract submatrix __A(__istart:__iend, __jstart:__jend)
TYPED(Matrix) * TYPED(submat)(const TYPED(Matrix) * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend) {

    // printf("Entered submat with i0: %lu if: %lu j0: %lu jf: %lu\n", __istart, __iend, __jstart, __jend);

    TYPED(Matrix) * sub = NULL;

    // if the upper bounds are lower than the starting bounds or if the upper indices are larger than the number of rows | cols, return null
    if (__iend < __istart || __jend < __jstart || __iend >= __A->nrows || __jend >= __A->ncols) {
        return sub;
    }

    // printf("First condition passed\n");

    size_t nrows = __iend - __istart + 1;
    size_t ncols = __jend - __jstart + 1;

    sub = TYPED(Matrix_new)(nrows, ncols);

    for (size_t i = __istart, irow = 0; i <= __iend; i++, irow++) {
        for (size_t j = __jstart, icol = 0; j <= __jend; j++, icol++) {
            // printf("Setting (%lu,%lu) to %d\n", irow, icol, TYPED(Matrix_at)(__A, i, j));
            TYPED(matset)(sub, irow, icol, TYPED(matat)(__A, i, j));
        }
    }

    return sub;
}

// Alternative spelling for object-oriented approach.
TYPED(Matrix) * TYPED(Matrix_submat)(const TYPED(Matrix) * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend) {
    return TYPED(submat)(__A, __istart, __iend, __jstart, __jend);
}

TYPED(Matrix) * TYPED(Matrix_minor)(const TYPED(Matrix) * __A, size_t __irow, size_t __icol) {

    // assert(TYPED(Matrix_is_square)(__A));

    // Split matrix into 4 corners
    // printf("nrows: %lu, ncols: %lu\n", __A->nrows, __A->ncols);

    TYPED(Matrix) *upper_left = NULL;
    TYPED(Matrix) *upper_right = NULL;
    TYPED(Matrix) *lower_left = NULL;
    TYPED(Matrix) *lower_right = NULL;
    TYPED(Matrix) *upper_half = NULL;
    TYPED(Matrix) *lower_half = NULL;
    TYPED(Matrix) *composite = NULL;

    if (__irow == 0) {

    // then we only use lower left and lower right

        if (__icol == 0) {
            // then we only use lower right!!
            lower_right = TYPED(Matrix_submat)(__A, 1, __A->nrows - 1, 1, __A->ncols - 1);
            return lower_right;
        } else if (__icol == __A->ncols-1) {
            // then we only use lower left!!
            lower_left = TYPED(Matrix_submat)(__A, 1, __A->nrows - 1, 0, __A->ncols - 2);
            return  lower_left;
        } else {
            lower_left = TYPED(Matrix_submat)(__A, 1, __A->nrows - 1, 0, __icol - 1);
            lower_right = TYPED(Matrix_submat)(__A, 1, __A->nrows - 1, __icol + 1, __A->ncols - 1);
            composite = TYPED(Matrix_ccat)(lower_left, lower_right);

            TYPED(Matrix_reset)(&lower_left);
            TYPED(Matrix_reset)(&lower_right);

            return composite;
        }

    } else if (__irow == __A->nrows - 1) {
    // irow is the last row so we only use the upper left and upper right sections
        // printf("final row selected\n");

        if (__icol == 0) {
            // then we only use upper right!!
            upper_right = TYPED(Matrix_submat)(__A, 0, __A->nrows - 2, 1, __A->ncols - 1);
            return upper_right;
        } else if (__icol == __A->ncols - 1) {
            // then we only use upper left!!
            upper_left = TYPED(Matrix_submat)(__A, 0, __A->nrows - 2, 0, __A->ncols - 2);
            // printf("Only using upper left!");
            return upper_left;
        } else {
            upper_left= TYPED(Matrix_submat)(__A, 0, __A->nrows - 2, 0, __icol - 1);
            upper_right = TYPED(Matrix_submat)(__A, 0, __A->nrows - 2, __icol + 1, __A->ncols - 1);
            composite = TYPED(Matrix_ccat)(upper_left, upper_right);

            TYPED(Matrix_reset)(&upper_left);
            TYPED(Matrix_reset)(&upper_right);

            return composite;
        }

    } else {
        // do whatever
        if (__icol == 0) {
            // use the upper right and lower right sections!
            // printf("Using upper right and lower right sections!\n");
            upper_right = TYPED(Matrix_submat)(__A, 0, __irow-1, 1, __A->ncols - 1);
            lower_right = TYPED(Matrix_submat)(__A, __irow + 1, __A->nrows - 1, 1, __A->ncols - 1);
            composite = TYPED(Matrix_rcat)(upper_right, lower_right);

            TYPED(Matrix_reset)(&upper_right);
            TYPED(Matrix_reset)(&lower_right);

            return composite;

        } else if (__icol == __A->ncols - 1) {
            // use the upper left and lower left sections!
            // printf("using upper_left and lower_left\n");
            upper_left = TYPED(Matrix_submat)(__A, 0, __irow-1, 0, __A->ncols - 2);
            lower_left = TYPED(Matrix_submat)(__A, __irow + 1, __A->nrows - 1, 0, __A->ncols - 2);
            composite = TYPED(Matrix_rcat)(upper_left, lower_left);

            TYPED(Matrix_reset)(&upper_left);
            TYPED(Matrix_reset)(&lower_left);

            return composite;
        } else {
            // use all 4 sections!!!

            upper_left = TYPED(Matrix_submat)(__A, 0, __irow - 1, 0, __icol - 1);
            upper_right = TYPED(Matrix_submat)(__A, 0, __irow - 1, __icol + 1, __A->ncols - 1);
            lower_left = TYPED(Matrix_submat)(__A, __irow + 1, __A->nrows - 1, 0, __icol - 1);
            lower_right = TYPED(Matrix_submat)(__A, __irow + 1, __A->nrows - 1, __icol + 1, __A->ncols - 1);

            upper_half = TYPED(Matrix_ccat)(upper_left, upper_right);
            lower_half = TYPED(Matrix_ccat)(lower_left, lower_right);

            composite = TYPED(Matrix_rcat)(upper_half, lower_half);

            TYPED(Matrix_reset)(&upper_left);
            TYPED(Matrix_reset)(&upper_right);
            TYPED(Matrix_reset)(&lower_left);
            TYPED(Matrix_reset)(&lower_right);
            TYPED(Matrix_reset)(&upper_half);
            TYPED(Matrix_reset)(&lower_half);

            return composite;
        }
    }
}

/**================================================================================================
 *!                                        Set/Get Matrices
 *================================================================================================**/

void TYPED(matfill)(TYPED(Matrix) *__A, const MATRIX_TYPE __value) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            TYPED(matset)(__A, i, j, __value);
        }
    }
}

// fill matrix with a single value
void TYPED(Matrix_fill)(TYPED(Matrix) * __A, const MATRIX_TYPE value) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            TYPED(Matrix_set)(__A, i, j, value);
        }
    }
}

/**
 * Set all of the elements who fulfill a mask equal to the value
 */
void TYPED(Matrix_fill_mask)(TYPED(Matrix) *__A, TYPED(Mask) __mask, const MATRIX_TYPE __value) {
    TYPED(Matrix_mask_k)(__A, __mask, TYPED(setelement), __value);
}

TYPED(Matrix) *TYPED(Matrix_rcat)(const TYPED(Matrix) * __A, const TYPED(Matrix) * __B) {

    if ( __A->ncols != __B->ncols) {
        perror("Cannont row concatenate two incompatible matrices\n");
        return NULL;
    } else {
        TYPED(Matrix) * Mcat = TYPED(Matrix_new)(__A->nrows + __B->nrows, __A->ncols);
        int status1 = TYPED(matcpyele)(Mcat, 0, __A->nrows - 1, 0, __A->ncols - 1, __A);
        int status2 = TYPED(matcpyele)(Mcat, __A->nrows, __A->nrows + __B->nrows - 1, 0, __A->ncols - 1, __B);

        if (status1 < 0 || status2 < 0) {
            TYPED(Matrix_reset)(&Mcat);
            return NULL;
        } else {
            return Mcat;
        }
    }
}

TYPED(Matrix) *TYPED(Matrix_ccat)(const TYPED(Matrix) *__A, const TYPED(Matrix) *__B) {

    if ( __A->nrows != __B->nrows) {
        perror("Cannont col concatenate two incompatible matrices\n");
        return NULL;
    } else {
        TYPED(Matrix) * Mcat = TYPED(Matrix_new)(__A->nrows, __A->ncols + __B->ncols);
        int status1 = TYPED(matcpyele)(Mcat, 0, __A->nrows - 1, 0, __A->ncols - 1, __A);
        int status2 = TYPED(matcpyele)(Mcat, 0, __A->nrows - 1, __A->ncols, __A->ncols + __B->ncols - 1, __B);

        if (status1 < 0 || status2 < 0) {
            TYPED(Matrix_reset)(&Mcat);
            return NULL;
        } else {
            return Mcat;
        }
    }
}