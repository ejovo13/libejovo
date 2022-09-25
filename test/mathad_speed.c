#include "ejovo_rand.h"
#include "ejovo_matrix_generic.h"
#include <stdio.h>

#define MAX_ITER 1E0
#define N 500

int main() {

    ejovo_seed();

    Matrix_d *m = Matrix_random_d(N, N, 1, 5);
    Matrix_d *m2 = Matrix_value_d(N, N, 1.05);

    for (size_t i = 0; i < MAX_ITER; i++) {
        // mathad_d(m, m2);
        // mathad_check_d(m, m2);
        m = Matrix_hadamard_d(m, m2);
        // Matrix_hadamard_at_d(m, m2);
    }

    printf("Finished hadamard trials\n");

    // Matrix_set_d(m, 1, 1, 0);
    // printf("M[0][0] = %lf\n", Matrix_at_d(m, 1, 1));

    printf("Getting submatrix:\n");
    Matrix_d *sub = submat_d(m, 0, 10, 0, 25);
    Matrix_print_d(sub);

    Matrix_print_d(m);



    return 0;
}