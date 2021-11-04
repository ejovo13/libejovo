// need to make sure that the various ways to calculate the Hadamard product lead to the same value
#include "ejovo_matrix.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define N 5

int main() {

    ejovo_seed();

    Matrix *base = Matrix_random(N, N, 0, 10);
    Matrix *m = Matrix_value(N, N, 1.1345);

    Matrix_print(base);
    Matrix_print(m);

    Matrix *h1 = matclone(base);
    mathad(h1, m);

    Matrix *h2 = matclone(base);
    mathad_check(h2, m);

    Matrix *h3 = Matrix_hadamard(base, m);

    assert(matcmp_bytes(h1, h2));
    assert(matcmp_bytes(h2, h3));

    Matrix_print(h1);
    Matrix_print(h2);
    Matrix_print(h3);


    return 0;
}