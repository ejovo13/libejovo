#include "matrix_functional.h"

Vector *filter(const Vector *__v, predicate_fn __pred) {

    printf("============ Calling filter!!! ============\n");

    // First I need to pass through the vector to see how many times the predicate is true...
    int count = 0;

    for (int i = 0; i < Vector_size(__v); i++) {

        if (__pred(Vector_at(__v, i))) count++;

    }

    Vector *out = Matrix_new(1, count);

    int j = 0; // index of out
    for (int i = 0; i < Vector_size(__v); i++) {
        if (__pred(Vector_at(__v, i))) {
            Vector_set(out, j, Vector_at(__v, i));
            j ++;
        }
    }

    return out;

}