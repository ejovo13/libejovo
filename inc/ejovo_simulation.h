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
#define PREY_P_REPRODUCE 0.11
#define PREY_P_CHDIR 0.30

#define PRED_START_ENERGY 100
#define PRED_D_ENERGY -10
#define PRED_P_REPRODUCE 0.10
#define PRED_P_MANGER 0.20
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
    prey->direction = unif(0, 3);

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
    enum Direction next_dir = unif(0, 3);

    while (next_dir == __prey->direction) { // while the direction guessed hasn't changed at all,
        next_dir = unif(0, 3);
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




/**========================================================================
 *!                           Predator functions
 *========================================================================**/

typedef struct predator_t {

    double energy;
    double d_energy;
    double p_reproduce;
    double p_manger;
    double p_ch_dir;
    Direction direction;
    bool has_moved; // True when the predator has moved since the last iteration

    struct predator_t* next;

} Pred;

Pred *new_Pred() {
    return (Pred *) malloc(sizeof(Pred));
}

// Pred default constructor
Pred *Pred_new() {

    Pred *pred = new_Pred();
    pred->energy = PRED_START_ENERGY;
    pred->d_energy = PRED_D_ENERGY;
    pred->p_reproduce = PRED_P_REPRODUCE;
    pred->p_manger = PRED_P_MANGER;
    pred->p_ch_dir = PRED_P_CHDIR;
    pred->has_moved = false;

    pred->direction = unif(0, 3);

}

// // Always return the HEAD of the new list!!!
Pred *Pred_append(Pred *__head, Pred *__pred) {

    Pred *ihead = __head;

    if (!ihead) { // if our initial list is empty, return __pred
        return __pred;
    }

    // iterate until we have found the finale position
    while (ihead->next) {
        ihead = ihead->next;
    }

    ihead->next = __pred; // consequently, if __pred is already a list we can concatenate these two lists fast
    return __head;

}

Pred *Pred_prepend(Pred *__head, Pred *__pred) {
    return Pred_append(__pred, __head); // This is some genius level shit, right?
}

size_t Pred_count(Pred *__head) {

    size_t count = 0;

    while (__head) {
        count ++;
        __head = __head->next;
    }

    return count;
}

// Decrease the amount of energy from the __pred and roll to change direction
void Pred_move(Pred *__pred) {

    __pred->has_moved = true;
    __pred->energy -= __pred->d_energy;

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

// Should the predator die if his energy is 0?
// any animal?




// typedef struct ycoordinate_t {

//     int y;
//     struct ycoordinate_t *up;
//     struct ycoordinate_t *down;

//     Pred* pred;
//     Prey* prey;

// } YCoordinate;


// typedef struct xcoordinate_t {

//     int x;
//     struct xcoordinate_t *right;
//     struct xcoordinate_t *left;
//     struct ycoordinate_t *y_coord;

// } XCoordinate;

// This means that the entire grid is kind of encapsulated in this space

// allocate space for one coordinate and return the pointer associated to the block of memory
// XCoordinate *new_XCoord() {return (XCoordinate *) malloc(sizeof(XCoordinate)); }
// YCoordinate *new_YCoord() {return (YCoordinate *) malloc(sizeof(YCoordinate)); }

// XCoordinate *XCoord_new(int __x) {
//     XCoordinate *coord = new_XCoord();
//     coord->x = __x;
//     coord->right = NULL;
//     coord->left = NULL;
//     return coord;
// }

// YCoordinate *YCoord_new(int __y) {

//     YCoordinate *coord = new_YCoord();
//     coord->y = __y;
//     coord->down = NULL;
//     coord->up = NULL;
//     coord->prey = NULL;
//     coord->pred = NULL;
// }

// size_t YCoord_count_prey(const YCoordinate *__ycoord) {

//     size_t count = 0;
//     Prey *itprey = __ycoord->prey;
//     while(itprey) {
//         count ++;
//         itprey = itprey->next;
//     }

//     return count;
// }

// size_t YCoord_count_pred(const YCoordinate *__ycoord) {

//     size_t count = 0;
//     Pred *itpred = __ycoord->pred;
//     while(itpred) {
//         count ++;
//         itpred = itpred->next;
//     }

//     return count;
// }


// YCoordinate *YCoord_append(YCoordinate *__head, YCoordinate *__y) {

//     YCoordinate *iy = __head;

//     if (!iy) { // if our initial list is empty, return __pred
//         return __y;
//     }

//     while (iy->down) {
//         iy = iy->down;
//     }

//     iy->down = __y;
//     __y->up = iy;

//     return __head;

// }

// YCoordinate *YCoord_prepend(YCoordinate *__head, YCoordinate *__y) {
//     return YCoord_append(__y, __head);
// }


// void YCoord_pred_append(YCoordinate *__ycoord, Pred *__pred) {
//     __ycoord->pred = Pred_append(__ycoord->pred, __pred);
// }

// void YCoord_pred_prepend(YCoordinate *__ycoord, Pred *__pred) {
//     __ycoord->pred = Pred_prepend(__ycoord->pred, __pred);
// }

// void YCoord_prey_append(const YCoordinate *__ycoord, Prey *__prey) {
//     Prey_append(__ycoord->prey, __prey);
// }

// void YCoord_prey_prepend(const YCoordinate *__ycoord, Prey *__prey) {
//     Prey_prepend(__ycoord->prey, __prey);
// }

// void YCoord_summary(const YCoordinate *__ycoord) {
//     printf("{@%x .y = %d, pred_count: %ld, prey_count: %ld,  up: %x, down: %x\n", __ycoord, __ycoord->y, YCoord_count_pred(__ycoord), YCoord_count_prey(__ycoord), __ycoord->up, __ycoord->down);
// }

// void Print_Y(const YCoordinate *__ycoord) {
//     YCoordinate *iter_y = __ycoord;
//     while (iter_y) {
//         YCoord_summary(iter_y);
//         iter_y = iter_y->down;
//     }
// }

// // Set the has_moved attribute to false for every predator at this coordinate
// void YCoord_reset_pred_move(const YCoordinate *__ycoord) {

//     Pred *it_pred = __ycoord->pred;

//     while (it_pred) {

//         it_pred->has_moved = false;
//         it_pred = it_pred->next;
//     }
// }




// // Process all of the predator's operations, for a single y coordinate
// YCoordinate *YCoord_process_pred(const YCoordinate *__ycoord) {

//     Pred *it_pred = __ycoord->pred;

//     while (it_pred) {

//         // Move predator
//         // what does it mean to move a predator?








//         it_pred = it_pred->next;
//     }



// }










// // The high level idea of "Prey move" is implemented as remove_prey, insert_prey
// // iterate through every pred and se if they need to eat!
// void Sim_pred_eat(const XCoordinate *__x0) {





// }


// void Simulation_step() {




// }









// void Coordinate_prepend_x(XCoordinate *__xlist, int __x) {



// }

// // Assume that the x list is sorted
// void Coordinate_insert_x(XCoordinate **__xlist, int __x) {

//     XCoordinate *xiter = *__xlist;

//     if(!xiter) {
//         (*__xlist) = XCoord_new(__x); // point the first x coordinate towards this new coord
//         return;
//     }

//     while (xiter) {

//         if (xiter->right) { // if we are not at the ned of the coordinates

//             if (xiter->right->x > __x) { // go ahead and insert __xcoord here




//             }



//         }

//         xiter = xiter->right;
//     }




// }

// For a y coordinate,


#endif