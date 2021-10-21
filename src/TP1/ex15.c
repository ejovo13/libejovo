// Start the final exercise
#include "hw_printer.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

int get_rand_int(int max) {
// get random integer between 1 and max
    double x = ((double) rand()) / RAND_MAX;
    return (int) ceil(x * max);
}

int main() {

    ex(15, "Simuler l'evolution du remplissage de la salle");

    srand( time( NULL) );

    const int NB_RANG = 5;
    const int NB_PLACES = 5; // places par rang
    const int MAX_GROUPE = 12; // groupes d'au plus MAX_GROUPE personnes


    int places_left = NB_RANG * NB_PLACES;
    int places_left_in_row = NB_PLACES;
    int current_row = 1;

    int places_demandees;

    bool group_placed = false; // true when all members of a group are seated

    printf("NB_RANG = %d\n", NB_RANG);
    printf("NB_PLACES = %d\n", NB_PLACES);
    printf("MAX_GROUPE = %d\n\n", MAX_GROUPE);

    printf("Il y a %d places disponibles\n", NB_RANG * NB_PLACES);

    while( places_left > 0) {

        places_demandees = get_rand_int(MAX_GROUPE);

        // printf("rand = %d\t", places_demandees);

        if( places_demandees > places_left ) {
            printf("Group size of %d cannot be acommodated\n", places_demandees);
            break;
        }
        places_left -= places_demandees;

        printf("%d personne(s) a placer\n", places_demandees);
        group_placed = false;

        while (!group_placed) {

            if ( places_demandees == 0) break;
            if ( places_demandees >= places_left_in_row ) {

                printf("** %d personne(s) placee(s) dans la rangee %d\n", places_left_in_row, current_row);
                current_row ++;
                places_demandees -= places_left_in_row;
                places_left_in_row = NB_PLACES;
            } else {
                printf("%d personne(s) placee(s) dans la rangee %d\n", places_demandees, current_row);
                // current_row++;
                group_placed = true;
                places_left_in_row -= places_demandees;
            }

        }

        printf("Il reste %d place(s)\n", places_left);


    }



    return 0;
}