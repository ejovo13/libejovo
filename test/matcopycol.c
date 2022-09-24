#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>


int main() {

    printf("Yes\n");

    ejovo_seed();

    MATRIX_T *col_vector = MATRIX_FN(rand)(10, 1);
    MATRIX_T *row_vector = MATRIX_FN(rand)(1, 10);
    MATRIX_T *m = MATRIX_FN(rand)(13, 13);

    MATRIX_T *c1 = MATRIX_FN(get_col)(col_vector, 0);
    MATRIX_T *r1 = MATRIX_FN(get_row)(row_vector, 0);

    assert(MAT_FN(cmp)(c1, col_vector));
    assert(MAT_FN(cmp)(r1, row_vector));

    printf("col_vector:\n");
    MATRIX_FN(print)(col_vector);

    printf("Clone:\n");
    MATRIX_FN(print)(c1);

    printf("row_vector:\n");
    MATRIX_FN(print)(row_vector);

    printf("Clone:\n");
    MATRIX_FN(print)(r1);

    MATRIX_FN(print)(m);

    MATRIX_FN(free)(c1);
    MATRIX_FN(free)(m);
    return 0;
}