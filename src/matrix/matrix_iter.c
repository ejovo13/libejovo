// functions that deal with the creation of iterator objects

#include "ejovo_matrix.h"

// TODO I need to add checks for some of my iterator functions like matdiagend -> Matrix_diag_end

/**================================================================================================
 *!                                        Special Types of Iterators
 *================================================================================================**/
// Should have row, col, diagonal iterators. There are even some special iterators like "checkerboards"
// that can hit every other element.

MatIter matdiagbegin(const Matrix *__m, const int __d) {
    if (__d == 0) {
        return MatIter_new(matacc(__m, 0, 0), __m->ncols + 1);
    } else if (__d > 0) {
        return MatIter_new(matacc(__m, 0, __d), __m->ncols + 1);
    } else {
        return MatIter_new(matacc(__m, -__d, 0), __m->ncols + 1);
    }
}

MatIter matdiagend(const Matrix *__m, const int __d) {

    // First I have to work out whether is wide or tall
    size_t lim = 0;

    if (__d == 0) {
        // Then i need to find the smaller side
        lim = Matrix_rect_limit(__m);
        return MatIter_new(matacc(__m, lim, lim), __m->ncols + 1);

    } else if (__d > 0) {
        size_t adj_cols = __m->ncols - __d;
        lim = adj_cols < __m->nrows ? adj_cols : __m->nrows;
        return MatIter_new(matacc(__m, lim, lim + __d), __m->ncols + 1);
    } else {
        size_t adj_rows = __m->nrows + __d;
        lim = adj_rows < __m->ncols ? adj_rows : __m->ncols;
        return MatIter_new(matacc(__m, lim - __d, lim), __m->ncols + 1);
    }
}

void MatIter_print(const MatIter __begin, const MatIter __end) {

    MatIter iter = __begin;

    printf("{");
    iter = MatIter_next(iter);

    while (! MatIter_cmp(iter, __end)) {
        printf("%lf, ", *(iter.ptr - iter.ptr_diff)); //basically, print the previous value
        iter = MatIter_next(iter);
    }

    printf("%lf}\n", *(iter.ptr - iter.ptr_diff)); //basically, print the previous value

}


// The 0th diagonal will start at the position __m(0, 0)
// The 1st diagonal will start at the position __m(0, 1)
// The -1  diagonal will start at the position __m(1, 0)
// MatIter Matrix_diag_begin(const Matrix *__m, const int __d) {
//
// }






/**================================================================================================
 *!                                        RowCol and ColIter
 *================================================================================================**/

MATRIX_TYPE Iter_dot(const MatIter __r, const MatIter __rend, const MatIter __c) {

    MATRIX_TYPE dot = 0;

    while(!MatIter_cmp(__r, __rend)) {

        dot += MatIter_value(__r) * MatIter_value(__c);
        MatIter_next(__r);
        MatIter_next(__c);

    }

    return dot;

}

/**=======================================================================================================================
 *!                                           Matrix Interface to Iter functions
 *=======================================================================================================================**/

void Matrix_print_row(const Matrix *__A, size_t __i) {

    MatIter b = Matrix_row_begin(__A, __i);
    MatIter e = Matrix_row_end(__A, __i);

    printf("Row %ld: ", __i + 1);
    MatIter_print(b, e);
}

void Matrix_print_col(const Matrix *__A, size_t __j) {

    MatIter b = Matrix_col_begin(__A, __j);
    MatIter e = Matrix_col_end(__A, __j);

    printf("Col %ld: ", __j + 1);
    MatIter_print(b, e);
}


void Matrix_print_diag(const Matrix *__A, size_t __d) {

    MatIter b = matdiagbegin(__A, __d);
    MatIter e = matdiagend(__A, __d);

    printf("Diag %ld: ", __d);
    MatIter_print(b, e);
}

// Here I want to be able to manipulate the functions defined above to create clean and simple Matrix api

// let's start simple and add rows together

// matrix elementary row operation (add two rows)
void matrowop_add(Matrix *__A, const size_t __r1, const size_t __r2, const size_t __col_offset) {

    const MatIter r1begin = matrowpos(__A, __r1, __col_offset);
    const MatIter r1end = matrowend(__A, __r1);
    const MatIter r2begin = matrowpos(__A, __r2, __col_offset);

    MatIter_apply_add_iter(r1begin, r1end, r2begin);
}

// matrix elementary row operation (add two rows)
void matrowop_add_scaled(Matrix *__A, const size_t __r1, const size_t __r2, const MATRIX_TYPE __k, const size_t __col_offset) {

    const MatIter r1begin = matrowpos(__A, __r1, __col_offset);
    const MatIter r1end = matrowend(__A, __r1);
    const MatIter r2begin = matrowpos(__A, __r2, __col_offset);

    MatIter_apply_add_iter_scaled(r1begin, r1end, r2begin, __k);
}

void Matrix_rowop_add(Matrix *__A, const size_t __r1, const size_t __r2) {
    matrowop_add(__A, __r1, __r2, 0);
}

void Matrix_rowop_add_offset(Matrix *__A, const size_t __r1, const size_t __r2, const size_t __col_offset) {
    if (__col_offset < __A->ncols) {
        matrowop_add(__A, __r1, __r2, __col_offset);
    }
}

void Matrix_rowop_add_scaled(Matrix *__A, const size_t __r1, const size_t __r2, const MATRIX_TYPE __k) {
    matrowop_add_scaled(__A, __r1, __r2, __k, 0);
}

MATRIX_TYPE Matrix_row_min(const Matrix *__A, const size_t __i) {
    MatIter b = matrowbegin(__A, __i);
    MatIter e = matrowend(__A, __i);

    MATRIX_TYPE min = MatIter_min(b, e);
    return min;
}

MATRIX_TYPE Matrix_row_max(const Matrix *__A, const size_t __i) {
    return MatIter_max(matrowbegin(__A, __i), matrowend(__A, __i));
}

MATRIX_TYPE Matrix_col_min(const Matrix *__A, const size_t __j) {
    return MatIter_min(matcolbegin(__A, __j), matcolend(__A, __j));
}

MATRIX_TYPE Matrix_col_max(const Matrix *__A, const size_t __j) {
    return MatIter_max(matcolbegin(__A, __j), matcolend(__A, __j));
}

MATRIX_TYPE Matrix_diag_min(const Matrix *__A, const size_t __j) {
    return MatIter_min(matdiagbegin(__A, __j), matdiagend(__A, __j));
}

MATRIX_TYPE Matrix_diag_max(const Matrix *__A, const size_t __j) {
    return MatIter_max(matdiagbegin(__A, __j), matdiagend(__A, __j));
}

MATRIX_TYPE Matrix_row_prod(const Matrix *__A, const size_t __i) {
    return MatIter_prod(matrowbegin(__A, __i), matrowend(__A, __i));
}

MATRIX_TYPE Matrix_col_prod(const Matrix *__A, const size_t __i) {
    return MatIter_prod(matcolbegin(__A, __i), matcolend(__A, __i));
}

MATRIX_TYPE Matrix_diag_prod(const Matrix *__A, const size_t __i) {
    return MatIter_prod(matdiagbegin(__A, __i), matdiagend(__A, __i));
}


MATRIX_TYPE Matrix_row_sum(const Matrix *__A, const size_t __i) {
    return MatIter_sum(matrowbegin(__A, __i), matrowend(__A, __i));
}

MATRIX_TYPE Matrix_col_sum(const Matrix *__A, const size_t __i) {
    return MatIter_sum(matcolbegin(__A, __i), matcolend(__A, __i));
}

MATRIX_TYPE Matrix_diag_sum(const Matrix *__A, const size_t __i) {
    return MatIter_sum(matdiagbegin(__A, __i), matdiagend(__A, __i));
}



MatIter matcolpos(const Matrix *__A, size_t __i, size_t __j) {
    return MatIter_new(matacc(__A, __i, __j), __A->ncols);
}

// return a new Matumn Iterator that points to the final element in this column
MatIter Matrix_col_end(const Matrix *__A, size_t __j) {

    if (__j < __A->ncols) {
        return matcolpos(__A, __A->nrows, __j);
    } else {
        perror("Matrix does not have that many columns");
        MatIter null = {.ptr = NULL, .ptr_diff = 0};
        return null;
    }

}

MatIter Matrix_col_begin(const Matrix *__A, size_t __j) {

    if (__j < __A->ncols) {
        return matcolpos(__A, 0, __j);
    } else {
        perror("Matrix does not have that many columns");
        return MatIter_null();
    }
}

MatIter matcolbegin(const Matrix *__A, size_t __i) {
    return matcolpos(__A, __i, 0);
}

MatIter matcolend(const Matrix *__A, size_t __i) {
    return matcolpos(__A, __i, __A->ncols);
}

MatIter matrowpos(const Matrix *__A, size_t __i, size_t __j) {
    return MatIter_new(matacc(__A, __i, __j), 1); // In row-major order, rows are next to each other
}

// get row iterator without checking bounds
MatIter matrowbegin(const Matrix *__A, size_t __i) {
    return matrowpos(__A, __i, 0);
}

MatIter matrowend(const Matrix *__A, size_t __i) {
    return matrowpos(__A, __i, __A->ncols);
}

// return a new Column Iterator that points to the final element in this column
MatIter Matrix_row_end(const Matrix *__A, size_t __i) {

    if (__i < __A->ncols) {
        return matrowpos(__A, __i, __A->ncols);
    } else {
        perror("Matrix does not have that many columns");
        return MatIter_null();
    }

}

MatIter Matrix_row_begin(const Matrix *__A, size_t __i) {

    if (__i < __A->ncols) {
        return matrowpos(__A, __i, 0);
    } else {
        perror("Matrix does not have that many rows");
        return MatIter_null();
    }
}

/**=======================================================================================================================
 *!                                                   MIter that has more general capabilities
 *=======================================================================================================================**/
MatIter MatIter_new(MATRIX_TYPE *__ptr, size_t __ptr_diff) {
    MatIter c = {.ptr = __ptr, .ptr_diff = __ptr_diff};
    return c;
}

MatIter MatIter_null() {
    MatIter null = {.ptr = NULL, .ptr_diff = 0};
    return null;
}

bool MatIter_is_null(MatIter __i) {
    return __i.ptr == NULL;
}

// Increment the row iter
MatIter MatIter_next(MatIter __c) {
    MatIter next = {.ptr = __c.ptr += __c.ptr_diff, .ptr_diff = __c.ptr_diff};
    return next;
}

// Return true if the __lhs and __rhs point to the same element
bool MatIter_cmp(const MatIter __lhs, const MatIter __rhs) {
    return __lhs.ptr == __rhs.ptr;
}

MATRIX_TYPE MatIter_value(const MatIter __c) {
    return *(__c.ptr);
}

// Return the number of iteration between begin and end
size_t MatIter_length(const MatIter begin, const MatIter end) {
    // printf("[MatIter_length]   end->ptr: %x, begin->ptr: %x\n", end->ptr, begin->ptr);
    size_t diff = end.ptr - begin.ptr;
    return diff / begin.ptr_diff;
}

/**========================================================================
 *!                           Functional Iter functions
 *========================================================================**/
MATRIX_TYPE MatIter_sum(const MatIter __begin, const MatIter __end) {

    MATRIX_TYPE sum = 0;
    MatIter iter = __begin;

    while (!MatIter_cmp(iter, __end)) {
        sum += MatIter_value(iter);
        iter = MatIter_next(iter);
    }

    return sum;
}

MATRIX_TYPE MatIter_prod(const MatIter __begin, const MatIter __end) {

    MATRIX_TYPE prod = 1;
    MatIter iter = __begin;

    while (!MatIter_cmp(iter, __end)) {
        prod *= MatIter_value(iter);
        iter = MatIter_next(iter);
    }

    return prod;
}

// Get the maximum value in a row
MATRIX_TYPE MatIter_max(MatIter __a, const MatIter __b) {

    MATRIX_TYPE max = MatIter_value(__a);
    __a = MatIter_next(__a);

    // This is the MatIter idiom to traverse a row
    while (!MatIter_cmp(__a, __b)) {

        if (MatIter_value(__a) > max)
            max = MatIter_value(__a);

        __a = MatIter_next(__a);
    }

    return max;

}

// Get the maximum value in a row
MATRIX_TYPE MatIter_min(MatIter __a, const MatIter __b) {

    MATRIX_TYPE min = MatIter_value(__a);
    __a = MatIter_next(__a);

    // This is the MatIter idiom to traverse a row
    while (!MatIter_cmp(__a, __b)) {

        if (MatIter_value(__a) < min)
            min = MatIter_value(__a);

        __a = MatIter_next(__a);
    }

    return min;

}

/**================================================================================================
 *!                                        MatIter basic utility routines - SINGLE
 *================================================================================================**/

void MatIter_set(MatIter __r, const MATRIX_TYPE __k) {
    *(__r.ptr) = __k;
}

void MatIter_add_k(MatIter __r, const MATRIX_TYPE __k) {
    *(__r.ptr) += __k;
}

void MatIter_sub_k(MatIter __r, const MATRIX_TYPE __k) {
    *(__r.ptr) -= __k;
}

void MatIter_mult_k(MatIter __r, const MATRIX_TYPE __k) {
    *(__r.ptr) *= __k;
}

void MatIter_div_k(MatIter __r, const MATRIX_TYPE __k) {
    *(__r.ptr) /= __k;
}

void MatIter_set_ptr(MatIter __r, const MATRIX_TYPE *__ptr) {
    *(__r.ptr) = *__ptr;
}

void MatIter_add_ptr(MatIter __r, const MATRIX_TYPE *__ptr) {
    *(__r.ptr) += *__ptr;
}

void MatIter_sub_ptr(MatIter __r, const MATRIX_TYPE *__ptr) {
    *(__r.ptr) -= *__ptr;
}

void MatIter_mult_ptr(MatIter __r, const MATRIX_TYPE *__ptr) {
    *(__r.ptr) *= *__ptr;
}

void MatIter_div_ptr(MatIter __r, const MATRIX_TYPE *__ptr) {
    *(__r.ptr) /= *__ptr;
}

void MatIter_set_iter(MatIter __a, const MatIter __b) {
    *(__a.ptr) = *(__b.ptr);
}

void MatIter_add_iter(MatIter __a, const MatIter __b) {
    *(__a.ptr) += *(__b.ptr);
}

void MatIter_add_iter_scaled(MatIter __a, const MatIter __b, const MATRIX_TYPE __k) {
    *(__a.ptr) += *(__b.ptr) * __k;
}

void MatIter_sub_iter(MatIter __a, const MatIter __b) {
    *(__a.ptr) -= *(__b.ptr);
}

void MatIter_mult_iter(MatIter __a, const MatIter __b) {
    *(__a.ptr) *= *(__b.ptr);
}

void MatIter_div_iter(MatIter __a, const MatIter __b) {
    *(__a.ptr) /= *(__b.ptr);
}





/**================================================================================================
 *!                                        MatIter basic utility routines - ROW
 *================================================================================================**/

// Set the elements of a row when given a row iterator and a value k
void MatIter_row_set_k(const MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k) {

    MatIter rbegin = __rbegin;

    while (! MatIter_cmp(rbegin, __rend)) {
        MatIter_set(rbegin, __k);
        rbegin = MatIter_next(rbegin);
    }
}

// Set the elements of a row when given a row iterator and another starting iterator
void MatIter_row_set_iter(const MatIter __rbegin, const MatIter __rend, const MatIter __bbegin) {

    MatIter rbegin = __rbegin;
    MatIter bbegin = __bbegin;

    while (! MatIter_cmp(rbegin, __rend)) {
        MatIter_set_iter(rbegin, bbegin);
        rbegin = MatIter_next(rbegin);
        bbegin = MatIter_next(bbegin);
    }
}


void MatIter_row_add_k(const MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k) {

    MatIter rbegin = __rbegin;

    while (! MatIter_cmp(rbegin, __rend)) {
        MatIter_add_k(rbegin, __k);
        rbegin = MatIter_next(rbegin);
    }
}

void MatIter_row_sub_k(const MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k) {

    MatIter rbegin = __rbegin;

    while (! MatIter_cmp(rbegin, __rend)) {
        MatIter_sub_k(rbegin, __k);
        rbegin = MatIter_next(rbegin);
    }
}

void MatIter_row_mult_k(const MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k) {

    MatIter rbegin = __rbegin;

    while (! MatIter_cmp(rbegin, __rend)) {
        MatIter_mult_k(rbegin, __k);
        rbegin = MatIter_next(rbegin);
    }
}

void MatIter_row_div_k(const MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k) {

    MatIter rbegin = __rbegin;

    while (! MatIter_cmp(rbegin, __rend)) {
        MatIter_div_k(rbegin, __k);
        rbegin = MatIter_next(rbegin);
    }
}

// Add to row __a the elements of row __b
void MatIter_row_add_row(const MatIter __abegin, const MatIter __aend, const MatIter __bbegin) {

    MatIter abegin = __abegin;
    MatIter bbegin = __bbegin;

    while (! MatIter_cmp(abegin, __aend)) {
        MatIter_add_iter(abegin, bbegin);
        abegin = MatIter_next(abegin);
        bbegin = MatIter_next(bbegin);
    }
}


/**================================================================================================
 *!                                        Experimental APPLY functions
 *================================================================================================**/

// Appy functions are a way to iterate a ColIter until we reach the "end" point


void MatIter_apply(const MatIter __rbegin, const MatIter __rend, MatIterFn __fn) {

    MatIter rbegin = __rbegin;

    while (! MatIter_cmp(rbegin, __rend)) {
        __fn(rbegin);
        rbegin = MatIter_next(rbegin);
    }
}

void MatIter_apply_k(const MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k, MatIterFn_k __fn_k) {

    MatIter rbegin = __rbegin;

    while (! MatIter_cmp(rbegin, __rend)) {
        __fn_k(rbegin, __k);
        rbegin = MatIter_next(rbegin);
    }
}

void MatIter_apply_ptr(const MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE *__ptr, MatIterFn_ptr __fn_ptr) {

    MatIter rbegin = __rbegin;

    while (! MatIter_cmp(rbegin, __rend)) {
        __fn_ptr(rbegin, __ptr);
        rbegin = MatIter_next(rbegin);
    }
}

void MatIter_apply_iter(const MatIter __abegin, const MatIter __aend, const MatIter __bbegin, MatIterFn_iter __fn_iter) {

    MatIter abegin = __abegin;
    MatIter bbegin = __bbegin;

    while (! MatIter_cmp(abegin, __aend)) {
        __fn_iter(abegin, bbegin);
        abegin = MatIter_next(abegin);
        bbegin = MatIter_next(bbegin);
    }
}

void MatIter_apply_iter_scaled(const MatIter __abegin, const MatIter __aend, const MatIter __bbegin, const MATRIX_TYPE __k, MatIterFn_iter_k __fn_iter_k) {

    MatIter abegin = __abegin;
    MatIter bbegin = __bbegin;

    while (! MatIter_cmp(abegin, __aend)) {
        __fn_iter_k(abegin, bbegin, __k);
        abegin = MatIter_next(abegin);
        bbegin = MatIter_next(bbegin);
    }}

/**================================================================================================
 *!                                        Mat manipulations using apply functions
 *================================================================================================**/

/**======================
 *!    Scalar operations
 *========================**/
void MatIter_apply_set_k(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k) {
    MatIter_apply_k(__rbegin, __rend, __k, MatIter_set);
}

void MatIter_apply_add_k(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k) {
    MatIter_apply_k(__rbegin, __rend, __k, MatIter_add_k);
}

void MatIter_apply_sub_k(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k) {
    MatIter_apply_k(__rbegin, __rend, __k, MatIter_sub_k);
}

void MatIter_apply_mult_k(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k) {
    MatIter_apply_k(__rbegin, __rend, __k, MatIter_mult_k);
}

void MatIter_apply_div_k(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE __k) {
    MatIter_apply_k(__rbegin, __rend, __k, MatIter_div_k);
}

/**======================
 *!    Pointer operations
 *========================**/

void MatIter_apply_set_ptr(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE *__ptr) {
    MatIter_apply_ptr(__rbegin, __rend, __ptr, MatIter_set_ptr);
}

void MatIter_apply_add_ptr(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE *__ptr) {
    MatIter_apply_ptr(__rbegin, __rend, __ptr, MatIter_add_ptr);
}

void MatIter_apply_sub_ptr(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE *__ptr) {
    MatIter_apply_ptr(__rbegin, __rend, __ptr, MatIter_sub_ptr);
}

void MatIter_apply_mult_ptr(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE *__ptr) {
    MatIter_apply_ptr(__rbegin, __rend, __ptr, MatIter_mult_ptr);
}

void MatIter_apply_div_ptr(MatIter __rbegin, const MatIter __rend, const MATRIX_TYPE *__ptr) {
    MatIter_apply_ptr(__rbegin, __rend, __ptr, MatIter_div_ptr);
}

/**======================
 *!    Iterator operations
 *========================**/

void MatIter_apply_set_iter(MatIter __abegin, const MatIter __aend, MatIter __bbegin) {
    MatIter_apply_iter(__abegin, __aend, __bbegin, MatIter_set_iter);
}

void MatIter_apply_add_iter(MatIter __abegin, const MatIter __aend, MatIter __bbegin) {
    MatIter_apply_iter(__abegin, __aend, __bbegin, MatIter_add_iter);
}

void MatIter_apply_sub_iter(MatIter __abegin, const MatIter __aend, MatIter __bbegin) {
    MatIter_apply_iter(__abegin, __aend, __bbegin, MatIter_sub_iter);
}

void MatIter_apply_mult_iter(MatIter __abegin, const MatIter __aend, MatIter __bbegin) {
    MatIter_apply_iter(__abegin, __aend, __bbegin, MatIter_mult_iter);
}

void MatIter_apply_div_iter(MatIter __abegin, const MatIter __aend, MatIter __bbegin) {
    MatIter_apply_iter(__abegin, __aend, __bbegin, MatIter_div_iter);
}

/**======================
 *!    add iter scaled
 *========================**/
void MatIter_apply_add_iter_scaled(MatIter __abegin, const MatIter __aend, MatIter __bbegin, const MATRIX_TYPE __k) {
    MatIter_apply_iter_scaled(__abegin, __aend, __bbegin, __k, MatIter_add_iter_scaled);
}


