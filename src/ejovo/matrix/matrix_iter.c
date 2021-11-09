// functions that deal with the creation of iterator objects

#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Column Iterators
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

inline void ColIter_next(ColIter *__c) {
    __c->ptr += __c->ncols;
}

// Return true if the __lhs and __rhs point to the same element
inline bool ColIter_cmp(const ColIter *__lhs, const ColIter *__rhs) {
    return __lhs->ptr == __rhs->ptr;
}

inline ColIter *matcolpos(const Matrix *__A, size_t __i, size_t __j) {
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

inline MATRIX_TYPE ColIter_value(const ColIter *__c) {
    return *(__c->ptr);
}

/**================================================================================================
 *!                                        Row Iterators
 *================================================================================================**/
RowIter *RowIter_new(MATRIX_TYPE *__ptr, size_t __ptr_diff) {

    RowIter *c = (RowIter *) malloc(sizeof(RowIter));

    if (c) {
        c->ptr = __ptr;
        c->ptr_diff = __ptr_diff;
    }
    return c;
}

RowIter *RowIter_clone(const RowIter *__c) {
    return RowIter_new(__c->ptr, __c->ptr_diff);
}

void RowIter_free(RowIter *__c) {

    if (__c) {

        if (__c->ptr) {
            free(__c->ptr);
        }
        free(__c);
    }
}

inline void RowIter_next(RowIter *__c) {
    __c->ptr += __c->ptr_diff;
}

// Return true if the __lhs and __rhs point to the same element
inline bool RowIter_cmp(const RowIter *__lhs, const RowIter *__rhs) {
    return __lhs->ptr == __rhs->ptr;
}

inline RowIter *matrowpos(const Matrix *__A, size_t __i, size_t __j) {
    return RowIter_new(matacc(__A, __i, __j), 1); // In row-major order, rows are next to each other
}


// return a new Column Iterator that points to the final element in this column
RowIter *Matrix_row_end(const Matrix *__A, size_t __i) {

    if (__i < __A->ncols) {
        return matrowpos(__A, __i, __A->ncols);
    } else {
        perror("Matrix does not have that many columns");
        return NULL;
    }

}

RowIter *Matrix_row_begin(const Matrix *__A, size_t __i) {

    if (__i < __A->ncols) {
        return matrowpos(__A, 0, __i);
    } else {
        perror("Matrix does not have that many rows");
        return NULL;
    }
}

inline MATRIX_TYPE RowIter_value(const RowIter *__c) {
    return *(__c->ptr);
}