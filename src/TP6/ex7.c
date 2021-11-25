#include "ejovo_simulation.h"
#include <stdio.h>

int main() {


    printf("Hello world\n");

    Prey *head = Prey_new(0, 0);

    Prey *new = Prey_new(1, 1);

    head = Prey_append(head, new);
    head = Prey_prepend_new(head, 2, 2);

    Prey_print_all(head);

    printf("Removing head...\n");
    head = Prey_remove(head);

    Prey_print_all(head);

    head = Prey_append_new(head, 4, 4);
    head = Prey_append_new(head, 5, 5);
    head = Prey_append_new(head, 6, 6);
    head = Prey_append_new(head, 8, 8);

    Prey_print_all(head);


    Prey *nth = Prey_get_nth(head, 4);
    printf("Prey_get_nth(4) -> \n");
    Prey_print(nth);

    nth = Prey_get_nth(head, 5);
    printf("Prey_get_nth(5) -> \n");
    Prey_print(nth);

    // nth = Prey_get_nth(head, 6);
    // printf("Prey_get_nth(6) -> \n");
    // Prey_print(nth);

    printf("Prey_count(head) -> %lu\n", Prey_count(head));

    Prey_insert_prev(nth, Prey_new(9, 9));
    Prey_insert_next(Prey_get_nth(head, 3), Prey_new(-3, -3));

    nth = Prey_get_nth(head, 2);
    nth = Prey_remove(nth);

    Prey_print_all(head);

    head = Prey_remove_all(head);
    Prey_print(head);


    printf("=====================\n");
    printf("Starting simulation steps tests\n");

    // head = Prey_init(1);

    // Prey_print(head);
    // head = Prey_remove(head);
    // head = Prey_remove(head);

    // head = Prey_append_new(head, 1, 1);

    // Prey_print(head);


    // head = Prey_init(50);

    // for (size_t i = 0; i < 10; i++) {
    //     head = Prey_remove(head);
    //     printf("Size after removal: %ld\n", Prey_count(head));
    // }

    ejovo_seed();

    // Prey_print(head);

    // Prey_act(head);
    // const int N_STEPS = 5000;

    // Prey_print_all(head);

    // Prey_print(Prey_head(head));

    // for (size_t i = 0; i < N_STEPS; i++) {

    //     // Prey_print_all(head);
    //     head = Prey_act_all(head);
    //     printf("%5d | Count: %lu\n", i, Prey_count(head));
    //     printf("==========================\n");
    //     if (!head) break;


    // }

    // Prey_print(head);
    // Prey_print_all(head);

    // Prey_remove_all(head);


    Simulation *sim = Simulation_new(5, 5);

    Simulation_summary(sim);

    Simulation_nsteps(sim, 40);


    Simulation_summary(sim);

    // Simulation_print_pred(sim);








    // free(head);


    // YCoordinate *yhead = YCoord_new(0);

    // YCoordinate *yhead2 = YCoord_new(20);
    // yhead2 = YCoord_append(yhead2, YCoord_new(23));
    // yhead2 = YCoord_append(yhead2, YCoord_new(21));

    // Print_Y(yhead2);
    // printf("\n");

    // yhead = YCoord_append(yhead, YCoord_new(4));
    // Print_Y(yhead);

    // printf("Combining the two: \n");

    // yhead = YCoord_prepend(yhead, yhead2);
    // Print_Y(yhead);

    return 0;
}