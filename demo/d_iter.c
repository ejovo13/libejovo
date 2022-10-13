// showcase some iter functions

#include "ejovo.h"

int main() {

    ejovo_seed();

    Matrix_d *m = Matrix_rnorm_d(10, 5, 0, 1);
    Matrix_i *mi = Matrix_rnorm_i(10, 5, 0, 1);

    Matrix_print_fixed_d(m);


    // Let's try and extract a new matrix whose columns are [1, 1, 1]

    Vector_d*ind = vector_d(3, 1.0, 0.0, 4.0);

    Matrix_d *new = Matrix_extract_cols_d(m, ind);

    Matrix_print_fixed_d(Matrix_anon_d(new));
    // Matrix_print_fixed_d(new);

    // Let's now extract a few rows
    new = Matrix_extract_rows_d(m, matanon_d(3, 0.0, 5.0, 2.0));

    // Matrix_print_fixed_d(new);

    Matrix_anon_d(new);
    Matrix_anon_free_d();
    Matrix_reset_d(&ind);
    Matrix_reset_d(&m);
    Matrix_free_i(mi);

    return 0;
}
