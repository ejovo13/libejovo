// functions that deal with the creation of iterator objects

#include "ejovo_matrix.h"

// TODO I think it might be a good idea to actually
//! implement the functions that use col iters
//! should be passing copies of the colIter and NOT a pointer
//! I don't really want to modify/ consume the iterator...

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
 *!                                        ColIter basic utility routines - SINGLE
 *================================================================================================**/

/**======================
 *!    Scalar operations
 *========================**/
inline void ColIter_set(ColIter *__c, const MATRIX_TYPE __k) {
    *(__c->ptr) = __k;
}

inline void ColIter_add_k(ColIter *__c, const MATRIX_TYPE __k) {
    *(__c->ptr) += __k;
}

inline void ColIter_sub_k(ColIter *__c, const MATRIX_TYPE __k) {
    *(__c->ptr) -= __k;
}

inline void ColIter_mult_k(ColIter *__c, const MATRIX_TYPE __k) {
    *(__c->ptr) *= __k;
}

inline void ColIter_div_k(ColIter *__c, const MATRIX_TYPE __k) {
    *(__c->ptr) /= __k;
}

/**======================
 *!    Pointer operations
 *========================**/
inline void ColIter_set_ptr(ColIter *__c, const MATRIX_TYPE *__ptr) {
    *(__c->ptr) = *__ptr;
}

inline void ColIter_add_ptr(ColIter *__c, const MATRIX_TYPE *__ptr) {
    *(__c->ptr) += *__ptr;
}

inline void ColIter_sub_ptr(ColIter *__c, const MATRIX_TYPE *__ptr) {
    *(__c->ptr) -= *__ptr;
}

inline void ColIter_mult_ptr(ColIter *__c, const MATRIX_TYPE *__ptr) {
    *(__c->ptr) *= *__ptr;
}

inline void ColIter_div_ptr(ColIter *__c, const MATRIX_TYPE *__ptr) {
    *(__c->ptr) /= *__ptr;
}

/**======================
 *!    Iterator functions
 *========================**/
inline void ColIter_set_iter(ColIter *__a, const ColIter *__b) {
    *(__a->ptr) = *(__b->ptr);
}

inline void ColIter_add_iter(ColIter *__a, const ColIter *__b) {
    *(__a->ptr) += *(__b->ptr);
}

inline void ColIter_sub_iter(ColIter *__a, const ColIter *__b) {
    *(__a->ptr) -= *(__b->ptr);
}

inline void ColIter_mult_iter(ColIter *__a, const ColIter *__b) {
    *(__a->ptr) *= *(__b->ptr);
}

inline void ColIter_div_iter(ColIter *__a, const ColIter *__b) {
    *(__a->ptr) /= *(__b->ptr);
}

/**================================================================================================
 *!                                        ColIter basic utility routines - COLUMN
 *================================================================================================**/

// Set the elements of a row when given a row iterator and a value k
inline void ColIter_col_set_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {

    ColIter *cbegin = ColIter_clone(__cbegin);

    while (! ColIter_cmp(cbegin, __cend)) {
        ColIter_set(cbegin, __k);
        ColIter_next(cbegin);
    }
}

inline void ColIter_col_add_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {

    ColIter *cbegin = ColIter_clone(__cbegin);

    while (! ColIter_cmp(cbegin, __cend)) {
        ColIter_add_k(cbegin, __k);
        ColIter_next(cbegin);
    }
}

inline void ColIter_col_sub_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {

    ColIter *cbegin = ColIter_clone(__cbegin);

    while (! ColIter_cmp(cbegin, __cend)) {
        ColIter_sub_k(cbegin, __k);
        ColIter_next(cbegin);
    }
}

inline void ColIter_col_mult_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {

    ColIter *cbegin = ColIter_clone(__cbegin);

    while (! ColIter_cmp(cbegin, __cend)) {
        ColIter_mult_k(cbegin, __k);
        ColIter_next(cbegin);
    }
}

inline void ColIter_col_div_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {

    ColIter *cbegin = ColIter_clone(__cbegin);

    while (! ColIter_cmp(cbegin, __cend)) {
        ColIter_div_k(cbegin, __k);
        ColIter_next(cbegin);
    }
}

// Add to row __a the elements of row __b
inline void ColIter_col_add_col(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin) {

    ColIter *abegin = ColIter_clone(__abegin);
    ColIter *bbegin = ColIter_clone(__bbegin);

    while (! ColIter_cmp(abegin, __aend)) {
        ColIter_add_iter(abegin, __bbegin);
        ColIter_next(abegin);
        ColIter_next(bbegin);
    }
}

/**================================================================================================
 *!                                        Experimental APPLY functions
 *================================================================================================**/

// Appy functions are a way to iterate a ColIter until we reach the "end" point

inline void ColIter_apply(ColIter *__cbegin, const ColIter *__cend, ColIterFn __fn) {

    ColIter *cbegin = ColIter_clone(__cbegin);

    while (! ColIter_cmp(cbegin, __cend)) {
        __fn(cbegin);
        ColIter_next(cbegin);
    }
}

inline void ColIter_apply_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k, ColIterFn_k __fn_k) {

    ColIter *cbegin = ColIter_clone(__cbegin);

    while (! ColIter_cmp(cbegin, __cend)) {
        __fn_k(cbegin, __k);
        ColIter_next(cbegin);
    }
}

inline void ColIter_apply_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr, ColIterFn_ptr __fn_ptr) {

    ColIter *cbegin = ColIter_clone(__cbegin);

    while (! ColIter_cmp(cbegin, __cend)) {
        __fn_ptr(cbegin, __ptr);
        ColIter_next(cbegin);
    }
}

inline void ColIter_apply_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin, ColIterFn_iter __fn_iter) {

    ColIter *abegin = ColIter_clone(__abegin);
    ColIter *bbegin = ColIter_clone(__bbegin);

    while (! ColIter_cmp(abegin, __aend)) {
        __fn_iter(abegin, bbegin);
        ColIter_next(abegin);
        ColIter_next(bbegin);
    }
}

/**================================================================================================
 *!                                        Col manipulations using apply functions
 *================================================================================================**/

/**======================
 *!    Scalar operations
 *========================**/
void ColIter_apply_set_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {
    ColIter_apply_k(__cbegin, __cend, __k, ColIter_set);
}

void ColIter_apply_add_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {
    ColIter_apply_k(__cbegin, __cend, __k, ColIter_add_k);
}

void ColIter_apply_sub_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {
    ColIter_apply_k(__cbegin, __cend, __k, ColIter_sub_k);
}

void ColIter_apply_mult_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {
    ColIter_apply_k(__cbegin, __cend, __k, ColIter_mult_k);
}

void ColIter_apply_div_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {
    ColIter_apply_k(__cbegin, __cend, __k, ColIter_div_k);
}

/**======================
 *!    Pointer operations
 *========================**/

void ColIter_apply_set_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr) {
    ColIter_apply_ptr(__cbegin, __cend, __ptr, ColIter_set_ptr);
}

void ColIter_apply_add_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr) {
    ColIter_apply_ptr(__cbegin, __cend, __ptr, ColIter_add_ptr);
}

void ColIter_apply_sub_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr) {
    ColIter_apply_ptr(__cbegin, __cend, __ptr, ColIter_sub_ptr);
}

void ColIter_apply_mult_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr) {
    ColIter_apply_ptr(__cbegin, __cend, __ptr, ColIter_mult_ptr);
}

void ColIter_apply_div_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr) {
    ColIter_apply_ptr(__cbegin, __cend, __ptr, ColIter_div_ptr);
}

/**======================
 *!    Iterator operations
 *========================**/

void ColIter_apply_set_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin) {
    ColIter_apply_iter(__abegin, __aend, __bbegin, ColIter_set_iter);
}

void ColIter_apply_add_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin) {
    ColIter_apply_iter(__abegin, __aend, __bbegin, ColIter_add_iter);
}

void ColIter_apply_sub_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin) {
    ColIter_apply_iter(__abegin, __aend, __bbegin, ColIter_sub_iter);
}

void ColIter_apply_mult_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin) {
    ColIter_apply_iter(__abegin, __aend, __bbegin, ColIter_mult_iter);
}

void ColIter_apply_div_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin) {
    ColIter_apply_iter(__abegin, __aend, __bbegin, ColIter_div_iter);
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

//! This function should actually never be called
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
        return matrowpos(__A, __i, 0);
    } else {
        perror("Matrix does not have that many rows");
        return NULL;
    }
}

inline MATRIX_TYPE RowIter_value(const RowIter *__c) {
    return *(__c->ptr);
}

/**================================================================================================
 *!                                        RowIter basic utility routines - SINGLE
 *================================================================================================**/

inline void RowIter_set(RowIter *__r, const MATRIX_TYPE __k) {
    *(__r->ptr) = __k;
}

inline void RowIter_add_k(RowIter *__r, const MATRIX_TYPE __k) {
    *(__r->ptr) += __k;
}

inline void RowIter_sub_k(RowIter *__r, const MATRIX_TYPE __k) {
    *(__r->ptr) -= __k;
}

inline void RowIter_mult_k(RowIter *__r, const MATRIX_TYPE __k) {
    *(__r->ptr) *= __k;
}

inline void RowIter_div_k(RowIter *__r, const MATRIX_TYPE __k) {
    *(__r->ptr) /= __k;
}

inline void RowIter_set_ptr(RowIter *__r, const MATRIX_TYPE *__ptr) {
    *(__r->ptr) = *__ptr;
}

inline void RowIter_add_ptr(RowIter *__r, const MATRIX_TYPE *__ptr) {
    *(__r->ptr) += *__ptr;
}

inline void RowIter_sub_ptr(RowIter *__r, const MATRIX_TYPE *__ptr) {
    *(__r->ptr) -= *__ptr;
}

inline void RowIter_mult_ptr(RowIter *__r, const MATRIX_TYPE *__ptr) {
    *(__r->ptr) *= *__ptr;
}

inline void RowIter_div_ptr(RowIter *__r, const MATRIX_TYPE *__ptr) {
    *(__r->ptr) /= *__ptr;
}

inline void RowIter_set_iter(RowIter *__a, const RowIter *__b) {
    *(__a->ptr) = *(__b->ptr);
}

inline void RowIter_add_iter(RowIter *__a, const RowIter *__b) {
    *(__a->ptr) += *(__b->ptr);
}

inline void RowIter_sub_iter(RowIter *__a, const RowIter *__b) {
    *(__a->ptr) -= *(__b->ptr);
}

inline void RowIter_mult_iter(RowIter *__a, const RowIter *__b) {
    *(__a->ptr) *= *(__b->ptr);
}

inline void RowIter_div_iter(RowIter *__a, const RowIter *__b) {
    *(__a->ptr) /= *(__b->ptr);
}

/**================================================================================================
 *!                                        RowIter basic utility routines - ROW
 *================================================================================================**/

// Set the elements of a row when given a row iterator and a value k
inline void RowIter_row_set_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {

    while (! RowIter_cmp(__rbegin, __rend)) {
        RowIter_set(__rbegin, __k);
        RowIter_next(__rbegin);
    }
}

inline void RowIter_row_add_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {

    while (! RowIter_cmp(__rbegin, __rend)) {
        RowIter_add_k(__rbegin, __k);
        RowIter_next(__rbegin);
    }
}

inline void RowIter_row_sub_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {

    while (! RowIter_cmp(__rbegin, __rend)) {
        RowIter_sub_k(__rbegin, __k);
        RowIter_next(__rbegin);
    }
}

inline void RowIter_row_mult_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {

    while (! RowIter_cmp(__rbegin, __rend)) {
        RowIter_mult_k(__rbegin, __k);
        RowIter_next(__rbegin);
    }
}

inline void RowIter_row_div_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {

    while (! RowIter_cmp(__rbegin, __rend)) {
        RowIter_div_k(__rbegin, __k);
        RowIter_next(__rbegin);
    }
}

// Add to row __a the elements of row __b
inline void RowIter_row_add_row(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin) {

    while (! RowIter_cmp(__abegin, __aend)) {
        RowIter_add_iter(__abegin, __bbegin);
        RowIter_next(__abegin);
        RowIter_next(__bbegin);
    }
}


/**================================================================================================
 *!                                        Experimental APPLY functions
 *================================================================================================**/

// Appy functions are a way to iterate a ColIter until we reach the "end" point


inline void RowIter_apply(RowIter *__rbegin, const RowIter *__rend, RowIterFn __fn) {
    while (! RowIter_cmp(__rbegin, __rend)) {
        __fn(__rbegin);
        RowIter_next(__rbegin);
    }
}

inline void RowIter_apply_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k, RowIterFn_k __fn_k) {
    while (! RowIter_cmp(__rbegin, __rend)) {
        __fn_k(__rbegin, __k);
        RowIter_next(__rbegin);
    }
}

inline void RowIter_apply_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr, RowIterFn_ptr __fn_ptr) {
    while (! RowIter_cmp(__rbegin, __rend)) {
        __fn_ptr(__rbegin, __ptr);
        RowIter_next(__rbegin);
    }
}

inline void RowIter_apply_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin, RowIterFn_iter __fn_iter) {
    while (! RowIter_cmp(__abegin, __aend)) {
        __fn_iter(__abegin, __bbegin);
        RowIter_next(__abegin);
        RowIter_next(__bbegin);
    }
}

/**================================================================================================
 *!                                        Row manipulations using apply functions
 *================================================================================================**/

/**======================
 *!    Scalar operations
 *========================**/
void RowIter_apply_set_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {
    RowIter_apply_k(__rbegin, __rend, __k, RowIter_set);
}

void RowIter_apply_add_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {
    RowIter_apply_k(__rbegin, __rend, __k, RowIter_add_k);
}

void RowIter_apply_sub_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {
    RowIter_apply_k(__rbegin, __rend, __k, RowIter_sub_k);
}

void RowIter_apply_mult_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {
    RowIter_apply_k(__rbegin, __rend, __k, RowIter_mult_k);
}

void RowIter_apply_div_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {
    RowIter_apply_k(__rbegin, __rend, __k, RowIter_div_k);
}

/**======================
 *!    Pointer operations
 *========================**/

void RowIter_apply_set_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr) {
    RowIter_apply_ptr(__rbegin, __rend, __ptr, RowIter_set_ptr);
}

void RowIter_apply_add_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr) {
    RowIter_apply_ptr(__rbegin, __rend, __ptr, RowIter_add_ptr);
}

void RowIter_apply_sub_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr) {
    RowIter_apply_ptr(__rbegin, __rend, __ptr, RowIter_sub_ptr);
}

void RowIter_apply_mult_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr) {
    RowIter_apply_ptr(__rbegin, __rend, __ptr, RowIter_mult_ptr);
}

void RowIter_apply_div_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr) {
    RowIter_apply_ptr(__rbegin, __rend, __ptr, RowIter_div_ptr);
}

/**======================
 *!    Iterator operations
 *========================**/

void RowIter_apply_set_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin) {
    RowIter_apply_iter(__abegin, __aend, __bbegin, RowIter_set_iter);
}

void RowIter_apply_add_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin) {
    RowIter_apply_iter(__abegin, __aend, __bbegin, RowIter_add_iter);
}

void RowIter_apply_sub_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin) {
    RowIter_apply_iter(__abegin, __aend, __bbegin, RowIter_sub_iter);
}

void RowIter_apply_mult_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin) {
    RowIter_apply_iter(__abegin, __aend, __bbegin, RowIter_mult_iter);
}

void RowIter_apply_div_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin) {
    RowIter_apply_iter(__abegin, __aend, __bbegin, RowIter_div_iter);
}






