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

static double is_neg(double x) {
    return x < 0;
}

void t_index() {

    MATRIX_T *m = VECTOR_FN(rnorm)(100, 0, 1);

    MATRIX_T *ind = range(0, 10, 3);

    // VECTOR_FN(print_as_row)(m);
    MATRIX_FN(print)(ind);

    // VECTOR_FN(print_as_row)(MATRIX_FN(index)(m, ind));

    // // Get every other element
    // MATRIX_FN(reset)(&ind);

    // ind = range(0, 99, 5);
    // VECTOR_FN(print_as_row)(ind);

    // MATRIX_FN(print)(MATRIX_FN(index)(m, ind));

    // // So there are multiple different valid ways of extracting data that fit a certain criteria.

    // // We can filter :
    // // MATRIX_FN(as_logical)
    // // we can use logical indexing;
    // // we can use indices and MATRIX_FN(where)

    // ind = MATRIX_FN(where)(m, is_neg);
    // // VECTOR_FN(print_as_row)(ind);
    // MATRIX_FN(print)(ind);

    // // Now use the indices to extract the negative components of m!

    // MATRIX_FN(print)(MATRIX_FN(index)(m, ind));


}

void t_set_index() {

    MATRIX_T *m = VECTOR_FN(rnorm)(100, 0, 3);
    m->ncols = 100;
    m->nrows = 1;


    Vector *r = range(0, 99, 2);

    // Pay careful attention, these values HAVE TO BE DOUBLES otherwise they will end up mangled by the variadic function
    Vector *a = anon(3, 1.0, 2.0, 3.0);
    MATRIX_FN(print)(a);

    MAT_FN(setind)(m, r, a);

    MATRIX_FN(anon_free)();
    // printf("Hello\n");

    MATRIX_FN(print)(m);
    MATRIX_FN(free)(m);
    MATRIX_FN(free)(r);



}