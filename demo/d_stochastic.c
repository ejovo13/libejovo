#include "ejovo_matrix.h"

int main() {

    ejovo_seed();

    // Matrix *stoch = Matrix_as_stochastic(Matrix_runif(10, 10, 0, 5));
    Matrix *stoch = Matrix_as_stochastic(Matrix_runif(2, 2, 0, 5));

    Matrix_print(stoch);

    return 0;
}