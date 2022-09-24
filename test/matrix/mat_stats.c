#include "test_mat.h"

void t_stats();

int main() {
    t_stats();
    return 0;
}

void t_stats() {

    Vector *v = get_V();

    assert(VECTOR_FN(iter_sum)(v) == 4827);
    assert(VECTOR_FN(iter_mean)(v) == 48.27);
    assert(VECTOR_FN(iter_prod)(v) == 2084665261716893743665907133825444382365162377526258418090488426290510496570594647344840764092672500968715732110683532356837753775075967405071449991413760.0);
    assert(VECTOR_FN(iter_mean_squared)(v) == 3140.6700);
    assert(VECTOR_FN(iter_rms)(v) == sqrt(3140.6700));
    assert(VECTOR_FN(iter_min)(v) == 1);
    assert(VECTOR_FN(iter_max)(v) == 97);
    assert(VECTOR_FN(iter_std)(v) == 28.472391891093377); // Hell yeah this shit matches exactly with MATLAB's calculation.
    assert(VECTOR_FN(iter_var)(v) == 810.6770999999999);

    assert(MATRIX_FN(iter_sum)(v) == 4827);
    assert(MATRIX_FN(iter_mean)(v) == 48.27);
    assert(MATRIX_FN(iter_prod)(v) == 2084665261716893743665907133825444382365162377526258418090488426290510496570594647344840764092672500968715732110683532356837753775075967405071449991413760.0);
    assert(MATRIX_FN(iter_mean_squared)(v) == 3140.6700);
    assert(MATRIX_FN(iter_rms)(v) == sqrt(3140.6700));
    assert(MATRIX_FN(iter_min)(v) == 1);
    assert(MATRIX_FN(iter_max)(v) == 97);
    assert(MATRIX_FN(iter_std)(v) == 28.472391891093377); // Hell yeah this shit matches exactly with MATLAB's calculation.
    assert(MATRIX_FN(iter_var)(v) == 810.6770999999999);

    MATRIX_T *a = get_A();

    MATRIX_FN(print)(v);
    MATRIX_FN(print)(a);

    assert(MATRIX_FN(iter_sum)(a) == 21);
    assert(MATRIX_FN(iter_mean)(a) == 3.5);
    assert(MATRIX_FN(iter_prod)(a) == 720);
    assert(MATRIX_FN(iter_mean_squared)(a) == 15.166666666666666);
    assert(MATRIX_FN(iter_rms)(a) == sqrt(15.166666666666666));
    assert(MATRIX_FN(iter_min)(a) == 1);
    assert(MATRIX_FN(iter_max)(a) == 6);
    assert(MATRIX_FN(iter_std)(a) == 1.707825127659933); // Hell yeah this shit matches exactly with MATLAB's calculation.
    printf("Var: %lf\n", MATRIX_FN(iter_var)(a));
    assert(fabs(MATRIX_FN(iter_var)(a) - 2.916666666666667) < 0.000000001); // can't get bitwise precision here.

    MATRIX_FN(free)(v);
    MATRIX_FN(free)(a);
}