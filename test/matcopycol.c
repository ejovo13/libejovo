#include "ejovo_matrix_generic.h"
#include <assert.h>
#include <stdbool.h>


int main() {

    printf("Yes\n");

    ejovo_seed();

    Matrix_d *col_vector = Matrix_rand_d(10, 1);
    Matrix_d *row_vector = Matrix_rand_d(1, 10);
    Matrix_d *m = Matrix_rand_d(13, 13);

    Matrix_d *c1 = Matrix_get_col_d(col_vector, 0);
    Matrix_d *r1 = Matrix_get_row_d(row_vector, 0);

    assert(matcmp_d(c1, col_vector));
    assert(matcmp_d(r1, row_vector));

    printf("col_vector:\n");
    Matrix_print_d(col_vector);

    printf("Clone:\n");
    Matrix_print_d(c1);

    printf("row_vector:\n");
    Matrix_print_d(row_vector);

    printf("Clone:\n");
    Matrix_print_d(r1);

    Matrix_print_d(m);

    Matrix_free_d(c1);
    Matrix_free_d(m);
    return 0;
}