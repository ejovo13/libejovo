#define MATRIX_TYPE int

#include "ejovo_matrix.h"
#include "ejovo_labyrinth.h"

int main() {

    ejovo_seed();

    const size_t NUM_COL = 5;
    const size_t NUM_ROW = 5;

    Matrix *lab = Matrix_random(NUM_ROW, NUM_COL, 0, 1);

    Matrix_print(lab);

    long test[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Matrix *b = Matrix_from(test, 5, 2);

    for (size_t i = 0; i < 10; i++) {
        printf("%d ", test[i]);
    }

    Matrix_print(b);



    return 0;
}
