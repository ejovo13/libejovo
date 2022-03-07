// Routines that are used in Computational Science and Engineering

#include "ejovo_matrix.h"

/**================================================================================================
 *!                                        Finite Differences Matrices
 *================================================================================================**/

// Tridiagonal K matrix
Matrix *Matrix_K(size_t __n) {
// assert that __n > 1
    assert(__n > 1);

    Matrix *mat = Matrix_new(__n, __n);
    // set first row
    matset(mat, 0, 0, 2);
    matset(mat, 0, 1, -1);

    // set middle rows
    for (size_t i = 1; i < __n - 1; i++) {

        matset(mat, i, i - 1, -1);
        matset(mat, i, i, 2);
        matset(mat, i, i + 1, -1);

    }

    // set final row
    matset(mat, __n - 1, __n - 2, -1);
    matset(mat, __n - 1, __n - 1, 2);

    return mat;
}

// Circular matrix
Matrix *Matrix_C(size_t __n) {

    assert(__n > 1);

    Matrix *mat = Matrix_K(__n);
    matset(mat, 0, __n - 1, -1); // set the top right value
    matset(mat, __n - 1, 0, -1); // set the bottom left value

    return mat;

}

Matrix *Matrix_T(size_t __n) {

    assert(__n > 1);

    Matrix *mat = Matrix_K(__n);
    matset(mat, 0, 0, 1);

    return mat;

}

Matrix *Matrix_B(size_t __n) {

    assert(__n > 1);

    Matrix *mat = Matrix_T(__n);
    matset(mat, __n - 1, __n - 1, 1);

    return mat;

}