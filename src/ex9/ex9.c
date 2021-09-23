//// Bataille navale simple
// Bataille navale COMPLEXE

// les bateaux sont tous de longcuer 1

// 11 points au jouer

// fabriquer une grille 4 x 4 et choisir au hasard 5 cases pour mettre les bateaux

#include "ejovo_print.h"
#include "ejovo_rand.h"
#include "battleship_cli.h"
#include "battleship_board.h"
#include "battleship_ai.h"


int main() {

    // create board


    DockingStation enemy_station = make_new_game(BOARD_SIZE);
    DockingStation player_stations = make_new_game(BOARD_SIZE);

    // TODO Create AI
    // TODO Add pretty introduction
    // TODO Add pretty end
    // TODO Add salvo game mode


    // place_carrier(5, 5, 'N', board);
    // place_battleship(2, 2, 'S', board);
    // place_cruiser(9, 9, 'W', board);
    // place_submarine(0, 2, 'E', board);
    // place_destroyer(7, 8, 'E', board);

    play_game(&enemy_station);

    return 0;
}