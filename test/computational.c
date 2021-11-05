#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>


int main() {

    printf("Sup bitch\n");

    Matrix *K = Matrix_K(2);
    Matrix_print(K);
    Matrix_free(K);

    Matrix *K5 = Matrix_K(5);
    Matrix_print(K);

    Matrix *K15 = Matrix_K(15);
    Matrix_print(K15);

    Matrix *C5 = Matrix_C(5);
    Matrix_print(C5);

    Matrix *T5 = Matrix_T(5);
    Matrix_print(T5);

    Matrix *B5 = Matrix_B(5);
    Matrix_print(B5);

    Matrix_free(K5);
    Matrix_free(K15);
    Matrix_free(C5);
    Matrix_free(T5);
    Matrix_free(B5);


    return 0;
}