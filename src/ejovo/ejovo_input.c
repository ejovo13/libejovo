// A Collection of functions used to get input from the user.

// The function prototype is
//
// TYPE get_TYPE(void)
//
// and will get an appropriate type from the user
#include "ejovo_input.h"

int get_int(void) {

    int input = 0;
    bool input_validated = false;

    while(!input_validated) {

        int num_values = scanf("%d", &input); // something went wrong
        if (num_values != 1) {
            printf("\nImproper number of values read, please try again\n");
            fflush(stdin);
            continue;
        } else {
            input_validated = true;
            return input;
        }
    }

    return 0;

}