#ifndef BATTLESHIP_AI
#define BATTLESHIP_AI

#include <stdbool.h>
#include <stdint.h>
#include "battleship_board.h"
#include "battleship_cli.h"
#include "ejovo_rand.h"

// Define all the functions needed by an enemy AI (artifical intelligence)

typedef struct AI {

    int last_i;
    int last_j;
    int last_direction;
    bool last_success;
    DockingStation * human_ds;
    DockingStation * ai_ds;

} AI;


// need a way to place all of the ships
void ai_place_ships(AI * ai) {
// Basic algorithm to have the ai choose a ship placement.

// Before I implement the placement stage, I want to get a random list of positions that have at least
// one valid direction

// that is way fucking overkill, I literally just need to get a random position and check to make sure
// there is at least one direction in which I can place a ship.

    Board board = ai->ai_ds->board;

    int irow = 0, jcol = 0, num_valid_directions = 0, direction = 0;
    char * cptr = NULL;

    // place the ship, but the first ship has free choice for a number on the board.
    for (int i = 0; i < NUM_SHIPS; i ++) {

        num_valid_directions = 0;

        // randomly decide a position that has at least one direction to go to.
        while(num_valid_directions == 0) {

            irow = unif(0, NUM_SHIPS-1);
            jcol = unif(0, NUM_SHIPS-1);

            // check to see if the position is valid
            cptr = get_valid_directions(board, irow, jcol, SHIP_LENGTHS[i], &num_valid_directions);

        }

        // randomly choose one of the directions
        direction = unif(0, num_valid_directions - 1);
        place_ship(irow, jcol, cptr[direction], board, SHIP_TYPES[i], SHIP_LENGTHS[i]);
        printf("[AI]\t placed ship %s at %c%d with orientation %c\n", SHIP_FULL_NAMES[i], LETTERS[irow], NUMBERS[jcol], cptr[direction]);

    }

    printf("[AI]\t placed all ships!\n\n");

}

// char * AI_DIRECTIONS = NULL; // List of directions that AI has attempted already
// bool LAST_SUCCESS = false; // Boolean to keep track of last attempt
// int LAST_SHIP = -1; // Last ship that I hit

uint8_t ai_choose_direction(AI * ai, int * __i, int * __j) {
// choose a tile and return its value
    // First branch is "did I get a hit last time?"
    int i_choice = 0, j_choice = 0;
    Board human_board = ai->human_ds->board;
    // If I got a hit, follow this algorithm
    if (ai->last_success) {

        puts("WE GOT A HIT!!!! WHAT TO DO NOW???");
        dsleep(5);

        return 0;

    } else { // If I missed, choose a position randomly


        // printf("Choosing direction with rng seeded:\n");
        // print_xoshiro256ss_state(&XOSHIRO_RNG);

        i_choice = unif(0, BOARD_SIZE - 1);
        j_choice = unif(0, BOARD_SIZE - 1);

        // printf("Chose i: %d\tChose j: %d\n", i_choice, j_choice);

        while ( is_attempted(human_board[i_choice * BOARD_SIZE + j_choice] )) {
            i_choice = unif(0, BOARD_SIZE - 1);
            j_choice = unif(0, BOARD_SIZE - 1);
            // puts("This location has already been attempted");
        }

        *__i = i_choice;
        *__j = j_choice;
        return human_board[i_choice * BOARD_SIZE + j_choice];

    }

}


// Find the location of a ship type that isnt blown up.
void cheat() {




}


// need a way to attack the players ships. Pass the player turn as the value for the AI to attack
// return the string of the choice
void ai_turn(AI * ai) {
// start off by randomly attacking the enemy ships and seeing if i get a hit or not.

    DockingStation * ds = ai->human_ds;
    // printf("\n\n AI'S TURN!!! \n\n");

    int i = 0, j = 0, value = 0;
    bool turn_over = false;

    // int * ai_selection = (int *) malloc(sizeof(int) * 2);

    while (!turn_over) {

        // Guess the position completely randomly..., let's go ahead and choose this way smarter

        value = ai_choose_direction(ai, &i, &j);

        if ( is_occupied(value) ) { // We got a hit!!!

            printf("%c%d\n", LETTERS[i], j + 1);
            puts("");
            dsleep(0.15);


            printf("Hit. ");
            ds->board[i*10 + j] += (HIT + ATTEMPTED);
            ai->last_success = true;

            if ( is_carrier(value) ) {
                ds->carrier_lives_left --;

                if ( ds->carrier_lives_left == 0 ) {
                    printf("AI sunk my carrier!!!\n");
                } else {
                    printf("Carrier\n");
                }
            } else if ( is_battleship(value) ) {
                ds->battleship_lives_left --;

                if ( ds->battleship_lives_left == 0 ) {
                    printf("AI sunk my battleship!!!\n");
                } else {
                    printf("Battleship\n");
                }
            } else if ( is_cruiser(value) ) {
                ds->cruiser_lives_left --;

                if ( ds->cruiser_lives_left == 0 ) {
                    printf("AI sunk my cruiser!!!\n");
                } else {
                    printf("Cruiser\n");
                }
            } else if ( is_submarine(value) ) {
                ds->submarine_lives_left --;

                if ( ds->submarine_lives_left == 0 ) {
                    printf("AI sunk my submarine!!!\n");
                } else {
                    printf("Submarine\n");
                }
            } else if ( is_destroyer(value) ) {
                ds->destroyer_lives_left --;

                if ( ds->destroyer_lives_left == 0 ) {
                    printf("AI sunk my destroyer!!!\n");
                } else {
                    printf("Destroyer\n");
                }
            }

        } else { // Then we missed!

            printf("%c%d\n", LETTERS[i], j + 1);

            printf("Miss!\n");
            ds->board[i*10 + j] += (MISS + ATTEMPTED);
            ai->last_success = false;

        }
        turn_over = true;
        ai->last_i = i;
        ai->last_j = j;
    }

    // ai_selection[0] = i;
    // ai_selection[1] = j;

    // return ai_selection;

}










#endif