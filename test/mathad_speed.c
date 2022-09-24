#include "ejovo_rand.h"
#include "ejovo_matrix_generic.h"
#include <stdio.h>

#define MAX_ITER 1E0
#define N 500

int main() {

    ejovo_seed();

    MATRIX_T *m = MATRIX_FN(random)(N, N, 1, 5);
    MATRIX_T *m2 = MATRIX_FN(value)(N, N, 1.05);

    for (size_t i = 0; i < MAX_ITER; i++) {
        // MAT_FN(had)(m, m2);
        // MAT_FN(had_check)(m, m2);
        m = MATRIX_FN(hadamard)(m, m2);
        // MATRIX_FN(hadamard_at)(m, m2);
    }

    printf("Finished hadamard trials\n");

    // MATRIX_FN(set)(m, 1, 1, 0);
    // printf("M[0][0] = %lf\n", MATRIX_FN(at)(m, 1, 1));

    printf("Getting submatrix:\n");
    MATRIX_T *sub = submat_d(m, 0, 10, 0, 25);
    MATRIX_FN(print)(sub);

    Matrix_d_print(sub);




    return 0;
}