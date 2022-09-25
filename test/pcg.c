#include <stdio.h>
#include "ejovo.h"

// #include "pcg_variants.h"

int main() {


    // First thing I want to do is learn how to get a single 64 bit integer.

    ejovo_seed();

    DEFAULT_RNG = unif_xoroshiro;

    Matrix_d *x = runif_d(10, 1, 5);

    DEFAULT_RNG = unif_xoroshiro;

    Matrix_d *y = runif_d(10, 1, 5);

    Matrix_print_d(x);
    Matrix_print_d(y);

    printf("Mean: %lf\n", mean_d(x));

    Matrix_free_d(x);
    Matrix_free_d(y);



    return 0;
}