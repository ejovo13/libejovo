#include "ejovo_matrix.h"

int main() {

    ejovo_seed();

    // MATRIX_T *m = MATRIX_FN(random)(4, 4, 1, 10);

    MATRIX_T *m = MATRIX_FN(rnorm)(10, 10, 0, 1);
    // Vector *v = vector(4, 3.0, 5.0, 3.0, 4.0);

    // MATRIX_FN(print)(v);

    // printf("max: %lf\n", max(v));
    // printf("index: %d\n", MATRIX_FN(col_max_index)(v, 0));

    MATRIX_FN(print_fixed)(m);

    MATRIX_T *a = gausselim(m, NULL);

    MATRIX_FN(print_fixed)(a);

    // MATRIX_FN(print_all_digits)(a);

    // MATRIX_FN(print_iter)(a);

    return 0;
}