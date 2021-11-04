#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>

#define N 7500
#define MAX_ITER 1E1

int main() {

    ejovo_seed();

    // I want to test the speed of two different compares. To do this I can use gprof
    Matrix *base = Matrix_rand(N, N);
    Matrix *clone = Matrix_clone(base);

    bool result = false;

    // I now want to compare this MAX_ITER times
    for (size_t i = 0; i < MAX_ITER; i++) {

        result = matcmp(base, clone);
        result = matcmp_bytes(base, clone);

    }

    printf("Result: %d\n", result);


    return 0;
}