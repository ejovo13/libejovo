// matrix_core.c contains essential functions
// that deal with the creation, destruction and setting of matrix elements

// This header is to make my linter STFU
#ifndef MATRIX_TYPE
#define MATRIX_TYPE double
#define TYPE_SUFFIX _d
#endif

// #include "ejovo_matrix_matrix.h"
#include "ejovo_matrix.h"

#ifdef MATRIX_COMPLEX
    #include <complex.h>
#endif

TYPED(Matrix) *TYPED(g_ANON) = NULL;

#ifdef FIRST_COMPILATION_PASS
// #undef FIRST_COMPILATION_PASS

    const double PI = 3.141592653589793;
    const double TWO_PI = 2.0 * 3.141592653589793;
    const double HALF_PI = 3.141592653589793 / 2.0;
    const double EPS = 1E-10;


#endif



/**================================================================================================
 *!                                        Memory and Allocation
 *================================================================================================**/
TYPED(Matrix) *TYPED(matvec)(double __k) {

    TYPED(Matrix) *x = TYPED(matalloc)(1, 1);
    x->data[0] = __k;
    return x;
}

// Let's use a new variadic function called anon to instantiate a new anonymous matrix that should get slotted for immediate
// removal. -- This could easily lead to concurrency issues FYI
TYPED(Matrix) *TYPED(matanon)(int __count, ...) {

    va_list ptr;
    va_start(ptr, __count);

    // allocate a new vector with the alloted elements;
    TYPED(Vector)*v = TYPED(matalloc)(__count, 1);


    double next = va_arg(ptr, double);

    if (__count == 0) return NULL;


    for (int i = 0; i < __count; i++) {
        v->data[i] = next;
        next = va_arg(ptr, double);
    }

    TYPED(Matrix_anon)(v);

    return v;
}

// set all of the elements of __A to 0
TYPED(Matrix) *TYPED(Matrix_clean)(TYPED(Matrix) *__A) {
    TYPED(Matrix_fill)(__A, 0);
    return __A;
}

// copy the contents of matrix __src into __dest
TYPED(Matrix) *TYPED(matclone)(const TYPED(Matrix) *restrict __src) {

    TYPED(Matrix) * clone = NULL;

    clone = TYPED(Matrix_new)(__src->nrows, __src->ncols);
    if (clone) {
        TYPED(matcpy)(clone, __src);
    }

    return clone;
}

// Catch an unnamed TYPED(Matrix) pointer returned from the right side and store it in the
// __lhs_ptr. Return the __rhs
// This Is useful for preventing memory leaks for expressions of the type A = A * B
TYPED(Matrix) *TYPED(Matrix_catch)(TYPED(Matrix) **__lhs_ptr, TYPED(Matrix) *__anon_rhs) {
    if (*__lhs_ptr) {
        if ((*__lhs_ptr)->data)
            free((*__lhs_ptr)->data);
        free (*__lhs_ptr);
    }

    *__lhs_ptr = __anon_rhs;
    return __anon_rhs;
}

// Used to manage memory of anonymous Matrices that are the results of intermediate operations
// FOr example TYPED(Matrix_print)(TYPED(Matrix_mult)(a, b))
// will lead to a memory leak.
// Instead, wrap the previous call with
// TYPED(Matrix_print)(TYPED(Matrix_anon)(TYPED(Matrix_mult)(a, b)));
// and finall, at the end of the program / scope call
// TYPED(Matrix_anon_free)
TYPED(Matrix) *TYPED(Matrix_anon)(TYPED(Matrix) *__anon_rhs) {
    if (TYPED(g_ANON)) {
        if (TYPED(g_ANON)->data) free(TYPED(g_ANON)->data);
        free (TYPED(g_ANON));
    }

    TYPED(g_ANON) = __anon_rhs;
    return __anon_rhs;
}

void TYPED(Matrix_anon_free)() {
    TYPED(Matrix_anon)(NULL);
}

TYPED(Matrix) *TYPED(Matrix_transpose)(const TYPED(Matrix) *__m) {

    TYPED(Matrix) *mt = TYPED(matalloc)(__m->ncols, __m->nrows);


    for (size_t i = 0; i < __m->ncols; i++) {

        TYPED(MatIter) m_it = TYPED(Matrix_col_begin)(__m, i);
        TYPED(MatIter) m_end = TYPED(Matrix_col_end)(__m, i);

        // TYPED(MatIter) mt_end = TYPED(Matrix_row_end)(mt, i);
        TYPED(MatIter) mt_it = TYPED(Matrix_row_begin)(mt, i);

        for (; !TYPED(MatIter_cmp)(m_it, m_end); m_it = TYPED(MatIter_next)(m_it), mt_it = TYPED(MatIter_next)(mt_it)) {
            TYPED(MatIter_set)(mt_it, TYPED(MatIter_value)(m_it));
        }
    }

    return mt;
}

/**================================================================================================
 *!                                        Assignment Operator
 *================================================================================================**/
// I'd like to make the statement A = TYPED(Matrix_take)(A, M); allow the matrix A to point to the data
// of matrix M, and then to free the other matrix

TYPED(Matrix) *TYPED(Matrix_shallow_copy)(const TYPED(Matrix) *__rhs) {

    TYPED(Matrix) *__lhs = (TYPED(Matrix) *) malloc(sizeof(TYPED(Matrix) ));

    __lhs->data = __rhs->data;
    __lhs->ncols = __rhs->ncols;
    __lhs->nrows = __rhs->nrows;

    return __lhs;

}

// This function has a FATAL FLAW since it does not deallocate the matrix that is potentially being stored in the left hand side!!
TYPED(Matrix) *TYPED(Matrix_take)(TYPED(Matrix) *__rhs) {

    TYPED(Matrix) *__lhs = (TYPED(Matrix) *) malloc(sizeof(TYPED(Matrix) ));

    __lhs->data = __rhs->data;
    __lhs->ncols = __rhs->ncols;
    __lhs->nrows = __rhs->nrows;

    __rhs->data = NULL;

    TYPED(Matrix_free)(__rhs);
    return __lhs;

}





/**================================================================================================
 *!                                        TYPED(Matrix) Constructors
 *================================================================================================**/

TYPED(Matrix) * TYPED(Matrix_new)(int __nrows, int __ncols) {

    TYPED(Matrix) *x = (TYPED(Matrix) *) malloc(sizeof(TYPED(Matrix) ));

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
TYPED(Matrix) *TYPED(Matrix_move)(MATRIX_TYPE **__arr_ptr, size_t __nrows, size_t __ncols) {
    TYPED(Matrix) *m = (TYPED(Matrix) *) malloc(sizeof(TYPED(Matrix) ));
    m->ncols = __ncols;
    m->nrows = __nrows;
    m->data = *__arr_ptr;

    printf("Address of arr_ptr inside TYPED(Matrix_move): %p\n", __arr_ptr);
    printf("Address of m->data inside matrix: %p\n", m->data);

    // TYPED(Matrix_print)(m);

    *__arr_ptr = NULL;

    printf("Address of arr inside TYPED(Matrix_move): %p\n", *__arr_ptr);

    return m;
}

// When given an array, clone the array (copy its memory)
TYPED(Matrix) *TYPED(Matrix_from)(const MATRIX_TYPE *__arr, size_t __nrows, size_t __ncols) {

    TYPED(Matrix) *m = TYPED(matalloc)(__nrows, __ncols);
    memcpy(m->data, __arr, sizeof(MATRIX_TYPE) * (__nrows * __ncols));

    return m;
}

// When creating vectors we can just go ahead and memcpy the data!
TYPED(Matrix) *TYPED(Matrix_colvec)(const MATRIX_TYPE *__arr, size_t __nrows) {
    return TYPED(Matrix_from)(__arr, __nrows, 1);
}

TYPED(Matrix) *TYPED(Matrix_rowvec)(const MATRIX_TYPE *__arr, size_t __ncols) {
    return TYPED(Matrix_from)(__arr, 1, __ncols);
}

TYPED(Matrix) * TYPED(Matrix_clone)(const TYPED(Matrix) *restrict __src) {
    return TYPED(matclone)(__src);
}

// matrix of all ones
TYPED(Matrix) * TYPED(Matrix_ones)(size_t __nrows, size_t __ncols) {

    TYPED(Matrix) * m = TYPED(Matrix_new)(__nrows, __ncols);
    TYPED(matfill)(m, 1);

    return m;

}

TYPED(Matrix) * TYPED(Matrix_ij)(size_t __nrows, size_t __ncols) {

    TYPED(Matrix) * m = TYPED(Matrix_new)(__nrows, __ncols);
    if(m) {
        for (size_t i = 0; i < __nrows; i++) {
            for (size_t j = 0; j < __ncols; j++) {
                TYPED(matset)(m, i, j, i + j + 1);
            }
        }
    }

    return m;

}

 TYPED(Vector)*TYPED(Vector_range)(double __start, int __end, int __diff) {
    return TYPED(range)(__start, __end, __diff);
}

 TYPED(Vector)*TYPED(range)(int __start, int __end, int __diff) {

    // first calculate how many elements there will be.
    int n = (__end - __start) / __diff + 1;
    TYPED(Vector)*v = TYPED(Matrix_new)(1, n);

    for (int i = 0; i < n; i++) {
        TYPED(Vector_set)(v, i, __start + i * __diff);
    }

    return v;
}

 TYPED(Vector)*TYPED(linspace)(MATRIX_TYPE __start, MATRIX_TYPE __end, int __N) {

    TYPED(Vector)*v = TYPED(Vector_linspace)(__start, __end, __N);
    int tmp = v->ncols;
    v->ncols = v->nrows;
    v->nrows = tmp;

    return v;
}

MATRIX_TYPE TYPED(raisedBy10)(MATRIX_TYPE __input) {
    return pow(10, __input);
}

// use base 10
 TYPED(Vector)*TYPED(logspace)(double __start, double __end, int __n) {

    TYPED(Vector)*exp = TYPED(linspace)(__start, __end, __n);

    TYPED(Vector)*out = TYPED(Vector_map)(exp, TYPED(raisedBy10));

    TYPED(Matrix_free)(exp);

    return out;
}

 TYPED(Vector)*TYPED(Vector_linspace)(MATRIX_TYPE __start, MATRIX_TYPE __end, int __N) {

    MATRIX_TYPE difference = (__end - __start) / (__N - 1.0);
    TYPED(Vector)*v = TYPED(Vector_new)(__N);
    TYPED(Vector_set_first)(v, __start);
    TYPED(Vector_set_last)(v, __end);

    for (int i = 1; i < __N - 1; i++) {
        TYPED(Vector_set)(v, i, __start + difference * i);
    }

    return v;
}



/**
 * @brief Create a square diagonal matrix with random entries from 1 to 10
 *
 * @param __n
 * @return Matrix*
 */
TYPED(Matrix) *TYPED(Matrix_diagonal)(size_t __n) {

    TYPED(Matrix) *A = TYPED(Matrix_new)(__n, __n);
    for (size_t i = 0; i < __n; i++) {
        TYPED(Matrix_set)(A, i, i, unifi(1, 10));
    }

    return A;

}

TYPED(Matrix) *TYPED(Matrix_tridiagonal)(size_t __n) {

    TYPED(Matrix) *A = TYPED(Matrix_new)(__n, __n);

    TYPED(matset)(A, 0, 0, unifi(1, 10));
    TYPED(matset)(A, 0, 1, unifi(1, 10));

    for (size_t i = 1; i < __n-1; i++) {
        TYPED(matset)(A, i, i - 1, unifi(1, 10));
        TYPED(matset)(A, i, i, unifi(1, 10));
        TYPED(matset)(A, i, i + 1, unifi(1, 10));
    }

    TYPED(matset)(A, __n-1, __n-2, unifi(1, 10));
    TYPED(matset)(A, __n-1, __n-1, unifi(1, 10));

    return A;

}

TYPED(Matrix) * TYPED(Matrix_value)(size_t __nrows, size_t __ncols, MATRIX_TYPE __value) {

    TYPED(Matrix) * m = TYPED(Matrix_new)(__nrows, __ncols);
    TYPED(matfill)(m, __value);

    return m;
}

// MUST INITIALIZE EJOVO_SEED TO GET RANDOM VALUES
TYPED(Matrix) * TYPED(Matrix_random)(size_t __nrows, size_t __ncols, int __min, int __max) {

    TYPED(Matrix) * m = TYPED(Matrix_new)(__nrows, __ncols);

    // for (size_t i = 0; i < __nrows; i++) {
    //     for (size_t j = 0; j < __ncols; j++) {
    //         TYPED(matset)(m, i, j, unifi(__min, __max));
    //     }
    // }
    
    for (size_t i = 0; i < TYPED(Matrix_size)(m); i++) {
        m->data[i] = unifi(__min, __max);
    }

    return m;

}

TYPED(Matrix) * TYPED(Matrix_rand)(size_t __nrows, size_t __ncols) {
    return TYPED(Matrix_random)(__nrows, __ncols, 0, 10);
}

TYPED(Matrix) *TYPED(Matrix_id)(size_t __m, size_t __n) {

    TYPED(Matrix) *m = TYPED(Matrix_new)(__m, __n);

    TYPED(MatIter) diag = TYPED(Matrix_diag_begin)(m, 0);
    const TYPED(MatIter) end = TYPED(Matrix_diag_end)(m, 0);

    for (; !TYPED(MatIter_cmp)(diag, end); diag = TYPED(MatIter_next)(diag)) {
        TYPED(MatIter_set)(diag, 1);
    }

    return m;
}

TYPED(Matrix) * TYPED(Matrix_identity)(size_t __n) {

    TYPED(Matrix) * m = TYPED(Matrix_new)(__n, __n);

    for (size_t i = 0; i < __n; i++) {
        TYPED(matset)(m, i, i, 1);
    }

    return m;

}

/**================================================================================================
 *!                                        Miscellaneous
 *================================================================================================**/
// void 

/**========================================================================
 *!                           Double
 *========================================================================**/
// void matprintfloat(const Matrix_float *__m) {
//         TYPED(Matrix_summary)(__m);
//     for (size_t i = 0; i < __m->nrows; i++) {
//         printf("| ");
//         for (size_t j = 0; j < __m->ncols; j++) {
//             printf("%4.4lf ", TYPED(matat)(__m, i, j));
//         }

//         printf("|\n");

//     }
// }


void TYPED(matprint)(const TYPED(Matrix) *__m) {

    TYPED(Matrix_summary)(__m);
    for (size_t i = 0; i < __m->nrows; i++) {
        printf("| ");
        for (size_t j = 0; j < __m->ncols; j++) {

// #if defined MATRIX_DOUBLE
// #elif defined MATRIX_FLOAT 
// #elif defined MATRIX_INT
// #elif defined MATRIX_COMPLEX
// #endif

        #if defined MATRIX_DOUBLE 

            printf("%4.4lf ", TYPED(Matrix_at)(__m, i, j));

        #elif defined MATRIX_FLOAT 

            printf("%4.4f ", TYPED(Matrix_at)(__m, i, j));

        #elif defined MATRIX_INT

            printf("%5d ", TYPED(Matrix_at)(__m, i, j));

        #elif defined MATRIX_COMPLEX

            printf("(%4.4lf, %4.4lf) ", creal(matat_c(__m, i, j)), cimag(matat_c(__m, i, j)));

        #endif
        }

        printf("|\n");

    }
}

void TYPED(Matrix_print)(const TYPED(Matrix) *__m) {

    if (!__m) {
        printf("Matrix is NULL.\n");
        return;
    }

    TYPED(Matrix_summary)(__m);
    for (size_t i = 0; i < __m->nrows; i++) {
        printf("| ");
        for (size_t j = 0; j < __m->ncols; j++) {

        #if defined MATRIX_DOUBLE 

            printf("%4.4lf ", TYPED(Matrix_at)(__m, i, j));

        #elif defined MATRIX_FLOAT 

            printf("%4.4f ", TYPED(Matrix_at)(__m, i, j));

        #elif defined MATRIX_INT

            printf("%5d ", TYPED(Matrix_at)(__m, i, j));

        #elif defined MATRIX_COMPLEX

            printf("(%4.4lf, %4.4lf) ", creal(matat_c(__m, i, j)), cimag(matat_c(__m, i, j)));

        #endif


        }

        printf("|\n");
    }
}

void TYPED(Matrix_print_fixed)(const TYPED(Matrix) *__m) {

    if (!__m) {
        printf("TYPED(Matrix) is NULL.\n");
        return;
    }

    TYPED(Matrix_summary)(__m);
    for (size_t i = 0; i < __m->nrows; i++) {
        printf("| ");
        for (size_t j = 0; j < __m->ncols; j++) {

        #if defined MATRIX_DOUBLE 

            printf("%16.8lf ", TYPED(Matrix_at)(__m, i, j));

        #elif defined MATRIX_FLOAT 

            printf("%16.8f ", TYPED(Matrix_at)(__m, i, j));

        #elif defined MATRIX_INT

            printf("%10d ", TYPED(Matrix_at)(__m, i, j));

        #elif defined MATRIX_COMPLEX

            printf("(%16.8lf, %16.8lf) ", creal(matat_c(__m, i, j)), cimag(matat_c(__m, i, j)));

        #endif
        }

        printf("|\n");
    }
}

#if defined MATRIX_INT

#else 

void TYPED(Matrix_print_all_digits)(const TYPED(Matrix) *__m) {

    if (!__m) {
        printf("TYPED(Matrix) is NULL.\n");
        return;
    }

    TYPED(Matrix_summary)(__m);
    for (size_t i = 0; i < __m->nrows; i++) {
        printf("| ");
        for (size_t j = 0; j < __m->ncols; j++) {
#if defined MATRIX_COMPLEX
            printf("(%.16lf, %.16lf) ", creal(matat_c(__m, i, j)), cimag(matat_c(__m, i, j)));
#elif defined MATRIX_FLOAT
            printf("%.16f ", TYPED(Matrix_at)(__m, i, j));
#elif defined MATRIX_DOUBLE
            printf("%.16lf ", TYPED(Matrix_at)(__m, i, j));
#endif
        }


        printf("|\n");
    }
}
#endif

// Print in the {1, 2, 3} iter style
void TYPED(Matrix_print_iter)(const TYPED(Matrix) *__m) {
    TYPED(MatIter_print)(TYPED(Matrix_begin)(__m), TYPED(Matrix_end)(__m));
}

void TYPED(Matrix_summary)(const TYPED(Matrix) *__m) {
    printf("%lu x %lu %s\n", __m->nrows, __m->ncols, STRINGIFY(TYPED(Matrix)));
}

void TYPED(Vector_print_head)(const TYPED(Matrix) *__m, int __n) {

    assert(__n >= 0);

    size_t n = TYPED(Vector_size)(__m) < (size_t) __n ? TYPED(Vector_size)(__m) : (size_t) __n;

    // TYPED(Matrix_summary)(__m);
    printf("| ");
    for (size_t i = 0; i < n; i++) {
#if defined MATRIX_DOUBLE 
            printf("%4.4lf ", __m->data[i]);
#elif defined MATRIX_FLOAT 
            printf("%4.4f ", __m->data[i]);
#elif defined MATRIX_INT
            printf("%5d ", __m->data[i]);
#elif defined MATRIX_COMPLEX
            printf("(%4.4lf, %4.4lf) ", creal(__m->data[i]), cimag(__m->data[i]));
#endif
    }
    printf("|\n");

}