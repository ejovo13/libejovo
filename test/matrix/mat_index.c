#include "test_mat.h"

void t_index();

int main() {

    ejovo_seed();

    t_index();

    return 0;
}

static double is_neg(double x) {
    return x < 0;
}

void t_index() {

    Matrix *m = Vector_rnorm(100, 0, 1);

    Matrix *ind = range(0, 10, 3);

    Vector_print_as_row(m);
    Matrix_print(ind);

    Vector_print_as_row(Matrix_index(m, ind));

    // Get every other element
    Matrix_reset(&ind);

    ind = range(0, 99, 5);
    Vector_print_as_row(ind);

    Matrix_print(Matrix_index(m, ind));

    // So there are multiple different valid ways of extracting data that fit a certain criteria.

    // We can filter :
    // Matrix_as_logical
    // we can use logical indexing;
    // we can use indices and Matrix_where

    ind = Matrix_where(m, is_neg);
    // Vector_print_as_row(ind);
    Matrix_print(ind);

    // Now use the indices to extract the negative components of m!

    Matrix_print(Matrix_index(m, ind));


}