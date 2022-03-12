// showcase some iter functions

#include "ejovo_matrix.h"

int main() {

    ejovo_seed();

    Matrix *m = Matrix_rnorm(10, 5, 0, 1);

    Matrix_print_fixed(m);


    // Let's try and extract a new matrix whose columns are [1, 1, 1]

    Vector *ind = vector(3, 1.0, 0.0, 4.0);

    Matrix *new = Matrix_extract_cols(m, ind);

    Matrix_print_fixed(Matrix_anon(new));
    // Matrix_print_fixed(new);

    // Let's now extract a few rows
    new = Matrix_extract_rows(m, anon(3, 0.0, 5.0, 2.0));

    // Matrix_print_fixed(new);

    Matrix_anon(new);
    Matrix_anon_free();
    Matrix_reset(&ind);
    Matrix_reset(&m);


    return 0;
}
