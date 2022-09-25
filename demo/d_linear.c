#include "ejovo_matrix_generic.h"

int main() {

    ejovo_seed();

    // Matrix_d *m = Matrix_random_d(4, 4, 1, 10);

    Matrix_d *m = Matrix_rnorm_d(10, 10, 0, 1);
    // Vector_d*v = vector_d(4, 3.0, 5.0, 3.0, 4.0);

    // Matrix_print_d(v);

    // printf("max: %lf\n", max_d(v));
    // printf("index: %d\n", Matrix_col_max_index_d(v, 0));

    Matrix_print_fixed_d(m);

    Matrix_d *a = gausselim_d(m, NULL);

    Matrix_print_fixed_d(a);

    // Matrix_print_all_digits_d(a);

    // Matrix_print_iter_d(a);

    return 0;
}