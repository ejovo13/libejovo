#include "ejovo_labyrinth.h"
#include "stdbool.h"

#define MATRIX_TYPE long


// Using this for a piece that is 3x3
long *piece_array(long __1, long __2, long __3, long __4, long __5, long __6, long __7, long __8, long __9) { // Don't even ask

    long *arr = (long *) malloc(sizeof(long) * 9);

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
Matrix *get_piece_matrix(PIECE_TYPE __t) {

    long *data = {0};

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

    return Matrix_from(data, 3, 3);
}

LabPiece *get_piece(PIECE_TYPE __t) {

    LabPiece *p = malloc(sizeof(LabPiece));
    if(p) {
        p->mat = get_piece_matrix(__t);
        p->type = __t;
    }

    return p;
}

LabPiece *get_piece_from_matrix(Matrix *__m, size_t __i, size_t __j) {

    LabPiece *p = malloc(sizeof(LabPiece));
    if(p) {
        p->mat = Matrix_submat(__m, __i, __i+2, __j, __j+2);
        p->type = OTHER;
    }

    return p;

}

void print_piece(LabPiece *__p, size_t __n) {

    for (size_t i = 0; i < __n; i++) {
        for (size_t j = 0; j < __n; j++) {
            if(Matrix_at(__p->mat, i, j)) {
                printf("@");
            } else {
                printf(" ");
            }

        }
        printf("\n");
    }
}

void print_matrix_as_lab(Matrix *__m) {

    for (size_t i = 0; i < __m->nrows; i++) {
        for (size_t j = 0; j < __m->ncols; j++) {

            if(Matrix_at(__m, i, j)) {
                printf("@");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
// Place a LabPiece at a given index of a matrix
void place_piece(Matrix *__m, PIECE_TYPE __t, size_t __i, size_t __j) {

    matcpyele(__m, __i*3, __i*3 + 2, __j*3, __j*3 + 2, get_piece_matrix(__t));

}

Matrix *create_checkerboard(size_t __nrows, size_t __ncols) {
    if (__nrows < 0 || __ncols < 0) {
        perror("Cannot instantiate new checkerboard with 0 rows/cols\n");
        return NULL;
    }

    // printf("Creating a checkerboard %lu x %lu\n", __nrows*3, __ncols*3);

    Matrix *m = Matrix_new(__nrows * 3, __ncols * 3);



    if(m) {
        for (size_t i = 0; i < __nrows; i++) {
            for (size_t j = 0; j < __ncols; j++) {
                // matcpyele(m, i*3, i*3 + 2, j*3, j*3 + 2, get_piece_matrix(unif(0, 10)));
                place_piece(m, unif(0,10), i, j);
                // printf("i = %lu, j = %lu\n", i, j);
            }
        }
    } else {
        perror("Matrix not initialised\n");
    }

    return m;
}

void set_border_elements(Matrix *__m, size_t __jtop, size_t __jbot) {

    // set all of the elements to 1 besides (__i1, __j1) and (__i2, __j2)
    for (size_t i = 0; i < __m->nrows; i++) {

        if (i == 0 || i == __m->nrows - 1) { // if we are dealing with the first or last rows

            for (size_t j = 0; j < __m->ncols; j++) { // iterate through each column
                if (j == __jtop && i == 0) {
                    Matrix_set(__m, i, j, 0);
                    continue;
                } else if ( j == __jbot && i == __m->nrows - 1) {
                    Matrix_set(__m, i, j, 0);
                    continue;
                } else {
                    Matrix_set(__m, i, j, 1);
                }
            }
        }

        Matrix_set(__m, i, 0, 1);
        Matrix_set(__m, i, __m->ncols - 1, 1);

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

        rand_piece = unif(0, 10);

    } while (! is_piece_open(rand_piece, __d));

    return rand_piece;
}

// return the type of a random piece that is open to the d direction
PIECE_TYPE get_open_piece_type_2(DIRECTION __d1, DIRECTION __d2) {

    int rand_piece = 11;

    do {

        rand_piece = unif(0, 10);

    } while (!is_piece_open(rand_piece, __d1) || !is_piece_open(rand_piece, __d2));

    return rand_piece;
}




// Create a path through the matrix from the top to the bottom
void create_path(Matrix *__m, size_t __start_j, size_t __end_j) {

    // start by choosing an initial piece that has an opening through the top

    for(size_t i = 0; i < __m->ncols/3; i++) {

        place_piece(__m, i, i*3, get_open_piece_type_2(RIGHT, LEFT));

    }
}






Matrix *create_maze(size_t __nrows, size_t __ncols) {

    // Set the border of the checkerboard

    Matrix *M = create_checkerboard(__nrows, __ncols);
    place_piece(M, CROSS, 0, 0);
    create_path(M, 0, 0);
    set_border_elements(M, 1, __ncols * 3 - 2);
    return M;


}




















