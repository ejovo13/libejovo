#include "test_mat.h"

void t_stats();

int main() {
    t_stats();
    return 0;
}

void t_stats() {

    ejovo_seed();
    Vector *v = get_V();

    assert(Vector_iter_sum(v) == 4827);
    assert(Vector_iter_mean(v) == 48.27);
    assert(Vector_iter_prod(v) == 2084665261716893743665907133825444382365162377526258418090488426290510496570594647344840764092672500968715732110683532356837753775075967405071449991413760.0);
    assert(Vector_iter_mean_squared(v) == 3140.6700);
    assert(Vector_iter_rms(v) == sqrt(3140.6700));
    assert(Vector_iter_min(v) == 1);
    assert(Vector_iter_max(v) == 97);

    Matrix_print(v);

    Matrix_free(v);
}