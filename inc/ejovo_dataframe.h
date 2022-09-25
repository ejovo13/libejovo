#pragma once

#include <stdarg.h>

#include "ejovo_matrix_generic.h"
#include "ejovo_string.h"

// Routines dealing with the manipulating of multiple columns of data
/**========================================================================
 *!                           Chain functions
 *========================================================================**/
typedef struct chain_t {

    String *data;
    struct chain_t *next;

} Chain;

Chain *newChain(const char *__str);

// Return the root node of the chain just in case the chain is initially empty
Chain *appendChain(Chain *__chain, const char *__str);

int sizeChain(const Chain *__chain);

void printChain(const Chain *__chain);

Chain *newChainVar(int __count, ...);

/**========================================================================
 *!                           Space functions
 *========================================================================**/
typedef struct space_t {

    Vector_d *data;
    struct space_t *next;

} Space;

Space *newSpace( Vector_d *__v);

Space *appendSpace(Space *__space, Vector_d *__v);

Space *newSpaceVar(int __count, ...);


// Count the number of vectors in the space
int dimSpace(const Space *__space);

// Print the number and addresses of the vectors in this space
void printSpace(const Space *__space);

// verify that the dimensions of the matrices in __space are all the same
bool uniformSpace(const Space *__space);

/**========================================================================
 *!                           DataFrame functions
 *========================================================================**/

// Now I want a structure that is a pointer to a chain and a pointer to a space.
// This object will be used for data exportation

// I should also be able to add a new column to a data frame
// when given a string and a conforming vector
typedef struct data_frame_t {

    Chain *chain;
    Space *space;

} DataFrame;

DataFrame *newDataFrame(Chain *__chain, Space *__space);

int dimDataFrame(const DataFrame *__df);

typedef void (* string_vector_fn) (const String *, const Vector_d *);
typedef void (* string_fn) (String *);
typedef void (* vector_fn) ( Vector_d *);

void foreachSV(const DataFrame *__df, string_vector_fn fn);

void foreachString(const DataFrame *__df, string_fn fn);

void foreachVector(const DataFrame *__df, vector_fn fn);

// print the name of the col and then the first __nel elements
void printDataFrameCol(const String *__str, const Vector_d *__v);

void printDataFrame(const DataFrame *__df);

void writeDelimiter(const DataFrame *__df, const char *__filename, const char delim);

void writeCSV(const DataFrame *__df, const char *__filename);

// Simply write the contents of this data frame to a file, seperating the elements
// by whitespace
void writeGP(const DataFrame *__df, const char *__filename);

// Return a pointer to the column in question
// Columns shall be ZERO indexed
 Vector_d *getColDF(const DataFrame *__df, int __j);

/**========================================================================
 *!                           History functions
 *========================================================================**/ 
// Return a vector of doubles that is the result of some
// function call whose return is a double and whose input is
// null
typedef double (*double_fn)(void);

 Vector_d *save_doubles(double_fn fn, int n);