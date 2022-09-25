#include "ejovo_matrix_generic.h"
#include <assert.h>
#include <stdbool.h>


int main() {

    printf("Sup bitch\n");

    Matrix_d *K = Matrix_K_d(2);
    Matrix_print_d(K);
    Matrix_free_d(K);

    Matrix_d *K5 = Matrix_K_d(5);
    Matrix_print_d(K);

    Matrix_d *K15 = Matrix_K_d(15);
    Matrix_print_d(K15);

    Matrix_d *C5 = Matrix_C_d(5);
    Matrix_print_d(C5);

    Matrix_d *T5 = Matrix_T_d(5);
    Matrix_print_d(T5);

    Matrix_d *B5 = Matrix_B_d(5);
    Matrix_print_d(B5);

    Matrix_free_d(K5);
    Matrix_free_d(K15);
    Matrix_free_d(C5);
    Matrix_free_d(T5);
    Matrix_free_d(B5);


    return 0;
}