// #include "test_mat.h"
#include "ejovo.h"

void t_index();
void t_set_index();


int main() {

    ejovo_seed();

    // t_index();
    t_set_index();

    return 0;
}

// static double is_neg(double x) {
//     return x < 0;
// }

void t_index() {

    Matrix_d *m = Vector_rnorm_d(100, 0, 1);

    Matrix_d *ind = range_d(0, 10, 3);

    // Vector_print_as_row_d(m);
    Matrix_print_d(ind);

    // Vector_print_as_row_d(Matrix_index_d(m, ind));

    // // Get every other element
    // Matrix_reset_d(&ind);

    // ind = range_double(0, 99, 5);
    // Vector_print_as_row_d(ind);

    // Matrix_print_d(Matrix_index_d(m, ind));

    // // So there are multiple different valid ways of extracting data that fit a certain criteria.

    // // We can filter :
    // // Matrix_as_logical_d
    // // we can use logical indexing;
    // // we can use indices and Matrix_where_d

    // ind = Matrix_where_d(m, is_neg);
    // // Vector_print_as_row_d(ind);
    // Matrix_print_d(ind);

    // // Now use the indices to extract the negative components of m!

    // Matrix_print_d(Matrix_index_d(m, ind));

    Matrix_free_d(m);

}

void t_set_index() {

    Matrix_d *m = Vector_rnorm_d(100, 0, 3);
    m->ncols = 100;
    m->nrows = 1;


    Vector_d*r = range_d(0, 99, 2);

    // Pay careful attention, these values HAVE TO BE DOUBLES otherwise they will end up mangled by the variadic function
    Vector_d*a = matanon_d(3, 1.0, 2.0, 3.0);
    Matrix_print_d(a);

    matsetind_d(m, r, a);

    Matrix_anon_free_d();
    // printf("Hello\n");

    Matrix_print_d(m);
    Matrix_free_d(m);
    Matrix_free_d(r);



}