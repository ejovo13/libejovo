#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>

void t_matlu();
void t_Matrix_lu();

int main() {

    t_matlu();
    t_Matrix_lu();


    return 0;
}

void t_matlu() {

    ejovo_seed();

    Matrix *m = Matrix_random(3, 3, 1, 10);
    Matrix_print(m);

    Matrix *U = Matrix_clone(m);

    Matrix *L = matlu_nopivot(U);
    Matrix_print(L);
    Matrix_print(U);

    printf("L * U = \n");

    Matrix_print(Matrix_multiply(L, U));

}

void t_Matrix_lu() {

    Matrix *m = Matrix_random(10, 10, 1, 12);

    LU lu = Matrix_lu(m);

    Matrix_print(m);
    printf("\n LU decomposition: \n");

    Matrix_print(lu.L);
    Matrix_print(lu.U);



}