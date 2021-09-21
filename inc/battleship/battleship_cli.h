#ifndef BATTLESHIP_CLI
#define BATTLESHIP_CLI

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "battleship_board.h"

// sleep for __s seconds
void dsleep(double __s) {

    usleep(1E6 * __s);

}

int index_letters(char c) {

    int index = -1;

    for(int i = 0; i < 10; i ++) {
        if (LETTERS[i] == c) {
            return i;
        }
    }

    return index;

}

uint32_t get_row_index() {

    bool is_valid_input = false;

    // printf("Please enter the letter of the row to select\n");

    int index;

    while(!is_valid_input) {

        char c = '0';
        int ret = scanf("%c", &c);

        if (ret != 1) {
            printf("input not recognized, please enter a valid character\n");
            continue;
        }

        if (c == '\n' || c == ' ') {
            continue;
        }

        // printf("Input as char = %c, input as decimal = %d\n", c, c);

        index = index_letters(c);

        if (index == -1) { // Then the input value is NOT in letters
            printf("%c not contained in [A-I], please enter a character in [A-I]\n", c);
            continue;
        } else {
            is_valid_input = true;
            break;
        }
    }

    return index;
}

uint32_t get_col_index() {

    bool is_valid_input = false;

    // printf("Please enter the number of the col to select\n");

    int d = 0;

    while(!is_valid_input) {

        int ret = scanf("%d", &d);

        if (ret != 1) {
            printf("input not recognized, please enter a valid integer\n");
            continue;
        }

        if (d < 1 || d > 10) { // Then the input value is NOT in [1-10]
            printf("%d not contained in [1-10], please enter an integer in [1-10]\n", d);
            continue;
        } else {
            is_valid_input = true;
            break;
        }
    }

    return d - 1;
}

void player_turn(DockingStation * ds) {
// Prompt the user for a location in the form of 'A8' and process that information

    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t value = 0;
    bool turn_over = false;

    while(!turn_over) {
        // get guess
        i = get_row_index();
        j = get_col_index();
        value = ds->board[i*10 + j];

        if ( is_attempted(value) ) {
            printf("You already tried this location, try again\n");
            continue;
        } else if ( is_occupied(value) ) { // We got a hit!!!

            printf("Hit. ");
            ds->board[i*10 + j] += (HIT + ATTEMPTED);

            if ( is_carrier(value) ) {
                ds->carrier_lives_left --;

                if ( ds->carrier_lives_left == 0 ) {
                    printf("You've sunk my carrier!!!\n");
                } else {
                    printf("Carrier\n");
                }
            } else if ( is_battleship(value) ) {
                ds->battleship_lives_left --;

                if ( ds->battleship_lives_left == 0 ) {
                    printf("You've sunk my battleship!!!\n");
                } else {
                    printf("Battleship\n");
                }
            } else if ( is_cruiser(value) ) {
                ds->cruiser_lives_left --;

                if ( ds->cruiser_lives_left == 0 ) {
                    printf("You've sunk my cruiser!!!\n");
                } else {
                    printf("Cruiser\n");
                }
            } else if ( is_submarine(value) ) {
                ds->submarine_lives_left --;

                if ( ds->submarine_lives_left == 0 ) {
                    printf("You've sunk my submarine!!!\n");
                } else {
                    printf("Submarine\n");
                }
            } else if ( is_destroyer(value) ) {
                ds->destroyer_lives_left --;

                if ( ds->destroyer_lives_left == 0 ) {
                    printf("You've sunk my destroyer!!!\n");
                } else {
                    printf("Destroyer\n");
                }
            }

        } else { // Then we missed!

            printf("Miss!\n");
            ds->board[i*10 + j] += (MISS + ATTEMPTED);

        }

        turn_over = true;
    }
}

void enemy_turn() {

    printf("Waiting for enemy");

    // for (int i = 0; i < 5; i ++) {
    //     printf(".");
    //     dsleep(0.5);
    // }

    printf("\n");


}

bool is_game_over(DockingStation ds) {

    return (ds.carrier_lives_left == 0 && ds.battleship_lives_left == 0 && ds.cruiser_lives_left == 0 &&
            ds.submarine_lives_left == 0 && ds.destroyer_lives_left == 0);
}

void step(DockingStation * ds) {

    print_full_board(ds->board);
    printf("Please make a selection: ");
    player_turn(ds);
    enemy_turn();

}

void play_game(DockingStation * ds) {

    while ( !is_game_over(*ds) ) {

        step(ds);

    }

}



#endif

