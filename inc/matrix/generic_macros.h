#ifndef GENERIC_MACROS_H
#define GENERIC_MACROS_H

// Used to expand the definition of TYPED(Matrix)YPe 
// when calling MATRIX
#define CAT(X, Y) CAT2(X, Y)
#define CAT2(X, Y) X##Y
#define STRINGIFY(X) STRINGIFY2(X)
#define STRINGIFY2(X) #X

#define CAT3(X, Y, Z) CAT32(X, Y, Z)
#define CAT32(X, Y, Z) X ## Y ## Z


/**========================================================================
 *!                           Data type Macros
 *========================================================================**/
// #define TYPED(Vector) CAT(Vector, TYPE_SUFFIX)
// #define MAT_T CAT(mat, TYPE_SUFFIX)
// #define MATITER_T CAT(MatIter, TYPE_SUFFIX)

/**========================================================================
 *!                           The only type macros I need
 *========================================================================**/
// #define MATRIX_TYPE CAT(Matrix, TYPE_SUFFIX)
#define TYPED(name) CAT(name, TYPE_SUFFIX)

/**========================================================================
 *!                           Function Macros
 *========================================================================**/
// #define TYPED(Matrix_fn_name) CAT3(Matrix_, fn_name, TYPE_SUFFIX)
// #define TYPED(Vector_fn_name) CAT3(Vector_, fn_name, TYPE_SUFFIX)
// #define TYPED(MatIter_fn_name) CAT3(MatIter_, fn_name, TYPE_SUFFIX)

// #define TYPED(matfn_name) CAT3(mat, fn_name, TYPE_SUFFIX)
// #define TYPED(fn_name) CAT(fn_name, TYPE_SUFFIX)

// deprecated
#define MATRIX(TYPE) CAT(Matrix_, TYPE) 
#define MATITER_NEW CAT(MatIter_new, TYPE_SUFFIX)


#endif