// Essential routines to get and set elements and columns and rows of matrices

#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Set/Get Individual Elements
 *================================================================================================**/

// return the value of the element at __m(__i, __j) [zero indexed]
// return -1 if bounds are not respected and prints an error to the screen
// inline MATRIX_TYPE MATRIX_FN(at)(const MATRIX_T *__m, size_t __i, size_t __j) {

//     if (MATRIX_FN(valid_bounds)(__m, __i, __j)) {

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

// inline MATRIX_TYPE MAT_FN(get)(const MATRIX_T *__m, size_t __i) {
//     return __m->data[__i];
// }

// inline MATRIX_TYPE MATRIX_FN(first)(const MATRIX_T *__m) {
//     return MAT_FN(at)(__m, 0, 0);
// }

// inline MATRIX_TYPE MATRIX_FN(last)(const MATRIX_T *__m) {
//     return MAT_FN(at)(__m, __m->nrows - 1, __m->ncols - 1);
// }



// inline MATITER_T MATRIX_FN(end)(const MATRIX_T *__m) {
//     MATITER_T e = {.ptr = MAT_FN(acc)(__m, __m->nrows - 1, __m->ncols), .ptr_diff = 1}; // want the elment justtt after the final one
//     return e;
// }

// // Return element at __m[__i][__j] without checking bounds
// inline MATRIX_TYPE MAT_FN(at)(const MATRIX_T *__m, size_t __i, size_t __j) {
//     return __m->data[__i * __m->ncols + __j];
// }

// // set value of the element at __m(__i, __j) [zero indexed]
// // return 0 if the bounds were respected, -1 elsewise
// inline int MATRIX_FN(set)(MATRIX_T * __m, size_t __i, size_t __j, MATRIX_TYPE __value) {

//     if (MATRIX_FN(valid_bounds)(__m, __i, __j)) {
//         __m->data[__i*__m->ncols + __j] = __value;
//         return 0;
//     } else {
//         fprintf(stderr, "**WARNING** Trying to access array element out of bounds. (set)\n");
//         return 1;
//     }
// }

// // set value of the element at __m(__i, __j) without checking the indices
// inline void MAT_FN(set)(MATRIX_T *__m, size_t __i, size_t __j, MATRIX_TYPE __value) {
//     __m->data[__i * __m->ncols + __j] = __value;
// }

// // return a pointer to the element at __m(__i, __j) [zero indexed]
// inline MATRIX_TYPE *MATRIX_FN(access)(const MATRIX_T * __m, size_t __i, size_t __j) {
//     return MAT_FN(acc_check)(__m, __i, __j);
// }

// // return a pointer to the element at __m(__i, __j) without checking the indices
// inline MATRIX_TYPE *MAT_FN(acc)(const MATRIX_T *__m, size_t __i, size_t __j) {
//     return __m->data + (__i * __m->ncols + __j);
// }

// // return a pointer to the element at __m(__i, __j) checking the indices
// // returns null if the bounds are not respected
// inline MATRIX_TYPE *MAT_FN(acc_check)(const MATRIX_T *__m, size_t __i, size_t __j) {

//     if (MATRIX_FN(valid_bounds)(__m, __i, __j)) {
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
// inline void MAT_FN(swap)(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
//     MATRIX_TYPE temp = *__a;
//     *(__a) = *(__b);
//     *(__b) = temp;
// }

// /**================================================================================================
//  *!                                        Set/Get range of elements
//  *================================================================================================**/

// // Copy the matrix __src into the submatrix of __dest prescribed by the start and end indices
// inline int MAT_FN(cpyele)(MATRIX_T * __dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, MATRIX_T * __src) {

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

//     MAT_FN(cpyele_unsafe)(__dest, __istart, __iend, __jstart, __jend, __src);


//     return 0;
// }

// // Copy the elements of __src into the submatrix of __dest prescribed by the start and end indices WITHOUT CHECKING THE BOUNDS
// inline void MAT_FN(cpyele_unsafe)(MATRIX_T *__dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, MATRIX_T *__src) {

//     for (size_t i = __istart, irow = 0; i <= __iend; i++, irow++) {
//         for (size_t j = __jstart, jcol = 0; j <= __jend; j++, jcol++) {
//             MATRIX_FN(set)(__dest, i, j, MATRIX_FN(at)(__src, irow, jcol));
//         }
//     }
//     // optimized for row-major access

// }

// /**================================================================================================
//  *!                                        Set/Get Rows/Cols
//  *================================================================================================**/

// // Set the first __n indices of row __i, starting at column __j
// inline void MAT_FN(setrow)(MATRIX_T *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n) {

//     MATRIX_TYPE *row_start = MAT_FN(acc)(__A, __i, __j); // start of the row
//     memcpy((void *) row_start, (void *) __src, sizeof(MATRIX_TYPE) * __n);

// }

// inline void MAT_FN(setcol)(MATRIX_T *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n) {

//     MATRIX_TYPE *col_start = MAT_FN(acc)(__A, __i, __j); // start of the col
//     for (size_t i = 0; i < __n; i++) {
//         *(col_start + (__A->nrows * i)) = __src[i];
//     }
// }

// matsetrow_mult_k
// matsetrow_div_k
// matsetrow_sub_k
// matsetrow_add_k

// multiply the row of a matrix times the value __k
void MAT_FN(setrow_mult_k)(MATRIX_T *__A, MATITER_T __r, const MATITER_T __row_end, MATRIX_TYPE __k) {

    while(! MATITER_FN(cmp)(__r, __row_end)) { // while we haven't reached the end,
        multscalar(__r.ptr, __k);
        __r = MATITER_FN(next)(__r);
    }

}

// multiply the row of a matrix times the value __k
void MAT_FN(setrow_div_k)(MATRIX_T *__A, MATITER_T __r, const MATITER_T __row_end, MATRIX_TYPE __k) {

    while(! MATITER_FN(cmp)(__r, __row_end)) { // while we haven't reached the end,
        divscalar(__r.ptr, __k);
        __r = MATITER_FN(next)(__r);
    }

}
// multiply the row of a matrix times the value __k
void MAT_FN(setrow_add_k)(MATRIX_T *__A, MATITER_T __r, const MATITER_T __row_end, MATRIX_TYPE __k) {

    while(! MATITER_FN(cmp)(__r, __row_end)) { // while we haven't reached the end,
        addscalar(__r.ptr, __k);
        __r = MATITER_FN(next)(__r);
    }

}

// multiply the row of a matrix times the value __k
void MAT_FN(setrow_sub_k)(MATRIX_T *__A, MATITER_T __r, const MATITER_T __row_end, MATRIX_TYPE __k) {

    while(! MATITER_FN(cmp)(__r, __row_end)) { // while we haven't reached the end,
        subscalar(__r.ptr, __k);
        __r = MATITER_FN(next)(__r);
    }

}

int MATRIX_FN(mult_row_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k) {

    const MATITER_T row_end = MATRIX_FN(row_end)(__A, __i);
    MATITER_T row_begin = MATRIX_FN(row_begin)(__A, __i);

    MAT_FN(setrow_mult_k)(__A, row_begin, row_end, __k);
    return EXIT_SUCCESS;

}

int MATRIX_FN(div_row_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k) {

    const MATITER_T row_end = MATRIX_FN(row_end)(__A, __i);
    MATITER_T row_begin = MATRIX_FN(row_begin)(__A, __i);

    MAT_FN(setrow_div_k)(__A, row_begin, row_end, __k);
    return EXIT_SUCCESS;

}
int MATRIX_FN(add_row_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k) {


    const MATITER_T row_end = MATRIX_FN(row_end)(__A, __i);
    MATITER_T row_begin = MATRIX_FN(row_begin)(__A, __i);

    MAT_FN(setrow_add_k)(__A, row_begin, row_end, __k);
    return EXIT_SUCCESS;

}

int MATRIX_FN(sub_row_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k) {

    const MATITER_T row_end = MATRIX_FN(row_end)(__A, __i);
    MATITER_T row_begin = MATRIX_FN(row_begin)(__A, __i);

    MAT_FN(setrow_sub_k)(__A, row_begin, row_end, __k);
    return EXIT_SUCCESS;

}

// editing columns now
void MAT_FN(setcol_mult_k)(MATRIX_T *__A, MATITER_T __c, const MATITER_T __col_end, MATRIX_TYPE __k) {

    while(! MATITER_FN(cmp)(__c, __col_end)) { // while we haven't reached the end,
        multscalar(__c.ptr, __k);
        MATITER_FN(next)(__c);
    }

}

// multiply the col of a matrix times the value __k
void MAT_FN(setcol_div_k)(MATRIX_T *__A, MATITER_T __c, const MATITER_T __col_end, MATRIX_TYPE __k) {

    while(! MATITER_FN(cmp)(__c, __col_end)) { // while we haven't reached the end,
        divscalar(__c.ptr, __k);
        MATITER_FN(next)(__c);
    }

}
// multiply the col of a matrix times the value __k
void MAT_FN(setcol_add_k)(MATRIX_T *__A, MATITER_T __c, const MATITER_T __col_end, MATRIX_TYPE __k) {

    while(! MATITER_FN(cmp)(__c, __col_end)) { // while we haven't reached the end,
        addscalar(__c.ptr, __k);
        MATITER_FN(next)(__c);
    }

}

// multiply the col of a matrix times the value __k
void MAT_FN(setcol_sub_k)(MATRIX_T *__A, MATITER_T __c, const MATITER_T __col_end, MATRIX_TYPE __k) {

    while(! MATITER_FN(cmp)(__c, __col_end)) { // while we haven't reached the end,
        subscalar(__c.ptr, __k);
        MATITER_FN(next)(__c);
    }

}

int MATRIX_FN(mult_col_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k) {

    const MATITER_T col_end = MATRIX_FN(col_end)(__A, __i);
    MATITER_T col_begin = MATRIX_FN(col_begin)(__A, __i);

    MAT_FN(setcol_mult_k)(__A, col_begin, col_end, __k);
    return EXIT_SUCCESS;

}

int MATRIX_FN(div_col_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k) {

    const MATITER_T col_end = MATRIX_FN(col_end)(__A, __i);
    MATITER_T col_begin = MATRIX_FN(col_begin)(__A, __i);

    MAT_FN(setcol_div_k)(__A, col_begin, col_end, __k);
    return EXIT_SUCCESS;

}
int MATRIX_FN(add_col_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k) {


    const MATITER_T col_end = MATRIX_FN(col_end)(__A, __i);
    MATITER_T col_begin = MATRIX_FN(col_begin)(__A, __i);

    MAT_FN(setcol_add_k)(__A, col_begin, col_end, __k);
    return EXIT_SUCCESS;

}

int MATRIX_FN(sub_col_k)(MATRIX_T *__A, const size_t __i, const MATRIX_TYPE __k) {

    const MATITER_T col_end = MATRIX_FN(col_end)(__A, __i);
    MATITER_T col_begin = MATRIX_FN(col_begin)(__A, __i);

    MAT_FN(setcol_sub_k)(__A, col_begin, col_end, __k);
    return EXIT_SUCCESS;

}




// SETS THE iTH ROW OF __A USING A ROW VECTOR!!!! That is, a ONE by M matrix
int MATRIX_FN(set_row)(MATRIX_T *__A, size_t __i, const MATRIX_T *__cow) {

    // Check that the __cow matrix is actually a row matrix and that the number of columns match
    if (!MATRIX_FN(is_row)(__cow)) {
        perror("MATRIX_T is not a row vector");
        return EXIT_FAILURE;
    }
    if (__cow->ncols != __A->ncols) {
        perror("MATRIX_T does not have the same number of cols");
        return EXIT_FAILURE;
    }

    MAT_FN(setrow)(__A, __i, 0, __cow->data, __cow->ncols);
    return EXIT_SUCCESS;

}

// SETS THE iTH ROW OF __A USING A ROW VECTOR!!!! That is, a ONE by M matrix
int MATRIX_FN(set_col)(MATRIX_T *__A, size_t __j, const MATRIX_T *__col) {

    // Check that the __row matrix is actually a row matrix and that the number of columns match
    if (!MATRIX_FN(is_col)(__col)) {
        perror("MATRIX_T is not a col vector");
        return EXIT_FAILURE;
    }
    if (__col->nrows != __A->nrows) {
        perror("MATRIX_T does not have the same number of rows");
        return EXIT_FAILURE;
    }

    MAT_FN(setcol)(__A, 0, __j, __col->data, __col->nrows);
    return EXIT_SUCCESS;

}

// It is remarkably faster to extract a specific row since we are just memcpy a certain period of bytes!
MATRIX_T *MATRIX_FN(get_col)(const MATRIX_T *__A, size_t __j) {
    // don't even check bounds or anything just copy that shit!
    if (__j >= __A->ncols) {
        perror("jth column doesnt exist, returning NULL pointer");
        return NULL;
    }
    // so we want to copy __A->nrow elements.
    MATRIX_T *x = MAT_FN(alloc)(__A->nrows, 1);
    // iterate through the proper positions
    for (size_t i = 0; i < __A->nrows; i++) {
        MAT_FN(set)(x, i, 0, MAT_FN(at)(__A, i, __j));
    }

    return x;

}

// On the other hand, matrow is quite slow since we have to access the elements with a for loop.
// As a design choice, I'd like to implement some sort of low level "row iterator" that will allow us
// to iterate allong the row of a MATRIX_T (to access it later) without actually performing a copy
MATRIX_T *MATRIX_FN(get_row)(const MATRIX_T *__A, size_t __i) {

    if (__i >= __A->nrows) {
        perror("ith row doesnt exist, returning NULL pointer");
        return NULL;
    }

    // printf("Trying to set row\n");
    MATRIX_T *row = MAT_FN(alloc)(1, __A->ncols);
    MAT_FN(setrow)(row, 0, 0, MAT_FN(acc)(__A, __i, 0), __A->ncols);
    return row;

}

// I want to create a function that is going to multiply the row of a matrix, starting with it's row iterator.








/**================================================================================================
 *!                                        Set/Get Submatrices
 *================================================================================================**/

// Extract submatrix __A(__istart:__iend, __jstart:__jend)
MATRIX_T * CAT(sub, MAT_T)(const MATRIX_T * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend) {

    // printf("Entered submat with i0: %lu if: %lu j0: %lu jf: %lu\n", __istart, __iend, __jstart, __jend);

    MATRIX_T * sub = NULL;

    // if the upper bounds are lower than the starting bounds or if the upper indices are larger than the number of rows | cols, return null
    if (__iend < __istart || __jend < __jstart || __iend >= __A->nrows || __jend >= __A->ncols) {
        return sub;
    }

    // printf("First condition passed\n");

    size_t nrows = __iend - __istart + 1;
    size_t ncols = __jend - __jstart + 1;

    sub = MATRIX_FN(new)(nrows, ncols);

    for (size_t i = __istart, irow = 0; i <= __iend; i++, irow++) {
        for (size_t j = __jstart, icol = 0; j <= __jend; j++, icol++) {
            // printf("Setting (%lu,%lu) to %d\n", irow, icol, MATRIX_FN(at)(__A, i, j));
            MAT_FN(set)(sub, irow, icol, MAT_FN(at)(__A, i, j));
        }
    }

    return sub;
}

// Alternative spelling for object-oriented approach.
MATRIX_T * MATRIX_FN(submat)(const MATRIX_T * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend) {
    return CAT(sub, MAT_T)(__A, __istart, __iend, __jstart, __jend);
}

MATRIX_T * MATRIX_FN(minor)(const MATRIX_T * __A, size_t __irow, size_t __icol) {

    // assert(MATRIX_FN(is_square)(__A));

    // Split matrix into 4 corners
    // printf("nrows: %lu, ncols: %lu\n", __A->nrows, __A->ncols);

    MATRIX_T *upper_left = NULL;
    MATRIX_T *upper_right = NULL;
    MATRIX_T *lower_left = NULL;
    MATRIX_T *lower_right = NULL;
    MATRIX_T *upper_half = NULL;
    MATRIX_T *lower_half = NULL;
    MATRIX_T *composite = NULL;

    if (__irow == 0) {

    // then we only use lower left and lower right

        if (__icol == 0) {
            // then we only use lower right!!
            lower_right = MATRIX_FN(submat)(__A, 1, __A->nrows - 1, 1, __A->ncols - 1);
            return lower_right;
        } else if (__icol == __A->ncols-1) {
            // then we only use lower left!!
            lower_left = MATRIX_FN(submat)(__A, 1, __A->nrows - 1, 0, __A->ncols - 2);
            return  lower_left;
        } else {
            lower_left = MATRIX_FN(submat)(__A, 1, __A->nrows - 1, 0, __icol - 1);
            lower_right = MATRIX_FN(submat)(__A, 1, __A->nrows - 1, __icol + 1, __A->ncols - 1);
            composite = MATRIX_FN(ccat)(lower_left, lower_right);

            MATRIX_FN(reset)(&lower_left);
            MATRIX_FN(reset)(&lower_right);

            return composite;
        }

    } else if (__irow == __A->nrows - 1) {
    // irow is the last row so we only use the upper left and upper right sections
        // printf("final row selected\n");

        if (__icol == 0) {
            // then we only use upper right!!
            upper_right = MATRIX_FN(submat)(__A, 0, __A->nrows - 2, 1, __A->ncols - 1);
            return upper_right;
        } else if (__icol == __A->ncols - 1) {
            // then we only use upper left!!
            upper_left = MATRIX_FN(submat)(__A, 0, __A->nrows - 2, 0, __A->ncols - 2);
            // printf("Only using upper left!");
            return upper_left;
        } else {
            upper_left= MATRIX_FN(submat)(__A, 0, __A->nrows - 2, 0, __icol - 1);
            upper_right = MATRIX_FN(submat)(__A, 0, __A->nrows - 2, __icol + 1, __A->ncols - 1);
            composite = MATRIX_FN(ccat)(upper_left, upper_right);

            MATRIX_FN(reset)(&upper_left);
            MATRIX_FN(reset)(&upper_right);

            return composite;
        }

    } else {
        // do whatever
        if (__icol == 0) {
            // use the upper right and lower right sections!
            // printf("Using upper right and lower right sections!\n");
            upper_right = MATRIX_FN(submat)(__A, 0, __irow-1, 1, __A->ncols - 1);
            lower_right = MATRIX_FN(submat)(__A, __irow + 1, __A->nrows - 1, 1, __A->ncols - 1);
            composite = MATRIX_FN(rcat)(upper_right, lower_right);

            MATRIX_FN(reset)(&upper_right);
            MATRIX_FN(reset)(&lower_right);

            return composite;

        } else if (__icol == __A->ncols - 1) {
            // use the upper left and lower left sections!
            // printf("using upper_left and lower_left\n");
            upper_left = MATRIX_FN(submat)(__A, 0, __irow-1, 0, __A->ncols - 2);
            lower_left = MATRIX_FN(submat)(__A, __irow + 1, __A->nrows - 1, 0, __A->ncols - 2);
            composite = MATRIX_FN(rcat)(upper_left, lower_left);

            MATRIX_FN(reset)(&upper_left);
            MATRIX_FN(reset)(&lower_left);

            return composite;
        } else {
            // use all 4 sections!!!

            upper_left = MATRIX_FN(submat)(__A, 0, __irow - 1, 0, __icol - 1);
            upper_right = MATRIX_FN(submat)(__A, 0, __irow - 1, __icol + 1, __A->ncols - 1);
            lower_left = MATRIX_FN(submat)(__A, __irow + 1, __A->nrows - 1, 0, __icol - 1);
            lower_right = MATRIX_FN(submat)(__A, __irow + 1, __A->nrows - 1, __icol + 1, __A->ncols - 1);

            upper_half = MATRIX_FN(ccat)(upper_left, upper_right);
            lower_half = MATRIX_FN(ccat)(lower_left, lower_right);

            composite = MATRIX_FN(rcat)(upper_half, lower_half);

            MATRIX_FN(reset)(&upper_left);
            MATRIX_FN(reset)(&upper_right);
            MATRIX_FN(reset)(&lower_left);
            MATRIX_FN(reset)(&lower_right);
            MATRIX_FN(reset)(&upper_half);
            MATRIX_FN(reset)(&lower_half);

            return composite;
        }
    }
}

/**================================================================================================
 *!                                        Set/Get Matrices
 *================================================================================================**/

void MAT_FN(fill)(MATRIX_T *__A, const MATRIX_TYPE __value) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            MAT_FN(set)(__A, i, j, __value);
        }
    }
}

// fill matrix with a single value
void MATRIX_FN(fill)(MATRIX_T * __A, const MATRIX_TYPE value) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            MATRIX_FN(set)(__A, i, j, value);
        }
    }
}

/**
 * Set all of the elements who fulfill a mask equal to the value
 */
void MATRIX_FN(fill_mask)(MATRIX_T *__A, Mask __mask, const MATRIX_TYPE __value) {
    MATRIX_FN(mask_k)(__A, __mask, setelement, __value);
}

MATRIX_T *MATRIX_FN(rcat)(const MATRIX_T * __A, const MATRIX_T * __B) {

    if ( __A->ncols != __B->ncols) {
        perror("Cannont row concatenate two incompatible matrices\n");
        return NULL;
    } else {
        MATRIX_T * Mcat = MATRIX_FN(new)(__A->nrows + __B->nrows, __A->ncols);
        int status1 = MAT_FN(cpyele)(Mcat, 0, __A->nrows - 1, 0, __A->ncols - 1, __A);
        int status2 = MAT_FN(cpyele)(Mcat, __A->nrows, __A->nrows + __B->nrows - 1, 0, __A->ncols - 1, __B);

        if (status1 < 0 || status2 < 0) {
            MATRIX_FN(reset)(&Mcat);
            return NULL;
        } else {
            return Mcat;
        }
    }
}

MATRIX_T *MATRIX_FN(ccat)(const MATRIX_T *__A, const MATRIX_T *__B) {

    if ( __A->nrows != __B->nrows) {
        perror("Cannont col concatenate two incompatible matrices\n");
        return NULL;
    } else {
        MATRIX_T * Mcat = MATRIX_FN(new)(__A->nrows, __A->ncols + __B->ncols);
        int status1 = MAT_FN(cpyele)(Mcat, 0, __A->nrows - 1, 0, __A->ncols - 1, __A);
        int status2 = MAT_FN(cpyele)(Mcat, 0, __A->nrows - 1, __A->ncols, __A->ncols + __B->ncols - 1, __B);

        if (status1 < 0 || status2 < 0) {
            MATRIX_FN(reset)(&Mcat);
            return NULL;
        } else {
            return Mcat;
        }
    }
}