#ifndef EJOVO_MATRIX_GENERIC_H
#define EJOVO_MATRIX_GENERIC_H

#define MATRIX_TYPE double
#define TYPE_SUFFIX _d

#include "matrix/generic_macros.h"

// Top-level looping constructs

/**========================================================================
 *!                           Double
 *========================================================================**/
// My first attempt at including 
// all of the matrix header's 

    #include "ejovo_matrix.h"

    #undef MATRIX_H
    #undef MATRIX_COMPUTE_H
    #undef MATRIX_DIST_H
    #undef MATRIX_CORE_H
    #undef MATRIX_FOREACH_H
    #undef MATRIX_GETSET_H
    #undef MATRIX_ITER_H
    #undef MATRIX_LINEAR_H
    #undef MATRIX_SPECIAL_H
    #undef MATRIX_STATE_H
    #undef MATRIX_VECTOR_H
    #undef MATRIX_STATS_H
    #undef MATRIX_FUNCTIONAL_H
    #undef MATRIX_LOGICAL_H
    #undef MATRIX_INDEX_H
    #undef MATRIX_STOCHASTIC_H
    // #undef EJOVO_MATRIX_H

// #undef MATRIX_TYPE
// #undef TYPE_SUFFIX

/**========================================================================
 *!                           Float
 *========================================================================**/


/**========================================================================
 *!                           Integer (32bits)
 *========================================================================**/

/**========================================================================
 *!                           Bool
 *========================================================================**/

#endif // EJOVO_MATRIX_GENERIC_H