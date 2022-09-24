#include <stdio.h>
#include "ejovo.h"

// #include "pcg_variants.h"

int main() {


    // First thing I want to do is learn how to get a single 64 bit integer.

    ejovo_seed();

    DEFAULT_RNG = unif_xoroshiro;

    MATRIX_T *x = TYPED_FN(runif)(10, 1, 5);

    DEFAULT_RNG = unif_xoroshiro;

    MATRIX_T *y = TYPED_FN(runif)(10, 1, 5);

    MATRIX_FN(print)(x);
    MATRIX_FN(print)(y);

    printf("Mean: %lf\n", TYPED_FN(mean)(x));

    MATRIX_FN(free)(x);
    MATRIX_FN(free)(y);



    return 0;
}