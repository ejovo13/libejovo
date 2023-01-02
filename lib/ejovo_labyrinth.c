#include "ejovo_labyrinth.h"
#include "stdbool.h"


// Using this for a piece that is 3x3
MATRIX_TYPE *piece_array(MATRIX_TYPE __1, MATRIX_TYPE __2, MATRIX_TYPE __3, MATRIX_TYPE __4, MATRIX_TYPE __5, MATRIX_TYPE __6, MATRIX_TYPE __7, MATRIX_TYPE __8, MATRIX_TYPE __9) { // Don't even ask

    MATRIX_TYPE *arr = (MATRIX_TYPE *) malloc(sizeof(MATRIX_TYPE) * 9);

    if(arr) {

        arr[0] = __1;
        arr[1] = __2;
        arr[2] = __3;
        arr[3] = __4;
        arr[4] = __5;
        arr[5] = __6;
        arr[6] = __7;
        arr[7] = __8;
        arr[8] = __9;
    }

    return arr;
}

// Pass an enum value and get the 3 x 3 matrix that corresponds to this piece
TYPED(Matrix) *get_piece_matrix(PIECE_TYPE __t) {

    MATRIX_TYPE *data = {0};

    switch (__t) {

        case V_PIPE:
            data = piece_array(1, 0, 1, 1, 0, 1, 1, 0, 1);
            break;

        case H_PIPE:
            data = piece_array(1, 1, 1, 0, 0, 0, 1, 1, 1);
            break;

        case TOPL_L:
            data = piece_array(1, 0, 1, 0, 0, 1, 1, 1, 1);
            break;

        case TOPR_L:
            data = piece_array(1, 0, 1, 1, 0, 0, 1, 1, 1);
            break;

        case BOTR_L:
            data = piece_array(1, 1, 1, 1, 0, 0, 1, 0, 1);
            break;

        case BOTL_L:
            data = piece_array(1, 1, 1, 0, 0, 1, 1, 0, 1);
            break;

        case CROSS:
            data = piece_array(1, 0, 1, 0, 0, 0, 1, 0, 1);
            break;

        case TET_D:
            data = piece_array(1, 1, 1, 0, 0, 0, 1, 0, 1);
            break;

        case TET_R:
            data = piece_array(1, 0, 1, 1, 0, 0, 1, 0, 1);
            break;

        case TET_U:
            data = piece_array(1, 0, 1, 0, 0, 0, 1, 1, 1);
            break;

        case TET_L:
            data = piece_array(1, 0, 1, 0, 0, 1, 1, 0, 1);
            break;
        default:
            data = piece_array(0, 0, 0, 0, 0, 0, 0, 0, 0);
    }

    return TYPED(Matrix_from)(data, 3, 3);
}

LabPiece *get_piece(PIECE_TYPE __t) {

    LabPiece *p = malloc(sizeof(LabPiece));
    if(p) {
        p->mat = get_piece_matrix(__t);
        p->type = __t;
    }

    return p;
}

LabPiece *get_piece_from_matrix(TYPED(Matrix) *__m, size_t __i, size_t __j) {

    LabPiece *p = malloc(sizeof(LabPiece));
    if(p) {
        p->mat = TYPED(Matrix_submat)(__m, __i, __i+2, __j, __j+2);
        p->type = OTHER;
    }

    return p;

}

void print_piece(LabPiece *__p, size_t __n) {

    for (size_t i = 0; i < __n; i++) {
        for (size_t j = 0; j < __n; j++) {
            if(TYPED(Matrix_at)(__p->mat, i, j)) {
                printf("@");
            } else {
                printf(" ");
            }

        }
        printf("\n");
    }
}

void print_matrix_as_lab(TYPED(Matrix) *__m) {

    for (size_t i = 0; i < __m->nrows; i++) {
        for (size_t j = 0; j < __m->ncols; j++) {

            if(TYPED(Matrix_at)(__m, i, j) == 1) {
                // printf("\u25AE");
                printf("\u2588");
                // printf("\u2B1B");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
// Place a LabPiece at a given index of a matrix
void place_piece(TYPED(Matrix) *__m, PIECE_TYPE __t, size_t __i, size_t __j) {

    TYPED(matcpyele)(__m, __i*3, __i*3 + 2, __j*3, __j*3 + 2, get_piece_matrix(__t));

}

TYPED(Matrix) *create_checkerboard(size_t __nrows, size_t __ncols) {
    if (__nrows < 0 || __ncols < 0) {
        perror("Cannot instantiate new checkerboard with 0 rows/cols\n");
        return NULL;
    }

    // printf("Creating a checkerboard %lu x %lu\n", __nrows*3, __ncols*3);

    TYPED(Matrix) *m = TYPED(Matrix_new)(__nrows * 3, __ncols * 3);



    if(m) {
        for (size_t i = 0; i < __nrows; i++) {
            for (size_t j = 0; j < __ncols; j++) {
                // TYPED(matcpyele)(m, i*3, i*3 + 2, j*3, j*3 + 2, get_piece_matrix(unif(0, 10)));
                place_piece(m, unifi(0,10), i, j);
                // printf("i = %lu, j = %lu\n", i, j);
            }
        }
    } else {
        perror("TYPED(Matrix) not initialised\n");
    }

    return m;
}

void set_border_elements(TYPED(Matrix) *__m, size_t __jtop, size_t __jbot) {

    // set all of the elements to 1 besides (__i1, __j1) and (__i2, __j2)
    for (size_t i = 0; i < __m->nrows; i++) {

        if (i == 0 || i == __m->nrows - 1) { // if we are dealing with the first or last rows

            for (size_t j = 0; j < __m->ncols; j++) { // iterate through each column
                if (j == __jtop && i == 0) {
                    TYPED(Matrix_set)(__m, i, j, 0);
                    continue;
                } else if ( j == __jbot && i == __m->nrows - 1) {
                    TYPED(Matrix_set)(__m, i, j, 0);
                    continue;
                } else {
                    TYPED(Matrix_set)(__m, i, j, 1);
                }
            }
        }

        TYPED(Matrix_set)(__m, i, 0, 1);
        TYPED(Matrix_set)(__m, i, __m->ncols - 1, 1);

    }
}


bool open_right_t(PIECE_TYPE __t) {

    switch (__t) {

        case H_PIPE: case TOPR_L: case BOTR_L: case CROSS:
        case TET_D:  case TET_R:  case TET_U:

            return true;

        default:

            return false;

    }
}

bool open_left_t(PIECE_TYPE __t) {

    switch (__t) {

        case H_PIPE: case TOPL_L: case BOTL_L: case CROSS:
        case TET_D:  case TET_L:  case TET_U:

            return true;

        default:

            return false;

    }
}
bool open_up_t(PIECE_TYPE __t) {

    switch (__t) {

        case V_PIPE: case TOPR_L: case TOPL_L: case CROSS:
        case TET_U:  case TET_R:  case TET_L:

            return true;

        default:

            return false;

    }
}
bool open_down_t(PIECE_TYPE __t) {

    switch (__t) {

        case V_PIPE: case BOTL_L: case BOTR_L: case CROSS:
        case TET_D:  case TET_R:  case TET_L:

            return true;

        default:

            return false;

    }
}

// return true if the piece type is open in the direction
bool is_piece_open(PIECE_TYPE __t, DIRECTION __d) {

    switch (__d) {

        case RIGHT:

            return open_right_t(__t);
            break;

        case LEFT:

            return open_left_t(__t);
            break;

        case UP:

            return open_up_t(__t);
            break;

        case DOWN:

            return open_down_t(__t);
            break;
    }
}

// return the type of a random piece that is open to the d direction
PIECE_TYPE get_open_piece_type(DIRECTION __d) {

    int rand_piece = 11;

    do {

        rand_piece = unifi(0, 10);

    } while (! is_piece_open(rand_piece, __d));

    return rand_piece;
}

// return the type of a random piece that is open to the d direction
PIECE_TYPE get_open_piece_type_2(DIRECTION __d1, DIRECTION __d2) {

    int rand_piece = 11;

    do {

        rand_piece = unifi(0, 10);

    } while (!is_piece_open(rand_piece, __d1) || !is_piece_open(rand_piece, __d2));

    return rand_piece;
}




// Create a path through the matrix from the top to the bottom
void create_path(TYPED(Matrix) *__m, size_t __start_j, size_t __end_j) {

    // start by choosing an initial piece that has an opening through the top

    for(size_t i = 0; i < __m->ncols/3; i++) {

        place_piece(__m, i, i*3, get_open_piece_type_2(RIGHT, LEFT));

    }
}

enum cell_status {

    VISITED = -1,

};

bool cell_has_unvisited_neighbors(TYPED(Matrix) *__maze, size_t __celli, size_t __cellj) {

    if (TYPED(Matrix_valid_bounds)(__maze, __celli + 2, __cellj) ) {
        if (TYPED(Matrix_at)(__maze, __celli + 2, __cellj) != -1) return true;
    }

    if (TYPED(Matrix_valid_bounds)(__maze, __celli - 2, __cellj) ) {
        if (TYPED(Matrix_at)(__maze, __celli - 2, __cellj) != -1) return true;
    }

    if (TYPED(Matrix_valid_bounds)(__maze, __celli, __cellj - 2) ) {
        if (TYPED(Matrix_at)(__maze, __celli, __cellj - 2) != -1) return true;
    }

    if (TYPED(Matrix_valid_bounds)(__maze, __celli, __cellj + 2) ) {
        if (TYPED(Matrix_at)(__maze, __celli, __cellj + 2) != -1) return true;
    }

    return false;

    // // true is __maze(i + 2, j + 2) || __maze(i + 2, j - 2) || ... is not equal to 1
    // return (TYPED(Matrix_at)(__maze, __celli + 2, __cellj + 2) != -1 ||
    //         TYPED(Matrix_at)(__maze, __celli - 2, __cellj + 2) != -1 ||
    //         TYPED(Matrix_at)(__maze, __celli + 2, __cellj - 2) != -1 ||
    //         TYPED(Matrix_at)(__maze, __celli - 2, __cellj - 2) != -1   );

}

void choose_next_cell(TYPED(Matrix) *__maze, size_t *__celli_ptr, size_t *__cellj_ptr) {

    // set the __celli and __cellj value to the next cell that is available

    // choose random value between 1 and 4

    int rand_cell = 0;
    bool right_checked = false;
    bool left_checked = false;
    bool down_checked = false;
    bool up_checked = false;

    while (!(right_checked && left_checked && down_checked && up_checked)) {

        rand_cell = unifi(1, 4);

        switch (rand_cell) {

            case 1:

                if (TYPED(Matrix_valid_bounds)(__maze, *__celli_ptr + 2, *__cellj_ptr) ) {

                    if (TYPED(Matrix_at)(__maze, *__celli_ptr + 2, *__cellj_ptr) != -1) {
                        // open up the space between this cell and the next
                        TYPED(Matrix_set)(__maze, *__celli_ptr + 1, *__cellj_ptr, 0);
                        // then this cell is unvisited, set cell coordinates for the next cell
                        *__celli_ptr += 2;
                        return;
                    }
                }

                right_checked = true;
                break;

            case 2:

                if (TYPED(Matrix_valid_bounds)(__maze, *__celli_ptr - 2, *__cellj_ptr) ) {

                    if (TYPED(Matrix_at)(__maze, *__celli_ptr - 2, *__cellj_ptr) != -1) {
                        TYPED(Matrix_set)(__maze, *__celli_ptr - 1, *__cellj_ptr, 0);
                        // then this cell is unvisited, set cell coordinates for the next cell
                        *__celli_ptr -= 2;
                        return;
                    }

                }

                left_checked = true;
                break;


            case 3:

                if (TYPED(Matrix_valid_bounds)(__maze, *__celli_ptr, *__cellj_ptr - 2) ) {

                    if (TYPED(Matrix_at)(__maze, *__celli_ptr, *__cellj_ptr - 2) != -1) {
                        TYPED(Matrix_set)(__maze, *__celli_ptr, *__cellj_ptr - 1, 0);
                        // then this cell is unvisited, set cell coordinates for the next cell
                        *__cellj_ptr -= 2;
                        return;
                    }
                }

                down_checked = true;
                break;

            case 4:

                if (TYPED(Matrix_valid_bounds)(__maze, *__celli_ptr, *__cellj_ptr + 2) ) {

                    if (TYPED(Matrix_at)(__maze, *__celli_ptr, *__cellj_ptr + 2) != -1) {
                        TYPED(Matrix_set)(__maze, *__celli_ptr, *__cellj_ptr + 1, 0);
                        // then this cell is unvisited, set cell coordinates for the next cell
                        *__cellj_ptr += 2;
                        return;
                    }
                }

                up_checked = true;
                break;

        }

        // printf("Can't choose cell\n");

    }
}


Cell *Cell_new(size_t __i, size_t __j) {

    Cell *cell = malloc(sizeof(Cell));

    if(cell) {

        cell->i = __i;
        cell->j = __j;
        cell->below = NULL;

    }

    return cell;

}

void CellStack_push(CellStack *__stack, Cell *__cell) {

    if(__stack->top) {
        __cell->below = __stack->top;
    } else {
        __cell->below = NULL;
    }
    __stack->top = __cell;

}

Cell *CellStack_pop(CellStack *__stack) {

    if(__stack->top) {

        Cell *cell = __stack->top;
        __stack->top = __stack->top->below;
        cell->below = NULL;
        return cell;

    } else {
        return NULL;
    }
}

void generate_path(TYPED(Matrix) *__maze, CellStack *__stack, size_t __celli, size_t __cellj) {

    // printf("Entered cell (%lu, %lu)\n", __celli, __cellj);

    TYPED(Matrix_set)(__maze, __celli, __cellj, -1); // mark the cell as visitedj

    size_t next_celli = __celli;
    size_t next_cellj = __cellj;

    while (cell_has_unvisited_neighbors(__maze, __celli, __cellj)) {

        choose_next_cell(__maze, &next_celli, &next_cellj);
        CellStack_push(__stack, Cell_new(next_celli, next_cellj));

        // printf("Next i: %lu, next j: %lu\n", next_celli, next_cellj);
        // printf("__celli = %lu, __cellj = %lu\n", __celli, __cellj);

        if (!(next_celli == __stack->top->below->i && next_cellj == __stack->top->below->j)) {
            generate_path(__maze, __stack, next_celli, next_cellj);
        } else {

            if (__stack->top) {
                CellStack_pop(__stack);
                generate_path(__maze, __stack, __stack->top->i, __stack->top->j);
            }

            break;
        }

        // printf("Cell hase unvisited neighbors\n");
        // print_matrix_as_lab(__maze);

    }


    // else go back to the previous cell

    // while (cell_has_unvisited_neighbors(__maze, __celli, __cellj)){
    //     choose_next_cell(__maze, &next_celli, &next_cellj);
    //     generate_path(__maze, next_celli, next_cellj);
    // }


}

TYPED(Matrix) *create_maze(size_t __nrows, size_t __ncols) {

    // create cell stack
    CellStack *stack = (CellStack *) malloc(sizeof(CellStack));

    // start searching from the point (1, 1);

    Cell *cell = Cell_new(1, 1);
    CellStack_push(stack, cell);


    // Start by making a matrix that is composed of cells
    TYPED(Matrix) *maze = TYPED(Matrix_value)(__nrows*2 + 1, __ncols*2 + 1, 1);
    // Open up the cells
    for (size_t i = 1; i < __nrows*2; i += 2) {
        for (size_t j = 1; j < __ncols*2; j += 2) {

            TYPED(Matrix_set)(maze, i, j, 0);

        }
    }


    printf("Generating path...\n");
    generate_path(maze, stack, 1, 1);

    return maze;
}




// When given a maze, determine if there is an open path from (1,1) to the bottom right corner
bool chercher_chemin(TYPED(Matrix) *__maze, size_t __starti, size_t __startj) {





    return true;

}