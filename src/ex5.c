// ecrire une fonction permettant de multiplier deux matrices. On n'oubliera pas de traiter les
// cas d'erreur

// Need to obviously implement a simple matrix class
#include "ejovo_matrix.h"

int main(void) {

    Matrix *A = Matrix_new(1, 2);
    Matrix *B = Matrix_new(2, 1);
    Matrix *B_2 = Matrix_new(2, 1);

    Matrix_summary(A);
    Matrix_set(A, 0, 0, 2);
    Matrix_set(A, 0, 1, -1);
    Matrix_print(A);

    Matrix_summary(B);
    Matrix_set(B, 0, 0, 5);
    Matrix_set(B, 1, 0, 10);
    Matrix_print(B);

    Matrix_summary(B_2);
    Matrix_set(B_2, 0, 0, 5);
    Matrix_set(B_2, 1, 0, 10);
    Matrix_print(B_2);

    Matrix * C = matmul(B, A);
    assert(C);
    Matrix_summary(C);
    Matrix_print(C);

    Matrix * B_sum = matadd(B, B_2);
    assert(B_sum);
    Matrix_summary(B_sum);
    Matrix_print(B_sum);

    Matrix * C_sub = submat(C, 0, 1, 1,1);
    assert(C_sub);
    Matrix_summary(C_sub);
    Matrix_print(C_sub);

    Matrix_free(A);
    Matrix_free(B);
    Matrix_free(C);
    Matrix_free(B_sum);

    printf("Freed all matrices\n");


    return 0;
}