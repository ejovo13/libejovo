#include "ejovo_matrix.h"

Matrix * Matrix_new(int __nrows, int __ncols) {

    Matrix * x = (Matrix *) malloc(sizeof(Matrix));

    if ( __nrows > 0 && __ncols > 0) {
        MATRIX_TYPE * data = (MATRIX_TYPE *) calloc(__nrows * __ncols, sizeof(MATRIX_TYPE));
        x->data = data;
        if (data) { // if the data is allocated properly
            x->nrows = __nrows;
            x->ncols = __ncols;
        } else {
            x->nrows = 0;
            x->ncols = 0;
        }
    } else {
        x->data = NULL;
        x->nrows = 0;
        x->ncols = 0;
    }

    return x;
}

// Free the memory associated with the matrix and then free the pointer itself
void Matrix_free(Matrix * __A) {
    if (__A) {
        if (__A->data) {
            free(__A->data);
        }
        __A->ncols = 0;
        __A->nrows = 0;
        free(__A);
    }
}

bool Matrix_valid_bounds(Matrix * __m, size_t __i, size_t __j) {
    return (__i < __m->nrows && __j < __m->ncols);
}


// return the value of the element at __m(__i, __j) [zero indexed]
// return -1 if bounds are not respected and prints an error to the screen
MATRIX_TYPE Matrix_at(Matrix * __m, size_t __i, size_t __j) {

    if (Matrix_valid_bounds(__m, __i, __j)) {

        return __m->data[__i*__m->ncols + __j];

    } else {
        fprintf(stderr, "**WARNING** Trying to access array element out of bounds.\n");
        return 0;
    }

}

// set value of the element at __m(__i, __j) [zero indexed]
// return 0 if the bounds were respected, -1 elsewise
int Matrix_set(Matrix * __m, size_t __i, size_t __j, MATRIX_TYPE __value) {

    if (Matrix_valid_bounds(__m, __i, __j)) {
        __m->data[__i*__m->ncols + __j] = __value;
        return 0;
    } else {
        fprintf(stderr, "**WARNING** Trying to access array element out of bounds.\n");
        return 1;
    }
}

// return a pointer to the element at __m(__i, __j) [zero indexed]
MATRIX_TYPE * Matrix_access(Matrix * __m, size_t __i, size_t __j) {

    if (Matrix_valid_bounds(__m, __i, __j)) {
        return __m->data + (__i*__m->ncols + __j);
    } else {
        fprintf(stderr, "**WARNING** Trying to access array element out of bounds.\n");
        return NULL;
    }

}

void Matrix_print(Matrix * __m) {

    Matrix_summary(__m);
    for (size_t i = 0; i < __m->nrows; i++) {
        printf("| ");
        for (size_t j = 0; j < __m->ncols; j++) {
            printf("%3d ", Matrix_at(__m, i, j));
        }

        printf("|\n");
    }
}

void Matrix_summary(Matrix * __m) {
    printf("%lu x %lu matrix\n", __m->nrows, __m->ncols);
}


// Take the inner product of the the __irow row of __A with the __icol col of __B
// used as a subroutine called in matmul
MATRIX_TYPE col_dot_row(Matrix * __A, Matrix * __B, size_t __irow, size_t __icol) {

    // We are assuming that __A and __B are compatible matrices for matrix multiplication
    MATRIX_TYPE inner_product = 0;

    for (size_t i = 0; i < __A->ncols; i++) {
        inner_product += (Matrix_at(__A, __irow, i) * Matrix_at(__B, i, __icol));
    }

    return inner_product;

}

// return true if __A and __B have the same size and all of the elements are identical
bool matcmp(Matrix * __A, Matrix * __B) {

    if ( __A->nrows != __B->nrows || __A->ncols != __B->ncols) {
        return false;
    }
    // check every element
    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            if ( Matrix_at(__A, i, j) != Matrix_at(__B, i, j) ) {
                return false;
            }
        }
    }
    return true;
}

// Are __A and __B compatible for addition?
bool Matrix_comp_add(Matrix * __A, Matrix * __B) {
    return (__A->nrows == __B->nrows && __A->ncols == __B->ncols);
}

// Are __A and __B compatible for addition?
bool Matrix_comp_mult(Matrix * __A, Matrix * __B) {
    return (__A->ncols == __B->nrows);
}

// Copy the bytes
// this is a utility function and should not be used by the end user
static bool matcpy(Matrix * __dest, Matrix * __src) {

    // Copy the bytes of __src->data into __dest->data
    memcpy(__dest->data, __src->data, sizeof(MATRIX_TYPE)*(__src->nrows * __src->nrows));
    __dest->ncols = __src->ncols;
    __dest->nrows = __src->nrows;
    if(__dest && __src && __dest->data) { // if all the pointers are not null, return true
        return  true;
    } else {
        return false;
    }
}


// copy the contents of matrix __src into __dest
Matrix * matclone(Matrix * __src) {

    Matrix * clone = NULL;

    clone = Matrix_new(__src->ncols, __src->nrows);
    if (clone) {
        matcpy(clone, __src);
    }

    return clone;
}
Matrix * Matrix_clone(Matrix * __src) {
    return matclone(__src);
}

Matrix * matmul(Matrix * __A, Matrix * __B) {

    // if compatible, multiply the matrices

    // else, return Null pointer

    Matrix * product = NULL;

    if (Matrix_comp_mult(__A, __B)) {

        product = Matrix_new(__A->nrows, __B->ncols);

        if (product){
            for (size_t i = 0; i < __A->nrows; i++) {
                for (size_t j = 0; j < __B->ncols; j++) {
                    Matrix_set(product, i, j, col_dot_row(__A, __B, i, j));
                }
            }
        }
    }

    return product;
}
Matrix * Matrix_multiply(Matrix * __A, Matrix * __B) {
    return matmul(__A, __B);
}

// IDEA!! MAKE THESE VARIADIC FUNCTIONS!!!
Matrix * matadd(Matrix * __A, Matrix * __B) {

    Matrix * sum = NULL;

    if (Matrix_comp_add(__A, __B)) {

        sum = Matrix_new(__A->nrows, __B->ncols);

        if (sum) {
            for (size_t i = 0; i < __A->nrows; i++) {
                for (size_t j = 0; j < __A->ncols; j++) {
                    Matrix_set(sum, i, j, Matrix_at(__A, i, j) + Matrix_at(__B, i, j));
                }
            }
        }
    }

    return sum;
}

Matrix * Matrix_add(Matrix * __A, Matrix * __B) {
    return matadd(__A, __B);
}

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
    size_t irow = 0, icol = 0;

    sub = Matrix_new(nrows, ncols);


    for (size_t i = __istart, irow = 0; i <= __iend; i++, irow++) {

        for (size_t j = __jstart, icol = 0; j <= __jend; j++, icol++) {
            // printf("Setting (%lu,%lu) to %d\n", irow, icol, Matrix_at(__A, i, j));
            Matrix_set(sub, irow, icol, Matrix_at(__A, i, j));
        }
    }

    return sub;
}

// Alternative spelling for object-oriented approach.
Matrix * Matrix_submat(Matrix * __A, size_t __istart, size_t __iend, size_t __jstart, size_t __jend) {
    return submat(__A, __istart, __iend, __jstart, __jend);
}

// fill matrix with a single value
Matrix * Matrix_fill(Matrix * __A, MATRIX_TYPE value) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {

            Matrix_set(__A, i, j, value);

        }
    }
}

// matrix of all ones
Matrix * Matrix_ones(size_t __nrows, size_t __ncols) {

    Matrix * m = Matrix_new(__nrows, __ncols);
    Matrix_fill(m, 1);

    return m;

}


Matrix * Matrix_ij(size_t __nrows, size_t __ncols) {

    Matrix * m = Matrix_new(__nrows, __ncols);
    if(m) {
        for (size_t i = 0; i < __nrows; i++) {
            for (size_t j = 0; j < __ncols; j++) {
                Matrix_set(m, i, j, i + j + 1);
            }
        }
    }

    return m;

}

Matrix * Matrix_value(size_t __nrows, size_t __ncols, MATRIX_TYPE __value) {

    Matrix * m = Matrix_new(__nrows, __ncols);
    Matrix_fill(m, __value);

    return m;
}

// MUST INITIALIZE EJOVO_SEED TO GET RANDOM VALUES
Matrix * Matrix_random(size_t __nrows, size_t __ncols, int __min, int __max) {

    Matrix * m = Matrix_new(__nrows, __ncols);

    for (size_t i = 0; i < __nrows; i++) {
        for (size_t j = 0; j < __ncols; j++) {
            Matrix_set(m, i, j, unif(__min, __max));
        }
    }

    return m;

}

Matrix * Matrix_identity(size_t __n) {

    Matrix * m = Matrix_new(__n, __n);

    for (size_t i = 0; i < __n; i++) {
        Matrix_set(m, i, i, 1);
    }

    return m;

}

Matrix * Matrix_rand(size_t __nrows, size_t __ncols) {
    return Matrix_random(__nrows, __ncols, 0, 100);
}

bool Matrix_is_square(Matrix * __A) {
    return __A->nrows == __A->ncols;
}

Matrix * Matrix_pow(Matrix * __A, size_t __power) {

    assert(Matrix_is_square(__A));
    if ( __power == 0 ) {
        return Matrix_identity(__A->nrows);
    }

    if ( __power == 1 ) {
        return Matrix_clone(__A);
    }

    Matrix * m = Matrix_clone(__A);

    for (size_t i = 2; i <= __power; i++) {
        m = Matrix_multiply(__A, m);
    }

    return m;

}
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

    size_t irow = 0, jcol = 0; // indices for __src matrix
    for (size_t i = __istart, irow = 0; i <= __iend; i++, irow++) {
        for (size_t j = __jstart, jcol = 0; j <= __jend; j++, jcol++) {
            Matrix_set(__dest, i, j, Matrix_at(__src, irow, jcol));
        }
    }

    return 0;
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
            return NULL;
        } else {
            return Mcat;
        }
    }
}


Matrix * Matrix_minor(Matrix * __A, size_t __irow, size_t __icol) {

    // assert(Matrix_is_square(__A));

    // Split matrix into 4 corners
    // printf("nrows: %lu, ncols: %lu\n", __A->nrows, __A->ncols);

    Matrix * upper_left = NULL;
    Matrix * upper_right = NULL;
    Matrix * lower_left = NULL;
    Matrix * lower_right = NULL;
    Matrix * upper_half = NULL;
    Matrix * lower_half = NULL;

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
            return Matrix_ccat(lower_left, lower_right);
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
            return Matrix_ccat(upper_left, upper_right);
        }

    } else {
        // do whatever
        if (__icol == 0) {
            // use the upper right and lower right sections!
            // printf("Using upper right and lower right sections!\n");
            upper_right = Matrix_submat(__A, 0, __irow-1, 1, __A->ncols - 1);
            lower_right = Matrix_submat(__A, __irow + 1, __A->nrows - 1, 1, __A->ncols - 1);
            return Matrix_rcat(upper_right, lower_right);
        } else if (__icol == __A->ncols - 1) {
            // use the upper left and lower left sections!
            // printf("using upper_left and lower_left\n");
            upper_left = Matrix_submat(__A, 0, __irow-1, 0, __A->ncols - 2);
            lower_left = Matrix_submat(__A, __irow + 1, __A->nrows - 1, 0, __A->ncols - 2);
            return Matrix_rcat(upper_left, lower_left);
        } else {
            // use all 4 sections!!!

            upper_left = Matrix_submat(__A, 0, __irow - 1, 0, __icol - 1);
            upper_right = Matrix_submat(__A, 0, __irow - 1, __icol + 1, __A->ncols - 1);
            lower_left = Matrix_submat(__A, __irow + 1, __A->nrows - 1, 0, __icol - 1);
            lower_right = Matrix_submat(__A, __irow + 1, __A->nrows - 1, __icol + 1, __A->ncols - 1);

            upper_half = Matrix_ccat(upper_left, upper_right);
            lower_half = Matrix_ccat(lower_left, lower_right);

            return Matrix_rcat(upper_half, lower_half);

        }
    }
}




// recursive algorithm to compute the determinant of a matrix
double Matrix_det(Matrix * __A) {

    assert(Matrix_is_square(__A));

    double local_det = 0;

    if (__A->ncols == 1 && __A->nrows == 1) {
        return Matrix_at(__A, 0, 0);
    } else {

        size_t i = 0;
        for (size_t j = 0; j < __A->ncols; j++) {
            double cofactor = pow(-1.0, i + j)*Matrix_det(Matrix_minor(__A, i, j));
            // printf("Cofactor: %lf, i: %lu, j: %lu\n", cofactor, i, j);
            local_det += cofactor * Matrix_at(__A, i, j);
        }
    }

    return local_det;


}