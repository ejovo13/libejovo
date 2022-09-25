// need to make sure that the various ways to calculate the Hadamard product lead to the same value
#include "ejovo_matrix_generic.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define N 5

int main() {

    ejovo_seed();

    Matrix_d *base = Matrix_random_d(N, N, 0, 10);
    Matrix_d *m = Matrix_value_d(N, N, 1.1345);

    Matrix_print_d(base);
    Matrix_print_d(m);

    Matrix_d *h1 = matclone_d(base);
    mathad_d(h1, m);

    Matrix_d *h2 = matclone_d(base);
    mathad_check_d(h2, m);

    Matrix_d *h3 = Matrix_hadamard_d(base, m);

    assert(matcmp_bytes_d(h1, h2));
    assert(matcmp_bytes_d(h2, h3));

    Matrix_print_d(h1);
    Matrix_print_d(h2);
    Matrix_print_d(h3);


    return 0;
}