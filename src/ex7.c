#define MATRIX_TYPE int

#include "ejovo_matrix.h"
#include "ejovo_labyrinth.h"

int main() {

    ejovo_seed();

    Matrix *maze = create_maze(20, 50);
    print_matrix_as_lab(maze);

    printf("Does the maze have a solution?\n");



    return 0;
}
