#ifndef EJOVO_LABYRINTH
#define EJOVO_LABYRINTH

#include "stdbool.h"
#include <stddef.h>
// #define MATRIX_TYPE int
// #include "ejovo_matrix_generic.h"
// #include "matrix/matrix_d.h"
#include "ejovo_matrix.h"

// This file contains some functions to generate a labyrinth and then later how to solve the maze
// #ifndef MATRIX_TYPE
// #define MATRIX_TYPE int
// #endif


typedef enum piece_e {
    V_PIPE, // Vertical pipe
    H_PIPE, // Horizontal pipe
    TOPL_L, // Top left L shape
    TOPR_L, // Top right L shape
    BOTR_L, // Bottom right L shape
    BOTL_L, // Bottom left L shape
    CROSS,
    TET_D, // Piece that looks like tetris, pointing down
    TET_L,
    TET_U,
    TET_R,
    ZERO, // all zeros
    OTHER,
} PIECE_TYPE;

typedef struct labyrinth_piece_t {

    // contain a 3 by 3 matrix and one field that is the PIECE_TYPE enum
    Matrix_d *mat;
    PIECE_TYPE type;

} LabPiece;




Matrix_d *TYPED(Matrix_from)(const MATRIX_TYPE *__arr, size_t __nrows, size_t __ncols);


// Using this for a piece that is 3x3
MATRIX_TYPE *piece_array(MATRIX_TYPE __1, MATRIX_TYPE __2, MATRIX_TYPE __3, MATRIX_TYPE __4, MATRIX_TYPE __5, MATRIX_TYPE __6, MATRIX_TYPE __7, MATRIX_TYPE __8, MATRIX_TYPE __9);

// Pass an enum value and get the 3 x 3 matrix that corresponds to this piece
Matrix_d *get_piece_matrix(PIECE_TYPE __t);

LabPiece *get_piece(PIECE_TYPE __t);

void print_piece(LabPiece *__p, size_t __n);

LabPiece *get_piece_from_matrix(Matrix_d *__m, size_t __i, size_t __j);


void print_matrix_as_lab(Matrix_d *__m);

Matrix_d *create_checkerboard(size_t __nrows, size_t __ncols);

typedef enum directions_s {

    RIGHT,
    LEFT,
    UP,
    DOWN,

} DIRECTION;

bool open_right_t(PIECE_TYPE __t);

bool open_left_t(PIECE_TYPE __t);

bool open_up_t(PIECE_TYPE __t);

bool open_down_t(PIECE_TYPE __t);

// return true if the piece type is open in the direction
bool is_piece_open(PIECE_TYPE __t, DIRECTION __d);

// return the type of a random piece that is open to the d direction
PIECE_TYPE get_open_piece_type(DIRECTION __d);

// return the type of a random piece that is open to the d direction
PIECE_TYPE get_open_piece_type_2(DIRECTION __d1, DIRECTION __d2);

// Create a path through the matrix from the top to the bottom
void create_path(Matrix_d *__m, size_t __start_j, size_t __end_j);

Matrix_d *create_maze(size_t __nrows, size_t __ncols);

typedef struct cell_t {
    size_t i;
    size_t j;
    struct cell_t *below;
} Cell;

typedef struct cell_stack_t {

    Cell *top;

} CellStack;

void generate_path(Matrix_d *__maze, CellStack *__stack, size_t __celli, size_t __cellj);

#endif