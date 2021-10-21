// -- Ecrire une fonction qui demande a l'utilisateur le nombre de lignes et de colonnes d'une matrices d'entiers
// puis remplit la matrice en demandant les valeurs a l'utilisateur.
// -- Ecrire une fonction affiche_mat(m,l,c) qui permet d'afficher une matrice m de l lignes et c colonnes

typedef int MatrixElement;
typedef MatrixElement * Matrix;


#include "ejovo_input.h"
#include <stdlib.h>


void set_row_col(MatrixElement * __e1, MatrixElement * __e2) {

    int temp_i = 0, temp_j = 0;

    // get row
    printf("Choose number of rows > 0\n");
    do {
        temp_i = get_int();
    } while ( temp_i < 1 );
    // get column
    printf("Choose number of cols > 0\n");
    do {
        temp_j = get_int();
    } while ( temp_j < 1 );

    *__e1 = temp_i;
    *__e2 = temp_j;

}

// First prompt the user for the number of columns and rows
Matrix rempli_matrix(int __nrows, int __ncols) {

    Matrix A = (Matrix) malloc(sizeof(MatrixElement) * (__nrows * __ncols));
    if (A) {

        printf("\n %d x %d matrix created. Please fill the matrix in row major order with elements separated by spaces.\n", __nrows, __ncols);

        for (int i = 0; i < __nrows; i++) {
            for (int j = 0; j < __ncols; j++) {
                A[i*__ncols + j] = get_int();
            }
            if (i != __nrows - 1)
                printf("\n... row %d filled ...\n", i + 1);
        }
        printf("Matrix completely filled!\n");
    }
    return A;
}

void affiche_mat(Matrix __m, size_t __nrows, size_t __ncols) {

    for (size_t j = 0; j < __ncols; j++) {
        printf("| ");
        for (size_t i = 0; i < __nrows; i++) {
            printf("%3d ", __m[i*__ncols + j]);
        }

        printf("|\n");
    }
}

int main() {

    int nrows = 0, ncols = 0;
    // Get rows and columns from user input
    set_row_col(&nrows, &ncols);
    // create and fill a new matrix based on user input
    Matrix A = rempli_matrix(nrows, ncols);
    // print matrix to screen
    affiche_mat(A, nrows, ncols);

    return 0;
}