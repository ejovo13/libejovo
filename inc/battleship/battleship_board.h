#ifndef BATTLESHIP_BOARD
#define BATTLESHIP_BOARD

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t * Board;

const uint8_t CARRIER =     0b00000001;
const uint8_t BATTLESHIP =  0b00000010;
const uint8_t CRUISER =     0b00000100;
const uint8_t SUBMARINE =   0b00001000;
const uint8_t DESTROYER =   0b00010000;
const uint8_t ATTEMPTED =   0b00100000; // did we already try and shoot here?
const uint8_t MISS =        0b01000000;
const uint8_t HIT =         0b10000000;

const int NUM_SHIPS = 5;
const int BOARD_SIZE = 10;

const int CARRIER_LENGTH = 5;
const int BATTLESHIP_LENGTH = 4;
const int CRUISER_LENGTH = 3;
const int SUBMARINE_LENGTH = 3;
const int DESTROYER_LENGTH = 2;

const char LETTERS[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
const int NUMBERS[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const char DIRECTIONS[4] = {'N', 'E', 'S', 'W'};
const uint8_t SHIP_TYPES[5] = {CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER};
const int SHIP_LENGTHS[5] = {CARRIER_LENGTH, BATTLESHIP_LENGTH, CRUISER_LENGTH, SUBMARINE_LENGTH, DESTROYER_LENGTH};
const char SHIP_LETTERS[5] = {'C', 'B', 'R', 'S', 'D'};
const char SHIP_FULL_NAMES[5][15] = {"CARRIER", "BATTLESHIP", "CRUISER", "SUBMARINE", "DESTROYER"};

typedef struct DockingStation { // Docking station contains information about the board, how many lives are left

    Board board;
    uint8_t carrier_lives_left;
    uint8_t battleship_lives_left;
    uint8_t cruiser_lives_left;
    uint8_t submarine_lives_left;
    uint8_t destroyer_lives_left;

} DockingStation;

DockingStation make_new_game(int size) {

    DockingStation d;

    Board board = (Board) malloc( sizeof(uint8_t) * (size * size) );

    // initialize board
    for (int i = 0; i < size; i ++) {
        for (int j = 0; j < size; j ++) {
            board[i * size + j] = 0;
        }
    }

    d.board = board;
    d.carrier_lives_left = CARRIER_LENGTH;
    d.battleship_lives_left = BATTLESHIP_LENGTH;
    d.cruiser_lives_left = CRUISER_LENGTH;
    d.submarine_lives_left = SUBMARINE_LENGTH;
    d.destroyer_lives_left = DESTROYER_LENGTH;

    return d;

}

// Provide functions to create a new board, keep track of the board, print the board, etc

// Implement the board

// The board must be a 10x10 2-dimensional array of unsigned integers.

/**==============================================
 *
 *
 *
 *          Functions concerning the occupancy
 *          state of a location
 *
 *
 *=============================================**/

// is_carrier
bool is_carrier(uint8_t flag) {
    return (flag & CARRIER) == CARRIER;
}

// is_battleship
bool is_battleship(uint8_t flag) {
    return (flag & BATTLESHIP) == BATTLESHIP;
}

// is_cruiser
bool is_cruiser(uint8_t flag) {
    return (flag & CRUISER) == CRUISER;
}

// is_submarine
bool is_submarine(uint8_t flag) {
    return (flag & SUBMARINE) == SUBMARINE;
}
// is_destroyer
bool is_destroyer(uint8_t flag) {
    return (flag & DESTROYER) == DESTROYER;
}
// is_attempted
bool is_attempted(uint8_t flag) {
    return (flag & ATTEMPTED) == ATTEMPTED;
}
// is_miss
bool is_miss(uint8_t flag) {
    return (flag & MISS) == MISS;
}

bool is_hit(uint8_t flag) {
    return (flag & HIT) == HIT;
}

bool is_occupied(uint8_t flag) {
    return (is_carrier(flag) || is_battleship(flag) || is_cruiser(flag) || is_submarine(flag) || is_destroyer(flag));
}

/**========================================================================
 *                             Functions to place the ships
 *
 *  ERRORS MUST BE HANDLED BEFORE CALLING PLACE_SHIP FUNCTIONS
 *  these functions WILL NOT CHECK if the placements are valid
 *
 *========================================================================**/
void set_direction(int * i_ptr, int * j_ptr, char direction) {

    // printf("Setting direction: %c\n", direction);

    switch(direction) {
        case 'N':
            *i_ptr = -1;
            *j_ptr = 0;
            // printf("N matched\n");
            break;
        case 'E':
            *i_ptr = 0;
            *j_ptr = 1;
            // printf("E matched\n");
            break;
        case 'S':
            *i_ptr = 1;
            *j_ptr = 0;
            // printf("S matched\n");
            break;
        case 'W':
            *i_ptr = 0;
            *j_ptr = -1;
            // printf("W matched\n");
            break;
    }

    // printf("set *i_ptr = %d, *j_ptr = %d\n", *i_ptr, *j_ptr);

}

void place_ship(int i, int j, char direction, Board board, uint8_t ship_type, int ship_length) {

    int i_inc = 0;
    int j_inc = 0;

    set_direction(&i_inc, &j_inc, direction);

    // printf("Placing ship with length %d in direction %c\n", ship_length, direction);
    // printf("i_inc = %d, j_inc = %d\n", i_inc, j_inc);

    for(int n = 0; n < ship_length; n ++) {

        board[i*BOARD_SIZE + j] += ship_type;
        i += i_inc;
        j += j_inc;

    }
}

void place_carrier(int i, int j, char direction, Board board) {
    place_ship(i, j, direction, board, CARRIER, CARRIER_LENGTH);
}

void place_battleship(int i, int j, char direction, Board board) {
    place_ship(i, j, direction, board, BATTLESHIP, BATTLESHIP_LENGTH);
}

void place_cruiser(int i, int j, char direction, Board board) {
    place_ship(i, j, direction, board, CRUISER, CRUISER_LENGTH);
}

void place_submarine(int i, int j, char direction, Board board) {
    place_ship(i, j, direction, board, SUBMARINE, SUBMARINE_LENGTH);
}

void place_destroyer(int i, int j, char direction, Board board) {
    place_ship(i, j, direction, board, DESTROYER, DESTROYER_LENGTH);
}

bool validate_placement(int i, int j, char direction, Board board, int ship_length) {

    // printf("VALIDATING_PLACEMENT of i = %d, j = %d, dir = %c, len = %d\n", i, j, direction, ship_length);

    int i_inc = 0;
    int j_inc = 0;

    set_direction(&i_inc, &j_inc, direction);

    // if any of the indexes would go out of bounds
    if (i + (ship_length - 1) * i_inc > (BOARD_SIZE - 1) || i + (ship_length - 1) * i_inc < 0 || j + (ship_length - 1) * j_inc > (BOARD_SIZE - 1) || j + (ship_length - 1) * j_inc < 0) {
        return false;
    }

    // if any of the spots in that direction are occupied
    for(int n = 0; n < ship_length; n ++) {

        // printf("Checking if %c%d is occupied\n", LETTERS[i], NUMBERS[j]);
        if( is_occupied(board[i*BOARD_SIZE + j]) ) {
            return false;
        }
        i += i_inc;
        j += j_inc;
    }

    // If none of the previous conditions are met, return true;
    return true;
}

// bool validate_carrier(int i, int j, char direction, uint8_t * board) {
//     return validate_placement(i, j, direction, board, CARRIER, CARRIER_LENGTH);
// }

// bool validate_battleship(int i, int j, char direction, uint8_t * board) {
//     return validate_placement(i, j, direction, board, BATTLESHIP, BATTLESHIP_LENGTH);
// }

// bool validate_cruiser(int i, int j, char direction, uint8_t * board) {
//     return validate_placement(i, j, direction, board, CRUISER, CRUISER_LENGTH);
// }

// bool validate_submarine(int i, int j, char direction, uint8_t * board) {
//     return validate_placement(i, j, direction, board, SUBMARINE, SUBMARINE_LENGTH);
// }

// bool validate_destroyer(int i, int j, char direction, uint8_t * board) {
//     return validate_placement(i, j, direction, board, DESTROYER, DESTROYER_LENGTH);
// }


// print board
void print_full_board(Board board) {

    char c = '-';

    printf("  ");

    for(int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", NUMBERS[i]);
    }

    printf("\n");

    for(int i = 0; i < BOARD_SIZE; i ++) {

        printf("%c ", LETTERS[i]);

        for(int j = 0; j < BOARD_SIZE; j ++) {

            if ( is_hit(board[i*BOARD_SIZE + j] ) ) {
                c = 'X';
            } else if ( is_carrier(board[i*BOARD_SIZE + j]) ) {
                c = 'C';
            } else if ( is_battleship(board[i*BOARD_SIZE + j]) ) {
                c = 'B';
            } else if ( is_cruiser(board[i*BOARD_SIZE + j]) ) {
                c = 'R';
            } else if ( is_submarine(board[i*BOARD_SIZE + j]) ) {
                c = 'S';
            } else if ( is_destroyer(board[i*BOARD_SIZE + j]) ) {
                c = 'D';
            } else if ( is_miss( board[i*BOARD_SIZE + j] ) ) {
                c = '-';
            } else {
                c = ' ';
            }

            printf("%c ", c);
        }

        printf("\n");
    }

    printf("\n");
}

char get_location_char(Board * board, int i, int j) {

    char c = '-';

    if ( is_hit(board[i*BOARD_SIZE + j] ) ) {
        c = 'X';
    } else if ( is_carrier(board[i*BOARD_SIZE + j]) ) {
        c = 'C';
    } else if ( is_battleship(board[i*BOARD_SIZE + j]) ) {
        c = 'B';
    } else if ( is_cruiser(board[i*BOARD_SIZE + j]) ) {
        c = 'R';
    } else if ( is_submarine(board[i*BOARD_SIZE + j]) ) {
        c = 'S';
    } else if ( is_destroyer(board[i*BOARD_SIZE + j]) ) {
        c = 'D';
    } else if ( is_miss( board[i*BOARD_SIZE + j] ) ) {
        c = '-';
    } else {
        c = ' ';
    }

    return c;

}

void print_docking_station(DockingStation * __left, DockingStation * __right) {
    // print your board to the left and to the right the enemy board
    char c = '-';
    char * player_board = __left->board;
    char * enemy_board = __right->board;

    printf("  ");

    for(int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", NUMBERS[i]);
    }

    // printf("\n");

    for(int i = -1; i < BOARD_SIZE; i ++) {


        if (i == -1) {
            printf("  |  ");
            for(int k = 0; k < BOARD_SIZE; k++) {
                printf("%d ", NUMBERS[k]);
            }
            printf("\n");
        } else {

            printf("%c ", LETTERS[i]);
            printf("  |  ");

            for(int j = 0; j < BOARD_SIZE; j ++) {

                c = get_location_char(player_board, i, j);
                printf("%c ", c);
            }

            for(int j = 0; j < BOARD_SIZE; j ++) {

                c = get_location_char(enemy_board, i, j);
                printf("%c ", c);

            }

            printf("\n");
        }
    }




    printf("\n");



}

#endif