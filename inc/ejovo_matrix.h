// #ifndef EJOVO_MATRIX_H
// #define EJOVO_MATRIX_H

#ifdef MATRIX_TYPE

#define FOREACH(MAT) for (size_t i = 0; i < TYPED(Matrix_size)(MAT); i++)
#define FORIJ(MAT, INIT_LOOP, INSIDE_LOOP, OUTSIDE_LOOP) \
    const size_t __m = MAT->nrows; \
    const size_t __n = MAT->ncols; \
        for (size_t i = 0; i < __m; i++) { \
        INIT_LOOP \
        for (size_t j = 0; j < __n; j++) {  \
            INSIDE_LOOP \
        } \
        OUTSIDE_LOOP\
    } \

#include "ejovo_assert.h"

#include "matrix/generic_macros.h"

#include "matrix/matrix.h"
#include "matrix/matrix_core.h"
#include "matrix/matrix_compute.h"
#include "matrix/matrix_foreach.h"
#include "matrix/matrix_getset.h"
#include "matrix/matrix_iter.h"
#include "matrix/matrix_linear.h"
#include "matrix/matrix_special.h"
#include "matrix/matrix_state.h"
#include "matrix/matrix_vector.h"
#include "matrix/matrix_stats.h"
#include "matrix/matrix_dist.h"
#include "matrix/matrix_functional.h"
#include "matrix/matrix_logical.h"
#include "matrix/matrix_index.h"
#include "matrix/matrix_stochastic.h"

#endif // MATRIX_TYPE

// #endif // EJOVO_MATRIX_H