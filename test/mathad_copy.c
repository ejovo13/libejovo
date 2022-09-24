// need to make sure that the various ways to calculate the Hadamard product lead to the same value
#include "ejovo_matrix_generic.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define N 5

int main() {

    ejovo_seed();

    MATRIX_T *base = MATRIX_FN(random)(N, N, 0, 10);
    MATRIX_T *m = MATRIX_FN(value)(N, N, 1.1345);

    MATRIX_FN(print)(base);
    MATRIX_FN(print)(m);

    MATRIX_T *h1 = MAT_FN(clone)(base);
    MAT_FN(had)(h1, m);

    MATRIX_T *h2 = MAT_FN(clone)(base);
    MAT_FN(had_check)(h2, m);

    MATRIX_T *h3 = MATRIX_FN(hadamard)(base, m);

    assert(MAT_FN(cmp_bytes)(h1, h2));
    assert(MAT_FN(cmp_bytes)(h2, h3));

    MATRIX_FN(print)(h1);
    MATRIX_FN(print)(h2);
    MATRIX_FN(print)(h3);


    return 0;
}