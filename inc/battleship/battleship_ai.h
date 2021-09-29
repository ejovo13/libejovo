#ifndef BATTLESHIP_AI
#define BATTLESHIP_AI

#include <stdbool.h>
#include <stdint.h>
#include "battleship_board.h"
#include "ejovo_rand.h"

// Define all the functions needed by an enemy AI (artifical intelligence)


// need a way to place all of the ships
void ai_place_ships(Board board) {
// Basic algorithm to have the ai choose a ship placement.

// Before I implement the placement stage, I want to get a random list of positions that have at least
// one valid direction

// that is way fucking overkill, I literally just need to get a random position and check to make sure
// there is at least one direction in which I can place a ship.

    int irow = 0, jcol = 0, num_valid_directions = 0, direction = 0;
    char * cptr = NULL;

    // place the ship, but the first ship has free choice for a number on the board.
    for (int i = 0; i < NUM_SHIPS; i ++) {

        num_valid_directions = 0;

        // randomly decide a position that has at least one direction to go to.
        while(num_valid_directions == 0) {

            irow = get_rand_int_range(0, NUM_SHIPS-1);
            jcol = get_rand_int_range(0, NUM_SHIPS-1);

            // check to see if the position is valid
            cptr = get_valid_directions(board, irow, jcol, SHIP_LENGTHS[i], &num_valid_directions);

        }

        // randomly choose one of the directions
        direction = get_rand_int_range(0, num_valid_directions - 1);
        place_ship(irow, jcol, cptr[direction], board, SHIP_TYPES[i], SHIP_LENGTHS[i]);
        printf("[AI]\t placed ship %s at %c%d with orientation %c\n", SHIP_FULL_NAMES[i], LETTERS[irow], NUMBERS[jcol], cptr[direction]);

    }

    printf("[AI]\t placed all ships!\n\n");

}

// need a way to attack the players ships
void ai_turn(Board board) {
// start off by randomly attacking the enemy ships and seeing if i get a hit or not.





}










#endif