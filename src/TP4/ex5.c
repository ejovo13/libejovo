// ecrire une fonction permettant de multiplier deux matrices. On n'oubliera pas de traiter les
// cas d'erreur

// Need to obviously implement a simple matrix class
#include "ejovo_matrix.h"

int main(void) {

    ejovo_seed();

    Matrix *A = Matrix_random(3, 5, 0, 10);
    Matrix *B = Matrix_random(5, 6, 0, 10);

    Matrix *AB = Matrix_multiply(A, B);

    printf("A |\n===\n");
    Matrix_print(A);

    printf("B |\n===\n");
    Matrix_print(B);

    printf("\nA*B |\n=====\n");
    Matrix_print(AB);


    return 0;
}