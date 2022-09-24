// Routines that are used in Computational Science and Engineering

#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Finite Differences Matrices
 *================================================================================================**/

// Tridiagonal K matrix
MATRIX_T *MATRIX_FN(K)(size_t __n) {
// assert that __n > 1
    assert(__n > 1);

    MATRIX_T *mat = MATRIX_FN(new)(__n, __n);
    // set first row
    MAT_FN(set)(mat, 0, 0, 2);
    MAT_FN(set)(mat, 0, 1, -1);

    // set middle rows
    for (size_t i = 1; i < __n - 1; i++) {

        MAT_FN(set)(mat, i, i - 1, -1);
        MAT_FN(set)(mat, i, i, 2);
        MAT_FN(set)(mat, i, i + 1, -1);

    }

    // set final row
    MAT_FN(set)(mat, __n - 1, __n - 2, -1);
    MAT_FN(set)(mat, __n - 1, __n - 1, 2);

    return mat;
}

// Circular matrix
MATRIX_T *MATRIX_FN(C)(size_t __n) {

    assert(__n > 1);

    MATRIX_T *mat = MATRIX_FN(K)(__n);
    MAT_FN(set)(mat, 0, __n - 1, -1); // set the top right value
    MAT_FN(set)(mat, __n - 1, 0, -1); // set the bottom left value

    return mat;

}

MATRIX_T *MATRIX_FN(T)(size_t __n) {

    assert(__n > 1);

    MATRIX_T *mat = MATRIX_FN(K)(__n);
    MAT_FN(set)(mat, 0, 0, 1);

    return mat;

}

MATRIX_T *MATRIX_FN(B)(size_t __n) {

    assert(__n > 1);

    MATRIX_T *mat = MATRIX_FN(T)(__n);
    MAT_FN(set)(mat, __n - 1, __n - 1, 1);

    return mat;

}