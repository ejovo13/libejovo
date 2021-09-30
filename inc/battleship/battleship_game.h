#ifndef BATTLESHIP_GAME
#define BATTLESHIP_GAME

#include "battleship_ai.h"
#include "battleship_board.h"
#include "battleship_cli.h"

void step(DockingStation * player_ds, DockingStation * enemy_ds, AI * ai) {


    printf("Please make a selection: ");
    player_turn(enemy_ds);
    dsleep(0.75);
    clear_screen();
    print_docking_station(player_ds, enemy_ds);
    printf("AI's turn\n");
    for (int i = 0; i < 3; i ++) {
        puts(".");
        dsleep(0.25);
    }

    int * ai_selection;
    ai_turn(ai);
    // printf("AI selection: ");
    // printf("%c%d\n", LETTERS[ai_selection[0]], ai_selection[1] + 1);
    dsleep(1.5);

    clear_screen();
    print_docking_station(player_ds, enemy_ds);
    // printf("Enemy screen: \n\n");
    // print_full_board(enemy_ds->board);

}

void play_game(DockingStation * player_ds, DockingStation * enemy_ds) {

    xor_rng rng;
    seed_xoshiro256ss(&rng);
    seed_xoshiro256ss(&XOSHIRO_RNG);

    // print_xoshiro256ss_state(&XOSHIRO_RNG);

    // dsleep(2.5);
    AI ai = {0, 0, 0, false, player_ds, enemy_ds};
    ai_place_ships(&ai);


    printf("WELCOME TO THE GAME \n\n");

    // print_full_board(ds->board);



    // get_player_placement(player_ds);

    clear_screen();

    printf("Awesome!! Now are you ready to get fucked up by the AI???\n\n");
    dsleep(0.5);
    clear_screen();
    print_docking_station(player_ds, enemy_ds);

    while ( !is_game_over(*player_ds) && !is_game_over(*enemy_ds)) {

        step(player_ds, enemy_ds, &ai);

    }

}

#endif