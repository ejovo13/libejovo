// Loto
//
// Rempli le premier tableau de 6 entiers entre 1 et 49
//
//

#include "ejovo_rand.h"
#include "ejovo_print.h"
#include <stdbool.h>

#define MAX_VALUE 49

int main() {

    ejovo_seed(); // Use my seeding function
    // get 6 random numbers between 1 and MAX_VALUE and make sure that there are no duplicates
    int random_number;
    int loto[6] = {0};
    int player_input[6] = {0};
    bool duplicate = false;

    loto[0] = unif(1, MAX_VALUE);
    for (int i = 1; i < 6; i ++) {

        do {

            duplicate = false;

            random_number = unif(1, MAX_VALUE);

            for (int j = 0; j < i; j ++) {
                if ( random_number == loto[j] ) {
                    // we have a duplicate, break out of this loop and get another one
                    duplicate = true;
                    break;
                } else {
                    continue;
                }
            }


        } while ( duplicate );

        loto[i] = random_number;
    }

    printf("We have finished selecting the 6 random values!\n");

    print_int_array(loto, 6);

    int user_value = 0;
    duplicate = false;

    printf("Please enter 6 integers in [1-%d] separated by a space or a new line!\n\n", MAX_VALUE);

    // Let's get some user input and validate that the value has not appeared in the array.
    for (int i = 0; i < 6; i ++) {

        do {

            duplicate = false;

            scanf("%d", &user_value);

            if ( user_value < 1 || user_value > MAX_VALUE) {
                printf("Value entered is not between 1 and %d. Value not recorded\n", MAX_VALUE);
                printf("Please enter a valid integer between 1 and %d\n", MAX_VALUE);
            }

            for (int j = 0; j < i; j ++) {
                if ( user_value == player_input[j] ) {
                    // we have a duplicate, break out of this loop and get another one
                    duplicate = true;
                    break;
                } else {
                    continue;
                }
            }


        } while ( duplicate );

        player_input[i] = user_value;
    }

    // printf("Finished gathering human input!\n");

    // Check to see if the player won or not

    bool won = false;

    for (int i = 0; i < 6; i ++) {

        if ( loto[i] != player_input[i] ) {
            won = false;
            break;
        }

        won = true;

    }

    if (won) {
        printf("You won!! Congrats!! Here's a cookie...\n\n");
    } else {
        printf("You are a loser!!\n\n");
    }






    return 0;
}