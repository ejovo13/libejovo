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
    // assert(Vector_iter_mean(v) == 48.27);

    MatIter b = Vector_begin(v);
    MatIter e = Vector_end(v);

    // printf("Vector_size(v) -> %ld\n", Vector_size(v));

    // printf("Length of v: %ld\n", MatIter_length(b, e));
    // printf("Mean of v: %lf\n", Vector_iter_mean(v));
    printf("[t_stats]          end->ptr: %x, begin->ptr: %x\n", e.ptr, b.ptr);
    printf("MatIter_mean(b, e): %lf\n", MatIter_mean(b, e));
    // printf("MatIter_sum(b, e): %lf\n", MatIter_sum(b, e));
    // printf("MatIter_sum(b, b): %lf\n", MatIter_sum(b, b));

    Matrix_free(v);


}