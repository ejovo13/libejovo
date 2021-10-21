#include "ejovo_matrix.h"

// La fonction Matrix_det est defini en ejovo_matrix.c

int main() {


    ejovo_seed();
    Matrix *A = Matrix_random(3, 3, 0, 5);
    Matrix_print(A);

    printf("Det(A): %lf\n", Matrix_det(A));


    return 0;
}