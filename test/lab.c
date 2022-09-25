#include "ejovo_labyrinth.h"
#include "ejovo_matrix_generic.h"

int main() {

    ejovo_seed(); // needs to be called before any functions that use random variables

    // print_matrix_as_lab(maze);


    TYPED(Matrix) *maze = create_maze(20, 50);
    // generate_path(maze, 1, 1);
    print_matrix_as_lab(maze);

    TYPED(Matrix_reset)(&maze);


    return 0;
}