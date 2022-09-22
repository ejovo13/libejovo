// TP6 Exercice 7
#ifndef EJOVO_SIMULATION_H
#define EJOVO_SIMULATION_H

#include "ejovo_list.h"
#include "ejovo_rand.h"
#include <stdbool.h>

typedef enum Direction { UP, RIGHT, DOWN, LEFT} Direction;

#define PREY_START_ENERGY 100
#define PREY_D_ENERGY -10
// #define PREY_P_REPRODUCE 1.0
#define PREY_P_REPRODUCE 0.20
#define PREY_P_CHDIR 0.30

#define PRED_START_ENERGY 100
#define PRED_D_ENERGY -10
#define PRED_P_REPRODUCE 0.10
#define PRED_P_MANGER 0.50
#define PRED_P_CHDIR 0.30


// everything is getting built in as a list...
typedef struct proie_t {

    int x;
    int y;

    double energy;
    double d_energy;
    double p_reproduce;
    double p_ch_dir;
    Direction direction;
    bool has_acted; // True if the prey has moved since the last iteration

    struct proie_t *next;
    struct proie_t *prev;

} Prey;

Prey *new_Prey() {
    return (Prey *) malloc(sizeof(Prey));
}

// Prey default constructor
Prey *Prey_new(int __x, int __y) {

    Prey *prey = new_Prey();

    prey->x = __x;
    prey->y = __y;

    prey->energy = PREY_START_ENERGY;
    prey->d_energy = PREY_D_ENERGY;
    prey->p_reproduce = PREY_P_REPRODUCE;
    prey->p_ch_dir = PREY_P_CHDIR;
    prey->direction = unifi(0, 3);

    prey->has_acted = true;

    prey->next = NULL;
    prey->prev = NULL;

}


// Append __prey to the end of the doubly-linked list headed by __head
Prey *Prey_append(const Prey *__head, Prey *__prey) {

    // printf("Inside prey_append\n");

    Prey *iter = __head;

    if (!iter) {
        // printf("__head is null, aborting\n");
        __prey->prev = NULL;
        return __prey;
    } else {

        // iterate to the end of __head
        while (iter->next) {
            iter = iter->next;
        }

        iter->next = __prey;

        if (__prey) {
            __prey->prev = iter;
        }
    }

    return __head;

}

// create a new prey and append it to the list of head, returning the head
Prey *Prey_append_new(const Prey *__head, int __x, int __y) {
    return Prey_append(__head, Prey_new(__x, __y));
}

// What actually happens is we prepend the entire list pointed to by __prey, instead of just a single prey
// getting prepended
Prey *Prey_prepend(const Prey *__head, const Prey *__prey) {
    return Prey_append(__prey, __head);
}

Prey *Prey_prepend_new(const Prey *__head, int __x, int __y) {
    return Prey_prepend(__head, Prey_new(__x, __y));
}

// Insert a SINGLE __prey to the right of __head and return a pointer to the new head
Prey *Prey_insert_next(Prey *__head, Prey *__prey) {

    if (__head) {

        if (__head->next) {

            __head->next->prev = __prey;
            __prey->next = __head->next;

            __prey->prev = __head;
            __head->next = __prey;

        } else {

            __head->next = __prey;
            __prey->prev = __head;

            __prey->next = NULL;

        }

        return __head;

    } else {

        return __prey;

    }
}

Prey *Prey_insert_prev(Prey *__head, Prey *__prey) {

    if (__head) {

        if (__head->prev) {

            __head->prev->next = __prey;
            __prey->prev = __head->prev;

            __prey->next = __head;
            __head->prev = __prey;

        } else {

            __head->prev = __prey;
            __prey->next = __head;

            __prey->prev = NULL;

        }

        return __prey;

    } else {
        return __prey;
    }
}

// Remove this prey from the list it lives in and free the memory associated with it
// Return a pointer to next element of __prey
Prey *Prey_remove(Prey *__prey) {

    if (!__prey) return NULL; // do nothing if __prey is null

    if (__prey->prev && __prey->next) { // If __prey is not on a boarder

        __prey->prev->next = __prey->next;
        __prey->next->prev = __prey->prev;

        Prey *temp = __prey->prev;

        __prey->next = NULL;
        __prey->prev = NULL;

        free(__prey);
        return temp;

    } else if (__prey->prev && !__prey->next) { // If __prey is the last element

        __prey->prev->next = NULL;

        Prey *temp = __prey->prev;

        __prey->next = NULL;
        __prey->prev = NULL;

        free(__prey);
        return temp;

    } else if (!__prey->prev && __prey->next) { // If __prey is the first element

        __prey->next->prev = NULL;

        Prey *temp = __prey->next;

        __prey->next = NULL;
        __prey->prev = NULL;

        free(__prey);
        return temp;

    } else { // __prey is the SOLE element

        free(__prey);
        return NULL;

    }
}

Prey *Prey_remove_all(Prey *__head) {

    while(__head) {
        __head = Prey_remove(__head);
    }
    return __head;
}

void Prey_print(const Prey *__prey) {
    if (__prey) {
        printf("Prey@%x, .energy: %lf, .x: %d, .y: %d, .prev: %x, .next: %x\n", __prey, __prey->energy, __prey->x, __prey->y, __prey->prev, __prey->next);
    } else {
        printf("NULL\n");
    }
}

void Prey_print_all(const Prey *__prey) {
    Prey *iter = __prey;
    while (iter) {
        Prey_print(iter);
        iter = iter->next;
    }
}

// get nth prey offset from the head. Can return null
Prey *Prey_get_nth(const Prey *__head, int __n) {

    if (__n < 0) return NULL;

    Prey *iter = __head;
    while (iter && __n > 0) {
        iter = iter->next;
        __n --;
    }

    return iter;

}

size_t Prey_count(Prey *__head) {

    size_t count = 0;

    while (__head) {
        count ++;
        __head = __head->next;
    }

    return count;
}

void Prey_ch_dir(Prey *__prey) {

    // We should choose a direction that is not already occupied
    enum Direction next_dir = unifi(0, 3);

    while (next_dir == __prey->direction) { // while the direction guessed hasn't changed at all,
        next_dir = unifi(0, 3);
    }

    __prey->direction = next_dir;

}

// Make a new Prey
void Prey_reproduce(Prey *__prey) {
    Prey_insert_next(__prey, Prey_new(__prey->x, __prey->y)); // create a new prey right next to this one!
}

bool Prey_should_ch_dir(const Prey *__prey) {
    return unifd(0, 1) < __prey->p_ch_dir;
}

bool Prey_should_reproduce(const Prey *__prey) {
    return unifd(0, 1) < __prey->p_reproduce;
}

// Make a single prey move and return the next eligible Prey to act on
Prey *Prey_act(Prey *__prey) {

    if (!__prey) return NULL;

    // coordinates are interpreted so that right is positive x direction and up is positive y
    // Carry out the physical displacement
    switch (__prey->direction) {

        case UP:

            __prey->y ++;
            break;

        case RIGHT:

            __prey->x ++;
            break;

        case DOWN:

            __prey->y --;
            break;

        case LEFT:

            __prey->x --;
            break;
    }

    // Now adjust energy, attempt to change direction, reproduce, die?

    __prey->energy += __prey->d_energy;

    if (__prey->energy <= 0) {

        // printf("Prey@%x is dying!\n", __prey);
        __prey = Prey_remove(__prey);
        // printf("Prey after dying: %x\n", __prey);
        return __prey;

    } else {

        // Check if we should change direction
        if (Prey_should_ch_dir(__prey)) {
            // printf("Prey@%x is changing direction !\n", __prey);
            Prey_ch_dir(__prey);
        }

        if (Prey_should_reproduce(__prey)) {
            // printf("Prey@%x reproduced!\n", __prey);
            Prey_reproduce(__prey);
        }
    }

    if (__prey) __prey->has_acted = true;

    return __prey;

}

// Set the __has_acted attribute of all Prey to false
void Prey_reset_act(const Prey *__head) {

    Prey *iter = __head;

    while (iter) {
        iter->has_acted = false;
        iter = iter->next;
    }
}

// Search backwards for the head element and return it
Prey *Prey_head(const Prey *__prey) {

    Prey *iter = __prey;

    if (!iter) return iter;

    while (iter->prev) {
        iter = iter->prev;
    }

    return iter;

}

// Return a pointer the the new head (some elements get removed!)
Prey *Prey_act_all(const Prey *__head) {


    Prey *iter = Prey_head(__head);
    // printf("Prey_act_all iter: %x\n", iter);
    Prey *prev = __head;

    Prey_reset_act(__head);
    // printf("Population before step: %lu\n", Prey_count(__head));

    while (iter) {

        prev = iter;

        if (!iter->has_acted) {

            iter = Prey_act(iter);
            // printf("Prey just acted, iter should now be null?\n");
            // printf("iter: %x\n", iter); // iter is confirmed null
            if (!iter) return NULL; // If acting leaves us with an empty list, report that back

        } else {
            iter = iter->next;
        }
    }

    __head = Prey_head(prev);
    // printf("Population after step: %lu\n", Prey_count(__head));

    return __head;
}

// Initialize Prey list of __n prey all at (x, y) = (0, 0)
Prey *Prey_init(size_t __n) {

    Prey *head = Prey_new(0, 0);

    for (size_t i = 1; i < __n; i++) {
        head = Prey_append_new(head, 0, 0);
    }

    return head;

}

// Return the first prey found at this location or return null
Prey *Prey_find_at(const Prey *__head, int __x, int __y) {

    Prey *iprey = __head;

    while (iprey) {

        if (iprey->x == __x && iprey->y ==__y) return iprey;
        iprey = iprey->next;
    }

    return NULL; // no prey found at this position

}


/**========================================================================
 *!                           Predator functions
 *========================================================================**/

typedef struct predator_t {

    int x;
    int y;

    double energy;
    double d_energy;
    double p_reproduce;
    double p_manger;
    double p_ch_dir;
    Direction direction;
    bool has_acted; // True when the predator has moved since the last iteration

    struct predator_t* next;
    struct predator_t* prev;

} Pred;

Pred *new_Pred() {
    return (Pred *) malloc(sizeof(Pred));
}

// Pred default constructor
Pred *Pred_new(int __x, int __y) {

    Pred *pred = new_Pred();

    pred->x = __x;
    pred->y = __y;

    pred->energy = PRED_START_ENERGY;
    pred->d_energy = PRED_D_ENERGY;
    pred->p_reproduce = PRED_P_REPRODUCE;
    pred->p_manger = PRED_P_MANGER;
    pred->p_ch_dir = PRED_P_CHDIR;
    pred->direction = unifi(0, 3);

    pred->has_acted = true;

    pred->next = NULL;
    pred->prev = NULL;

}

// Append __prey to the end of the doubly-linked list headed by __head
Pred *Pred_append(const Pred *__head, Pred *__pred) {

    // printf("Inside prey_append\n");

    Pred *iter = __head;

    if (!iter) {
        // printf("__head is null, aborting\n");
        __pred->prev = NULL;
        return __pred;
    } else {

        // iterate to the end of __head
        while (iter->next) {
            iter = iter->next;
        }

        iter->next = __pred;

        if (__pred) {
            __pred->prev = iter;
        }
    }

    return __head;

}

// create a new prey and append it to the list of head, returning the head
Pred *Pred_append_new(const Pred *__head, int __x, int __y) {
    return Pred_append(__head, Pred_new(__x, __y));
}

// What actually happens is we prepend the entire list pointed to by __pred, instead of just a single prey
// getting prepended
Pred *Pred_prepend(const Pred *__head, const Pred *__pred) {
    return Pred_append(__pred, __head);
}

Pred *Pred_prepend_new(const Pred *__head, int __x, int __y) {
    return Pred_prepend(__head, Pred_new(__x, __y));
}

// Insert a SINGLE __prey to the right of __head and return a pointer to the new head
Pred *Pred_insert_next(Pred *__head, Pred *__pred) {

    if (__head) {

        if (__head->next) {

            __head->next->prev = __pred;
            __pred->next = __head->next;

            __pred->prev = __head;
            __head->next = __pred;

        } else {

            __head->next = __pred;
            __pred->prev = __head;

            __pred->next = NULL;

        }

        return __head;

    } else {

        return __pred;

    }
}

Pred *Pred_insert_prev(Pred *__head, Pred *__pred) {

    if (__head) {

        if (__head->prev) {

            __head->prev->next = __pred;
            __pred->prev = __head->prev;

            __pred->next = __head;
            __head->prev = __pred;

        } else {

            __head->prev = __pred;
            __pred->next = __head;

            __pred->prev = NULL;

        }

        return __pred;

    } else {
        return __pred;
    }
}

// Remove this prey from the list it lives in and free the memory associated with it
// Return a pointer to next element of __pred
Pred *Pred_remove(Pred *__pred) {

    if (!__pred) return NULL; // do nothing if __pred is null

    if (__pred->prev && __pred->next) { // If __pred is not on a boarder

        __pred->prev->next = __pred->next;
        __pred->next->prev = __pred->prev;

        Pred *temp = __pred->prev;

        __pred->next = NULL;
        __pred->prev = NULL;

        free(__pred);
        return temp;

    } else if (__pred->prev && !__pred->next) { // If __pred is the last element

        __pred->prev->next = NULL;

        Pred *temp = __pred->prev;

        __pred->next = NULL;
        __pred->prev = NULL;

        free(__pred);
        return temp;

    } else if (!__pred->prev && __pred->next) { // If __pred is the first element

        __pred->next->prev = NULL;

        Pred *temp = __pred->next;

        __pred->next = NULL;
        __pred->prev = NULL;

        free(__pred);
        return temp;

    } else { // __pred is the SOLE element

        free(__pred);
        return NULL;

    }
}

Pred *Pred_remove_all(Pred *__head) {

    while(__head) {
        __head = Pred_remove(__head);
    }
    return __head;
}

void Pred_print(const Pred *__pred) {
    if (__pred) {
        printf("Pred@%x, .energy: %lf, .x: %d, .y: %d, .prev: %x, .next: %x\n", __pred, __pred->energy, __pred->x, __pred->y, __pred->prev, __pred->next);
    } else {
        printf("NULL\n");
    }
}

void Pred_print_all(const Pred *__pred) {
    Pred *iter = __pred;
    while (iter) {
        Pred_print(iter);
        iter = iter->next;
    }
}

// get nth prey offset from the head. Can return null
Pred *Pred_get_nth(const Pred *__head, int __n) {

    if (__n < 0) return NULL;

    Pred *iter = __head;
    while (iter && __n > 0) {
        iter = iter->next;
        __n --;
    }

    return iter;

}

size_t Pred_count(Pred *__head) {

    size_t count = 0;

    while (__head) {
        count ++;
        __head = __head->next;
    }

    return count;
}

void Pred_ch_dir(Pred *__pred) {

    // We should choose a direction that is not already occupied
    enum Direction next_dir = unifi(0, 3);

    while (next_dir == __pred->direction) { // while the direction guessed hasn't changed at all,
        next_dir = unifi(0, 3);
    }

    __pred->direction = next_dir;

}

// Make a new Pred
void Pred_reproduce(Pred *__pred) {
    Pred_insert_next(__pred, Pred_new(__pred->x, __pred->y)); // create a new prey right next to this one!
}


// Eating the prey
Prey *Pred_eat(Pred *__pred, Prey *__prey) {

    if (__prey) {

        __pred->energy += __prey->energy;
        __prey = Prey_remove(__prey);
        return __prey;

    }

    return NULL;
}

// Maybe I want The predators decision to eat increase if he has lower energy !
bool Pred_should_eat(const Pred *__pred) {
    return unifd(0, 1) < __pred->p_manger;
}

bool Pred_should_ch_dir(const Pred *__pred) {
    return unifd(0, 1) < __pred->p_ch_dir;
}

bool Pred_should_reproduce(const Pred *__pred) {
    return unifd(0, 1) < __pred->p_reproduce;
}

// Make a single prey move and return the next eligible Pred to act on
// We might eat the __prey, so pass a double pointer
Pred *Pred_act(Pred *__pred, Prey **__prey) {

    if (!__pred) return NULL;

    // coordinates are interpreted so that right is positive x direction and up is positive y
    // Carry out the physical displacement
    switch (__pred->direction) {

        case UP:

            __pred->y ++;
            break;

        case RIGHT:

            __pred->x ++;
            break;

        case DOWN:

            __pred->y --;
            break;

        case LEFT:

            __pred->x --;
            break;
    }

    // Now adjust energy, attempt to change direction, reproduce, die?

    __pred->energy += __pred->d_energy;

    if (__pred->energy <= 0) {

        // printf("Pred@%x is dying!\n", __pred);
        __pred = Pred_remove(__pred);
        // printf("Pred after dying: %x\n", __pred);
        return __pred;

    } else {

        // Check if we should change direction
        if (Pred_should_ch_dir(__pred)) {
            // printf("Pred@%x is changing direction !\n", __pred);
            Pred_ch_dir(__pred);
        }

        if (Pred_should_reproduce(__pred)) {
            // printf("Pred@%x reproduced!\n", __pred);
            Pred_reproduce(__pred);
        }

        if (Pred_should_eat(__pred)) {

            // Pred_print_all(__pred);
            // printf("Predator at %d, %d having a snack!\n", __pred->x, __pred->y);
            // Prey_print_all(*__prey);
            Prey *prey = Prey_find_at(*__prey, __pred->x, __pred->y);
            if (prey) {
                // printf("Prey found!!:\n");
                // Prey_print(prey);
                (*__prey) = Prey_head(Pred_eat(__pred, prey)); // point (*__prey) at the correct head
            }
            // printf("Prey succesfully eaten?\n");
            // Prey_print_all(*__prey);

        }
    }

    if (__pred) __pred->has_acted = true;

    return __pred;

}

// Set the __has_acted attribute of all Pred to false
void Pred_reset_act(const Pred *__head) {

    Pred *iter = __head;

    while (iter) {
        iter->has_acted = false;
        iter = iter->next;
    }
}

// Search backwards for the head element and return it
Pred *Pred_head(const Pred *__pred) {

    Pred *iter = __pred;

    if (!iter) return iter;

    while (iter->prev) {
        iter = iter->prev;
    }

    return iter;

}

// Return a pointer the the new head (some elements get removed!)
Pred *Pred_act_all(const Pred *__head, Prey **__prey) {


    Pred *iter = Pred_head(__head);
    // printf("Pred_act_all iter: %x\n", iter);
    Pred *prev = __head;

    Pred_reset_act(__head);
    // printf("Population before step: %lu\n", Pred_count(__head));

    while (iter) {

        prev = iter;

        if (!iter->has_acted) {

            iter = Pred_act(iter, __prey);
            // printf("Pred just acted, iter should now be null?\n");
            // printf("iter: %x\n", iter); // iter is confirmed null
            if (!iter) return NULL; // If acting leaves us with an empty list, report that back

        } else {
            iter = iter->next;
        }
    }

    __head = Pred_head(prev);
    // printf("Population after step: %lu\n", Pred_count(__head));

    return __head;
}

// Initialize Pred list of __n prey all at (x, y) = (0, 0)
Pred *Pred_init(size_t __n) {

    Pred *head = Pred_new(0, 0);

    for (size_t i = 1; i < __n; i++) {
        head = Pred_append_new(head, 0, 0);
    }

    return head;

}

// A Simulation just consists of a pointer to a Pred and a pointer to a Prey...
typedef struct simulation_t {

    Pred *pred;
    Prey *prey;

} Simulation;

void Simulation_step(Simulation *__sim) {

    __sim->prey = Prey_act_all(__sim->prey);
    __sim->pred = Pred_act_all(__sim->pred, &(__sim->prey));

}

Simulation *Simulation_new(size_t __npred, size_t __nprey) {

    Simulation *sim = (Simulation *) malloc(sizeof(Simulation));

    sim->pred = Pred_init(__npred);
    sim->prey = Prey_init(__nprey);

    return sim;

}

void Simulation_summary(const Simulation *__sim) {

    int pred_count = Pred_count(__sim->pred);
    int prey_count = Prey_count(__sim->prey);

    printf("Simulation has %d pred and %d prey\n", pred_count, prey_count);

}

void Simulation_nsteps(Simulation *__sim, size_t __n) {

    for (size_t i = 0; i < __n; i++) {

        Simulation_step(__sim);
    }
}

void Simulation_nsteps_summary(Simulation *__sim, size_t __n) {
    for (size_t i = 0; i < __n; i++) {
        Simulation_summary(__sim);
        Simulation_step(__sim);
    }
}

void Sumulation_print_prey(const Simulation *__sim) {
    Prey_print_all(__sim->prey);
}

void Simulation_print_pred(const Simulation *__sim) {
    Pred_print_all(__sim->pred);
}


#endif