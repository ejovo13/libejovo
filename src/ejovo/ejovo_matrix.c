#include "ejovo_matrix.h"

// perform literally 0 checks, just allocate the space for a new matrix
Matrix *matalloc(size_t __nrows, size_t __ncols) {

    Matrix *x = (Matrix *) malloc(sizeof(Matrix));
    MATRIX_TYPE *data = (MATRIX_TYPE *) malloc(sizeof(MATRIX_TYPE) * (__nrows * __ncols));
    x->data = data;
    x->nrows = __nrows;
    x->ncols = __ncols;

    return x;

}

Matrix * Matrix_new(int __nrows, int __ncols) {

    Matrix *x = (Matrix *) malloc(sizeof(Matrix));

    if(x) {

        if ( __nrows > 0 && __ncols > 0) {
            MATRIX_TYPE *data = (MATRIX_TYPE *) calloc(__nrows * __ncols, sizeof(MATRIX_TYPE));
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

    } else {

        return x;
    }
}

// when given an ordinary array, construct a matrix from it, taking the prrevious memory.
// MOVE should only be called with arrays that are allocated on the heap so that that is no
// array jank that happens as a side effect.
Matrix *Matrix_move(MATRIX_TYPE **__arr_ptr, size_t __nrows, size_t __ncols) {
    Matrix *m = (Matrix *) malloc(sizeof(Matrix));
    m->ncols = __ncols;
    m->nrows = __nrows;
    m->data = *__arr_ptr;

    printf("Address of arr_ptr inside Matrix_move: %p\n", __arr_ptr);
    printf("Address of m->data inside matrix: %p\n", m->data);

    // Matrix_print(m);

    *__arr_ptr = NULL;

    printf("Address of arr inside Matrix_move: %p\n", *__arr_ptr);

    return m;
}

// When given an array, clone the array (copy its memory)
Matrix *Matrix_from(const MATRIX_TYPE *__arr, size_t __nrows, size_t __ncols) {

    Matrix *m = matalloc(__nrows, __ncols);
    memcpy(m->data, __arr, sizeof(MATRIX_TYPE) * (__nrows * __ncols));

    return m;
}

// When creating vectors we can just go ahead and memcpy the data!
Matrix *Matrix_colvec(const MATRIX_TYPE *__arr, size_t __nrows) {
    return Matrix_from(__arr, __nrows, 1);
}

Matrix *Matrix_rowvec(const MATRIX_TYPE *__arr, size_t __ncols) {
    return Matrix_from(__arr, 1, __ncols);
}


// Free the memory associated with the matrix and then free the pointer itself
void Matrix_free(Matrix *__A) {
    if (__A) {
        if (__A->data) {
            free(__A->data);
        }
        __A->ncols = 0;
        __A->nrows = 0;
        free(__A);
    }
}

bool Matrix_valid_bounds(const Matrix *__m, size_t __i, size_t __j) {
    return (__i < __m->nrows && __j < __m->ncols);
}


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

void matprint(const Matrix *__m) {

    Matrix_summary(__m);
    for (size_t i = 0; i < __m->nrows; i++) {
        printf("| ");
        for (size_t j = 0; j < __m->ncols; j++) {
            printf("%4.4lf ", matat(__m, i, j));
        }

        printf("|\n");

    }



}

void Matrix_print(const Matrix *__m) {

    Matrix_summary(__m);
    for (size_t i = 0; i < __m->nrows; i++) {
        printf("| ");
        for (size_t j = 0; j < __m->ncols; j++) {
            printf("%4.4lf ", Matrix_at(__m, i, j));
        }

        printf("|\n");
    }
}

void Matrix_summary(const Matrix *__m) {
    printf("%lu x %lu matrix\n", __m->nrows, __m->ncols);
}


// Take the inner product of the the __irow row of __A with the __icol col of __B
// used as a subroutine called in matmul
MATRIX_TYPE matcdr_check(const Matrix *__A, const Matrix *__B, size_t __irow, size_t __icol) {

    // #if MATRIX_TYPE == Complex

    //     MATRIX_TYPE inner_product = Complex_zero();
    //     for (size_t i = 0; i < __A->ncols; i++) {
    //         inner_product = Complex_add(inner_product, ())
    //     }

    // #else
        // We are assuming that __A and __B are compatible matrices for matrix multiplication
        MATRIX_TYPE inner_product = 0;
        for (size_t i = 0; i < __A->ncols; i++) {
            inner_product += (Matrix_at(__A, __irow, i) * Matrix_at(__B, i, __icol));
        }
        return inner_product;
    // #endif
}

// Compute the dot product without checking any indices
MATRIX_TYPE matcdr(const Matrix *__A, const Matrix *__B, size_t __irow, size_t __icol) {
        MATRIX_TYPE inner_product = 0;
        for (size_t i = 0; i < __A->ncols; i++) {
            inner_product += (matat(__A, __irow, i) * matat(__B, i, __icol));
        }
        return inner_product;
}

// return true if __A and __B have the same size and all of the elements are identical
bool matcmp(const Matrix *__A, const Matrix *__B) {

    if ( __A->nrows != __B->nrows || __A->ncols != __B->ncols) {
        return false;
    }
    return matcmp_bytes(__A, __B);
}

// compare the bytes of the data using memcmp
bool matcmp_bytes(const Matrix *__A, const Matrix *__B) {
    return memcmp((void *) __A->data, (void *) __B->data, sizeof(MATRIX_TYPE) * (__A->nrows * __A->ncols)) == 0;
}

// Are __A and __B compatible for addition?
bool Matrix_comp_add(const Matrix *__A, const Matrix *__B) {
    return (__A->nrows == __B->nrows && __A->ncols == __B->ncols);
}

// Are __A and __B compatible for addition?
bool Matrix_comp_mult(const Matrix *__A, const Matrix *__B) {
    return (__A->ncols == __B->nrows);
}

// Copy the bytes
// this is a utility function and should not be used by the end user
static bool matcpy(Matrix *restrict __dest, const Matrix *restrict __src) {

    // Copy the bytes of __src->data into __dest->data
    memcpy(__dest->data, __src->data, sizeof(MATRIX_TYPE)*(__src->nrows * __src->ncols));
    __dest->ncols = __src->ncols;
    __dest->nrows = __src->nrows;
    if(__dest && __src && __dest->data) { // if all the pointers are not null, return true
        return  true;
    } else {
        return false;
    }
}


// copy the contents of matrix __src into __dest
Matrix * matclone(const Matrix *restrict __src) {

    Matrix * clone = NULL;

    clone = Matrix_new(__src->nrows, __src->ncols);
    if (clone) {
        matcpy(clone, __src);
    }

    return clone;
}

Matrix * Matrix_clone(const Matrix *restrict __src) {
    return matclone(__src);
}


Matrix *matmul(const Matrix *__A, const Matrix *__B) {

    Matrix *product = Matrix_new(__A->nrows, __B->ncols);

    if (product){
        for (size_t i = 0; i < __A->nrows; i++) {
            for (size_t j = 0; j < __B->ncols; j++) {
                matset(product, i, j, matcdr(__A, __B, i, j));
            }
        }
    }

    return product;
}

Matrix * Matrix_multiply(const Matrix *__A, const Matrix *__B) {

    Matrix *prod = NULL;

    if (Matrix_comp_mult(__A, __B)) {
        prod = matmul(__A, __B);
    } else {
        perror("Trying to multiply incompatible matrices");
    }

    return prod;
}

// matadd modifies __A in place for more efficient additions when we don't need the original matrix
void matadd(Matrix *__A, const Matrix *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            a = matacc(__A, i, j);
            b = matacc(__B, i, j);

            *a += *b;
        }
    }
}

// series of functions used to add two elements that Matrix_access pointers are pointing to
void add_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) += (*__b);
}

void sub_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) -= (*__b);
}

void mult_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) *= (*__b);
}

void div_each(MATRIX_TYPE *__a, MATRIX_TYPE *__b) {
    (*__a) /= (*__b);
}

// add a __B to __A, mutating __A in place, using a "foreach" construct
void matadd_foreach(Matrix *__A, const Matrix *__B) {
    Matrix_foreach_2(__A, __B, add_each);
}

void matsub_foreach(Matrix *__A, const Matrix *__B) {
    Matrix_foreach_2(__A, __B, sub_each);
}

void matmult_foreach(Matrix *__A, const Matrix *__B) {
    Matrix_foreach_2(__A, __B, mult_each);
}

void matdiv_foreach(Matrix *__A, const Matrix *__B) {
    Matrix_foreach_2(__A, __B, div_each);
}

Matrix *Matrix_add(const Matrix *__A, const Matrix *__B) {

    Matrix *sum = NULL;

    if (Matrix_comp_add(__A, __B)) {

        sum = matclone(__A); // clone the matrix and modify this new matrix in place
        matadd(sum, __B);

    } else {

        perror("Trying to add two incompatible matrices");

    }

    return sum;
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


// matrix of all ones
Matrix * Matrix_ones(size_t __nrows, size_t __ncols) {

    Matrix * m = Matrix_new(__nrows, __ncols);
    matfill(m, 1);

    return m;

}


Matrix * Matrix_ij(size_t __nrows, size_t __ncols) {

    Matrix * m = Matrix_new(__nrows, __ncols);
    if(m) {
        for (size_t i = 0; i < __nrows; i++) {
            for (size_t j = 0; j < __ncols; j++) {
                matset(m, i, j, i + j + 1);
            }
        }
    }

    return m;

}

Matrix * Matrix_value(size_t __nrows, size_t __ncols, MATRIX_TYPE __value) {

    Matrix * m = Matrix_new(__nrows, __ncols);
    matfill(m, __value);

    return m;
}

// MUST INITIALIZE EJOVO_SEED TO GET RANDOM VALUES
Matrix * Matrix_random(size_t __nrows, size_t __ncols, int __min, int __max) {

    Matrix * m = Matrix_new(__nrows, __ncols);

    for (size_t i = 0; i < __nrows; i++) {
        for (size_t j = 0; j < __ncols; j++) {
            matset(m, i, j, unif(__min, __max));
        }
    }

    return m;

}

Matrix * Matrix_identity(size_t __n) {

    Matrix * m = Matrix_new(__n, __n);

    for (size_t i = 0; i < __n; i++) {
        matset(m, i, i, 1);
    }

    return m;

}

Matrix * Matrix_rand(size_t __nrows, size_t __ncols) {
    return Matrix_random(__nrows, __ncols, 0, 100);
}

size_t Matrix_size(const Matrix *__A) {
    return __A->nrows * __A->ncols;
}

bool Matrix_is_square(const Matrix *__A) {
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
        return matat(__A, 0, 0);
    } else {

        size_t i = 0;
        for (size_t j = 0; j < __A->ncols; j++) {
            double cofactor = pow(-1.0, j)*Matrix_det(Matrix_minor(__A, i, j));
            // printf("Cofactor: %lf, i: %lu, j: %lu\n", cofactor, i, j);
            local_det += cofactor * matat(__A, i, j);
        }
    }

    return local_det;
}

// Low level implementation of Hadamard multiplication, mutating __A in place
void mathad(Matrix *__A, const Matrix *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    // Iterate through the columns and rows of __A and multiply the elements by __B
    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {

            a = matacc(__A, i, j);
            b = matacc(__B, i, j);

            *a *= *b;
        }
    }
}

// Call hadamard multiplication, checking the indices with each access.
void mathad_check(Matrix *__A, const Matrix *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    // Iterate through the columns and rows of __A and multiply the elements by __B
    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {

            a = matacc_check(__A, i, j);
            b = matacc_check(__B, i, j);

            *a *= *b;
        }
    }
}

/**
 * Compute the Hadamard product (element-wise multiplication) of two matrices
 */
Matrix *Matrix_hadamard(const Matrix *__A, const Matrix *__B) {
    // Don't compute the product in place.
    if (!Matrix_comp_add(__A, __B)) {
        perror("Cannot take the hadamard product of two incompatible matrices!");
    }
    // verify that the matrices can be added

    Matrix *C = matclone(__A);
    mathad(C, __B);

    return C;
}


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

// SETS THE iTH ROW OF __A USING A ROW VECTOR!!!! That is, a ONE by M matrix
int Matrix_set_row(Matrix *__A, size_t __i, const Matrix *__row) {

    // Check that the __row matrix is actually a row matrix and that the number of columns match
    if (!Matrix_is_row(__row)) {
        perror("Matrix is not a row vector");
        return EXIT_FAILURE;
    }
    if (__row->ncols != __A->ncols) {
        perror("Matrix does not have the same number of cols");
        return EXIT_FAILURE;
    }

    matsetrow(__A, __i, 0, __row->data, __row->ncols);
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

// return true if __A has one row
bool Matrix_is_row(const Matrix *__A) {
    return __A->nrows == 1;
}

// return true if __A has one column
bool Matrix_is_col(const Matrix *__A) {
    return __A->ncols == 1;
}

bool Matrix_is_vec(const Matrix *__A) {
    return Matrix_is_row(__A) || Matrix_is_col(__A);
}


// Tridiagonal K matrix
Matrix *Matrix_K(size_t __n) {
// assert that __n > 1
    assert(__n > 1);

    Matrix *mat = Matrix_new(__n, __n);
    // set first row
    matset(mat, 0, 0, 2);
    matset(mat, 0, 1, -1);

    // set middle rows
    for (size_t i = 1; i < __n - 1; i++) {

        matset(mat, i, i - 1, -1);
        matset(mat, i, i, 2);
        matset(mat, i, i + 1, -1);

    }

    // set final row
    matset(mat, __n - 1, __n - 2, -1);
    matset(mat, __n - 1, __n - 1, 2);

    return mat;
}

// Circular matrix
Matrix *Matrix_C(size_t __n) {

    assert(__n > 1);

    Matrix *mat = Matrix_K(__n);
    matset(mat, 0, __n - 1, -1); // set the top right value
    matset(mat, __n - 1, 0, -1); // set the bottom left value

    return mat;

}

Matrix *Matrix_T(size_t __n) {

    assert(__n > 1);

    Matrix *mat = Matrix_K(__n);
    matset(mat, 0, 0, 1);

    return mat;

}

Matrix *Matrix_B(size_t __n) {

    assert(__n > 1);

    Matrix *mat = Matrix_T(__n);
    matset(mat, __n - 1, __n - 1, 1);

    return mat;

}

// NUMERICAL LINEAR ALGEBRA ROUTEINES!!!!!!

// Subtract matrix __B from __A, modifying __A in place!
void matsub(Matrix *__A, const Matrix *__B) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {

            a = matacc(__A, i, j);
            b = matacc(__B, i, j);

            *a -= *b;

        }
    }
}

Matrix *Matrix_subtract(const Matrix *__A, const Matrix *__B) {

    Matrix *A = Matrix_clone(__A);
    matsub(A, __B);
    return A;

}

/**================================================================================================
 *!                                        FOREACH style functions
 *================================================================================================**/

/**
 * Perform an operation on a matrix when a given mask evaluates to true
 */
void Matrix_mask(Matrix *__A, Mask __mask, EDITOR __operator) {

    MATRIX_TYPE *el = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            el = matacc(__A, i, j); // access the ith, jth element
            if (__mask(el)) __operator(el); // if the __mask is true, do something to __el
        }
    }
}
// __mask is only applied to matrix __A
void Matrix_mask_2(Matrix *__A, Matrix *__B, Mask __mask, EDITOR_2 __operator) {

    MATRIX_TYPE *a = NULL;
    MATRIX_TYPE *b = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            a = matacc(__A, i, j); // access the ith, jth element
            b = matacc(__B, i, j); // access the ith, jth element
            if (__mask(a)) __operator(a, b); // if the __mask is true, do something to __el
        }
    }
}

void Matrix_mask_k(Matrix *__A, Mask __mask, EDITOR_K __operator, const MATRIX_TYPE __k) {

    MATRIX_TYPE *el = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            el = matacc(__A, i, j); // access the ith, jth element
            if (__mask(el)) __operator(el, __k); // if the __mask is true, do something to __el
        }
    }
}


void Matrix_foreach(Matrix *__A, EDITOR __fnc) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            __fnc(matacc(__A, i, j));
        }
    }
}

void Matrix_foreach_2(Matrix *__A, Matrix *__B, EDITOR_2 __fnc) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            __fnc(matacc(__A, i, j), matacc(__B, i, j));
        }
    }
}

void Matrix_foreach_k(Matrix *__A, EDITOR_K __fnc, MATRIX_TYPE __k) {

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            __fnc(matacc(__A, i, j), __k);
        }
    }
}

void matmultscalar(Matrix *__A, const MATRIX_TYPE __k) {
    Matrix_foreach_k(__A, multscalar, __k);
}

void mataddscalar(Matrix *__A, const MATRIX_TYPE __k) {
    Matrix_foreach_k(__A, addscalar, __k);
}

void matdivscalar(Matrix *__A, const MATRIX_TYPE __k) {
    Matrix_foreach_k(__A, divscalar, __k);
}

void matsubscalar(Matrix *__A, const MATRIX_TYPE __k) {
    Matrix_foreach_k(__A, subscalar, __k);
}

// MY FIRST EDITOR_K
void multscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) *= __k;
}

void addscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) += __k;
}

void divscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) /= __k;
}

void subscalar(MATRIX_TYPE *__el, MATRIX_TYPE __k) {
    (*__el) -= __k;
}

Matrix *Matrix_mult_scalar(const Matrix *__A, const MATRIX_TYPE __k) {
    Matrix *A = Matrix_clone(__A);
    matmultscalar(A, __k);
    return A;
}

Matrix *Matrix_add_scalar(const Matrix *__A, const MATRIX_TYPE __k) {
    Matrix *A = Matrix_clone(__A);
    mataddscalar(A, __k);
    return A;
}

Matrix *Matrix_sub_scalar(const Matrix *__A, const MATRIX_TYPE __k) {
    Matrix *A = Matrix_clone(__A);
    matsubscalar(A, __k);
    return A;
}

Matrix *Matrix_div_scalar(const Matrix *__A, const MATRIX_TYPE __k) {
    Matrix *A = Matrix_clone(__A);
    matdivscalar(A, __k);
    return A;
}



/**================================================================================================
 *!                                         VECTOR DECLARATIONS
 *================================================================================================**/

// Default to making a column vector
Vector *Vector_new(size_t __nrows) {
    return Matrix_new(__nrows, 1);
}

Vector *Vector_rand(size_t __nrows) {
    return Matrix_rand(__nrows, 1);
}

Vector *Vector_random(size_t __nrows, int __min, int __max) {
    return Matrix_random(__nrows, 1, __min, __max);
}


MATRIX_TYPE vecpnorm(const Matrix *__A) {





}

// Euclidean norm
MATRIX_TYPE vecnorm(const Vector *__A) {

    MATRIX_TYPE sum = 0;
    MATRIX_TYPE *a = NULL;

    for (size_t i = 0; i < __A->nrows; i++) {
        for (size_t j = 0; j < __A->ncols; j++) {
            a = matacc(__A, i, j);
            sum += (*a) * (*a);
        }
    }

    return sqrt(sum);
}

// Calculate the norm of a column using ColIter's
MATRIX_TYPE colnorm(ColIter *__begin, const ColIter *__end) {

    MATRIX_TYPE sum = 0;

    do {
        sum += ColIter_value(__begin) * ColIter_value(__begin);
        ColIter_next(__begin);
    } while(!ColIter_cmp(__begin, __end));

    return sqrt(sum);

}

// Calculate the norm of a specific column
MATRIX_TYPE Matrix_col_norm(const Matrix *__A, size_t __j) {

    if (__j < __A->ncols) {
        return colnorm(Matrix_col_begin(__A, __j), Matrix_col_end(__A, __j));
    } else {
        perror("Col requested exceeds bounds");
        return -1;
    }
}

void matnormcol(ColIter *__begin, const ColIter *__end) {

    ColIter *c = ColIter_clone(__begin);
    MATRIX_TYPE norm = colnorm(__begin, __end);

    // now that we have calculated the norm, divide the columns values by the norm

    while (!ColIter_cmp(c, __end)) {
        *(c->ptr) /= norm;
        ColIter_next(c);
    }
    // *(c->ptr) /= norm;
}

void matnormcols(Matrix *__A) {
    for (size_t j = 0; j < __A->ncols; j++) {
        matnormcol(Matrix_col_begin(__A, j), Matrix_col_end(__A, j));
    }
}

void vecnormalize(Vector *__u) {

    MATRIX_TYPE norm = vecnorm(__u);
    matdivscalar(__u, norm);
}

void Matrix_normalize_col(Matrix *__A, size_t __j) {

    if (__j < __A->ncols) {
        matnormcol(Matrix_col_begin(__A, __j), Matrix_col_end(__A, __j));
    } else {
        printf("selected column is out of bounds");
        return;
    }
}

void Matrix_normalize_cols(Matrix *__A) {
    matnormcols(__A);
}


// Return the norm of a vector (checking bounds?)
MATRIX_TYPE Vector_norm(const Vector *__u) {
    return vecnorm(__u);
}

// return a normalized version of this vector
Vector *Vector_normalize(const Vector *__u) {

    Vector *v = Matrix_clone(__u);

    vecnormalize(v);
    return v;
}

// Take the dot product of __u and __v in place, storing the results in u!
// we are also just assuming that __u and __v are column (OR ROW) vectors of the same size
MATRIX_TYPE vecdot(const Vector *__u, const Vector *__v) {
    MATRIX_TYPE dot = 0;
    for (size_t i = 0; i < __u->nrows; i++) {
        for (size_t j = 0; j < __u->ncols; j++) {
            dot += (*matacc(__u, i, j)) * (*matacc(__v, i, j));
        }
    }
    return dot;
}

MATRIX_TYPE Vector_inner(const Vector *__u, const Vector *__v) {
    // perform the appropriate checks
    if (!Matrix_comp_add) {
        perror("Vectors are not compatible to take the inner product");
        return -1;
    }

    return vecdot(__u, __v);

}

Vector *vecproject(const Vector *__v, const Vector *__u) {

    MATRIX_TYPE u_v = vecdot(__u, __v);
    MATRIX_TYPE u_u = vecdot(__u, __u);

    return Matrix_mult_scalar(__u, u_v / u_u);

}


// Take vector __v and project it ONTO __u
Vector *Vector_project_onto(const Vector *__v, const Vector *__u) {

    if (!Matrix_comp_add) {
        perror("Vectors are not compatible to project onto");
        return NULL;
    }
    if (!Matrix_is_vec) {
        perror("Operands must be row or column vectors");
        return NULL;
    }

    return vecproject(__v, __u);
}



// Return a column vector that contains the solutions
// this column vector can be null if there are no solutions/infinitely many solutions
Matrix *gausselim(Matrix *__A, const Matrix *__B) {








}

/**================================================================================================
 *                                         Iterator functions
 *================================================================================================**/
ColIter *ColIter_new(MATRIX_TYPE *__ptr, size_t __ncols) {

    ColIter *c = (ColIter *) malloc(sizeof(ColIter));

    if (c) {
        c->ptr = __ptr;
        c->ncols = __ncols;
    }
    return c;
}

ColIter *ColIter_clone(const ColIter *__c) {
    return ColIter_new(__c->ptr, __c->ncols);
}

void ColIter_free(ColIter *__c) {

    if (__c) {

        if (__c->ptr) {
            free(__c->ptr);
        }
        free(__c);
    }
}

void ColIter_next(ColIter *__c) {
    __c->ptr += __c->ncols;
}

// Return true if the __lhs and __rhs point to the same element
bool ColIter_cmp(const ColIter *__lhs, const ColIter *__rhs) {
    return __lhs->ptr == __rhs->ptr;
}

ColIter *matcolpos(const Matrix *__A, size_t __i, size_t __j) {
    return ColIter_new(matacc(__A, __i, __j), __A->ncols);
}


// return a new Column Iterator that points to the final element in this column
ColIter *Matrix_col_end(const Matrix *__A, size_t __j) {

    if (__j < __A->ncols) {
        return matcolpos(__A, __A->nrows, __j);
    } else {
        perror("Matrix does not have that many columns");
        return NULL;
    }

}

ColIter *Matrix_col_begin(const Matrix *__A, size_t __j) {

    if (__j < __A->ncols) {
        return matcolpos(__A, 0, __j);
    } else {
        perror("Matrix does not have that many columns");
        return NULL;
    }
}

MATRIX_TYPE ColIter_value(const ColIter *__c) {
    return *(__c->ptr);
}


// The very first thing to implement (in my opinion) is a simple
// Gaussian elimination

// Next we can implement Householder transformations

// We can also use the projection operator

// Do I have scalar multiplication? I don't think so...




/**================================================================================================
 *!                                        Matrix Mask functions
 *================================================================================================**/

/**
 * Set the element that a pointer is pointing to to __value
 */
void setelement(MATRIX_TYPE *__el, const MATRIX_TYPE __value) {
    *__el = __value;
}

/**
 * Set all of the elements who fulfill a mask equal to the value
 */
void Matrix_set_mask(Matrix *__A, Mask __mask, const MATRIX_TYPE __value) {
    Matrix_mask_k(__A, __mask, setelement, __value);
}