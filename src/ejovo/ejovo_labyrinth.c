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
                matcpyele(m, i*3, i*3 + 2, j*3, j*3 + 2, get_piece_matrix(get_rand_int_range(0, 10)));
                // printf("i = %lu, j = %lu\n", i, j);
            }
        }
    } else {
        perror("Matrix not initialised\n");
    }

    return m;
}

Matrix *create_maze(size_t __nrows, size_t __ncols) {

    // Set the border of the checkerboard




}




















