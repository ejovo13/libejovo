// matrix_core.c contains essential functions
// that deal with the creation, destruction and setting of matrix elements

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

Matrix * Matrix_rand(size_t __nrows, size_t __ncols) {
    return Matrix_random(__nrows, __ncols, 0, 100);
}

Matrix * Matrix_identity(size_t __n) {

    Matrix * m = Matrix_new(__n, __n);

    for (size_t i = 0; i < __n; i++) {
        matset(m, i, i, 1);
    }

    return m;

}