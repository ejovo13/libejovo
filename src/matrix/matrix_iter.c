// functions that deal with the creation of iterator objects

// #include "ejovo_matrix_generic.h"
// #include "ejovo_matrix.h"
#include "matrix/matrix_iter.h"
#include "matrix/matrix_vector.h"

// TODO I need to add checks for some of my iterator functions like matdiagend -> TYPED(Matrix_diag_end)
// TODO I should have an interface to change a "col iter" to a "row iter"
// TODO Allow constant iterators that are read only!

/**================================================================================================
 *!                                        Special Types of Iterators
 *================================================================================================**/
// Should have row, col, diagonal iterators. There are even some special iterators like "checkerboards"
// that can hit every other element.

TYPED(MatIter) TYPED(matdiagbegin)(const TYPED(Matrix) *__m, const int __d) {
    if (__d == 0) {
        return MATITER_NEW(TYPED(matacc)(__m, 0, 0), __m->ncols + 1);
    } else if (__d > 0) {
        return MATITER_NEW(TYPED(matacc)(__m, 0, __d), __m->ncols + 1);
    } else {
        return MATITER_NEW(TYPED(matacc)(__m, -__d, 0), __m->ncols + 1);
    }
}

TYPED(MatIter) TYPED(matdiagend)(const TYPED(Matrix) *__m, const int __d) {

    // First I have to work out whether is wide or tall
    size_t lim = 0;

    if (__d == 0) {
        // Then i need to find the smaller side
        lim = TYPED(Matrix_rect_limit)(__m);
        return MATITER_NEW(TYPED(matacc)(__m, lim, lim), __m->ncols + 1);

    } else if (__d > 0) {
        size_t adj_cols = __m->ncols - __d;
        lim = adj_cols < __m->nrows ? adj_cols : __m->nrows;
        return MATITER_NEW(TYPED(matacc)(__m, lim, lim + __d), __m->ncols + 1);
    } else {
        size_t adj_rows = __m->nrows + __d;
        lim = adj_rows < __m->ncols ? adj_rows : __m->ncols;
        return MATITER_NEW(TYPED(matacc)(__m, lim - __d, lim), __m->ncols + 1);
    }
}

void TYPED(MatIter_print)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end) {

    TYPED(MatIter) iter = __begin;

    printf("{");
    iter = TYPED(MatIter_next)(iter);

    while (! TYPED(MatIter_cmp)(iter, __end)) {
        // printf("%lf, ", *(iter.ptr - iter.ptr_diff)); //basically, print the previous value
        TYPED(print_el)(*(iter.ptr - iter.ptr_diff));
        iter = TYPED(MatIter_next)(iter);
    }

    TYPED(print_el_end)(*(iter.ptr - iter.ptr_diff)); //basically, print the previous value

}


// The 0th diagonal will start at the position __m(0, 0)
// The 1st diagonal will start at the position __m(0, 1)
// The -1  diagonal will start at the position __m(1, 0)
TYPED(MatIter) TYPED(Matrix_diag_begin)(const TYPED(Matrix) *__m, const int __d) {
    // Verify that the diagonal is even possible. If __d is negative, we should
    // compare the nrows. If __d is positive, we check the ncols
    if (__d < 0) {

        if ((size_t) abs(__d) >= __m->nrows) {
            perror("===TYPED(Matrix_diag_begin)===");
            perror("Not enough rows to accomodate diagonal");
            return TYPED(MatIter_null)();
        }
    } else if (__d > 0) {

        if ((size_t) __d >= __m->ncols) {
            perror("===TYPED(Matrix_diag_begin)===");
            perror("Not enough columns to accomodate diagonal");
            return TYPED(MatIter_null)();
        }
    }

    return TYPED(matdiagbegin)(__m, __d);
}

TYPED(MatIter) TYPED(Matrix_diag_end)(const TYPED(Matrix) *__m, const int __d) {

    if (__d < 0) {

        if ((size_t) abs(__d) >= __m->nrows) {
            perror("===TYPED(Matrix_diag_end)===");
            perror("Not enough rows to accomodate diagonal");
            return TYPED(MatIter_null)();
        }
    } else if (__d > 0) {

        if ((size_t) __d >= __m->ncols) {
            perror("===TYPED(Matrix_diag_end)===");
            perror("Not enough columns to accomodate diagonal");
            return TYPED(MatIter_null)();
        }
    }

    return TYPED(matdiagend)(__m, __d);
}




/**================================================================================================
 *!                                        RowCol and ColIter
 *================================================================================================**/

MATRIX_TYPE TYPED(Iter_dot)(const TYPED(MatIter) __r, const TYPED(MatIter) __rend, const TYPED(MatIter) __c) {

    MATRIX_TYPE dot = 0;

    while(!TYPED(MatIter_cmp)(__r, __rend)) {

        dot += TYPED(MatIter_value)(__r) * TYPED(MatIter_value)(__c);
        TYPED(MatIter_next)(__r);
        TYPED(MatIter_next)(__c);

    }

    return dot;

}

/**=======================================================================================================================
 *!                                           TYPED(Matrix) Interface to Iter functions
 *=======================================================================================================================**/

void TYPED(Matrix_print_row)(const TYPED(Matrix) *__A, size_t __i) {

    TYPED(MatIter) b = TYPED(Matrix_row_begin)(__A, __i);
    TYPED(MatIter) e = TYPED(Matrix_row_end)(__A, __i);

    printf("Row %ld: ", __i + 1);
    TYPED(MatIter_print)(b, e);
}

void TYPED(Matrix_print_col)(const TYPED(Matrix) *__A, size_t __j) {

    TYPED(MatIter) b = TYPED(Matrix_col_begin)(__A, __j);
    TYPED(MatIter) e = TYPED(Matrix_col_end)(__A, __j);

    printf("Col %ld: ", __j + 1);
    TYPED(MatIter_print)(b, e);
}


void TYPED(Matrix_print_diag)(const TYPED(Matrix) *__A, size_t __d) {

    TYPED(MatIter) b = TYPED(matdiagbegin)(__A, __d);
    TYPED(MatIter) e = TYPED(matdiagend)(__A, __d);

    printf("Diag %ld: ", __d);
    TYPED(MatIter_print)(b, e);
}

// Here I want to be able to manipulate the functions defined above to create clean and simple TYPED(Matrix) api

// let's start simple and add rows together

// matrix elementary row operation (add two rows)
void TYPED(matrowop_add)(TYPED(Matrix) *__A, const size_t __r1, const size_t __r2, const size_t __col_offset) {

    const TYPED(MatIter) r1begin = TYPED(matrowpos)(__A, __r1, __col_offset);
    const TYPED(MatIter) r1end = TYPED(matrowend)(__A, __r1);
    const TYPED(MatIter) r2begin = TYPED(matrowpos)(__A, __r2, __col_offset);

    TYPED(MatIter_apply_add_iter)(r1begin, r1end, r2begin);
}

// matrix elementary row operation (add two rows)
void TYPED(matrowop_add_scaled)(TYPED(Matrix) *__A, const size_t __r1, const size_t __r2, const MATRIX_TYPE __k, const size_t __col_offset) {

    const TYPED(MatIter) r1begin = TYPED(matrowpos)(__A, __r1, __col_offset);
    const TYPED(MatIter) r1end = TYPED(matrowend)(__A, __r1);
    const TYPED(MatIter) r2begin = TYPED(matrowpos)(__A, __r2, __col_offset);

    TYPED(MatIter_apply_add_iter_scaled)(r1begin, r1end, r2begin, __k);
}

void TYPED(Matrix_rowop_add)(TYPED(Matrix) *__A, const size_t __r1, const size_t __r2) {
    TYPED(matrowop_add)(__A, __r1, __r2, 0);
}

void TYPED(Matrix_rowop_add_offset)(TYPED(Matrix) *__A, const size_t __r1, const size_t __r2, const size_t __col_offset) {
    if (__col_offset < __A->ncols) {
        TYPED(matrowop_add)(__A, __r1, __r2, __col_offset);
    }
}

void TYPED(Matrix_rowop_add_scaled)(TYPED(Matrix) *__A, const size_t __r1, const size_t __r2, const MATRIX_TYPE __k) {
    TYPED(matrowop_add_scaled)(__A, __r1, __r2, __k, 0);
}

MATRIX_TYPE TYPED(Matrix_row_min)(const TYPED(Matrix) *__A, const size_t __i) {
    TYPED(MatIter) b = TYPED(matrowbegin)(__A, __i);
    TYPED(MatIter) e = TYPED(matrowend)(__A, __i);

    MATRIX_TYPE min = TYPED(MatIter_min)(b, e);
    return min;
}

MATRIX_TYPE TYPED(Matrix_row_max)(const TYPED(Matrix) *__A, const size_t __i) {
    return TYPED(MatIter_max)(TYPED(matrowbegin)(__A, __i), TYPED(matrowend)(__A, __i));
}

MATRIX_TYPE TYPED(Matrix_col_min)(const TYPED(Matrix) *__A, const size_t __j) {
    return TYPED(MatIter_min)(TYPED(matcolbegin)(__A, __j), TYPED(matcolend)(__A, __j));
}

MATRIX_TYPE TYPED(Matrix_col_max)(const TYPED(Matrix) *__A, const size_t __j) {
    return TYPED(MatIter_max)(TYPED(matcolbegin)(__A, __j), TYPED(matcolend)(__A, __j));
}

MATRIX_TYPE TYPED(Matrix_diag_min)(const TYPED(Matrix) *__A, const size_t __j) {
    return TYPED(MatIter_min)(TYPED(matdiagbegin)(__A, __j), TYPED(matdiagend)(__A, __j));
}

MATRIX_TYPE TYPED(Matrix_diag_max)(const TYPED(Matrix) *__A, const size_t __j) {
    return TYPED(MatIter_max)(TYPED(matdiagbegin)(__A, __j), TYPED(matdiagend)(__A, __j));
}

MATRIX_TYPE TYPED(Matrix_row_prod)(const TYPED(Matrix) *__A, const size_t __i) {
    return TYPED(MatIter_prod)(TYPED(matrowbegin)(__A, __i), TYPED(matrowend)(__A, __i));
}

MATRIX_TYPE TYPED(Matrix_col_prod)(const TYPED(Matrix) *__A, const size_t __i) {
    return TYPED(MatIter_prod)(TYPED(matcolbegin)(__A, __i), TYPED(matcolend)(__A, __i));
}

MATRIX_TYPE TYPED(Matrix_diag_prod)(const TYPED(Matrix) *__A, const size_t __i) {
    return TYPED(MatIter_prod)(TYPED(matdiagbegin)(__A, __i), TYPED(matdiagend)(__A, __i));
}


MATRIX_TYPE TYPED(Matrix_row_sum)(const TYPED(Matrix) *__A, const size_t __i) {
    return TYPED(MatIter_sum)(TYPED(matrowbegin)(__A, __i), TYPED(matrowend)(__A, __i));
}

MATRIX_TYPE TYPED(Matrix_col_sum)(const TYPED(Matrix) *__A, const size_t __i) {
    return TYPED(MatIter_sum)(TYPED(matcolbegin)(__A, __i), TYPED(matcolend)(__A, __i));
}

MATRIX_TYPE TYPED(Matrix_diag_sum)(const TYPED(Matrix) *__A, const size_t __i) {
    return TYPED(MatIter_sum)(TYPED(matdiagbegin)(__A, __i), TYPED(matdiagend)(__A, __i));
}



TYPED(MatIter) TYPED(matcolpos)(const TYPED(Matrix) *__A, size_t __i, size_t __j) {
    return MATITER_NEW(TYPED(matacc)(__A, __i, __j), __A->ncols);
}

// return a new Matumn Iterator that points to the final element in this column
TYPED(MatIter) TYPED(Matrix_col_end)(const TYPED(Matrix) *__A, size_t __j) {

    if (__j < __A->ncols) {
        return TYPED(matcolpos)(__A, __A->nrows, __j);
    } else {
        perror("TYPED(Matrix) does not have that many columns");
        TYPED(MatIter) null = {.ptr = NULL, .ptr_diff = 0};
        return null;
    }

}

TYPED(MatIter) TYPED(Matrix_col_begin)(const TYPED(Matrix) *__A, size_t __j) {

    if (__j < __A->ncols) {
        return TYPED(matcolpos)(__A, 0, __j);
    } else {
        perror("TYPED(Matrix) does not have that many columns");
        return TYPED(MatIter_null)();
    }
}

TYPED(MatIter) TYPED(Matrix_col_begin_from_row)(const TYPED(Matrix) *__A, size_t __j, size_t __i) {

    if (__j < __A->ncols) {
        return TYPED(matcolpos)(__A, __i, __j);
    } else {
        perror("TYPED(Matrix) does not have that many columns");
        return TYPED(MatIter_null)();
    }
}

TYPED(MatIter) TYPED(matcolbegin)(const TYPED(Matrix) *__A, size_t __i) {
    return TYPED(matcolpos)(__A, 0, __i);
}

TYPED(MatIter) TYPED(matcolend)(const TYPED(Matrix) *__A, size_t __i) {
    return TYPED(matcolpos)(__A, __A->nrows, __i);
}

TYPED(MatIter) TYPED(matrowpos)(const TYPED(Matrix) *__A, size_t __i, size_t __j) {
    return MATITER_NEW(TYPED(matacc)(__A, __i, __j), 1); // In row-major order, rows are next to each other
}

// get row iterator without checking bounds
TYPED(MatIter) TYPED(matrowbegin)(const TYPED(Matrix) *__A, size_t __i) {
    return TYPED(matrowpos)(__A, __i, 0);
}

TYPED(MatIter) TYPED(matrowend)(const TYPED(Matrix) *__A, size_t __i) {
    return TYPED(matrowpos)(__A, __i, __A->ncols);
}

// return a new Column Iterator that points to the final element in this column
TYPED(MatIter) TYPED(Matrix_row_end)(const TYPED(Matrix) *__A, size_t __i) {

    if (__i < __A->ncols) {
        return TYPED(matrowpos)(__A, __i, __A->ncols);
    } else {
        perror("TYPED(Matrix) does not have that many columns");
        return TYPED(MatIter_null)();
    }

}

TYPED(MatIter) TYPED(Matrix_row_begin)(const TYPED(Matrix) *__A, size_t __i) {

    if (__i < __A->nrows) {
        return TYPED(matrowpos)(__A, __i, 0);
    } else {
        perror("TYPED(Matrix) does not have that many rows");
        return TYPED(MatIter_null)();
    }
}

TYPED(MatIter) TYPED(Matrix_row_begin_from_col)(const TYPED(Matrix) *__A, size_t __i, size_t __j) {
    if (__i < __A->nrows) {
        return TYPED(matrowpos)(__A, __i, __j);
    } else {
        perror("TYPED(Matrix) does not have that many rows");
        return TYPED(MatIter_null)();
    }
}

/**=======================================================================================================================
 *!                                                   MIter that has more general capabilities
 *=======================================================================================================================**/
// TYPED(MatIter) MATITER_NEW(MATRIX_TYPE *__ptr, size_t __ptr_diff) {
//     TYPED(MatIter) c = {.ptr = __ptr, .ptr_diff = __ptr_diff};
//     return c;
// }

// TYPED(MatIter) TYPED(MatIter_null)() {
//     TYPED(MatIter) null = {.ptr = NULL, .ptr_diff = 0};
//     return null;
// }

// bool TYPED(MatIter_is_null)(TYPED(MatIter) __i) {
//     return __i.ptr == NULL;
// }

// Increment the row iter
// TYPED(MatIter) TYPED(MatIter_next)(TYPED(MatIter) __c) {
//     TYPED(MatIter) next = {.ptr = __c.ptr += __c.ptr_diff, .ptr_diff = __c.ptr_diff};
//     return next;
// }

// Return true if the __lhs and __rhs point to the same element
// bool TYPED(MatIter_cmp)(const TYPED(MatIter) __lhs, const TYPED(MatIter) __rhs) {
//     return __lhs.ptr == __rhs.ptr;
// }

// MATRIX_TYPE TYPED(MatIter_value)(const TYPED(MatIter) __c) {
//     return *(__c.ptr);
// }

// Return the number of iteration between begin and end
// size_t TYPED(MatIter_length)(const TYPED(MatIter) begin, const TYPED(MatIter) end) {
//     // printf("[TYPED(MatIter_length)]   end->ptr: %x, begin->ptr: %x\n", end->ptr, begin->ptr);
//     size_t diff = end.ptr - begin.ptr;
//     return diff / begin.ptr_diff;
// }

/**========================================================================
 *!                           Functional Iter functions
 *========================================================================**/
MATRIX_TYPE TYPED(MatIter_sum)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end) {

    MATRIX_TYPE sum = 0;
    TYPED(MatIter) iter = __begin;

    while (!TYPED(MatIter_cmp)(iter, __end)) {
        sum += TYPED(MatIter_value)(iter);
        iter = TYPED(MatIter_next)(iter);
    }

    return sum;
}

MATRIX_TYPE TYPED(MatIter_prod)(const TYPED(MatIter) __begin, const TYPED(MatIter) __end) {

    MATRIX_TYPE prod = 1;
    TYPED(MatIter) iter = __begin;

    while (!TYPED(MatIter_cmp)(iter, __end)) {
        prod *= TYPED(MatIter_value)(iter);
        iter = TYPED(MatIter_next)(iter);
    }

    return prod;
}

// Get the maximum value in a row
MATRIX_TYPE TYPED(MatIter_max)(TYPED(MatIter) __a, const TYPED(MatIter) __b) {

    MATRIX_TYPE max = TYPED(MatIter_value)(__a);
    __a = TYPED(MatIter_next)(__a);

    // This is the TYPED(MatIter) idiom to traverse a row
    while (!TYPED(MatIter_cmp)(__a, __b)) {
    #ifdef MATRIX_COMPLEX
        if (cabs(TYPED(MatIter_value)(__a)) > cabs(max))
    #else
        if (TYPED(MatIter_value)(__a) > max)
    #endif
            max = TYPED(MatIter_value)(__a);

        __a = TYPED(MatIter_next)(__a);
    }

    return max;

}

MATRIX_TYPE TYPED(MatIter_maxabs)(TYPED(MatIter) __a, const TYPED(MatIter) __b) {

#ifdef MATRIX_COMPLEX
    MATRIX_TYPE max = cabs(TYPED(MatIter_value)(__a));
#elif defined MATRIX_INT
    MATRIX_TYPE max = abs(TYPED(MatIter_value)(__a));
// #elif defined MATRIX_FLOAT
    // MATRIX_TYPE max = fabs(TYPED(MatIter_value)(__a));
#else
    MATRIX_TYPE max = fabs(TYPED(MatIter_value)(__a));
#endif
    __a = TYPED(MatIter_next)(__a);

    // This is the TYPED(MatIter) idiom to traverse a row
    while (!TYPED(MatIter_cmp)(__a, __b)) {
#ifdef MATRIX_COMPLEX
        if (cabs(TYPED(MatIter_value)(__a)) > cabs(max))
#elif defined MATRIX_INT
        if (abs(TYPED(MatIter_value)(__a)) > max)
#else
        if (fabs(TYPED(MatIter_value)(__a)) > max)
#endif
            max = TYPED(MatIter_value)(__a);

        __a = TYPED(MatIter_next)(__a);
    }

    return max;

}

// Get the maximum value in a row
MATRIX_TYPE TYPED(MatIter_min)(TYPED(MatIter) __a, const TYPED(MatIter) __b) {

    MATRIX_TYPE min = TYPED(MatIter_value)(__a);
    __a = TYPED(MatIter_next)(__a);

    // This is the TYPED(MatIter) idiom to traverse a row
    while (!TYPED(MatIter_cmp)(__a, __b)) {
    #ifdef MATRIX_COMPLEX
        if (cabs(TYPED(MatIter_value)(__a)) < cabs(min))
    #else
        if (TYPED(MatIter_value)(__a) < min)
    #endif
            min = TYPED(MatIter_value)(__a);

        __a = TYPED(MatIter_next)(__a);
    }

    return min;

}

/**================================================================================================
 *!                                        TYPED(MatIter) basic utility routines - SINGLE
 *================================================================================================**/

void TYPED(MatIter_set)(TYPED(MatIter) __r, const MATRIX_TYPE __k) {
    *(__r.ptr) = __k;
}

void TYPED(MatIter_add_k)(TYPED(MatIter) __r, const MATRIX_TYPE __k) {
    *(__r.ptr) += __k;
}

void TYPED(MatIter_sub_k)(TYPED(MatIter) __r, const MATRIX_TYPE __k) {
    *(__r.ptr) -= __k;
}

void TYPED(MatIter_mult_k)(TYPED(MatIter) __r, const MATRIX_TYPE __k) {
    *(__r.ptr) *= __k;
}

void TYPED(MatIter_div_k)(TYPED(MatIter) __r, const MATRIX_TYPE __k) {
    *(__r.ptr) /= __k;
}

void TYPED(MatIter_set_ptr)(TYPED(MatIter) __r, const MATRIX_TYPE *__ptr) {
    *(__r.ptr) = *__ptr;
}

void TYPED(MatIter_add_ptr)(TYPED(MatIter) __r, const MATRIX_TYPE *__ptr) {
    *(__r.ptr) += *__ptr;
}

void TYPED(MatIter_sub_ptr)(TYPED(MatIter) __r, const MATRIX_TYPE *__ptr) {
    *(__r.ptr) -= *__ptr;
}

void TYPED(MatIter_mult_ptr)(TYPED(MatIter) __r, const MATRIX_TYPE *__ptr) {
    *(__r.ptr) *= *__ptr;
}

void TYPED(MatIter_div_ptr)(TYPED(MatIter) __r, const MATRIX_TYPE *__ptr) {
    *(__r.ptr) /= *__ptr;
}

void TYPED(MatIter_set_iter)(TYPED(MatIter) __a, const TYPED(MatIter) __b) {
    *(__a.ptr) = *(__b.ptr);
}

void TYPED(MatIter_set_iter_pow)(TYPED(MatIter) __a, const TYPED(MatIter) __b, const MATRIX_TYPE __n) {
    *(__a.ptr) = pow(*(__b.ptr), __n);
}

void TYPED(MatIter_add_iter)(TYPED(MatIter) __a, const TYPED(MatIter) __b) {
    *(__a.ptr) += *(__b.ptr);
}

void TYPED(MatIter_add_iter_scaled)(TYPED(MatIter) __a, const TYPED(MatIter) __b, const MATRIX_TYPE __k) {
    *(__a.ptr) += *(__b.ptr) * __k;
}

void TYPED(MatIter_sub_iter)(TYPED(MatIter) __a, const TYPED(MatIter) __b) {
    *(__a.ptr) -= *(__b.ptr);
}

void TYPED(MatIter_mult_iter)(TYPED(MatIter) __a, const TYPED(MatIter) __b) {
    *(__a.ptr) *= *(__b.ptr);
}

void TYPED(MatIter_div_iter)(TYPED(MatIter) __a, const TYPED(MatIter) __b) {
    *(__a.ptr) /= *(__b.ptr);
}





/**================================================================================================
 *!                                        TYPED(MatIter) basic utility routines - ROW
 *================================================================================================**/

// Set the elements of a row when given a row iterator and a value k
void TYPED(MatIter_row_set_k)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k) {

    TYPED(MatIter) rbegin = __rbegin;

    while (! TYPED(MatIter_cmp)(rbegin, __rend)) {
        TYPED(MatIter_set)(rbegin, __k);
        rbegin = TYPED(MatIter_next)(rbegin);
    }
}

// Set the elements of a row when given a row iterator and another starting iterator
void TYPED(MatIter_row_set_iter)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const TYPED(MatIter) __bbegin) {

    TYPED(MatIter) rbegin = __rbegin;
    TYPED(MatIter) bbegin = __bbegin;

    while (! TYPED(MatIter_cmp)(rbegin, __rend)) {
        TYPED(MatIter_set_iter)(rbegin, bbegin);
        rbegin = TYPED(MatIter_next)(rbegin);
        bbegin = TYPED(MatIter_next)(bbegin);
    }
}


void TYPED(MatIter_row_add_k)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k) {

    TYPED(MatIter) rbegin = __rbegin;

    while (! TYPED(MatIter_cmp)(rbegin, __rend)) {
        TYPED(MatIter_add_k)(rbegin, __k);
        rbegin = TYPED(MatIter_next)(rbegin);
    }
}

void TYPED(MatIter_row_sub_k)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k) {

    TYPED(MatIter) rbegin = __rbegin;

    while (! TYPED(MatIter_cmp)(rbegin, __rend)) {
        TYPED(MatIter_sub_k)(rbegin, __k);
        rbegin = TYPED(MatIter_next)(rbegin);
    }
}

void TYPED(MatIter_row_mult_k)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k) {

    TYPED(MatIter) rbegin = __rbegin;

    while (! TYPED(MatIter_cmp)(rbegin, __rend)) {
        TYPED(MatIter_mult_k)(rbegin, __k);
        rbegin = TYPED(MatIter_next)(rbegin);
    }
}

void TYPED(MatIter_row_div_k)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k) {

    TYPED(MatIter) rbegin = __rbegin;

    while (! TYPED(MatIter_cmp)(rbegin, __rend)) {
        TYPED(MatIter_div_k)(rbegin, __k);
        rbegin = TYPED(MatIter_next)(rbegin);
    }
}

// Add to row __a the elements of row __b
void TYPED(MatIter_row_add_row)(const TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, const TYPED(MatIter) __bbegin) {

    TYPED(MatIter) abegin = __abegin;
    TYPED(MatIter) bbegin = __bbegin;

    while (! TYPED(MatIter_cmp)(abegin, __aend)) {
        TYPED(MatIter_add_iter)(abegin, bbegin);
        abegin = TYPED(MatIter_next)(abegin);
        bbegin = TYPED(MatIter_next)(bbegin);
    }
}


/**================================================================================================
 *!                                        Experimental APPLY functions
 *================================================================================================**/

// Appy functions are a way to iterate a ColIter until we reach the "end" point


void TYPED(MatIter_apply)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, TYPED(MatIterFn) __fn) {

    TYPED(MatIter) rbegin = __rbegin;

    while (! TYPED(MatIter_cmp)(rbegin, __rend)) {
        __fn(rbegin);
        rbegin = TYPED(MatIter_next)(rbegin);
    }
}

void TYPED(MatIter_apply_k)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k, TYPED(MatIterFn_k) __fn_k) {

    TYPED(MatIter) rbegin = __rbegin;

    while (! TYPED(MatIter_cmp)(rbegin, __rend)) {
        __fn_k(rbegin, __k);
        rbegin = TYPED(MatIter_next)(rbegin);
    }
}

void TYPED(MatIter_apply_ptr)(const TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE *__ptr, TYPED(MatIterFn_ptr) __fn_ptr) {

    TYPED(MatIter) rbegin = __rbegin;

    while (! TYPED(MatIter_cmp)(rbegin, __rend)) {
        __fn_ptr(rbegin, __ptr);
        rbegin = TYPED(MatIter_next)(rbegin);
    }
}

void TYPED(MatIter_apply_iter)(const TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, const TYPED(MatIter) __bbegin, TYPED(MatIterFn_iter) __fn_iter) {

    TYPED(MatIter) abegin = __abegin;
    TYPED(MatIter) bbegin = __bbegin;

    while (! TYPED(MatIter_cmp)(abegin, __aend)) {
        __fn_iter(abegin, bbegin);
        abegin = TYPED(MatIter_next)(abegin);
        bbegin = TYPED(MatIter_next)(bbegin);
    }
}

void TYPED(MatIter_apply_iter_scaled)(const TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, const TYPED(MatIter) __bbegin, const MATRIX_TYPE __k, TYPED(MatIterFn_iter_k) __fn_iter_k) {

    TYPED(MatIter) abegin = __abegin;
    TYPED(MatIter) bbegin = __bbegin;

    while (! TYPED(MatIter_cmp)(abegin, __aend)) {
        __fn_iter_k(abegin, bbegin, __k);
        abegin = TYPED(MatIter_next)(abegin);
        bbegin = TYPED(MatIter_next)(bbegin);
    }}

/**================================================================================================
 *!                                        Mat manipulations using apply functions
 *================================================================================================**/

/**======================
 *!    Scalar operations
 *========================**/
void TYPED(MatIter_apply_set_k)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k) {
    TYPED(MatIter_apply_k)(__rbegin, __rend, __k, TYPED(MatIter_set));
}

void TYPED(MatIter_apply_add_k)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k) {
    TYPED(MatIter_apply_k)(__rbegin, __rend, __k, TYPED(MatIter_add_k));
}

void TYPED(MatIter_apply_sub_k)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k) {
    TYPED(MatIter_apply_k)(__rbegin, __rend, __k, TYPED(MatIter_sub_k));
}

void TYPED(MatIter_apply_mult_k)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k) {
    TYPED(MatIter_apply_k)(__rbegin, __rend, __k, TYPED(MatIter_mult_k));
}

void TYPED(MatIter_apply_div_k)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE __k) {
    TYPED(MatIter_apply_k)(__rbegin, __rend, __k, TYPED(MatIter_div_k));
}

/**======================
 *!    Pointer operations
 *========================**/

void TYPED(MatIter_apply_set_ptr)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE *__ptr) {
    TYPED(MatIter_apply_ptr)(__rbegin, __rend, __ptr, TYPED(MatIter_set_ptr));
}

void TYPED(MatIter_apply_add_ptr)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE *__ptr) {
    TYPED(MatIter_apply_ptr)(__rbegin, __rend, __ptr, TYPED(MatIter_add_ptr));
}

void TYPED(MatIter_apply_sub_ptr)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE *__ptr) {
    TYPED(MatIter_apply_ptr)(__rbegin, __rend, __ptr, TYPED(MatIter_sub_ptr));
}

void TYPED(MatIter_apply_mult_ptr)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE *__ptr) {
    TYPED(MatIter_apply_ptr)(__rbegin, __rend, __ptr, TYPED(MatIter_mult_ptr));
}

void TYPED(MatIter_apply_div_ptr)(TYPED(MatIter) __rbegin, const TYPED(MatIter) __rend, const MATRIX_TYPE *__ptr) {
    TYPED(MatIter_apply_ptr)(__rbegin, __rend, __ptr, TYPED(MatIter_div_ptr));
}

/**======================
 *!    Iterator operations
 *========================**/

void TYPED(MatIter_apply_set_iter)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin) {
    TYPED(MatIter_apply_iter)(__abegin, __aend, __bbegin, TYPED(MatIter_set_iter));
}

void TYPED(MatIter_apply_set_iter_pow)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin, double __n) {
    TYPED(MatIter_apply_iter_scaled)(__abegin, __aend, __bbegin, __n, TYPED(MatIter_set_iter_pow));
}

void TYPED(MatIter_apply_add_iter)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin) {
    TYPED(MatIter_apply_iter)(__abegin, __aend, __bbegin, TYPED(MatIter_add_iter));
}

void TYPED(MatIter_apply_sub_iter)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin) {
    TYPED(MatIter_apply_iter)(__abegin, __aend, __bbegin, TYPED(MatIter_sub_iter));
}

void TYPED(MatIter_apply_mult_iter)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin) {
    TYPED(MatIter_apply_iter)(__abegin, __aend, __bbegin, TYPED(MatIter_mult_iter));
}

void TYPED(MatIter_apply_div_iter)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin) {
    TYPED(MatIter_apply_iter)(__abegin, __aend, __bbegin, TYPED(MatIter_div_iter));
}

/**======================
 *!    add iter scaled
 *========================**/
void TYPED(MatIter_apply_add_iter_scaled)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin, const MATRIX_TYPE __k) {
    TYPED(MatIter_apply_iter_scaled)(__abegin, __aend, __bbegin, __k, TYPED(MatIter_add_iter_scaled));
}


// Add a few new functions that allow me to set A Matrix's columns using an arbitrary iterator

// THIS FUNCTION MODIFIES IN PLACE
TYPED(Matrix) *TYPED(Matrix_set_col_iter)(TYPED(Matrix) *__m, size_t __j, TYPED(MatIter) __source) {

    TYPED(MatIter) it = TYPED(Matrix_col_begin)(__m, __j);
    const TYPED(MatIter) end = TYPED(Matrix_col_end)(__m, __j);
    TYPED(MatIter_apply_set_iter)(it, end, __source);

    return __m;
}

// THIS FUNCTION MODIFIES IN PLACE
TYPED(Matrix) *TYPED(Matrix_set_row_iter)(TYPED(Matrix) *__m, size_t __i, TYPED(MatIter) __source) {

    TYPED(MatIter) it = TYPED(Matrix_row_begin)(__m, __i);
    const TYPED(MatIter) end = TYPED(Matrix_row_end)(__m, __i);
    TYPED(MatIter_apply_set_iter)(it, end, __source);

    return __m;
}

// TODO I need to add other functions that are the matrix interface to these TYPED(MatIter) functions. I want to call
// TYPED(Matrix_add_row_iter)(m, 3, it);


// Here I want to implement some functions that deal with the distances between vectors
// given two iterators, I want to find their difference and store it in a new vector.
// Take a - b
 TYPED(Vector)*TYPED(MatIter_difference)(TYPED(MatIter) __abegin, const TYPED(MatIter) __aend, TYPED(MatIter) __bbegin) {

    // Compute the length of the iterator.
    size_t length = TYPED(MatIter_length)(__abegin, __aend);

    TYPED(Vector)*out = TYPED(Vector_new)(length);

    TYPED(MatIter) vout = TYPED(Vector_begin)(out);

    for (; !TYPED(MatIter_cmp)(__abegin, __aend);     vout = TYPED(MatIter_next)(vout),
                                                   __abegin = TYPED(MatIter_next)(__abegin),
                                                   __bbegin = TYPED(MatIter_next)(__bbegin))
    {
        TYPED(MatIter_set)(vout, TYPED(MatIter_value)(__abegin) - TYPED(MatIter_value)(__bbegin));
    }

    return out;
}