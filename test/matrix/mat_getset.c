#include "ejovo_matrix_generic.h"
#include <assert.h>
#include <stdbool.h>

void t_getset();


int main() {

    ejovo_seed();
    Matrix_d *m = Matrix_rand_d(4, 4);
    // Matrix_d *m = NULL;
    // m = Matrix_new_d(10, 10);
    Matrix_print_d(m);

    // Matrix_print_d(m);

    // Matrix_mult_row_k_d(m, 0, 3);

    // Matrix_print_d(m);

    // Matrix_mult_col_k_d(m, 0, 3);

    // Matrix_print_d(m);

    Matrix_free_d(m);
    m = NULL;

    t_getset();

    return 0;
}

void t_getset() {

    printf("tgetset\n");

    Matrix_d *m = Matrix_new_d(5, 5);
    matset_d(m, 0, 0, 999);
    Matrix_print_d(m);
    Matrix_free_d(m);


}