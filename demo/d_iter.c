// showcase some iter functions

#include "ejovo.h"

int main() {

    ejovo_seed();

    MATRIX_T *m = MATRIX_FN(rnorm)(10, 5, 0, 1);

    MATRIX_FN(print_fixed)(m);


    // Let's try and extract a new matrix whose columns are [1, 1, 1]

    Vector *ind = vector(3, 1.0, 0.0, 4.0);

    MATRIX_T *new = MATRIX_FN(extract_cols)(m, ind);

    MATRIX_FN(print_fixed)(MATRIX_FN(anon)(new));
    // MATRIX_FN(print_fixed)(new);

    // Let's now extract a few rows
    new = MATRIX_FN(extract_rows)(m, anon(3, 0.0, 5.0, 2.0));

    // MATRIX_FN(print_fixed)(new);

    MATRIX_FN(anon)(new);
    MATRIX_FN(anon_free)();
    MATRIX_FN(reset)(&ind);
    MATRIX_FN(reset)(&m);


    return 0;
}
