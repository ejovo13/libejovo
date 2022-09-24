#include "ejovo_matrix.h"

// a module to generate vectors containing variates following basic distributions.
// heaviliy reliant on the ejovo_rand.c module

// fill a vector with a uniform random distribution
Vector *VECTOR_FN(runif)(size_t __n, double __a, double __b) {

    Vector *v = VECTOR_FN(new)(__n); // this will create a column vector by default

    for (size_t i = 0; i < __n; i++) {
        MAT_FN(set)(v, i, 0, unifd(__a, __b));
    }

    return v;
}

Vector *VECTOR_FN(rnorm)(size_t __n, double __mean, double __std) {
    Vector *v = VECTOR_FN(new)(__n);

    // MATITER_T b= VECTOR_FN(begin)(v);
    // MATITER_T e = VECTOR_FN(end)(v);

    // experimental...
    for (MATITER_T b = VECTOR_FN(begin)(v); !MATITER_FN(cmp)(b, VECTOR_FN(end)(v)); b = MATITER_FN(next)(b)) {
        *(b.ptr) = normd(__mean, __std);
    }

    return v;
}

// fill a vector with a uniform random distribution
Vector *VECTOR_FN(rexp)(size_t __n, double __rate) {

    Vector *v = VECTOR_FN(new)(__n); // this will create a column vector by default

    for (size_t i = 0; i < __n; i++) {
        MAT_FN(set)(v, i, 0, expd(__rate));
    }

    return v;
}