#include "test_mat.h"

void t_logical();

int main() {

    ejovo_seed();

    t_logical();


    return 0;
}

double lambda_gt5(double x) {
    if (x > 5) return TRUE;
    else return FALSE;
}

void t_logical() {

    Matrix *m = Matrix_rand(13, 8);

    Matrix_print(m);

    Matrix *logical = Matrix_as_logical(m, lambda_gt5);
    Matrix_print(logical);

    Matrix *logic_5 = Matrix_gt(m, 5);
    Matrix *logic_lt5 = Matrix_lt(m, 5);
    Matrix_print(logic_lt5);


    Matrix *true_mat = Matrix_as_true(m);
    Matrix_print(true_mat);

    assert(Logical_all(true_mat));

    assert(Matrix_is_logical(logical));
    assert(!Matrix_is_logical(m));

    matsetmask(m, logical, 0);
    Matrix_print(m);

    Matrix *gt5 = Matrix_filter_mask(m, Logical_not(logical));
    Matrix_print(gt5);


    Matrix_reset(&m);
    Matrix_reset(&logical);
    Matrix_reset(&true_mat);
    Matrix_reset(&gt5);

}