#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>


int main() {

    printf("Yes\n");

    ejovo_seed();

    Matrix *col_vector = Matrix_rand(10, 1);
    Matrix *row_vector = Matrix_rand(1, 10);
    Matrix *m = Matrix_rand(13, 13);

    Matrix *c1 = Matrix_get_col(col_vector, 0);
    Matrix *r1 = Matrix_get_row(row_vector, 0);

    assert(matcmp(c1, col_vector));
    assert(matcmp(r1, row_vector));

    printf("col_vector:\n");
    Matrix_print(col_vector);

    printf("Clone:\n");
    Matrix_print(c1);

    printf("row_vector:\n");
    Matrix_print(row_vector);

    printf("Clone:\n");
    Matrix_print(r1);

    Matrix_print(m);

    Matrix_free(c1);
    Matrix_free(m);
    return 0;
}