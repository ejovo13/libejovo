// functions that deal with the creation of iterator objects

#include "ejovo_matrix.h"

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