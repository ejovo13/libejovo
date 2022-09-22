#include <stdio.h>
#include "ejovo.h"

// #include "pcg_variants.h"

int main() {


    // First thing I want to do is learn how to get a single 64 bit integer.

    ejovo_seed();

    DEFAULT_RNG = unif_xoroshiro;

    Matrix *x = runif(10, 1, 5);

    DEFAULT_RNG = unif_xoroshiro;

    Matrix *y = runif(10, 1, 5);

    Matrix_print(x);
    Matrix_print(y);

    printf("Mean: %lf\n", mean(x));

    Matrix_free(x);
    Matrix_free(y);



    return 0;
}