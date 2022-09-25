#include "ejovo_matrix_generic.h"
#include <assert.h>
#include <stdbool.h>

#define N 500
#define MAX_ITER 1E1

int main() {

    ejovo_seed();

    // I want to test the speed of two different compares. To do this I can use gprof
    Matrix_d *base = Matrix_rand_d(N, N);
    Matrix_d *clone = Matrix_clone_d(base);

    bool result = false;

    // I now want to compare this MAX_ITER times
    for (size_t i = 0; i < MAX_ITER; i++) {

        result = matcmp_d(base, clone);
        result = matcmp_bytes_d(base, clone);

    }

    printf("Result: %d\n", result);


    return 0;
}