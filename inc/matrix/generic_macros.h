#ifndef GENERIC_MACROS_H
#define GENERIC_MACROS_H


// Used to expand the definition of MATRIX_TYPe 
// when calling MATRIX
    #define CAT(X, Y) CAT2(X, Y)
    #define CAT2(X, Y) X##Y

    #define CAT3(X, Y, Z) CAT32(X, Y, Z)
    #define CAT32(X, Y, Z) X ## Y ## Z


/**========================================================================
 *!                           Data type Macros
 *========================================================================**/
#define MATRIX_T CAT(Matrix, TYPE_SUFFIX)
#define VECTOR_T CAT(Vector, TYPE_SUFFIX)
#define MAT_T CAT(mat, TYPE_SUFFIX)
#define MATITER_T CAT(MatIter, TYPE_SUFFIX)

// MATRIX_T

/**========================================================================
 *!                           Function Macros
 *========================================================================**/
#define MATRIX_FN(fn_name) CAT3(MATRIX_T, _, fn_name)
#define VECTOR_FN(fn_name) CAT3(VECTOR_T, _, fn_name)
#define MATITER_FN(fn_name) CAT3(MATITER_T, _, fn_name)

#define MAT_FN(fn_name) CAT(MAT_T, fn_name)
#define TYPED_FN(fn_name) CAT(fn_name, TYPE_SUFFIX)
#define TYPED(name) CAT(name, TYPE_SUFFIX)

// deprecated
#define MATRIX(TYPE) CAT(Matrix_, TYPE) 
#define MATITER_NEW CAT3(MATITER_T, _, new)


#endif