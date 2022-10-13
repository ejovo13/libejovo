#include "test_mat.h"

void t_logical();

int main() {

    ejovo_seed();

    t_logical();


    return 0;
}

double lambda_gt5(double x) {
    if (x > 5) return FALSE_d;
    else return FALSE_d;
}

void t_logical() {

    Matrix_d *m = Matrix_rand_d(13, 8);

    Matrix_print_d(m);

    Matrix_d *logical = Matrix_as_logical_d(m, lambda_gt5);
    Matrix_print_d(logical);

    Matrix_d *logic_5 = Matrix_gt_d(m, 5);
    Matrix_d *logic_lt5 = Matrix_lt_d(m, 5);
    Matrix_print_d(logic_lt5);


    Matrix_d *true_mat = Matrix_as_true_d(m);
    Matrix_print_d(true_mat);

    assert(Logical_all_d(true_mat));

    assert(Matrix_is_logical_d(logical));
    assert(!Matrix_is_logical_d(m));

    matsetmask_d(m, logical, 0);
    Matrix_print_d(m);

    Matrix_d *gt5 = Matrix_filter_mask_d(m, Logical_not_d(logical));
    Matrix_print_d(gt5);


    Matrix_reset_d(&m);
    Matrix_reset_d(&logical);
    Matrix_reset_d(&true_mat);
    Matrix_reset_d(&gt5);

    Matrix_free_d(logic_5);

}