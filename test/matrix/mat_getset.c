#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>

void t_getset();


int main() {

    ejovo_seed();
    Matrix *m = Matrix_rand(4, 4);
    // Matrix *m = NULL;
    // m = Matrix_new(10, 10);
    Matrix_print(m);

    // Matrix_print(m);

    // Matrix_mult_row_k(m, 0, 3);

    // Matrix_print(m);

    // Matrix_mult_col_k(m, 0, 3);

    // Matrix_print(m);

    Matrix_free(m);
    m = NULL;

    t_getset();

    return 0;
}

void t_getset() {

    printf("tgetset\n");

    Matrix *m = Matrix_new(5, 5);
    matset(m, 0, 0, 999);
    Matrix_print(m);
    Matrix_free(m);


}