// functions that deal with the creation of iterator objects

#include "ejovo_matrix.h"

// TODO I think it might be a good idea to actually
//! implement the functions that use col iters
//! should be passing copies of the colIter and NOT a pointer
//! I don't really want to modify/ consume the iterator...

// /**================================================================================================
//  *!                                        Column Iterators
//  *================================================================================================**/
// ColIter *ColIter_new(MATRIX_TYPE *__ptr, size_t __ncols) {

//     ColIter *c = (ColIter *) malloc(sizeof(ColIter));

//     if (c) {
//         c->ptr = __ptr;
//         c->ncols = __ncols;
//     }
//     return c;
// }

// ColIter *ColIter_clone(const ColIter *__c) {
//     return ColIter_new(__c->ptr, __c->ncols);
// }

// void ColIter_free(ColIter *__c) {

//     if (__c) {

//         if (__c->ptr) {
//             free(__c->ptr);
//         }
//         free(__c);
//     }
// }

// void ColIter_next(ColIter *__c) {
//     __c->ptr += __c->ncols;
// }

// // Return true if the __lhs and __rhs point to the same element
// bool ColIter_cmp(const ColIter *__lhs, const ColIter *__rhs) {
//     return __lhs->ptr == __rhs->ptr;
// }

// // ColIter *matcolpos(const Matrix *__A, size_t __i, size_t __j) {
// //     return ColIter_new(matacc(__A, __i, __j), __A->ncols);
// // }


// // // return a new Column Iterator that points to the final element in this column
// // ColIter *Matrix_col_end(const Matrix *__A, size_t __j) {

// //     if (__j < __A->ncols) {
// //         return matcolpos(__A, __A->nrows, __j);
// //     } else {
// //         perror("Matrix does not have that many columns");
// //         return NULL;
// //     }

// // }

// // ColIter *Matrix_col_begin(const Matrix *__A, size_t __j) {

// //     if (__j < __A->ncols) {
// //         return matcolpos(__A, 0, __j);
// //     } else {
// //         perror("Matrix does not have that many columns");
// //         return NULL;
// //     }
// // }

// MATRIX_TYPE ColIter_value(const ColIter *__c) {
//     return *(__c->ptr);
// }

// /**================================================================================================
//  *!                                        ColIter basic utility routines - SINGLE
//  *================================================================================================**/

// /**======================
//  *!    Scalar operations
//  *========================**/
// void ColIter_set(ColIter *__c, const MATRIX_TYPE __k) {
//     *(__c->ptr) = __k;
// }

// void ColIter_add_k(ColIter *__c, const MATRIX_TYPE __k) {
//     *(__c->ptr) += __k;
// }

// void ColIter_sub_k(ColIter *__c, const MATRIX_TYPE __k) {
//     *(__c->ptr) -= __k;
// }

// void ColIter_mult_k(ColIter *__c, const MATRIX_TYPE __k) {
//     *(__c->ptr) *= __k;
// }

// void ColIter_div_k(ColIter *__c, const MATRIX_TYPE __k) {
//     *(__c->ptr) /= __k;
// }

// /**======================
//  *!    Pointer operations
//  *========================**/
// void ColIter_set_ptr(ColIter *__c, const MATRIX_TYPE *__ptr) {
//     *(__c->ptr) = *__ptr;
// }

// void ColIter_add_ptr(ColIter *__c, const MATRIX_TYPE *__ptr) {
//     *(__c->ptr) += *__ptr;
// }

// void ColIter_sub_ptr(ColIter *__c, const MATRIX_TYPE *__ptr) {
//     *(__c->ptr) -= *__ptr;
// }

// void ColIter_mult_ptr(ColIter *__c, const MATRIX_TYPE *__ptr) {
//     *(__c->ptr) *= *__ptr;
// }

// void ColIter_div_ptr(ColIter *__c, const MATRIX_TYPE *__ptr) {
//     *(__c->ptr) /= *__ptr;
// }

// /**======================
//  *!    Iterator functions
//  *========================**/
// void ColIter_set_iter(ColIter *__a, const ColIter *__b) {
//     *(__a->ptr) = *(__b->ptr);
// }

// void ColIter_add_iter(ColIter *__a, const ColIter *__b) {
//     *(__a->ptr) += *(__b->ptr);
// }

// void ColIter_sub_iter(ColIter *__a, const ColIter *__b) {
//     *(__a->ptr) -= *(__b->ptr);
// }

// void ColIter_mult_iter(ColIter *__a, const ColIter *__b) {
//     *(__a->ptr) *= *(__b->ptr);
// }

// void ColIter_div_iter(ColIter *__a, const ColIter *__b) {
//     *(__a->ptr) /= *(__b->ptr);
// }

// /**================================================================================================
//  *!                                        ColIter basic utility routines - COLUMN
//  *================================================================================================**/

// // Set the elements of a row when given a row iterator and a value k
// void ColIter_col_set_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {

//     ColIter *cbegin = ColIter_clone(__cbegin);

//     while (! ColIter_cmp(cbegin, __cend)) {
//         ColIter_set(cbegin, __k);
//         ColIter_next(cbegin);
//     }
// }

// void ColIter_col_add_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {

//     ColIter *cbegin = ColIter_clone(__cbegin);

//     while (! ColIter_cmp(cbegin, __cend)) {
//         ColIter_add_k(cbegin, __k);
//         ColIter_next(cbegin);
//     }
// }

// void ColIter_col_sub_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {

//     ColIter *cbegin = ColIter_clone(__cbegin);

//     while (! ColIter_cmp(cbegin, __cend)) {
//         ColIter_sub_k(cbegin, __k);
//         ColIter_next(cbegin);
//     }
// }

// void ColIter_col_mult_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {

//     ColIter *cbegin = ColIter_clone(__cbegin);

//     while (! ColIter_cmp(cbegin, __cend)) {
//         ColIter_mult_k(cbegin, __k);
//         ColIter_next(cbegin);
//     }
// }

// void ColIter_col_div_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {

//     ColIter *cbegin = ColIter_clone(__cbegin);

//     while (! ColIter_cmp(cbegin, __cend)) {
//         ColIter_div_k(cbegin, __k);
//         ColIter_next(cbegin);
//     }
// }

// // Add to row __a the elements of row __b
// void ColIter_col_add_col(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin) {

//     ColIter *abegin = ColIter_clone(__abegin);
//     ColIter *bbegin = ColIter_clone(__bbegin);

//     while (! ColIter_cmp(abegin, __aend)) {
//         ColIter_add_iter(abegin, __bbegin);
//         ColIter_next(abegin);
//         ColIter_next(bbegin);
//     }
// }

// /**================================================================================================
//  *!                                        Experimental APPLY functions
//  *================================================================================================**/

// // Appy functions are a way to iterate a ColIter until we reach the "end" point

// void ColIter_apply(ColIter *__cbegin, const ColIter *__cend, ColIterFn __fn) {

//     ColIter *cbegin = ColIter_clone(__cbegin);

//     while (! ColIter_cmp(cbegin, __cend)) {
//         __fn(cbegin);
//         ColIter_next(cbegin);
//     }
// }

// void ColIter_apply_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k, ColIterFn_k __fn_k) {

//     ColIter *cbegin = ColIter_clone(__cbegin);

//     while (! ColIter_cmp(cbegin, __cend)) {
//         __fn_k(cbegin, __k);
//         ColIter_next(cbegin);
//     }
// }

// void ColIter_apply_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr, ColIterFn_ptr __fn_ptr) {

//     ColIter *cbegin = ColIter_clone(__cbegin);

//     while (! ColIter_cmp(cbegin, __cend)) {
//         __fn_ptr(cbegin, __ptr);
//         ColIter_next(cbegin);
//     }
// }

// void ColIter_apply_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin, ColIterFn_iter __fn_iter) {

//     ColIter *abegin = ColIter_clone(__abegin);
//     ColIter *bbegin = ColIter_clone(__bbegin);

//     while (! ColIter_cmp(abegin, __aend)) {
//         __fn_iter(abegin, bbegin);
//         ColIter_next(abegin);
//         ColIter_next(bbegin);
//     }
// }

// /**================================================================================================
//  *!                                        Col manipulations using apply functions
//  *================================================================================================**/

// /**======================
//  *!    Scalar operations
//  *========================**/
// void ColIter_apply_set_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {
//     ColIter_apply_k(__cbegin, __cend, __k, ColIter_set);
// }

// void ColIter_apply_add_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {
//     ColIter_apply_k(__cbegin, __cend, __k, ColIter_add_k);
// }

// void ColIter_apply_sub_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {
//     ColIter_apply_k(__cbegin, __cend, __k, ColIter_sub_k);
// }

// void ColIter_apply_mult_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {
//     ColIter_apply_k(__cbegin, __cend, __k, ColIter_mult_k);
// }

// void ColIter_apply_div_k(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE __k) {
//     ColIter_apply_k(__cbegin, __cend, __k, ColIter_div_k);
// }

// /**======================
//  *!    Pointer operations
//  *========================**/

// void ColIter_apply_set_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr) {
//     ColIter_apply_ptr(__cbegin, __cend, __ptr, ColIter_set_ptr);
// }

// void ColIter_apply_add_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr) {
//     ColIter_apply_ptr(__cbegin, __cend, __ptr, ColIter_add_ptr);
// }

// void ColIter_apply_sub_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr) {
//     ColIter_apply_ptr(__cbegin, __cend, __ptr, ColIter_sub_ptr);
// }

// void ColIter_apply_mult_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr) {
//     ColIter_apply_ptr(__cbegin, __cend, __ptr, ColIter_mult_ptr);
// }

// void ColIter_apply_div_ptr(ColIter *__cbegin, const ColIter *__cend, const MATRIX_TYPE *__ptr) {
//     ColIter_apply_ptr(__cbegin, __cend, __ptr, ColIter_div_ptr);
// }

// /**======================
//  *!    Iterator operations
//  *========================**/

// void ColIter_apply_set_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin) {
//     ColIter_apply_iter(__abegin, __aend, __bbegin, ColIter_set_iter);
// }

// void ColIter_apply_add_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin) {
//     ColIter_apply_iter(__abegin, __aend, __bbegin, ColIter_add_iter);
// }

// void ColIter_apply_sub_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin) {
//     ColIter_apply_iter(__abegin, __aend, __bbegin, ColIter_sub_iter);
// }

// void ColIter_apply_mult_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin) {
//     ColIter_apply_iter(__abegin, __aend, __bbegin, ColIter_mult_iter);
// }

// void ColIter_apply_div_iter(ColIter *__abegin, const ColIter *__aend, ColIter *__bbegin) {
//     ColIter_apply_iter(__abegin, __aend, __bbegin, ColIter_div_iter);
// }

// /**================================================================================================
//  *!                                        Row Iterators
//  *================================================================================================**/
// RowIter *RowIter_new(MATRIX_TYPE *__ptr, size_t __ptr_diff) {

//     RowIter *c = (RowIter *) malloc(sizeof(RowIter));

//     if (c) {
//         c->ptr = __ptr;
//         c->ptr_diff = __ptr_diff;
//     }
//     return c;
// }

// RowIter *RowIter_clone(const RowIter *__c) {
//     return RowIter_new(__c->ptr, __c->ptr_diff);
// }

// //! This function should actually never be called
// void RowIter_free(RowIter *__c) {

//     if (__c) {

//         if (__c->ptr) {
//             free(__c->ptr);
//         }
//         free(__c);
//     }
// }

// // Increment the row iter
// void RowIter_next(RowIter *__c) {
//     __c->ptr += __c->ptr_diff;
// }

// // Return true if the __lhs and __rhs point to the same element
// bool RowIter_cmp(const RowIter *__lhs, const RowIter *__rhs) {
//     return __lhs->ptr == __rhs->ptr;
// }

// // RowIter *matrowpos(const Matrix *__A, size_t __i, size_t __j) {
// //     return RowIter_new(matacc(__A, __i, __j), 1); // In row-major order, rows are next to each other
// // }

// // // get row iterator without checking bounds
// // RowIter *matrowbegin(const Matrix *__A, size_t __i) {
// //     return matrowpos(__A, __i, 0);
// // }

// // RowIter *matrowend(const Matrix *__A, size_t __i) {
// //     return matrowpos(__A, __i, __A->ncols);
// // }

// // // return a new Column Iterator that points to the final element in this column
// // RowIter *Matrix_row_end(const Matrix *__A, size_t __i) {

// //     if (__i < __A->ncols) {
// //         return matrowpos(__A, __i, __A->ncols);
// //     } else {
// //         perror("Matrix does not have that many columns");
// //         return NULL;
// //     }

// // }

// // RowIter *Matrix_row_begin(const Matrix *__A, size_t __i) {

// //     if (__i < __A->ncols) {
// //         return matrowpos(__A, __i, 0);
// //     } else {
// //         perror("Matrix does not have that many rows");
// //         return NULL;
// //     }
// // }

// MATRIX_TYPE RowIter_value(const RowIter *__c) {
//     return *(__c->ptr);
// }

// /**================================================================================================
//  *!                                        RowIter basic utility routines - SINGLE
//  *================================================================================================**/

// void RowIter_set(RowIter *__r, const MATRIX_TYPE __k) {
//     *(__r->ptr) = __k;
// }

// void RowIter_add_k(RowIter *__r, const MATRIX_TYPE __k) {
//     *(__r->ptr) += __k;
// }

// void RowIter_sub_k(RowIter *__r, const MATRIX_TYPE __k) {
//     *(__r->ptr) -= __k;
// }

// void RowIter_mult_k(RowIter *__r, const MATRIX_TYPE __k) {
//     *(__r->ptr) *= __k;
// }

// void RowIter_div_k(RowIter *__r, const MATRIX_TYPE __k) {
//     *(__r->ptr) /= __k;
// }

// void RowIter_set_ptr(RowIter *__r, const MATRIX_TYPE *__ptr) {
//     *(__r->ptr) = *__ptr;
// }

// void RowIter_add_ptr(RowIter *__r, const MATRIX_TYPE *__ptr) {
//     *(__r->ptr) += *__ptr;
// }

// void RowIter_sub_ptr(RowIter *__r, const MATRIX_TYPE *__ptr) {
//     *(__r->ptr) -= *__ptr;
// }

// void RowIter_mult_ptr(RowIter *__r, const MATRIX_TYPE *__ptr) {
//     *(__r->ptr) *= *__ptr;
// }

// void RowIter_div_ptr(RowIter *__r, const MATRIX_TYPE *__ptr) {
//     *(__r->ptr) /= *__ptr;
// }

// void RowIter_set_iter(RowIter *__a, const RowIter *__b) {
//     *(__a->ptr) = *(__b->ptr);
// }

// void RowIter_add_iter(RowIter *__a, const RowIter *__b) {
//     *(__a->ptr) += *(__b->ptr);
// }

// void RowIter_add_iter_scaled(RowIter *__a, const RowIter *__b, const MATRIX_TYPE __k) {
//     *(__a->ptr) += *(__b->ptr) * __k;
// }

// void RowIter_sub_iter(RowIter *__a, const RowIter *__b) {
//     *(__a->ptr) -= *(__b->ptr);
// }

// void RowIter_mult_iter(RowIter *__a, const RowIter *__b) {
//     *(__a->ptr) *= *(__b->ptr);
// }

// void RowIter_div_iter(RowIter *__a, const RowIter *__b) {
//     *(__a->ptr) /= *(__b->ptr);
// }

// // Get the maximum value in a row
// MATRIX_TYPE RowIter_max(RowIter *__a, const RowIter *__b) {

//     MATRIX_TYPE max = RowIter_value(__a);
//     RowIter_next(__a);

//     // This is the RowIter idiom to traverse a row
//     while (!RowIter_cmp(__a, __b)) {

//         if (RowIter_value(__a) > max)
//             max = RowIter_value(__a);

//         RowIter_next(__a);
//     }

//     return max;

// }

// // Get the maximum value in a row
// MATRIX_TYPE RowIter_min(RowIter *__a, const RowIter *__b) {

//     MATRIX_TYPE min = RowIter_value(__a);
//     RowIter_next(__a);

//     // This is the RowIter idiom to traverse a row
//     while (!RowIter_cmp(__a, __b)) {

//         if (RowIter_value(__a) < min)
//             min = RowIter_value(__a);

//         RowIter_next(__a);
//     }

//     return min;

// }



// /**================================================================================================
//  *!                                        RowIter basic utility routines - ROW
//  *================================================================================================**/

// // Set the elements of a row when given a row iterator and a value k
// void RowIter_row_set_k(const RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {

//     RowIter *rbegin = RowIter_clone(__rbegin);

//     while (! RowIter_cmp(rbegin, __rend)) {
//         RowIter_set(rbegin, __k);
//         RowIter_next(rbegin);
//     }

//     free(rbegin);
// }

// void RowIter_row_add_k(const RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {

//     RowIter *rbegin = RowIter_clone(__rbegin);

//     while (! RowIter_cmp(rbegin, __rend)) {
//         RowIter_add_k(rbegin, __k);
//         RowIter_next(rbegin);
//     }

//     free(rbegin);
// }

// void RowIter_row_sub_k(const RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {

//     RowIter *rbegin = RowIter_clone(__rbegin);

//     while (! RowIter_cmp(rbegin, __rend)) {
//         RowIter_sub_k(rbegin, __k);
//         RowIter_next(rbegin);
//     }

//     free(rbegin);
// }

// void RowIter_row_mult_k(const RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {

//     RowIter *rbegin = RowIter_clone(__rbegin);

//     while (! RowIter_cmp(rbegin, __rend)) {
//         RowIter_mult_k(rbegin, __k);
//         RowIter_next(rbegin);
//     }

//     free(rbegin);
// }

// void RowIter_row_div_k(const RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {

//     RowIter *rbegin = RowIter_clone(__rbegin);

//     while (! RowIter_cmp(rbegin, __rend)) {
//         RowIter_div_k(rbegin, __k);
//         RowIter_next(rbegin);
//     }

//     free(rbegin);
// }

// // Add to row __a the elements of row __b
// void RowIter_row_add_row(const RowIter *__abegin, const RowIter *__aend, const RowIter *__bbegin) {

//     RowIter *abegin = RowIter_clone(__abegin);
//     RowIter *bbegin = RowIter_clone(__bbegin);

//     while (! RowIter_cmp(abegin, __aend)) {
//         RowIter_add_iter(abegin, bbegin);
//         RowIter_next(abegin);
//         RowIter_next(bbegin);
//     }

//     free(abegin);
//     free(bbegin);
// }


// /**================================================================================================
//  *!                                        Experimental APPLY functions
//  *================================================================================================**/

// // Appy functions are a way to iterate a ColIter until we reach the "end" point


// void RowIter_apply(const RowIter *__rbegin, const RowIter *__rend, RowIterFn __fn) {

//     RowIter *rbegin = RowIter_clone(__rbegin);

//     while (! RowIter_cmp(rbegin, __rend)) {
//         __fn(rbegin);
//         RowIter_next(rbegin);
//     }

//     free(rbegin);
// }

// void RowIter_apply_k(const RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k, RowIterFn_k __fn_k) {

//     RowIter *rbegin = RowIter_clone(__rbegin);

//     while (! RowIter_cmp(rbegin, __rend)) {
//         __fn_k(rbegin, __k);
//         RowIter_next(rbegin);
//     }

//     free(rbegin);
// }

// void RowIter_apply_ptr(const RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr, RowIterFn_ptr __fn_ptr) {

//     RowIter *rbegin = RowIter_clone(__rbegin);

//     while (! RowIter_cmp(rbegin, __rend)) {
//         __fn_ptr(rbegin, __ptr);
//         RowIter_next(rbegin);
//     }

//     free(rbegin);
// }

// void RowIter_apply_iter(const RowIter *__abegin, const RowIter *__aend, const RowIter *__bbegin, RowIterFn_iter __fn_iter) {

//     RowIter *abegin = RowIter_clone(__abegin);
//     RowIter *bbegin = RowIter_clone(__bbegin);

//     while (! RowIter_cmp(abegin, __aend)) {
//         __fn_iter(abegin, bbegin);
//         RowIter_next(abegin);
//         RowIter_next(bbegin);
//     }

//     free(abegin);
//     free(bbegin);
// }

// void RowIter_apply_iter_scaled(const RowIter *__abegin, const RowIter *__aend, const RowIter *__bbegin, const MATRIX_TYPE __k, RowIterFn_iter_k __fn_iter_k) {

//     RowIter *abegin = RowIter_clone(__abegin);
//     RowIter *bbegin = RowIter_clone(__bbegin);

//     while (! RowIter_cmp(abegin, __aend)) {
//         __fn_iter_k(abegin, bbegin, __k);
//         RowIter_next(abegin);
//         RowIter_next(bbegin);
//     }

//     free(abegin);
//     free(bbegin);

// }

// /**================================================================================================
//  *!                                        Row manipulations using apply functions
//  *================================================================================================**/

// /**======================
//  *!    Scalar operations
//  *========================**/
// void RowIter_apply_set_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {
//     RowIter_apply_k(__rbegin, __rend, __k, RowIter_set);
// }

// void RowIter_apply_add_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {
//     RowIter_apply_k(__rbegin, __rend, __k, RowIter_add_k);
// }

// void RowIter_apply_sub_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {
//     RowIter_apply_k(__rbegin, __rend, __k, RowIter_sub_k);
// }

// void RowIter_apply_mult_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {
//     RowIter_apply_k(__rbegin, __rend, __k, RowIter_mult_k);
// }

// void RowIter_apply_div_k(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE __k) {
//     RowIter_apply_k(__rbegin, __rend, __k, RowIter_div_k);
// }

// /**======================
//  *!    Pointer operations
//  *========================**/

// void RowIter_apply_set_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr) {
//     RowIter_apply_ptr(__rbegin, __rend, __ptr, RowIter_set_ptr);
// }

// void RowIter_apply_add_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr) {
//     RowIter_apply_ptr(__rbegin, __rend, __ptr, RowIter_add_ptr);
// }

// void RowIter_apply_sub_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr) {
//     RowIter_apply_ptr(__rbegin, __rend, __ptr, RowIter_sub_ptr);
// }

// void RowIter_apply_mult_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr) {
//     RowIter_apply_ptr(__rbegin, __rend, __ptr, RowIter_mult_ptr);
// }

// void RowIter_apply_div_ptr(RowIter *__rbegin, const RowIter *__rend, const MATRIX_TYPE *__ptr) {
//     RowIter_apply_ptr(__rbegin, __rend, __ptr, RowIter_div_ptr);
// }

// /**======================
//  *!    Iterator operations
//  *========================**/

// void RowIter_apply_set_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin) {
//     RowIter_apply_iter(__abegin, __aend, __bbegin, RowIter_set_iter);
// }

// void RowIter_apply_add_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin) {
//     RowIter_apply_iter(__abegin, __aend, __bbegin, RowIter_add_iter);
// }

// void RowIter_apply_sub_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin) {
//     RowIter_apply_iter(__abegin, __aend, __bbegin, RowIter_sub_iter);
// }

// void RowIter_apply_mult_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin) {
//     RowIter_apply_iter(__abegin, __aend, __bbegin, RowIter_mult_iter);
// }

// void RowIter_apply_div_iter(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin) {
//     RowIter_apply_iter(__abegin, __aend, __bbegin, RowIter_div_iter);
// }

// /**======================
//  *!    add iter scaled
//  *========================**/
// void RowIter_apply_add_iter_scaled(RowIter *__abegin, const RowIter *__aend, RowIter *__bbegin, const MATRIX_TYPE __k) {
//     RowIter_apply_iter_scaled(__abegin, __aend, __bbegin, __k, RowIter_add_iter_scaled);
// }

/**================================================================================================
 *!                                        RowCol and ColIter
 *================================================================================================**/

MATRIX_TYPE Iter_dot(const MatIter *__r, const MatIter *__rend, const MatIter *__c) {

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

// Here I want to be able to manipulate the functions defined above to create clean and simple Matrix api

// let's start simple and add rows together

// matrix elementary row operation (add two rows)
void matrowop_add(Matrix *__A, const size_t __r1, const size_t __r2, const size_t __col_offset) {

    const MatIter *r1begin = matrowpos(__A, __r1, __col_offset);
    const MatIter *r1end = matrowend(__A, __r1);
    const MatIter *r2begin = matrowpos(__A, __r2, __col_offset);

    MatIter_apply_add_iter(r1begin, r1end, r2begin);

    free(r1begin);
    free(r1end);
    free(r2begin);
}

// matrix elementary row operation (add two rows)
void matrowop_add_scaled(Matrix *__A, const size_t __r1, const size_t __r2, const MATRIX_TYPE __k, const size_t __col_offset) {

    const MatIter *r1begin = matrowpos(__A, __r1, __col_offset);
    const MatIter *r1end = matrowend(__A, __r1);
    const MatIter *r2begin = matrowpos(__A, __r2, __col_offset);

    MatIter_apply_add_iter_scaled(r1begin, r1end, r2begin, __k);

    free(r1begin);
    free(r1end);
    free(r2begin);
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
    return MatIter_min(matrowbegin(__A, __i), matrowend(__A, __i));
}

MATRIX_TYPE Matrix_row_max(const Matrix *__A, const size_t __i) {
    return MatIter_max(matrowbegin(__A, __i), matrowend(__A, __i));
}

MatIter *matcolpos(const Matrix *__A, size_t __i, size_t __j) {
    return MatIter_new(matacc(__A, __i, __j), __A->ncols);
}


// return a new Matumn Iterator that points to the final element in this column
MatIter *Matrix_col_end(const Matrix *__A, size_t __j) {

    if (__j < __A->ncols) {
        return matcolpos(__A, __A->nrows, __j);
    } else {
        perror("Matrix does not have that many columns");
        return NULL;
    }

}

MatIter *Matrix_col_begin(const Matrix *__A, size_t __j) {

    if (__j < __A->ncols) {
        return matcolpos(__A, 0, __j);
    } else {
        perror("Matrix does not have that many columns");
        return NULL;
    }
}

MatIter *matrowpos(const Matrix *__A, size_t __i, size_t __j) {
    return MatIter_new(matacc(__A, __i, __j), 1); // In row-major order, rows are next to each other
}

// get row iterator without checking bounds
MatIter *matrowbegin(const Matrix *__A, size_t __i) {
    return matrowpos(__A, __i, 0);
}

MatIter *matrowend(const Matrix *__A, size_t __i) {
    return matrowpos(__A, __i, __A->ncols);
}

// return a new Column Iterator that points to the final element in this column
MatIter *Matrix_row_end(const Matrix *__A, size_t __i) {

    if (__i < __A->ncols) {
        return matrowpos(__A, __i, __A->ncols);
    } else {
        perror("Matrix does not have that many columns");
        return NULL;
    }

}

MatIter *Matrix_row_begin(const Matrix *__A, size_t __i) {

    if (__i < __A->ncols) {
        return matrowpos(__A, __i, 0);
    } else {
        perror("Matrix does not have that many rows");
        return NULL;
    }
}

/**=======================================================================================================================
 *!                                                   MIter that has more general capabilities
 *=======================================================================================================================**/
MatIter *MatIter_new(MATRIX_TYPE *__ptr, size_t __ptr_diff) {

    MatIter *c = (MatIter *) malloc(sizeof(MatIter));

    if (c) {
        c->ptr = __ptr;
        c->ptr_diff = __ptr_diff;
    }
    return c;
}

MatIter *MatIter_clone(const MatIter *__c) {
    return MatIter_new(__c->ptr, __c->ptr_diff);
}

//! This function should actually never be called
void MatIter_free(MatIter *__c) {

    if (__c) {

        if (__c->ptr) {
            free(__c->ptr);
        }
        free(__c);
    }
}

// Increment the row iter
void MatIter_next(MatIter *__c) {
    __c->ptr += __c->ptr_diff;
}

// Return true if the __lhs and __rhs point to the same element
bool MatIter_cmp(const MatIter *__lhs, const MatIter *__rhs) {
    return __lhs->ptr == __rhs->ptr;
}

MATRIX_TYPE MatIter_value(const MatIter *__c) {
    return *(__c->ptr);
}

// Return the number of iteration between begin and end
size_t MatIter_length(const MatIter *begin, const MatIter *end) {
    size_t diff = end->ptr - begin->ptr;
    return diff / begin->ptr_diff;
}

/**================================================================================================
 *!                                        MatIter basic utility routines - SINGLE
 *================================================================================================**/

void MatIter_set(MatIter *__r, const MATRIX_TYPE __k) {
    *(__r->ptr) = __k;
}

void MatIter_add_k(MatIter *__r, const MATRIX_TYPE __k) {
    *(__r->ptr) += __k;
}

void MatIter_sub_k(MatIter *__r, const MATRIX_TYPE __k) {
    *(__r->ptr) -= __k;
}

void MatIter_mult_k(MatIter *__r, const MATRIX_TYPE __k) {
    *(__r->ptr) *= __k;
}

void MatIter_div_k(MatIter *__r, const MATRIX_TYPE __k) {
    *(__r->ptr) /= __k;
}

void MatIter_set_ptr(MatIter *__r, const MATRIX_TYPE *__ptr) {
    *(__r->ptr) = *__ptr;
}

void MatIter_add_ptr(MatIter *__r, const MATRIX_TYPE *__ptr) {
    *(__r->ptr) += *__ptr;
}

void MatIter_sub_ptr(MatIter *__r, const MATRIX_TYPE *__ptr) {
    *(__r->ptr) -= *__ptr;
}

void MatIter_mult_ptr(MatIter *__r, const MATRIX_TYPE *__ptr) {
    *(__r->ptr) *= *__ptr;
}

void MatIter_div_ptr(MatIter *__r, const MATRIX_TYPE *__ptr) {
    *(__r->ptr) /= *__ptr;
}

void MatIter_set_iter(MatIter *__a, const MatIter *__b) {
    *(__a->ptr) = *(__b->ptr);
}

void MatIter_add_iter(MatIter *__a, const MatIter *__b) {
    *(__a->ptr) += *(__b->ptr);
}

void MatIter_add_iter_scaled(MatIter *__a, const MatIter *__b, const MATRIX_TYPE __k) {
    *(__a->ptr) += *(__b->ptr) * __k;
}

void MatIter_sub_iter(MatIter *__a, const MatIter *__b) {
    *(__a->ptr) -= *(__b->ptr);
}

void MatIter_mult_iter(MatIter *__a, const MatIter *__b) {
    *(__a->ptr) *= *(__b->ptr);
}

void MatIter_div_iter(MatIter *__a, const MatIter *__b) {
    *(__a->ptr) /= *(__b->ptr);
}

// Get the maximum value in a row
MATRIX_TYPE MatIter_max(MatIter *__a, const MatIter *__b) {

    MATRIX_TYPE max = MatIter_value(__a);
    MatIter_next(__a);

    // This is the MatIter idiom to traverse a row
    while (!MatIter_cmp(__a, __b)) {

        if (MatIter_value(__a) > max)
            max = MatIter_value(__a);

        MatIter_next(__a);
    }

    return max;

}

// Get the maximum value in a row
MATRIX_TYPE MatIter_min(MatIter *__a, const MatIter *__b) {

    MATRIX_TYPE min = MatIter_value(__a);
    MatIter_next(__a);

    // This is the MatIter idiom to traverse a row
    while (!MatIter_cmp(__a, __b)) {

        if (MatIter_value(__a) < min)
            min = MatIter_value(__a);

        MatIter_next(__a);
    }

    return min;

}



/**================================================================================================
 *!                                        MatIter basic utility routines - ROW
 *================================================================================================**/

// Set the elements of a row when given a row iterator and a value k
void MatIter_row_set_k(const MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k) {

    MatIter *rbegin = MatIter_clone(__rbegin);

    while (! MatIter_cmp(rbegin, __rend)) {
        MatIter_set(rbegin, __k);
        MatIter_next(rbegin);
    }

    free(rbegin);
}

void MatIter_row_add_k(const MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k) {

    MatIter *rbegin = MatIter_clone(__rbegin);

    while (! MatIter_cmp(rbegin, __rend)) {
        MatIter_add_k(rbegin, __k);
        MatIter_next(rbegin);
    }

    free(rbegin);
}

void MatIter_row_sub_k(const MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k) {

    MatIter *rbegin = MatIter_clone(__rbegin);

    while (! MatIter_cmp(rbegin, __rend)) {
        MatIter_sub_k(rbegin, __k);
        MatIter_next(rbegin);
    }

    free(rbegin);
}

void MatIter_row_mult_k(const MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k) {

    MatIter *rbegin = MatIter_clone(__rbegin);

    while (! MatIter_cmp(rbegin, __rend)) {
        MatIter_mult_k(rbegin, __k);
        MatIter_next(rbegin);
    }

    free(rbegin);
}

void MatIter_row_div_k(const MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k) {

    MatIter *rbegin = MatIter_clone(__rbegin);

    while (! MatIter_cmp(rbegin, __rend)) {
        MatIter_div_k(rbegin, __k);
        MatIter_next(rbegin);
    }

    free(rbegin);
}

// Add to row __a the elements of row __b
void MatIter_row_add_row(const MatIter *__abegin, const MatIter *__aend, const MatIter *__bbegin) {

    MatIter *abegin = MatIter_clone(__abegin);
    MatIter *bbegin = MatIter_clone(__bbegin);

    while (! MatIter_cmp(abegin, __aend)) {
        MatIter_add_iter(abegin, bbegin);
        MatIter_next(abegin);
        MatIter_next(bbegin);
    }

    free(abegin);
    free(bbegin);
}


/**================================================================================================
 *!                                        Experimental APPLY functions
 *================================================================================================**/

// Appy functions are a way to iterate a ColIter until we reach the "end" point


void MatIter_apply(const MatIter *__rbegin, const MatIter *__rend, MatIterFn __fn) {

    MatIter *rbegin = MatIter_clone(__rbegin);

    while (! MatIter_cmp(rbegin, __rend)) {
        __fn(rbegin);
        MatIter_next(rbegin);
    }

    free(rbegin);
}

void MatIter_apply_k(const MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k, MatIterFn_k __fn_k) {

    MatIter *rbegin = MatIter_clone(__rbegin);

    while (! MatIter_cmp(rbegin, __rend)) {
        __fn_k(rbegin, __k);
        MatIter_next(rbegin);
    }

    free(rbegin);
}

void MatIter_apply_ptr(const MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE *__ptr, MatIterFn_ptr __fn_ptr) {

    MatIter *rbegin = MatIter_clone(__rbegin);

    while (! MatIter_cmp(rbegin, __rend)) {
        __fn_ptr(rbegin, __ptr);
        MatIter_next(rbegin);
    }

    free(rbegin);
}

void MatIter_apply_iter(const MatIter *__abegin, const MatIter *__aend, const MatIter *__bbegin, MatIterFn_iter __fn_iter) {

    MatIter *abegin = MatIter_clone(__abegin);
    MatIter *bbegin = MatIter_clone(__bbegin);

    while (! MatIter_cmp(abegin, __aend)) {
        __fn_iter(abegin, bbegin);
        MatIter_next(abegin);
        MatIter_next(bbegin);
    }

    free(abegin);
    free(bbegin);
}

void MatIter_apply_iter_scaled(const MatIter *__abegin, const MatIter *__aend, const MatIter *__bbegin, const MATRIX_TYPE __k, MatIterFn_iter_k __fn_iter_k) {

    MatIter *abegin = MatIter_clone(__abegin);
    MatIter *bbegin = MatIter_clone(__bbegin);

    while (! MatIter_cmp(abegin, __aend)) {
        __fn_iter_k(abegin, bbegin, __k);
        MatIter_next(abegin);
        MatIter_next(bbegin);
    }

    free(abegin);
    free(bbegin);

}

/**================================================================================================
 *!                                        Mat manipulations using apply functions
 *================================================================================================**/

/**======================
 *!    Scalar operations
 *========================**/
void MatIter_apply_set_k(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k) {
    MatIter_apply_k(__rbegin, __rend, __k, MatIter_set);
}

void MatIter_apply_add_k(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k) {
    MatIter_apply_k(__rbegin, __rend, __k, MatIter_add_k);
}

void MatIter_apply_sub_k(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k) {
    MatIter_apply_k(__rbegin, __rend, __k, MatIter_sub_k);
}

void MatIter_apply_mult_k(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k) {
    MatIter_apply_k(__rbegin, __rend, __k, MatIter_mult_k);
}

void MatIter_apply_div_k(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE __k) {
    MatIter_apply_k(__rbegin, __rend, __k, MatIter_div_k);
}

/**======================
 *!    Pointer operations
 *========================**/

void MatIter_apply_set_ptr(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE *__ptr) {
    MatIter_apply_ptr(__rbegin, __rend, __ptr, MatIter_set_ptr);
}

void MatIter_apply_add_ptr(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE *__ptr) {
    MatIter_apply_ptr(__rbegin, __rend, __ptr, MatIter_add_ptr);
}

void MatIter_apply_sub_ptr(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE *__ptr) {
    MatIter_apply_ptr(__rbegin, __rend, __ptr, MatIter_sub_ptr);
}

void MatIter_apply_mult_ptr(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE *__ptr) {
    MatIter_apply_ptr(__rbegin, __rend, __ptr, MatIter_mult_ptr);
}

void MatIter_apply_div_ptr(MatIter *__rbegin, const MatIter *__rend, const MATRIX_TYPE *__ptr) {
    MatIter_apply_ptr(__rbegin, __rend, __ptr, MatIter_div_ptr);
}

/**======================
 *!    Iterator operations
 *========================**/

void MatIter_apply_set_iter(MatIter *__abegin, const MatIter *__aend, MatIter *__bbegin) {
    MatIter_apply_iter(__abegin, __aend, __bbegin, MatIter_set_iter);
}

void MatIter_apply_add_iter(MatIter *__abegin, const MatIter *__aend, MatIter *__bbegin) {
    MatIter_apply_iter(__abegin, __aend, __bbegin, MatIter_add_iter);
}

void MatIter_apply_sub_iter(MatIter *__abegin, const MatIter *__aend, MatIter *__bbegin) {
    MatIter_apply_iter(__abegin, __aend, __bbegin, MatIter_sub_iter);
}

void MatIter_apply_mult_iter(MatIter *__abegin, const MatIter *__aend, MatIter *__bbegin) {
    MatIter_apply_iter(__abegin, __aend, __bbegin, MatIter_mult_iter);
}

void MatIter_apply_div_iter(MatIter *__abegin, const MatIter *__aend, MatIter *__bbegin) {
    MatIter_apply_iter(__abegin, __aend, __bbegin, MatIter_div_iter);
}

/**======================
 *!    add iter scaled
 *========================**/
void MatIter_apply_add_iter_scaled(MatIter *__abegin, const MatIter *__aend, MatIter *__bbegin, const MATRIX_TYPE __k) {
    MatIter_apply_iter_scaled(__abegin, __aend, __bbegin, __k, MatIter_add_iter_scaled);
}


