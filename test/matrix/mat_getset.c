#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>

void t_getset();


int main() {

    ejovo_seed();
    MATRIX_T *m = MATRIX_FN(rand)(4, 4);
    // MATRIX_T *m = NULL;
    // m = MATRIX_FN(new)(10, 10);
    MATRIX_FN(print)(m);

    // MATRIX_FN(print)(m);

    // MATRIX_FN(mult_row_k)(m, 0, 3);

    // MATRIX_FN(print)(m);

    // MATRIX_FN(mult_col_k)(m, 0, 3);

    // MATRIX_FN(print)(m);

    MATRIX_FN(free)(m);
    m = NULL;

    t_getset();

    return 0;
}

void t_getset() {

    printf("tgetset\n");

    MATRIX_T *m = MATRIX_FN(new)(5, 5);
    MAT_FN(set)(m, 0, 0, 999);
    MATRIX_FN(print)(m);
    MATRIX_FN(free)(m);


}