// matrix_core.c contains essential functions
// that deal with the creation, destruction and setting of matrix elements

#include "ejovo_matrix.h"

Matrix *g_ANON = NULL;

/**================================================================================================
 *!                                        Memory and Allocation
 *================================================================================================**/


// perform literally 0 checks, just allocate the space for a new matrix
Matrix *matalloc(size_t __nrows, size_t __ncols) {

    Matrix *x = (Matrix *) malloc(sizeof(Matrix));
    MATRIX_TYPE *data = (MATRIX_TYPE *) malloc(sizeof(MATRIX_TYPE) * (__nrows * __ncols));
    x->data = data;
    x->nrows = __nrows;
    x->ncols = __ncols;

    return x;
}

Matrix *vec(double __k) {

    Matrix *x = matalloc(1, 1);
    x->data[0] = __k;
    return x;
}

// Let's use a new variadic function called anon to instantiate a new anonymous matrix that should get slotted for immediate
// removal. -- This could easily lead to concurrency issues FYI
Matrix *anon(int __count, ...) {

    va_list ptr;
    va_start(ptr, __count);

    // allocate a new vector with the alloted elements;
    Vector *v = matalloc(__count, 1);


    double next = va_arg(ptr, double);

    if (__count == 0) return NULL;


    for (int i = 0; i < __count; i++) {
        v->data[i] = next;
        next = va_arg(ptr, double);
    }

    return Matrix_anon(v);

}

// low level function to literally just free both pointers
void matfree(Matrix *__A) {
    free(__A->data); // if data is null, don't call free on it!!!
    free(__A);
}

// Free the memory associated with the matrix and then free the pointer itself
void Matrix_free(Matrix *__A) {
    if (__A) {
        if (__A->data) free(__A->data);
        free(__A);
    }
}

// Free the memeory and set the pointer equal to NULL
void Matrix_reset(Matrix **__A_ptr) {
    if (*__A_ptr) {
        if ((*__A_ptr)->data) free((*__A_ptr)->data);
        free (*__A_ptr);
    }

    *__A_ptr = NULL;
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

// Catch an unnamed Matrix pointer returned from the right side and store it in the
// __lhs_ptr. Return the __rhs
// This Is useful for preventing memory leaks for expressions of the type A = A * B
Matrix *Matrix_catch(Matrix **__lhs_ptr, const Matrix *__anon_rhs) {
    if (*__lhs_ptr) {
        if ((*__lhs_ptr)->data)
            free((*__lhs_ptr)->data);
        free (*__lhs_ptr);
    }

    *__lhs_ptr = __anon_rhs;
    return __anon_rhs;
}

// Used to manage memory of anonymous Matrices that are the results of intermediate operations
// FOr example Matrix_print(Matrix_mult(a, b))
// will lead to a memory leak.
// Instead, wrap the previous call with
// Matrix_print(Matrix_anon(Matrix_mult(a, b)));
// and finall, at the end of the program / scope call
// Matrix_anon_free
Matrix *Matrix_anon(const Matrix *__anon_rhs) {
    if (g_ANON) {
        if (g_ANON->data) free(g_ANON->data);
        free (g_ANON);
    }

    g_ANON = __anon_rhs;
    return __anon_rhs;
}

void Matrix_anon_free() {
    Matrix_anon(NULL);
}

Matrix *Matrix_transpose(const Matrix *__m) {

    Matrix *mt = matalloc(__m->ncols, __m->nrows);


    for (size_t i = 0; i < __m->ncols; i++) {

        MatIter m_it = Matrix_col_begin(__m, i);
        MatIter m_end = Matrix_col_end(__m, i);

        MatIter mt_end = Matrix_row_end(mt, i);
        MatIter mt_it = Matrix_row_begin(mt, i);

        for (m_it; !MatIter_cmp(m_it, m_end); m_it = MatIter_next(m_it), mt_it = MatIter_next(mt_it)) {
            MatIter_set(mt_it, MatIter_value(m_it));
        }
    }

    return mt;
}

/**================================================================================================
 *!                                        Assignment Operator
 *================================================================================================**/
// I'd like to make the statement A = Matrix_take(A, M); allow the matrix A to point to the data
// of matrix M, and then to free the other matrix

Matrix *Matrix_shallow_copy(const Matrix *__rhs) {

    Matrix *__lhs = (Matrix *) malloc(sizeof(Matrix));

    __lhs->data = __rhs->data;
    __lhs->ncols = __rhs->ncols;
    __lhs->nrows = __rhs->nrows;

    return __lhs;

}

// This function has a FATAL FLAW since it does not deallocate the matrix that is potentially being stored in the left hand side!!
Matrix *Matrix_take(Matrix *__rhs) {

    Matrix *__lhs = (Matrix *) malloc(sizeof(Matrix));

    __lhs->data = __rhs->data;
    __lhs->ncols = __rhs->ncols;
    __lhs->nrows = __rhs->nrows;

    __rhs->data = NULL;

    Matrix_free(__rhs);
    return __lhs;

}





/**================================================================================================
 *!                                        Matrix Constructors
 *================================================================================================**/

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

Vector *range(int __start, int __end, int __diff) {

    // first calculate how many elements there will be.
    int n = (__end - __start) / __diff + 1;
    Vector *v = Matrix_new(1, n);

    for (int i = 0; i < n; i++) {
        Vector_set(v, i, __start + i * __diff);
    }

    return v;
}

Vector *linspace(MATRIX_TYPE __start, MATRIX_TYPE __end, int __N) {

    Vector *v = Vector_linspace(__start, __end, __N);
    int tmp = v->ncols;
    v->ncols = v->nrows;
    v->nrows = tmp;

    return v;
}

double raisedBy10(double __input) {
    return pow(10, __input);
}

// use base 10
Vector *logspace(double __start, double __end, int __n) {

    Vector *exp = linspace(__start, __end, __n);

    Vector *out = Vector_map(exp, raisedBy10);

    Matrix_free(exp);

    return out;
}

Vector *Vector_linspace(MATRIX_TYPE __start, MATRIX_TYPE __end, int __N) {

    MATRIX_TYPE difference = (__end - __start) / (__N - 1.0);
    Vector *v = Vector_new(__N);
    Vector_set_first(v, __start);
    Vector_set_last(v, __end);

    for (int i = 1; i < __N - 1; i++) {
        Vector_set(v, i, __start + difference * i);
    }

    return v;
}



/**
 * @brief Create a square diagonal matrix with random entries from 1 to 10
 *
 * @param __n
 * @return Matrix*
 */
Matrix *Matrix_diagonal(size_t __n) {

    Matrix *A = Matrix_new(__n, __n);
    for (size_t i = 0; i < __n; i++) {
        Matrix_set(A, i, i, unif(1, 10));
    }

    return A;

}

Matrix *Matrix_tridiagonal(size_t __n) {

    Matrix *A = Matrix_new(__n, __n);

    matset(A, 0, 0, unif(1, 10));
    matset(A, 0, 1, unif(1, 10));

    for (size_t i = 1; i < __n-1; i++) {
        matset(A, i, i - 1, unif(1, 10));
        matset(A, i, i, unif(1, 10));
        matset(A, i, i + 1, unif(1, 10));
    }

    matset(A, __n-1, __n-2, unif(1, 10));
    matset(A, __n-1, __n-1, unif(1, 10));

    return A;

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
    return Matrix_random(__nrows, __ncols, 0, 10);
}

Matrix * Matrix_identity(size_t __n) {

    Matrix * m = Matrix_new(__n, __n);

    for (size_t i = 0; i < __n; i++) {
        matset(m, i, i, 1);
    }

    return m;

}

/**================================================================================================
 *!                                        Miscellaneous
 *================================================================================================**/
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

void Matrix_print_fixed(const Matrix *__m) {

    Matrix_summary(__m);
    for (size_t i = 0; i < __m->nrows; i++) {
        printf("| ");
        for (size_t j = 0; j < __m->ncols; j++) {
            printf("%8.4lf ", Matrix_at(__m, i, j));
        }

        printf("|\n");
    }
}


// Print in the {1, 2, 3} iter style
void Matrix_print_iter(const Matrix *__m) {
    MatIter_print(Matrix_begin(__m), Matrix_end(__m));
}

void Matrix_summary(const Matrix *__m) {
    printf("%lu x %lu matrix\n", __m->nrows, __m->ncols);
}

void Vector_print_head(const Matrix *__m, int __n) {

    int n = Vector_size(__m) < __n ? Vector_size(__m) : __n;

    Matrix_summary(__m);
    printf("| ");
    for (size_t i = 0; i < n; i++) {
        printf("%4.4lf ", Vector_at(__m, i));
    }
    printf("|\n");

}