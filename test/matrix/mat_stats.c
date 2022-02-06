#include "test_mat.h"

void t_stats();

int main() {
    t_stats();
    return 0;
}

void t_stats() {

    Vector *v = get_V();

    assert(Vector_iter_sum(v) == 4827);
    assert(Vector_iter_mean(v) == 48.27);
    assert(Vector_iter_prod(v) == 2084665261716893743665907133825444382365162377526258418090488426290510496570594647344840764092672500968715732110683532356837753775075967405071449991413760.0);
    assert(Vector_iter_mean_squared(v) == 3140.6700);
    assert(Vector_iter_rms(v) == sqrt(3140.6700));
    assert(Vector_iter_min(v) == 1);
    assert(Vector_iter_max(v) == 97);
    assert(Vector_iter_std(v) == 28.472391891093377); // Hell yeah this shit matches exactly with MATLAB's calculation.
    assert(Vector_iter_var(v) == 810.6770999999999);

    assert(Matrix_iter_sum(v) == 4827);
    assert(Matrix_iter_mean(v) == 48.27);
    assert(Matrix_iter_prod(v) == 2084665261716893743665907133825444382365162377526258418090488426290510496570594647344840764092672500968715732110683532356837753775075967405071449991413760.0);
    assert(Matrix_iter_mean_squared(v) == 3140.6700);
    assert(Matrix_iter_rms(v) == sqrt(3140.6700));
    assert(Matrix_iter_min(v) == 1);
    assert(Matrix_iter_max(v) == 97);
    assert(Matrix_iter_std(v) == 28.472391891093377); // Hell yeah this shit matches exactly with MATLAB's calculation.
    assert(Matrix_iter_var(v) == 810.6770999999999);

    Matrix *a = get_A();

    Matrix_print(a);
    Matrix_print(v);





    Matrix_free(v);
    Matrix_free(a);
}