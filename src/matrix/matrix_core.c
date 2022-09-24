// matrix_core.c contains essential functions
// that deal with the creation, destruction and setting of matrix elements

#include "ejovo_matrix_generic.h"
// #include "ejovo_matrix.h"

MATRIX_T *TYPED(g_ANON) = NULL;

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


// // perform literally 0 checks, just allocate the space for a new matrix
// MATRIX_T *MAT_FN(alloc)(size_t __nrows, size_t __ncols) {

//     MATRIX_T *x = (MATRIX_T *) malloc(sizeof(Matrix));
//     MATRIX_TYPE *data = (MATRIX_TYPE *) malloc(sizeof(MATRIX_TYPE) * (__nrows * __ncols));
//     x->data = data;
//     x->nrows = __nrows;
//     x->ncols = __ncols;

//     return x;
// }

MATRIX_T *MAT_FN(vec)(double __k) {

    MATRIX_T *x = MAT_FN(alloc)(1, 1);
    x->data[0] = __k;
    return x;
}

// Let's use a new variadic function called anon to instantiate a new anonymous matrix that should get slotted for immediate
// removal. -- This could easily lead to concurrency issues FYI
MATRIX_T *MAT_FN(anon)(int __count, ...) {

    va_list ptr;
    va_start(ptr, __count);

    // allocate a new vector with the alloted elements;
    Vector *v = MAT_FN(alloc)(__count, 1);


    double next = va_arg(ptr, double);

    if (__count == 0) return NULL;


    for (int i = 0; i < __count; i++) {
        v->data[i] = next;
        next = va_arg(ptr, double);
    }

    MATRIX_FN(anon)(v);

    return v;
}

// low level function to literally just free both pointers
// inline void MAT_FN(free)(MATRIX_T *__A) {
//     free(__A->data); // if data is null, don't call free on it!!!
//     free(__A);
// }

// // Free the memory associated with the matrix and then free the pointer itself
// inline void MATRIX_FN(free)(MATRIX_T *__A) {
//     if (__A) {
//         if (__A->data) free(__A->data);
//         free(__A);
//     }
// }

// // Free the memeory and set the pointer equal to NULL
// inline void MATRIX_FN(reset)(MATRIX_T **__A_ptr) {
//     if (*__A_ptr) {
//         if ((*__A_ptr)->data) free((*__A_ptr)->data);
//         free (*__A_ptr);
//     }

//     *__A_ptr = NULL;
// }

// set all of the elements of __A to 0
MATRIX_T *MATRIX_FN(clean)(MATRIX_T *__A) {
    MATRIX_FN(fill)(__A, 0);
}

// Copy the bytes
// this is a utility function and should not be used by the end user
// inline bool MAT_FN(cpy)(MATRIX_T *restrict __dest, const MATRIX_T *restrict __src) {

    // Copy the bytes of __src->data into __dest->data
    // memcpy(__dest->data, __src->data, sizeof(MATRIX_TYPE)*(__src->nrows * __src->ncols));
    // __dest->ncols = __src->ncols;
    // __dest->nrows = __src->nrows;
    // if(__dest && __src && __dest->data) { // if all the pointers are not null, return true
    //     return  true;
    // } else {
    //     return false;
    // }
// }

// copy the contents of matrix __src into __dest
MATRIX_T * MAT_FN(clone)(const MATRIX_T *restrict __src) {

    MATRIX_T * clone = NULL;

    clone = MATRIX_FN(new)(__src->nrows, __src->ncols);
    if (clone) {
        MAT_FN(cpy)(clone, __src);
    }

    return clone;
}

// Catch an unnamed MATRIX_T pointer returned from the right side and store it in the
// __lhs_ptr. Return the __rhs
// This Is useful for preventing memory leaks for expressions of the type A = A * B
MATRIX_T *MATRIX_FN(catch)(MATRIX_T **__lhs_ptr, MATRIX_T *__anon_rhs) {
    if (*__lhs_ptr) {
        if ((*__lhs_ptr)->data)
            free((*__lhs_ptr)->data);
        free (*__lhs_ptr);
    }

    *__lhs_ptr = __anon_rhs;
    return __anon_rhs;
}

// Used to manage memory of anonymous Matrices that are the results of intermediate operations
// FOr example MATRIX_FN(print)(MATRIX_FN(mult)(a, b))
// will lead to a memory leak.
// Instead, wrap the previous call with
// MATRIX_FN(print)(MATRIX_FN(anon)(MATRIX_FN(mult)(a, b)));
// and finall, at the end of the program / scope call
// MATRIX_FN(anon_free)
MATRIX_T *MATRIX_FN(anon)(MATRIX_T *__anon_rhs) {
    if (TYPED(g_ANON)) {
        if (TYPED(g_ANON)->data) free(TYPED(g_ANON)->data);
        free (TYPED(g_ANON));
    }

    TYPED(g_ANON) = __anon_rhs;
    return __anon_rhs;
}

void MATRIX_FN(anon_free)() {
    MATRIX_FN(anon)(NULL);
}

MATRIX_T *MATRIX_FN(transpose)(const MATRIX_T *__m) {

    MATRIX_T *mt = MAT_FN(alloc)(__m->ncols, __m->nrows);


    for (size_t i = 0; i < __m->ncols; i++) {

        MATITER_T m_it = MATRIX_FN(col_begin)(__m, i);
        MATITER_T m_end = MATRIX_FN(col_end)(__m, i);

        MATITER_T mt_end = MATRIX_FN(row_end)(mt, i);
        MATITER_T mt_it = MATRIX_FN(row_begin)(mt, i);

        for (m_it; !MATITER_FN(cmp)(m_it, m_end); m_it = MATITER_FN(next)(m_it), mt_it = MATITER_FN(next)(mt_it)) {
            MATITER_FN(set)(mt_it, MATITER_FN(value)(m_it));
        }
    }

    return mt;
}

/**================================================================================================
 *!                                        Assignment Operator
 *================================================================================================**/
// I'd like to make the statement A = MATRIX_FN(take)(A, M); allow the matrix A to point to the data
// of matrix M, and then to free the other matrix

MATRIX_T *MATRIX_FN(shallow_copy)(const MATRIX_T *__rhs) {

    MATRIX_T *__lhs = (MATRIX_T *) malloc(sizeof(MATRIX_T ));

    __lhs->data = __rhs->data;
    __lhs->ncols = __rhs->ncols;
    __lhs->nrows = __rhs->nrows;

    return __lhs;

}

// This function has a FATAL FLAW since it does not deallocate the matrix that is potentially being stored in the left hand side!!
MATRIX_T *MATRIX_FN(take)(MATRIX_T *__rhs) {

    MATRIX_T *__lhs = (MATRIX_T *) malloc(sizeof(MATRIX_T ));

    __lhs->data = __rhs->data;
    __lhs->ncols = __rhs->ncols;
    __lhs->nrows = __rhs->nrows;

    __rhs->data = NULL;

    MATRIX_FN(free)(__rhs);
    return __lhs;

}





/**================================================================================================
 *!                                        MATRIX_T Constructors
 *================================================================================================**/

MATRIX_T * MATRIX_FN(new)(int __nrows, int __ncols) {

    MATRIX_T *x = (MATRIX_T *) malloc(sizeof(MATRIX_T ));

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
MATRIX_T *MATRIX_FN(move)(MATRIX_TYPE **__arr_ptr, size_t __nrows, size_t __ncols) {
    MATRIX_T *m = (MATRIX_T *) malloc(sizeof(MATRIX_T ));
    m->ncols = __ncols;
    m->nrows = __nrows;
    m->data = *__arr_ptr;

    printf("Address of arr_ptr inside MATRIX_FN(move): %p\n", __arr_ptr);
    printf("Address of m->data inside matrix: %p\n", m->data);

    // MATRIX_FN(print)(m);

    *__arr_ptr = NULL;

    printf("Address of arr inside MATRIX_FN(move): %p\n", *__arr_ptr);

    return m;
}

// When given an array, clone the array (copy its memory)
MATRIX_T *MATRIX_FN(from)(const MATRIX_TYPE *__arr, size_t __nrows, size_t __ncols) {

    MATRIX_T *m = MAT_FN(alloc)(__nrows, __ncols);
    memcpy(m->data, __arr, sizeof(MATRIX_TYPE) * (__nrows * __ncols));

    return m;
}

// When creating vectors we can just go ahead and memcpy the data!
MATRIX_T *MATRIX_FN(colvec)(const MATRIX_TYPE *__arr, size_t __nrows) {
    return MATRIX_FN(from)(__arr, __nrows, 1);
}

MATRIX_T *MATRIX_FN(rowvec)(const MATRIX_TYPE *__arr, size_t __ncols) {
    return MATRIX_FN(from)(__arr, 1, __ncols);
}

MATRIX_T * MATRIX_FN(clone)(const MATRIX_T *restrict __src) {
    return MAT_FN(clone)(__src);
}

// matrix of all ones
MATRIX_T * MATRIX_FN(ones)(size_t __nrows, size_t __ncols) {

    MATRIX_T * m = MATRIX_FN(new)(__nrows, __ncols);
    MAT_FN(fill)(m, 1);

    return m;

}

MATRIX_T * MATRIX_FN(ij)(size_t __nrows, size_t __ncols) {

    MATRIX_T * m = MATRIX_FN(new)(__nrows, __ncols);
    if(m) {
        for (size_t i = 0; i < __nrows; i++) {
            for (size_t j = 0; j < __ncols; j++) {
                MAT_FN(set)(m, i, j, i + j + 1);
            }
        }
    }

    return m;

}

Vector *VECTOR_FN(range)(double __start, int __end, int __diff) {
    return TYPED_FN(range)(__start, __end, __diff);
}

Vector *TYPED_FN(range)(int __start, int __end, int __diff) {

    // first calculate how many elements there will be.
    int n = (__end - __start) / __diff + 1;
    Vector *v = MATRIX_FN(new)(1, n);

    for (int i = 0; i < n; i++) {
        VECTOR_FN(set)(v, i, __start + i * __diff);
    }

    return v;
}

Vector *TYPED_FN(linspace)(MATRIX_TYPE __start, MATRIX_TYPE __end, int __N) {

    Vector *v = VECTOR_FN(linspace)(__start, __end, __N);
    int tmp = v->ncols;
    v->ncols = v->nrows;
    v->nrows = tmp;

    return v;
}

MATRIX_TYPE TYPED_FN(raisedBy10)(MATRIX_TYPE __input) {
    return pow(10, __input);
}

// use base 10
Vector *TYPED_FN(logspace)(double __start, double __end, int __n) {

    Vector *exp = TYPED_FN(linspace)(__start, __end, __n);

    Vector *out = VECTOR_FN(map)(exp, TYPED_FN(raisedBy10));

    MATRIX_FN(free)(exp);

    return out;
}

Vector *VECTOR_FN(linspace)(MATRIX_TYPE __start, MATRIX_TYPE __end, int __N) {

    MATRIX_TYPE difference = (__end - __start) / (__N - 1.0);
    Vector *v = VECTOR_FN(new)(__N);
    VECTOR_FN(set_first)(v, __start);
    VECTOR_FN(set_last)(v, __end);

    for (int i = 1; i < __N - 1; i++) {
        VECTOR_FN(set)(v, i, __start + difference * i);
    }

    return v;
}



/**
 * @brief Create a square diagonal matrix with random entries from 1 to 10
 *
 * @param __n
 * @return Matrix*
 */
MATRIX_T *MATRIX_FN(diagonal)(size_t __n) {

    MATRIX_T *A = MATRIX_FN(new)(__n, __n);
    for (size_t i = 0; i < __n; i++) {
        MATRIX_FN(set)(A, i, i, unifi(1, 10));
    }

    return A;

}

MATRIX_T *MATRIX_FN(tridiagonal)(size_t __n) {

    MATRIX_T *A = MATRIX_FN(new)(__n, __n);

    MAT_FN(set)(A, 0, 0, unifi(1, 10));
    MAT_FN(set)(A, 0, 1, unifi(1, 10));

    for (size_t i = 1; i < __n-1; i++) {
        MAT_FN(set)(A, i, i - 1, unifi(1, 10));
        MAT_FN(set)(A, i, i, unifi(1, 10));
        MAT_FN(set)(A, i, i + 1, unifi(1, 10));
    }

    MAT_FN(set)(A, __n-1, __n-2, unifi(1, 10));
    MAT_FN(set)(A, __n-1, __n-1, unifi(1, 10));

    return A;

}

MATRIX_T * MATRIX_FN(value)(size_t __nrows, size_t __ncols, MATRIX_TYPE __value) {

    MATRIX_T * m = MATRIX_FN(new)(__nrows, __ncols);
    MAT_FN(fill)(m, __value);

    return m;
}

// MUST INITIALIZE EJOVO_SEED TO GET RANDOM VALUES
MATRIX_T * MATRIX_FN(random)(size_t __nrows, size_t __ncols, int __min, int __max) {

    MATRIX_T * m = MATRIX_FN(new)(__nrows, __ncols);

    // for (size_t i = 0; i < __nrows; i++) {
    //     for (size_t j = 0; j < __ncols; j++) {
    //         MAT_FN(set)(m, i, j, unifi(__min, __max));
    //     }
    // }
    
    for (int i = 0; i < MATRIX_FN(size)(m); i++) {
        m->data[i] = unifi(__min, __max);
    }

    return m;

}

MATRIX_T * MATRIX_FN(rand)(size_t __nrows, size_t __ncols) {
    return MATRIX_FN(random)(__nrows, __ncols, 0, 10);
}

MATRIX_T *MATRIX_FN(id)(size_t __m, size_t __n) {

    MATRIX_T *m = MATRIX_FN(new)(__m, __n);

    MATITER_T diag = MATRIX_FN(diag_begin)(m, 0);
    const MATITER_T end = MATRIX_FN(diag_end)(m, 0);

    for (diag; !MATITER_FN(cmp)(diag, end); diag = MATITER_FN(next)(diag)) {
        MATITER_FN(set)(diag, 1);
    }

    return m;
}

MATRIX_T * MATRIX_FN(identity)(size_t __n) {

    MATRIX_T * m = MATRIX_FN(new)(__n, __n);

    for (size_t i = 0; i < __n; i++) {
        MAT_FN(set)(m, i, i, 1);
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
//         MATRIX_FN(summary)(__m);
//     for (size_t i = 0; i < __m->nrows; i++) {
//         printf("| ");
//         for (size_t j = 0; j < __m->ncols; j++) {
//             printf("%4.4lf ", MAT_FN(at)(__m, i, j));
//         }

//         printf("|\n");

//     }
// }


void MAT_FN(print)(const MATRIX_T *__m) {

    MATRIX_FN(summary)(__m);
    for (size_t i = 0; i < __m->nrows; i++) {
        printf("| ");
        for (size_t j = 0; j < __m->ncols; j++) {
            printf("%4.4lf ", MAT_FN(at)(__m, i, j));
        }

        printf("|\n");

    }
}

void MATRIX_FN(print)(const MATRIX_T *__m) {

    if (!__m) {
        printf("MATRIX_T is NULL.\n");
        return;
    }

    MATRIX_FN(summary)(__m);
    for (size_t i = 0; i < __m->nrows; i++) {
        printf("| ");
        for (size_t j = 0; j < __m->ncols; j++) {
            printf("%4.4lf ", MATRIX_FN(at)(__m, i, j));
        }

        printf("|\n");
    }
}

void MATRIX_FN(print_fixed)(const MATRIX_T *__m) {

    if (!__m) {
        printf("MATRIX_T is NULL.\n");
        return;
    }

    MATRIX_FN(summary)(__m);
    for (size_t i = 0; i < __m->nrows; i++) {
        printf("| ");
        for (size_t j = 0; j < __m->ncols; j++) {
            printf("%16.8lf ", MATRIX_FN(at)(__m, i, j));
        }

        printf("|\n");
    }
}

void MATRIX_FN(print_all_digits)(const MATRIX_T *__m) {

    if (!__m) {
        printf("MATRIX_T is NULL.\n");
        return;
    }

    MATRIX_FN(summary)(__m);
    for (size_t i = 0; i < __m->nrows; i++) {
        printf("| ");
        for (size_t j = 0; j < __m->ncols; j++) {
            printf("%.16lf ", MATRIX_FN(at)(__m, i, j));
        }

        printf("|\n");
    }
}

// Print in the {1, 2, 3} iter style
void MATRIX_FN(print_iter)(const MATRIX_T *__m) {
    MATITER_FN(print)(MATRIX_FN(begin)(__m), MATRIX_FN(end)(__m));
}

void MATRIX_FN(summary)(const MATRIX_T *__m) {
    printf("%lu x %lu matrix\n", __m->nrows, __m->ncols);
}

void VECTOR_FN(print_head)(const MATRIX_T *__m, int __n) {

    int n = VECTOR_FN(size)(__m) < __n ? VECTOR_FN(size)(__m) : __n;

    MATRIX_FN(summary)(__m);
    printf("| ");
    for (size_t i = 0; i < n; i++) {
        printf("%4.4lf ", VECTOR_FN(at)(__m, i));
    }
    printf("|\n");

}