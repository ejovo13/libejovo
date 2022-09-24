#include <stdio.h>
#include "ejovo.h"

// #include "pcg_variants.h"

int main() {


    // First thing I want to do is learn how to get a single 64 bit integer.

    ejovo_seed();

    DEFAULT_RNG = unif_xoroshiro;

    MATRIX_T *x = runif(10, 1, 5);

    DEFAULT_RNG = unif_xoroshiro;

    MATRIX_T *y = runif(10, 1, 5);

    MATRIX_FN(print)(x);
    MATRIX_FN(print)(y);

    printf("Mean: %lf\n", mean(x));

    MATRIX_FN(free)(x);
    MATRIX_FN(free)(y);



    return 0;
}