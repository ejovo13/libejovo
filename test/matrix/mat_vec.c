#include "ejovo_matrix.h"
#include <assert.h>
#include <stdbool.h>


int main() {

    Matrix *m = Matrix_value(2, 2, 4);

    Matrix_print(m);

    printf("2-norm of first column: %lf\n", Matrix_col_norm(m, 0));
    // printf("3-norm of second column: %lf\n", Vector_pnorm_iter()

    printf("Frobenius norm: %lf\n", Matrix_frobenius(m));


    return 0;
}