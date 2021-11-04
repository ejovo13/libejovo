#include "ejovo_rand.h"
#include "ejovo_matrix.h"
#include <stdio.h>

#define MAX_ITER 1E0
#define N 500

int main() {

    ejovo_seed();

    Matrix *m = Matrix_random(N, N, 1, 5);
    Matrix *m2 = Matrix_value(N, N, 1.05);

    for (size_t i = 0; i < MAX_ITER; i++) {
        // mathad(m, m2);
        // mathad_check(m, m2);
        m = Matrix_hadamard(m, m2);
        // Matrix_hadamard_at(m, m2);
    }

    printf("Finished hadamard trials\n");

    // Matrix_set(m, 1, 1, 0);
    // printf("M[0][0] = %lf\n", Matrix_at(m, 1, 1));

    printf("Getting submatrix:\n");
    Matrix *sub = submat(m, 0, 10, 0, 25);
    matprint(sub);




    return 0;
}