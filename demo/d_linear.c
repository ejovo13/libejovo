#include "ejovo_matrix.h"

int main() {

    ejovo_seed();

    // Matrix *m = Matrix_random(4, 4, 1, 10);

    Matrix *m = Matrix_rnorm(10, 10, 0, 1);
    // Vector *v = vector(4, 3.0, 5.0, 3.0, 4.0);

    // Matrix_print(v);

    // printf("max: %lf\n", max(v));
    // printf("index: %d\n", Matrix_col_max_index(v, 0));

    Matrix_print_fixed(m);

    Matrix *a = gausselim(m, NULL);

    Matrix_print_fixed(a);

    // Matrix_print_all_digits(a);

    // Matrix_print_iter(a);

    return 0;
}