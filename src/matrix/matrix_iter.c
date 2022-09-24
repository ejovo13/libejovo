// functions that deal with the creation of iterator objects

#include "ejovo_matrix_generic.h"
// #include "ejovo_matrix.h"

// TODO I need to add checks for some of my iterator functions like matdiagend -> MATRIX_FN(diag_end)
// TODO I should have an interface to change a "col iter" to a "row iter"
// TODO Allow constant iterators that are read only!

/**================================================================================================
 *!                                        Special Types of Iterators
 *================================================================================================**/
// Should have row, col, diagonal iterators. There are even some special iterators like "checkerboards"
// that can hit every other element.

MATITER_T MAT_FN(diagbegin)(const MATRIX_T *__m, const int __d) {
    if (__d == 0) {
        return MATITER_NEW(MAT_FN(acc)(__m, 0, 0), __m->ncols + 1);
    } else if (__d > 0) {
        return MATITER_NEW(MAT_FN(acc)(__m, 0, __d), __m->ncols + 1);
    } else {
        return MATITER_NEW(MAT_FN(acc)(__m, -__d, 0), __m->ncols + 1);
    }
}

MATITER_T MAT_FN(diagend)(const MATRIX_T *__m, const int __d) {

    // First I have to work out whether is wide or tall
    size_t lim = 0;

    if (__d == 0) {
        // Then i need to find the smaller side
        lim = MATRIX_FN(rect_limit)(__m);
        return MATITER_NEW(MAT_FN(acc)(__m, lim, lim), __m->ncols + 1);

    } else if (__d > 0) {
        size_t adj_cols = __m->ncols - __d;
        lim = adj_cols < __m->nrows ? adj_cols : __m->nrows;
        return MATITER_NEW(MAT_FN(acc)(__m, lim, lim + __d), __m->ncols + 1);
    } else {
        size_t adj_rows = __m->nrows + __d;
        lim = adj_rows < __m->ncols ? adj_rows : __m->ncols;
        return MATITER_NEW(MAT_FN(acc)(__m, lim - __d, lim), __m->ncols + 1);
    }
}

void MATITER_FN(print)(const MATITER_T __begin, const MATITER_T __end) {

    MATITER_T iter = __begin;

    printf("{");
    iter = MATITER_FN(next)(iter);

    while (! MATITER_FN(cmp)(iter, __end)) {
        printf("%lf, ", *(iter.ptr - iter.ptr_diff)); //basically, print the previous value
        iter = MATITER_FN(next)(iter);
    }

    printf("%lf}\n", *(iter.ptr - iter.ptr_diff)); //basically, print the previous value

}


// The 0th diagonal will start at the position __m(0, 0)
// The 1st diagonal will start at the position __m(0, 1)
// The -1  diagonal will start at the position __m(1, 0)
MATITER_T MATRIX_FN(diag_begin)(const MATRIX_T *__m, const int __d) {
    // Verify that the diagonal is even possible. If __d is negative, we should
    // compare the nrows. If __d is positive, we check the ncols
    if (__d < 0) {

        if (abs(__d) >= __m->nrows) {
            perror("===MATRIX_FN(diag_begin)===");
            perror("Not enough rows to accomodate diagonal");
            return MATITER_FN(null)();
        }
    } else if (__d > 0) {

        if (__d >= __m->ncols) {
            perror("===MATRIX_FN(diag_begin)===");
            perror("Not enough columns to accomodate diagonal");
            return MATITER_FN(null)();
        }
    }

    return MAT_FN(diagbegin)(__m, __d);
}

MATITER_T MATRIX_FN(diag_end)(const MATRIX_T *__m, const int __d) {

    if (__d < 0) {

        if (abs(__d) >= __m->nrows) {
            perror("===MATRIX_FN(diag_end)===");
            perror("Not enough rows to accomodate diagonal");
            return MATITER_FN(null)();
        }
    } else if (__d > 0) {

        if (__d >= __m->ncols) {
            perror("===MATRIX_FN(diag_end)===");
            perror("Not enough columns to accomodate diagonal");
            return MATITER_FN(null)();
        }
    }

    return MAT_FN(diagend)(__m, __d);
}




/**================================================================================================
 *!                                        RowCol and ColIter
 *================================================================================================**/

MATRIX_TYPE TYPED_FN(Iter_dot)(const MATITER_T __r, const MATITER_T __rend, const MATITER_T __c) {

    MATRIX_TYPE dot = 0;

    while(!MATITER_FN(cmp)(__r, __rend)) {

        dot += MATITER_FN(value)(__r) * MATITER_FN(value)(__c);
        MATITER_FN(next)(__r);
        MATITER_FN(next)(__c);

    }

    return dot;

}

/**=======================================================================================================================
 *!                                           MATRIX_T Interface to Iter functions
 *=======================================================================================================================**/

void MATRIX_FN(print_row)(const MATRIX_T *__A, size_t __i) {

    MATITER_T b = MATRIX_FN(row_begin)(__A, __i);
    MATITER_T e = MATRIX_FN(row_end)(__A, __i);

    printf("Row %ld: ", __i + 1);
    MATITER_FN(print)(b, e);
}

void MATRIX_FN(print_col)(const MATRIX_T *__A, size_t __j) {

    MATITER_T b = MATRIX_FN(col_begin)(__A, __j);
    MATITER_T e = MATRIX_FN(col_end)(__A, __j);

    printf("Col %ld: ", __j + 1);
    MATITER_FN(print)(b, e);
}


void MATRIX_FN(print_diag)(const MATRIX_T *__A, size_t __d) {

    MATITER_T b = MAT_FN(diagbegin)(__A, __d);
    MATITER_T e = MAT_FN(diagend)(__A, __d);

    printf("Diag %ld: ", __d);
    MATITER_FN(print)(b, e);
}

// Here I want to be able to manipulate the functions defined above to create clean and simple MATRIX_T api

// let's start simple and add rows together

// matrix elementary row operation (add two rows)
void MAT_FN(rowop_add)(MATRIX_T *__A, const size_t __r1, const size_t __r2, const size_t __col_offset) {

    const MATITER_T r1begin = MAT_FN(rowpos)(__A, __r1, __col_offset);
    const MATITER_T r1end = MAT_FN(rowend)(__A, __r1);
    const MATITER_T r2begin = MAT_FN(rowpos)(__A, __r2, __col_offset);

    MATITER_FN(apply_add_iter)(r1begin, r1end, r2begin);
}

// matrix elementary row operation (add two rows)
void MAT_FN(rowop_add_scaled)(MATRIX_T *__A, const size_t __r1, const size_t __r2, const MATRIX_TYPE __k, const size_t __col_offset) {

    const MATITER_T r1begin = MAT_FN(rowpos)(__A, __r1, __col_offset);
    const MATITER_T r1end = MAT_FN(rowend)(__A, __r1);
    const MATITER_T r2begin = MAT_FN(rowpos)(__A, __r2, __col_offset);

    MATITER_FN(apply_add_iter_scaled)(r1begin, r1end, r2begin, __k);
}

void MATRIX_FN(rowop_add)(MATRIX_T *__A, const size_t __r1, const size_t __r2) {
    MAT_FN(rowop_add)(__A, __r1, __r2, 0);
}

void MATRIX_FN(rowop_add_offset)(MATRIX_T *__A, const size_t __r1, const size_t __r2, const size_t __col_offset) {
    if (__col_offset < __A->ncols) {
        MAT_FN(rowop_add)(__A, __r1, __r2, __col_offset);
    }
}

void MATRIX_FN(rowop_add_scaled)(MATRIX_T *__A, const size_t __r1, const size_t __r2, const MATRIX_TYPE __k) {
    MAT_FN(rowop_add_scaled)(__A, __r1, __r2, __k, 0);
}

MATRIX_TYPE MATRIX_FN(row_min)(const MATRIX_T *__A, const size_t __i) {
    MATITER_T b = MAT_FN(rowbegin)(__A, __i);
    MATITER_T e = MAT_FN(rowend)(__A, __i);

    MATRIX_TYPE min = MATITER_FN(min)(b, e);
    return min;
}

MATRIX_TYPE MATRIX_FN(row_max)(const MATRIX_T *__A, const size_t __i) {
    return MATITER_FN(max)(MAT_FN(rowbegin)(__A, __i), MAT_FN(rowend)(__A, __i));
}

MATRIX_TYPE MATRIX_FN(col_min)(const MATRIX_T *__A, const size_t __j) {
    return MATITER_FN(min)(MAT_FN(colbegin)(__A, __j), MAT_FN(colend)(__A, __j));
}

MATRIX_TYPE MATRIX_FN(col_max)(const MATRIX_T *__A, const size_t __j) {
    return MATITER_FN(max)(MAT_FN(colbegin)(__A, __j), MAT_FN(colend)(__A, __j));
}

MATRIX_TYPE MATRIX_FN(diag_min)(const MATRIX_T *__A, const size_t __j) {
    return MATITER_FN(min)(MAT_FN(diagbegin)(__A, __j), MAT_FN(diagend)(__A, __j));
}

MATRIX_TYPE MATRIX_FN(diag_max)(const MATRIX_T *__A, const size_t __j) {
    return MATITER_FN(max)(MAT_FN(diagbegin)(__A, __j), MAT_FN(diagend)(__A, __j));
}

MATRIX_TYPE MATRIX_FN(row_prod)(const MATRIX_T *__A, const size_t __i) {
    return MATITER_FN(prod)(MAT_FN(rowbegin)(__A, __i), MAT_FN(rowend)(__A, __i));
}

MATRIX_TYPE MATRIX_FN(col_prod)(const MATRIX_T *__A, const size_t __i) {
    return MATITER_FN(prod)(MAT_FN(colbegin)(__A, __i), MAT_FN(colend)(__A, __i));
}

MATRIX_TYPE MATRIX_FN(diag_prod)(const MATRIX_T *__A, const size_t __i) {
    return MATITER_FN(prod)(MAT_FN(diagbegin)(__A, __i), MAT_FN(diagend)(__A, __i));
}


MATRIX_TYPE MATRIX_FN(row_sum)(const MATRIX_T *__A, const size_t __i) {
    return MATITER_FN(sum)(MAT_FN(rowbegin)(__A, __i), MAT_FN(rowend)(__A, __i));
}

MATRIX_TYPE MATRIX_FN(col_sum)(const MATRIX_T *__A, const size_t __i) {
    return MATITER_FN(sum)(MAT_FN(colbegin)(__A, __i), MAT_FN(colend)(__A, __i));
}

MATRIX_TYPE MATRIX_FN(diag_sum)(const MATRIX_T *__A, const size_t __i) {
    return MATITER_FN(sum)(MAT_FN(diagbegin)(__A, __i), MAT_FN(diagend)(__A, __i));
}



MATITER_T MAT_FN(colpos)(const MATRIX_T *__A, size_t __i, size_t __j) {
    return MATITER_NEW(MAT_FN(acc)(__A, __i, __j), __A->ncols);
}

// return a new Matumn Iterator that points to the final element in this column
MATITER_T MATRIX_FN(col_end)(const MATRIX_T *__A, size_t __j) {

    if (__j < __A->ncols) {
        return MAT_FN(colpos)(__A, __A->nrows, __j);
    } else {
        perror("MATRIX_T does not have that many columns");
        MATITER_T null = {.ptr = NULL, .ptr_diff = 0};
        return null;
    }

}

MATITER_T MATRIX_FN(col_begin)(const MATRIX_T *__A, size_t __j) {

    if (__j < __A->ncols) {
        return MAT_FN(colpos)(__A, 0, __j);
    } else {
        perror("MATRIX_T does not have that many columns");
        return MATITER_FN(null)();
    }
}

MATITER_T MATRIX_FN(col_begin_from_row)(const MATRIX_T *__A, size_t __j, size_t __i) {

    if (__j < __A->ncols) {
        return MAT_FN(colpos)(__A, __i, __j);
    } else {
        perror("MATRIX_T does not have that many columns");
        return MATITER_FN(null)();
    }
}

MATITER_T MAT_FN(colbegin)(const MATRIX_T *__A, size_t __i) {
    return MAT_FN(colpos)(__A, 0, __i);
}

MATITER_T MAT_FN(colend)(const MATRIX_T *__A, size_t __i) {
    return MAT_FN(colpos)(__A, __A->nrows, __i);
}

MATITER_T MAT_FN(rowpos)(const MATRIX_T *__A, size_t __i, size_t __j) {
    return MATITER_NEW(MAT_FN(acc)(__A, __i, __j), 1); // In row-major order, rows are next to each other
}

// get row iterator without checking bounds
MATITER_T MAT_FN(rowbegin)(const MATRIX_T *__A, size_t __i) {
    return MAT_FN(rowpos)(__A, __i, 0);
}

MATITER_T MAT_FN(rowend)(const MATRIX_T *__A, size_t __i) {
    return MAT_FN(rowpos)(__A, __i, __A->ncols);
}

// return a new Column Iterator that points to the final element in this column
MATITER_T MATRIX_FN(row_end)(const MATRIX_T *__A, size_t __i) {

    if (__i < __A->ncols) {
        return MAT_FN(rowpos)(__A, __i, __A->ncols);
    } else {
        perror("MATRIX_T does not have that many columns");
        return MATITER_FN(null)();
    }

}

MATITER_T MATRIX_FN(row_begin)(const MATRIX_T *__A, size_t __i) {

    if (__i < __A->nrows) {
        return MAT_FN(rowpos)(__A, __i, 0);
    } else {
        perror("MATRIX_T does not have that many rows");
        return MATITER_FN(null)();
    }
}

MATITER_T MATRIX_FN(row_begin_from_col)(const MATRIX_T *__A, size_t __i, size_t __j) {
    if (__i < __A->nrows) {
        return MAT_FN(rowpos)(__A, __i, __j);
    } else {
        perror("MATRIX_T does not have that many rows");
        return MATITER_FN(null)();
    }
}

/**=======================================================================================================================
 *!                                                   MIter that has more general capabilities
 *=======================================================================================================================**/
MATITER_T MATITER_NEW(MATRIX_TYPE *__ptr, size_t __ptr_diff) {
    MATITER_T c = {.ptr = __ptr, .ptr_diff = __ptr_diff};
    return c;
}

MATITER_T MATITER_FN(null)() {
    MATITER_T null = {.ptr = NULL, .ptr_diff = 0};
    return null;
}

bool MATITER_FN(is_null)(MATITER_T __i) {
    return __i.ptr == NULL;
}

// Increment the row iter
MATITER_T MATITER_FN(next)(MATITER_T __c) {
    MATITER_T next = {.ptr = __c.ptr += __c.ptr_diff, .ptr_diff = __c.ptr_diff};
    return next;
}

// Return true if the __lhs and __rhs point to the same element
bool MATITER_FN(cmp)(const MATITER_T __lhs, const MATITER_T __rhs) {
    return __lhs.ptr == __rhs.ptr;
}

MATRIX_TYPE MATITER_FN(value)(const MATITER_T __c) {
    return *(__c.ptr);
}

// Return the number of iteration between begin and end
size_t MATITER_FN(length)(const MATITER_T begin, const MATITER_T end) {
    // printf("[MATITER_FN(length)]   end->ptr: %x, begin->ptr: %x\n", end->ptr, begin->ptr);
    size_t diff = end.ptr - begin.ptr;
    return diff / begin.ptr_diff;
}

/**========================================================================
 *!                           Functional Iter functions
 *========================================================================**/
MATRIX_TYPE MATITER_FN(sum)(const MATITER_T __begin, const MATITER_T __end) {

    MATRIX_TYPE sum = 0;
    MATITER_T iter = __begin;

    while (!MATITER_FN(cmp)(iter, __end)) {
        sum += MATITER_FN(value)(iter);
        iter = MATITER_FN(next)(iter);
    }

    return sum;
}

MATRIX_TYPE MATITER_FN(prod)(const MATITER_T __begin, const MATITER_T __end) {

    MATRIX_TYPE prod = 1;
    MATITER_T iter = __begin;

    while (!MATITER_FN(cmp)(iter, __end)) {
        prod *= MATITER_FN(value)(iter);
        iter = MATITER_FN(next)(iter);
    }

    return prod;
}

// Get the maximum value in a row
MATRIX_TYPE MATITER_FN(max)(MATITER_T __a, const MATITER_T __b) {

    MATRIX_TYPE max = MATITER_FN(value)(__a);
    __a = MATITER_FN(next)(__a);

    // This is the MATITER_T idiom to traverse a row
    while (!MATITER_FN(cmp)(__a, __b)) {

        if (MATITER_FN(value)(__a) > max)
            max = MATITER_FN(value)(__a);

        __a = MATITER_FN(next)(__a);
    }

    return max;

}

// Get the maximum value in a row
MATRIX_TYPE MATITER_FN(min)(MATITER_T __a, const MATITER_T __b) {

    MATRIX_TYPE min = MATITER_FN(value)(__a);
    __a = MATITER_FN(next)(__a);

    // This is the MATITER_T idiom to traverse a row
    while (!MATITER_FN(cmp)(__a, __b)) {

        if (MATITER_FN(value)(__a) < min)
            min = MATITER_FN(value)(__a);

        __a = MATITER_FN(next)(__a);
    }

    return min;

}

/**================================================================================================
 *!                                        MATITER_T basic utility routines - SINGLE
 *================================================================================================**/

void MATITER_FN(set)(MATITER_T __r, const MATRIX_TYPE __k) {
    *(__r.ptr) = __k;
}

void MATITER_FN(add_k)(MATITER_T __r, const MATRIX_TYPE __k) {
    *(__r.ptr) += __k;
}

void MATITER_FN(sub_k)(MATITER_T __r, const MATRIX_TYPE __k) {
    *(__r.ptr) -= __k;
}

void MATITER_FN(mult_k)(MATITER_T __r, const MATRIX_TYPE __k) {
    *(__r.ptr) *= __k;
}

void MATITER_FN(div_k)(MATITER_T __r, const MATRIX_TYPE __k) {
    *(__r.ptr) /= __k;
}

void MATITER_FN(set_ptr)(MATITER_T __r, const MATRIX_TYPE *__ptr) {
    *(__r.ptr) = *__ptr;
}

void MATITER_FN(add_ptr)(MATITER_T __r, const MATRIX_TYPE *__ptr) {
    *(__r.ptr) += *__ptr;
}

void MATITER_FN(sub_ptr)(MATITER_T __r, const MATRIX_TYPE *__ptr) {
    *(__r.ptr) -= *__ptr;
}

void MATITER_FN(mult_ptr)(MATITER_T __r, const MATRIX_TYPE *__ptr) {
    *(__r.ptr) *= *__ptr;
}

void MATITER_FN(div_ptr)(MATITER_T __r, const MATRIX_TYPE *__ptr) {
    *(__r.ptr) /= *__ptr;
}

void MATITER_FN(set_iter)(MATITER_T __a, const MATITER_T __b) {
    *(__a.ptr) = *(__b.ptr);
}

void MATITER_FN(set_iter_pow)(MATITER_T __a, const MATITER_T __b, double __n) {
    *(__a.ptr) = pow(*(__b.ptr), __n);
}

void MATITER_FN(add_iter)(MATITER_T __a, const MATITER_T __b) {
    *(__a.ptr) += *(__b.ptr);
}

void MATITER_FN(add_iter_scaled)(MATITER_T __a, const MATITER_T __b, const MATRIX_TYPE __k) {
    *(__a.ptr) += *(__b.ptr) * __k;
}

void MATITER_FN(sub_iter)(MATITER_T __a, const MATITER_T __b) {
    *(__a.ptr) -= *(__b.ptr);
}

void MATITER_FN(mult_iter)(MATITER_T __a, const MATITER_T __b) {
    *(__a.ptr) *= *(__b.ptr);
}

void MATITER_FN(div_iter)(MATITER_T __a, const MATITER_T __b) {
    *(__a.ptr) /= *(__b.ptr);
}





/**================================================================================================
 *!                                        MATITER_T basic utility routines - ROW
 *================================================================================================**/

// Set the elements of a row when given a row iterator and a value k
void MATITER_FN(row_set_k)(const MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k) {

    MATITER_T rbegin = __rbegin;

    while (! MATITER_FN(cmp)(rbegin, __rend)) {
        MATITER_FN(set)(rbegin, __k);
        rbegin = MATITER_FN(next)(rbegin);
    }
}

// Set the elements of a row when given a row iterator and another starting iterator
void MATITER_FN(row_set_iter)(const MATITER_T __rbegin, const MATITER_T __rend, const MATITER_T __bbegin) {

    MATITER_T rbegin = __rbegin;
    MATITER_T bbegin = __bbegin;

    while (! MATITER_FN(cmp)(rbegin, __rend)) {
        MATITER_FN(set_iter)(rbegin, bbegin);
        rbegin = MATITER_FN(next)(rbegin);
        bbegin = MATITER_FN(next)(bbegin);
    }
}


void MATITER_FN(row_add_k)(const MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k) {

    MATITER_T rbegin = __rbegin;

    while (! MATITER_FN(cmp)(rbegin, __rend)) {
        MATITER_FN(add_k)(rbegin, __k);
        rbegin = MATITER_FN(next)(rbegin);
    }
}

void MATITER_FN(row_sub_k)(const MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k) {

    MATITER_T rbegin = __rbegin;

    while (! MATITER_FN(cmp)(rbegin, __rend)) {
        MATITER_FN(sub_k)(rbegin, __k);
        rbegin = MATITER_FN(next)(rbegin);
    }
}

void MATITER_FN(row_mult_k)(const MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k) {

    MATITER_T rbegin = __rbegin;

    while (! MATITER_FN(cmp)(rbegin, __rend)) {
        MATITER_FN(mult_k)(rbegin, __k);
        rbegin = MATITER_FN(next)(rbegin);
    }
}

void MATITER_FN(row_div_k)(const MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k) {

    MATITER_T rbegin = __rbegin;

    while (! MATITER_FN(cmp)(rbegin, __rend)) {
        MATITER_FN(div_k)(rbegin, __k);
        rbegin = MATITER_FN(next)(rbegin);
    }
}

// Add to row __a the elements of row __b
void MATITER_FN(row_add_row)(const MATITER_T __abegin, const MATITER_T __aend, const MATITER_T __bbegin) {

    MATITER_T abegin = __abegin;
    MATITER_T bbegin = __bbegin;

    while (! MATITER_FN(cmp)(abegin, __aend)) {
        MATITER_FN(add_iter)(abegin, bbegin);
        abegin = MATITER_FN(next)(abegin);
        bbegin = MATITER_FN(next)(bbegin);
    }
}


/**================================================================================================
 *!                                        Experimental APPLY functions
 *================================================================================================**/

// Appy functions are a way to iterate a ColIter until we reach the "end" point


void MATITER_FN(apply)(const MATITER_T __rbegin, const MATITER_T __rend, TYPED(MatIterFn) __fn) {

    MATITER_T rbegin = __rbegin;

    while (! MATITER_FN(cmp)(rbegin, __rend)) {
        __fn(rbegin);
        rbegin = MATITER_FN(next)(rbegin);
    }
}

void MATITER_FN(apply_k)(const MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k, TYPED(MatIterFn_k) __fn_k) {

    MATITER_T rbegin = __rbegin;

    while (! MATITER_FN(cmp)(rbegin, __rend)) {
        __fn_k(rbegin, __k);
        rbegin = MATITER_FN(next)(rbegin);
    }
}

void MATITER_FN(apply_ptr)(const MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE *__ptr, TYPED(MatIterFn_ptr) __fn_ptr) {

    MATITER_T rbegin = __rbegin;

    while (! MATITER_FN(cmp)(rbegin, __rend)) {
        __fn_ptr(rbegin, __ptr);
        rbegin = MATITER_FN(next)(rbegin);
    }
}

void MATITER_FN(apply_iter)(const MATITER_T __abegin, const MATITER_T __aend, const MATITER_T __bbegin, TYPED(MatIterFn_iter) __fn_iter) {

    MATITER_T abegin = __abegin;
    MATITER_T bbegin = __bbegin;

    while (! MATITER_FN(cmp)(abegin, __aend)) {
        __fn_iter(abegin, bbegin);
        abegin = MATITER_FN(next)(abegin);
        bbegin = MATITER_FN(next)(bbegin);
    }
}

void MATITER_FN(apply_iter_scaled)(const MATITER_T __abegin, const MATITER_T __aend, const MATITER_T __bbegin, const MATRIX_TYPE __k, TYPED(MatIterFn_iter_k) __fn_iter_k) {

    MATITER_T abegin = __abegin;
    MATITER_T bbegin = __bbegin;

    while (! MATITER_FN(cmp)(abegin, __aend)) {
        __fn_iter_k(abegin, bbegin, __k);
        abegin = MATITER_FN(next)(abegin);
        bbegin = MATITER_FN(next)(bbegin);
    }}

/**================================================================================================
 *!                                        Mat manipulations using apply functions
 *================================================================================================**/

/**======================
 *!    Scalar operations
 *========================**/
void MATITER_FN(apply_set_k)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k) {
    MATITER_FN(apply_k)(__rbegin, __rend, __k, MATITER_FN(set));
}

void MATITER_FN(apply_add_k)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k) {
    MATITER_FN(apply_k)(__rbegin, __rend, __k, MATITER_FN(add_k));
}

void MATITER_FN(apply_sub_k)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k) {
    MATITER_FN(apply_k)(__rbegin, __rend, __k, MATITER_FN(sub_k));
}

void MATITER_FN(apply_mult_k)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k) {
    MATITER_FN(apply_k)(__rbegin, __rend, __k, MATITER_FN(mult_k));
}

void MATITER_FN(apply_div_k)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE __k) {
    MATITER_FN(apply_k)(__rbegin, __rend, __k, MATITER_FN(div_k));
}

/**======================
 *!    Pointer operations
 *========================**/

void MATITER_FN(apply_set_ptr)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE *__ptr) {
    MATITER_FN(apply_ptr)(__rbegin, __rend, __ptr, MATITER_FN(set_ptr));
}

void MATITER_FN(apply_add_ptr)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE *__ptr) {
    MATITER_FN(apply_ptr)(__rbegin, __rend, __ptr, MATITER_FN(add_ptr));
}

void MATITER_FN(apply_sub_ptr)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE *__ptr) {
    MATITER_FN(apply_ptr)(__rbegin, __rend, __ptr, MATITER_FN(sub_ptr));
}

void MATITER_FN(apply_mult_ptr)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE *__ptr) {
    MATITER_FN(apply_ptr)(__rbegin, __rend, __ptr, MATITER_FN(mult_ptr));
}

void MATITER_FN(apply_div_ptr)(MATITER_T __rbegin, const MATITER_T __rend, const MATRIX_TYPE *__ptr) {
    MATITER_FN(apply_ptr)(__rbegin, __rend, __ptr, MATITER_FN(div_ptr));
}

/**======================
 *!    Iterator operations
 *========================**/

void MATITER_FN(apply_set_iter)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin) {
    MATITER_FN(apply_iter)(__abegin, __aend, __bbegin, MATITER_FN(set_iter));
}

void MATITER_FN(apply_set_iter_pow)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin, double __n) {
    MATITER_FN(apply_iter_scaled)(__abegin, __aend, __bbegin, __n, MATITER_FN(set_iter_pow));
}

void MATITER_FN(apply_add_iter)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin) {
    MATITER_FN(apply_iter)(__abegin, __aend, __bbegin, MATITER_FN(add_iter));
}

void MATITER_FN(apply_sub_iter)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin) {
    MATITER_FN(apply_iter)(__abegin, __aend, __bbegin, MATITER_FN(sub_iter));
}

void MATITER_FN(apply_mult_iter)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin) {
    MATITER_FN(apply_iter)(__abegin, __aend, __bbegin, MATITER_FN(mult_iter));
}

void MATITER_FN(apply_div_iter)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin) {
    MATITER_FN(apply_iter)(__abegin, __aend, __bbegin, MATITER_FN(div_iter));
}

/**======================
 *!    add iter scaled
 *========================**/
void MATITER_FN(apply_add_iter_scaled)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin, const MATRIX_TYPE __k) {
    MATITER_FN(apply_iter_scaled)(__abegin, __aend, __bbegin, __k, MATITER_FN(add_iter_scaled));
}


// Add a few new functions that allow me to set A Matrix's columns using an arbitrary iterator

// THIS FUNCTION MODIFIES IN PLACE
MATRIX_T *MATRIX_FN(set_col_iter)(MATRIX_T *__m, size_t __j, MATITER_T __source) {

    MATITER_T it = MATRIX_FN(col_begin)(__m, __j);
    const MATITER_T end = MATRIX_FN(col_end)(__m, __j);
    MATITER_FN(apply_set_iter)(it, end, __source);

    return __m;
}

// THIS FUNCTION MODIFIES IN PLACE
MATRIX_T *MATRIX_FN(set_row_iter)(MATRIX_T *__m, size_t __i, MATITER_T __source) {

    MATITER_T it = MATRIX_FN(row_begin)(__m, __i);
    const MATITER_T end = MATRIX_FN(row_end)(__m, __i);
    MATITER_FN(apply_set_iter)(it, end, __source);

    return __m;
}

// TODO I need to add other functions that are the matrix interface to these MATITER_T functions. I want to call
// MATRIX_FN(add_row_iter)(m, 3, it);


// Here I want to implement some functions that deal with the distances between vectors
// given two iterators, I want to find their difference and store it in a new vector.
// Take a - b
Vector *MATITER_FN(difference)(MATITER_T __abegin, const MATITER_T __aend, MATITER_T __bbegin) {

    // Compute the length of the iterator.
    size_t length = MATITER_FN(length)(__abegin, __aend);

    Vector *out = VECTOR_FN(new)(length);

    MATITER_T vout = VECTOR_FN(begin)(out);

    for (__abegin; !MATITER_FN(cmp)(__abegin, __aend);     vout = MATITER_FN(next)(vout),
                                                   __abegin = MATITER_FN(next)(__abegin),
                                                   __bbegin = MATITER_FN(next)(__bbegin))
    {
        MATITER_FN(set)(vout, MATITER_FN(value)(__abegin) - MATITER_FN(value)(__bbegin));
    }

    return out;
}