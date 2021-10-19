#include "ejovo_labyrinth.h"
#include "ejovo_matrix.h"

int main() {

    LabPiece *p = get_piece(H_PIPE);

    ejovo_seed();

    Matrix *M = Matrix_random(10, 10, 0, 1);

    p = get_piece_from_matrix(M, 3, 2);

    // print_piece(p);
    // print all pieces

    for (int i = 0; i < 11; i++) {

        p = get_piece(i);
        print_piece(p, 3);
        printf("\n");

    }

    print_matrix_as_lab(M);

    M = create_checkerboard(15, 50);
    print_matrix_as_lab(M);
    // Matrix_print(M);


    return 0;
}