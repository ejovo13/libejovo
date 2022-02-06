// Essential routines to get and set elements and columns and rows of matrices

#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Set/Get Individual Elements
 *================================================================================================**/

// return the value of the element at __m(__i, __j) [zero indexed]
// return -1 if bounds are not respected and prints an error to the screen
MATRIX_TYPE Matrix_at(const Matrix *__m, size_t __i, size_t __j) {

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

// Return element at __m[__i][__j] without checking bounds
MATRIX_TYPE matat(const Matrix *__m, size_t __i, size_t __j) {
    return __m->data[__i * __m->ncols + __j];
}

// set value of the element at __m(__i, __j) [zero indexed]
// return 0 if the bounds were respected, -1 elsewise
int Matrix_set(Matrix * __m, size_t __i, size_t __j, MATRIX_TYPE __value) {

    if (Matrix_valid_bounds(__m, __i, __j)) {
        __m->data[__i*__m->ncols + __j] = __value;
        return 0;
    } else {
        fprintf(stderr, "**WARNING** Trying to access array element out of bounds. (set)\n");
        return 1;
    }
}

// set value of the element at __m(__i, __j) without checking the indices
void matset(Matrix *__m, size_t __i, size_t __j, MATRIX_TYPE __value) {
    __m->data[__i * __m->ncols + __j] = __value;
}

// return a pointer to the element at __m(__i, __j) [zero indexed]
MATRIX_TYPE *Matrix_access(const Matrix * __m, size_t __i, size_t __j) {
    return matacc_check(__m, __i, __j);
}

// return a pointer to the element at __m(__i, __j) without checking the indices
MATRIX_TYPE *matacc(const Matrix *__m, size_t __i, size_t __j) {
    return __m->data + (__i * __m->ncols + __j);
}

// return a pointer to the element at __m(__i, __j) checking the indices
// returns null if the bounds are not respected
MATRIX_TYPE *matacc_check(const Matrix *__m, size_t __i, size_t __j) {

    if (Matrix_valid_bounds(__m, __i, __j)) {
        return __m->data + (__i*__m->ncols + __j);
    } else {
        fprintf(stderr, "**WARNING** Trying to access array element out of bounds. (access)\n");
        return NULL;
    }
}
/**
 * Set the element that a pointer is pointing to to __value
 */
void setelement(MATRIX_TYPE *__el, const MATRIX_TYPE __value) {
    *__el = __value;
}

// Swap __a and __b
void matswap(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    MATRIX_TYPE temp = *__a;
    *(__a) = *(__b);
    *(__b) = temp;
}

/**================================================================================================
 *!                                        Set/Get range of elements
 *================================================================================================**/

// Copy the matrix __src into the submatrix of __dest prescribed by the start and end indices
int matcpyele(Matrix * __dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, Matrix * __src) {

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

// Copy the elements of __src into the submatrix of __dest prescribed by the start and end indices WITHOUT CHECKING THE BOUNDS
void matcpyele_unsafe(Matrix *__dest, size_t __istart, size_t __iend, size_t __jstart, size_t __jend, Matrix *__src) {

    for (size_t i = __istart, irow = 0; i <= __iend; i++, irow++) {
        for (size_t j = __jstart, jcol = 0; j <= __jend; j++, jcol++) {
            Matrix_set(__dest, i, j, Matrix_at(__src, irow, jcol));
        }
    }
    // optimized for row-major access

}

/**================================================================================================
 *!                                        Set/Get Rows/Cols
 *================================================================================================**/

// Set the first __n indices of row __i, starting at column __j
void matsetrow(Matrix *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n) {

    MATRIX_TYPE *row_start = matacc(__A, __i, __j); // start of the row
    memcpy((void *) row_start, (void *) __src, sizeof(MATRIX_TYPE) * __n);

}

void matsetcol(Matrix *__A, size_t __i, size_t __j, const MATRIX_TYPE *__src, size_t __n) {

    MATRIX_TYPE *col_start = matacc(__A, __i, __j); // start of the col
    for (size_t i = 0; i < __n; i++) {
        *(col_start + (__A->nrows * i)) = __src[i];
    }
}

// matsetrow_mult_k
// matsetrow_div_k
// matsetrow_sub_k
// matsetrow_add_k

// multiply the row of a matrix times the value __k
void matsetrow_mult_k(Matrix *__A, MatIter __r, const MatIter __row_end, MATRIX_TYPE __k) {

    while(! MatIter_cmp(__r, __row_end)) { // while we haven't reached the end,
        multscalar(__r.ptr, __k);
        __r = MatIter_next(__r);
    }

}

// multiply the row of a matrix times the value __k
void matsetrow_div_k(Matrix *__A, MatIter __r, const MatIter __row_end, MATRIX_TYPE __k) {

    while(! MatIter_cmp(__r, __row_end)) { // while we haven't reached the end,
        divscalar(__r.ptr, __k);
        __r = MatIter_next(__r);
    }

}
// multiply the row of a matrix times the value __k
void matsetrow_add_k(Matrix *__A, MatIter __r, const MatIter __row_end, MATRIX_TYPE __k) {

    while(! MatIter_cmp(__r, __row_end)) { // while we haven't reached the end,
        addscalar(__r.ptr, __k);
        __r = MatIter_next(__r);
    }

}

// multiply the row of a matrix times the value __k
void matsetrow_sub_k(Matrix *__A, MatIter __r, const MatIter __row_end, MATRIX_TYPE __k) {

    while(! MatIter_cmp(__r, __row_end)) { // while we haven't reached the end,
        subscalar(__r.ptr, __k);
        __r = MatIter_next(__r);
    }

}

int Matrix_mult_row_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k) {

    const MatIter row_end = Matrix_row_end(__A, __i);
    MatIter row_begin = Matrix_row_begin(__A, __i);

    matsetrow_mult_k(__A, row_begin, row_end, __k);
    return EXIT_SUCCESS;

}

int Matrix_div_row_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k) {

    const MatIter row_end = Matrix_row_end(__A, __i);
    MatIter row_begin = Matrix_row_begin(__A, __i);

    matsetrow_div_k(__A, row_begin, row_end, __k);
    return EXIT_SUCCESS;

}
int Matrix_add_row_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k) {


    const MatIter row_end = Matrix_row_end(__A, __i);
    MatIter row_begin = Matrix_row_begin(__A, __i);

    matsetrow_add_k(__A, row_begin, row_end, __k);
    return EXIT_SUCCESS;

}

int Matrix_sub_row_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k) {

    const MatIter row_end = Matrix_row_end(__A, __i);
    MatIter row_begin = Matrix_row_begin(__A, __i);

    matsetrow_sub_k(__A, row_begin, row_end, __k);
    return EXIT_SUCCESS;

}

// editing columns now
void matsetcol_mult_k(Matrix *__A, MatIter __c, const MatIter __col_end, MATRIX_TYPE __k) {

    while(! MatIter_cmp(__c, __col_end)) { // while we haven't reached the end,
        multscalar(__c.ptr, __k);
        MatIter_next(__c);
    }

}

// multiply the col of a matrix times the value __k
void matsetcol_div_k(Matrix *__A, MatIter __c, const MatIter __col_end, MATRIX_TYPE __k) {

    while(! MatIter_cmp(__c, __col_end)) { // while we haven't reached the end,
        divscalar(__c.ptr, __k);
        MatIter_next(__c);
    }

}
// multiply the col of a matrix times the value __k
void matsetcol_add_k(Matrix *__A, MatIter __c, const MatIter __col_end, MATRIX_TYPE __k) {

    while(! MatIter_cmp(__c, __col_end)) { // while we haven't reached the end,
        addscalar(__c.ptr, __k);
        MatIter_next(__c);
    }

}

// multiply the col of a matrix times the value __k
void matsetcol_sub_k(Matrix *__A, MatIter __c, const MatIter __col_end, MATRIX_TYPE __k) {

    while(! MatIter_cmp(__c, __col_end)) { // while we haven't reached the end,
        subscalar(__c.ptr, __k);
        MatIter_next(__c);
    }

}

int Matrix_mult_col_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k) {

    const MatIter col_end = Matrix_col_end(__A, __i);
    MatIter col_begin = Matrix_col_begin(__A, __i);

    matsetcol_mult_k(__A, col_begin, col_end, __k);
    return EXIT_SUCCESS;

}

int Matrix_div_col_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k) {

    const MatIter col_end = Matrix_col_end(__A, __i);
    MatIter col_begin = Matrix_col_begin(__A, __i);

    matsetcol_div_k(__A, col_begin, col_end, __k);
    return EXIT_SUCCESS;

}
int Matrix_add_col_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k) {


    const MatIter col_end = Matrix_col_end(__A, __i);
    MatIter col_begin = Matrix_col_begin(__A, __i);

    matsetcol_add_k(__A, col_begin, col_end, __k);
    return EXIT_SUCCESS;

}

int Matrix_sub_col_k(Matrix *__A, const size_t __i, const MATRIX_TYPE __k) {

    const MatIter col_end = Matrix_col_end(__A, __i);
    MatIter col_begin = Matrix_col_begin(__A, __i);

    matsetcol_sub_k(__A, col_begin, col_end, __k);
    return EXIT_SUCCESS;

}




// SETS THE iTH ROW OF __A USING A ROW VECTOR!!!! That is, a ONE by M matrix
int Matrix_set_row(Matrix *__A, size_t __i, const Matrix *__cow) {

    // Check that the __cow matrix is actually a row matrix and that the number of columns match
    if (!Matrix_is_row(__cow)) {
        perror("Matrix is not a row vector");
        return EXIT_FAILURE;
    }
    if (__cow->ncols != __A->ncols) {
        perror("Matrix does not have the same number of cols");
        return EXIT_FAILURE;
    }

    matsetrow(__A, __i, 0, __cow->data, __cow->ncols);
    return EXIT_SUCCESS;

}

// SETS THE iTH ROW OF __A USING A ROW VECTOR!!!! That is, a ONE by M matrix
int Matrix_set_col(Matrix *__A, size_t __j, const Matrix *__col) {

    // Check that the __row matrix is actually a row matrix and that the number of columns match
    if (!Matrix_is_col(__col)) {
        perror("Matrix is not a col vector");
        return EXIT_FAILURE;
    }
    if (__col->nrows != __A->nrows) {
        perror("Matrix does not have the same number of rows");
        return EXIT_FAILURE;
    }

    matsetcol(__A, 0, __j, __col->data, __col->nrows);
    return EXIT_SUCCESS;

}

// It is remarkably faster to extract a specific row since we are just memcpy a certain period of bytes!
Matrix *Matrix_get_col(const Matrix *__A, size_t __j) {
    // don't even check bounds or anything just copy that shit!
    if (__j >= __A->ncols) {
        perror("jth column doesnt exist, returning NULL pointer");
        return NULL;
    }
    // so we want to copy __A->nrow elements.
    Matrix *x = matalloc(__A->nrows, 1);
    // iterate through the proper positions
    for (size_t i = 0; i < __A->nrows; i++) {
        matset(x, i, 0, matat(__A, i, __j));
    }

    return x;

}

// On the other hand, matrow is quite slow since we have to access the elements with a for loop.
// As a design choice, I'd like to implement some sort of low level "row iterator" that will allow us
// to iterate allong the row of a Matrix (to access it later) without actually performing a copy
Matrix *Matrix_get_row(const Matrix *__A, size_t __i) {

    if (__i >= __A->nrows) {
        perror("ith row doesnt exist, returning NULL pointer");
        return NULL;
    }

    printf("Trying to set row\n");
    Matrix *row = matalloc(1, __A->ncols);
    matsetrow(row, 0, 0, matacc(__A, __i, 0), __A->ncols);
    return row;

}

// I want to create a function that is going to multiply the row of a matrix, starting with it's row iterator.








/**================================================================================================
 *!                                        Set/Get Submatrices
 *================================================================================================**/

// Extract submatrix __A(__istart:__iend, __jstart:__jend)
Matrix * submat(Matrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend) {

    // printf("Entered submat with i0: %lu if: %lu j0: %lu jf: %lu\n", __istart, __iend, __jstart, __jend);

    Matrix * sub = NULL;

    // if the upper bounds are lower than the starting bounds or if the upper indices are larger than the number of rows | cols, return null
    if (__iend < __istart || __jend < __jstart || __iend >= __A->nrows || __jend >= __A->ncols) {
        return sub;
    }

    // printf("First condition passed\n");

    size_t nrows = __iend - __istart + 1;
    size_t ncols = __jend - __jstart + 1;

    sub = Matrix_new(nrows, ncols);

    for (size_t i = __istart, irow = 0; i <= __iend; i++, irow++) {
        for (size_t j = __jstart, icol = 0; j <= __jend; j++, icol++) {
            // printf("Setting (%lu,%lu) to %d\n", irow, icol, Matrix_at(__A, i, j));
            matset(sub, irow, icol, matat(__A, i, j));
        }
    }

    return sub;
}

// Alternative spelling for object-oriented approach.
Matrix * Matrix_submat(Matrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend) {
    return submat(__A, __istart, __iend, __jstart, __jend);
}

Matrix * Matrix_minor(Matrix * __A, size_t __irow, size_t __icol) {

    // assert(Matrix_is_square(__A));

    // Split matrix into 4 corners
    // printf("nrows: %lu, ncols: %lu\n", __A->nrows, __A->ncols);

    Matrix *upper_left = NULL;
    Matrix *upper_right = NULL;
    Matrix *lower_left = NULL;
    Matrix *lower_right = NULL;
    Matrix *upper_half = NULL;
    Matrix *lower_half = NULL;
    Matrix *composite = NULL;

    if (__irow == 0) {

    // then we only use lower left and lower right

        if (__icol == 0) {
            // then we only use lower right!!
            lower_right = Matrix_submat(__A, 1, __A->nrows - 1, 1, __A->ncols - 1);
            return lower_right;
        } else if (__icol == __A->ncols-1) {
            // then we only use lower left!!
            lower_left = Matrix_submat(__A, 1, __A->nrows - 1, 0, __A->ncols - 2);
            return  lower_left;
        } else {
            lower_left = Matrix_submat(__A, 1, __A->nrows - 1, 0, __icol - 1);
            lower_right = Matrix_submat(__A, 1, __A->nrows - 1, __icol + 1, __A->ncols - 1);
            composite = Matrix_ccat(lower_left, lower_right);

            Matrix_reset(&lower_left);
            Matrix_reset(&lower_right);

            return composite;
        }

    } else if (__irow == __A->nrows - 1) {
    // irow is the last row so we only use the upper left and upper right sections
        // printf("final row selected\n");

        if (__icol == 0) {
            // then we only use upper right!!
            upper_right = Matrix_submat(__A, 0, __A->nrows - 2, 1, __A->ncols - 1);
            return upper_right;
        } else if (__icol == __A->ncols - 1) {
            // then we only use upper left!!
            upper_left = Matrix_submat(__A, 0, __A->nrows - 2, 0, __A->ncols - 2);
            // printf("Only using upper left!");
            return upper_left;
        } else {
            upper_left= Matrix_submat(__A, 0, __A->nrows - 2, 0, __icol - 1);
            upper_right = Matrix_submat(__A, 0, __A->nrows - 2, __icol + 1, __A->ncols - 1);
            composite = Matrix_ccat(upper_left, upper_right);

            Matrix_reset(&upper_left);
            Matrix_reset(&upper_right);

            return composite;
        }

    } else {
        // do whatever
        if (__icol == 0) {
            // use the upper right and lower right sections!
            // printf("Using upper right and lower right sections!\n");
            upper_right = Matrix_submat(__A, 0, __irow-1, 1, __A->ncols - 1);
            lower_right = Matrix_submat(__A, __irow + 1, __A->nrows - 1, 1, __A->ncols - 1);
            composite = Matrix_rcat(upper_right, lower_right);

            Matrix_reset(&upper_right);
            Matrix_reset(&lower_right);

            return composite;

        } else if (__icol == __A->ncols - 1) {
            // use the upper left and lower left sections!
            // printf("using upper_left and lower_left\n");
            upper_left = Matrix_submat(__A, 0, __irow-1, 0, __A->ncols - 2);
            lower_left = Matrix_submat(__A, __irow + 1, __A->nrows - 1, 0, __A->ncols - 2);
            composite = Matrix_rcat(upper_left, lower_left);

            Matrix_reset(&upper_left);
            Matrix_reset(&lower_left);

            return composite;
        } else {
            // use all 4 sections!!!

            upper_left = Matrix_submat(__A, 0, __irow - 1, 0, __icol - 1);
            upper_right = Matrix_submat(__A, 0, __irow - 1, __icol + 1, __A->ncols - 1);
            lower_left = Matrix_submat(__A, __irow + 1, __A->nrows - 1, 0, __icol - 1);
            lower_right = Matrix_submat(__A, __irow + 1, __A->nrows - 1, __icol + 1, __A->ncols - 1);

            upper_half = Matrix_ccat(upper_left, upper_right);
            lower_half = Matrix_ccat(lower_left, lower_right);

            composite = Matrix_rcat(upper_half, lower_half);

            Matrix_reset(&upper_left);
            Matrix_reset(&upper_right);
            Matrix_reset(&lower_left);
            Matrix_reset(&lower_right);
            Matrix_reset(&upper_half);
            Matrix_reset(&lower_half);

            return composite;
        }
    }
}

/**================================================================================================
 *!                                        Set/Get Matrices
 *================================================================================================**/

void matfill(Matrix *__A, const MATRIX_TYPE __value) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            matset(__A, i, j, __value);
        }
    }
}

// fill matrix with a single value
void Matrix_fill(Matrix * __A, const MATRIX_TYPE value) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            Matrix_set(__A, i, j, value);
        }
    }
}

/**
 * Set all of the elements who fulfill a mask equal to the value
 */
void Matrix_fill_mask(Matrix *__A, Mask __mask, const MATRIX_TYPE __value) {
    Matrix_mask_k(__A, __mask, setelement, __value);
}

Matrix * Matrix_rcat(Matrix * __A, Matrix * __B) {

    if ( __A->ncols != __B->ncols) {
        perror("Cannont row concatenate two incompatible matrices\n");
        return NULL;
    } else {
        Matrix * Mcat = Matrix_new(__A->nrows + __B->nrows, __A->ncols);
        int status1 = matcpyele(Mcat, 0, __A->nrows - 1, 0, __A->ncols - 1, __A);
        int status2 = matcpyele(Mcat, __A->nrows, __A->nrows + __B->nrows - 1, 0, __A->ncols - 1, __B);

        if (status1 < 0 || status2 < 0) {
            Matrix_reset(&Mcat);
            return NULL;
        } else {
            return Mcat;
        }
    }
}

Matrix * Matrix_ccat(Matrix * __A, Matrix * __B) {

    if ( __A->nrows != __B->nrows) {
        perror("Cannont col concatenate two incompatible matrices\n");
        return NULL;
    } else {
        Matrix * Mcat = Matrix_new(__A->nrows, __A->ncols + __B->ncols);
        int status1 = matcpyele(Mcat, 0, __A->nrows - 1, 0, __A->ncols - 1, __A);
        int status2 = matcpyele(Mcat, 0, __A->nrows - 1, __A->ncols, __A->ncols + __B->ncols - 1, __B);

        if (status1 < 0 || status2 < 0) {
            Matrix_reset(&Mcat);
            return NULL;
        } else {
            return Mcat;
        }
    }
}