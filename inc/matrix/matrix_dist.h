#pragma once

#include "matrix.h"

// a module to generate vectors containing variates following basic distributions.
// heaviliy reliant on the ejovo_rand.c module

// fill a vector with a uniform random distribution
Vector *VECTOR_FN(runif)(size_t __n, double __a, double __b);

Vector *VECTOR_FN(rnorm)(size_t __n, double __mean, double __std);

// fill a vector with a uniform random distribution
Vector *VECTOR_FN(rexp)(size_t __n, double __rate);