// Routines that are used in Computational Science and Engineering

// #include "ejovo_matrix_generic.h"
#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Finite Differences Matrices
 *================================================================================================**/

// Tridiagonal K matrix
TYPED(Matrix) *TYPED(Matrix_K)(size_t __n) {
// assert that __n > 1
    assert(__n > 1);

    TYPED(Matrix) *mat = TYPED(Matrix_new)(__n, __n);
    // set first row
    TYPED(matset)(mat, 0, 0, 2);
    TYPED(matset)(mat, 0, 1, -1);

    // set middle rows
    for (size_t i = 1; i < __n - 1; i++) {

        TYPED(matset)(mat, i, i - 1, -1);
        TYPED(matset)(mat, i, i, 2);
        TYPED(matset)(mat, i, i + 1, -1);

    }

    // set final row
    TYPED(matset)(mat, __n - 1, __n - 2, -1);
    TYPED(matset)(mat, __n - 1, __n - 1, 2);

    return mat;
}

// Circular matrix
TYPED(Matrix) *TYPED(Matrix_C)(size_t __n) {

    assert(__n > 1);

    TYPED(Matrix) *mat = TYPED(Matrix_K)(__n);
    TYPED(matset)(mat, 0, __n - 1, -1); // set the top right value
    TYPED(matset)(mat, __n - 1, 0, -1); // set the bottom left value

    return mat;

}

TYPED(Matrix) *TYPED(Matrix_T)(size_t __n) {

    assert(__n > 1);

    TYPED(Matrix) *mat = TYPED(Matrix_K)(__n);
    TYPED(matset)(mat, 0, 0, 1);

    return mat;

}

TYPED(Matrix) *TYPED(Matrix_B)(size_t __n) {

    assert(__n > 1);

    TYPED(Matrix) *mat = TYPED(Matrix_T)(__n);
    TYPED(matset)(mat, __n - 1, __n - 1, 1);

    return mat;

}