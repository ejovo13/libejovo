// #include "ejovo_matrix_generic.h"
#include "ejovo_matrix.h"

// a module to generate vectors containing variates following basic distributions.
// heaviliy reliant on the ejovo_rand.c module

// fill a vector with a uniform random distribution
 TYPED(Vector)*TYPED(Vector_runif)(size_t __n, double __a, double __b) {

    TYPED(Vector)*v = TYPED(Vector_new)(__n); // this will create a column vector by default

    for (size_t i = 0; i < __n; i++) {
        TYPED(matset)(v, i, 0, unifd(__a, __b));
    }

    return v;
}

 TYPED(Vector)*TYPED(Vector_rnorm)(size_t __n, double __mean, double __std) {
    TYPED(Vector)*v = TYPED(Vector_new)(__n);

    // TYPED(MatIter) b= TYPED(Vector_begin)(v);
    // TYPED(MatIter) e = TYPED(Vector_end)(v);

    // experimental...
    for (TYPED(MatIter) b = TYPED(Vector_begin)(v); !TYPED(MatIter_cmp)(b, TYPED(Vector_end)(v)); b = TYPED(MatIter_next)(b)) {
        *(b.ptr) = normd(__mean, __std);
    }

    return v;
}

// fill a vector with a uniform random distribution
 TYPED(Vector)*TYPED(Vector_rexp)(size_t __n, double __rate) {

    TYPED(Vector)*v = TYPED(Vector_new)(__n); // this will create a column vector by default

    for (size_t i = 0; i < __n; i++) {
        TYPED(matset)(v, i, 0, expd(__rate));
    }

    return v;
}