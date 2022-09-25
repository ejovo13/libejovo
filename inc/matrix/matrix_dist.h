#ifndef MATRIX_DIST_H
#define MATRIX_DIST_H

#include "matrix.h"

// a module to generate vectors containing variates following basic distributions.
// heaviliy reliant on the ejovo_rand.c module

// fill a vector with a uniform random distribution
TYPED(Vector) *TYPED(Vector_runif)(size_t __n, double __a, double __b);

TYPED(Vector) *TYPED(Vector_rnorm)(size_t __n, double __mean, double __std);

// fill a vector with a uniform random distribution
TYPED(Vector) *TYPED(Vector_rexp)(size_t __n, double __rate);

#endif // MATRIX_DIST_H