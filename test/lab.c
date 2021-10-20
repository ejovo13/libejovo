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

    printf("\n");
    M = create_maze(1, 20);
    print_matrix_as_lab(M);



    // Matrix *M2 = Matrix_from(piece_array(0, 1, 1, 1, 0, 1, 1, 1, 0), 3, 3);

    // for (int i = 0; i < 5; i++) {

    //     printf("A^{%d}:\n", i);
    //     Matrix_print(Matrix_pow(M2, i));

    // }

    // printf("======================\n\n");
    // for (int i = 0; i < 15; i++) {

    //     Matrix_print(get_piece_matrix(get_open_matrix(RIGHT)));


    // }





    return 0;
}