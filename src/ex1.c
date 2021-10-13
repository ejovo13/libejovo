// Écrire un algorithme récursif qui affiche l’écriture inverse d’un entier donné en entrée (par
// exemple si on entre -2344, on obtiendra l’affichage -4432).

#include "ejovo_print.h"
#include "math.h"
#include <stdio_ext.h>
#include <stdbool.h>
#include <stdlib.h>


// Creer une fonction recursive
void reverse(int n) {

    if ( n < 10 ) {
        printf("%d", n);
    } else {
        
    }




}


int main() {

    long int user_input = 0;

    printf("Please enter any integer: ");
    scanf("%ld", &user_input);

    // printf("Value entered: %ld\n", user_input);

    // Find out the number of digits again
    int num_digits = 0;

    bool is_negative = false;

    if ( user_input < 0 ) {

        is_negative = true;
        num_digits = (int) log10((double) labs(user_input) ) + 2;

    } else {

        num_digits = (int) log10((double) labs(user_input) ) + 1;

    }



    // printf("Num digits = %d\n", num_digits);



    // Write the number to a string and then reverse it



    char num_forward[num_digits + 1];
    char num_reverse[num_digits + 1];

    num_forward[num_digits] = '\0';
    num_reverse[num_digits] = '\0';

    // sprintf the integer into my string

    sprintf(num_forward, "%ld", user_input);

    // printf("Here is the number as a string: %s|\n", num_forward);

    // time to reverse the string

    // if negative, we should skip the very first element
    if(is_negative) {

        num_reverse[0] = '-';
        // printf("number is negative\n");


        for (int i = 1; i < num_digits; i ++) {



            // printf("Processing digit: %c\n", num_forward[num_digits - (i)]);
            num_reverse[i] = num_forward[num_digits - ( i )];

        }

    } else {

        // printf("Number is not negative\n");
        // printf("Num digits = %d\n", num_digits);

        for (int i = 0; i < num_digits; i ++) {

            // printf("Processing digit: %c\n", num_forward[num_digits - (i) - 1]);
            num_reverse[i] = num_forward[num_digits - ( i ) - 1 ];

        }
    }
    // __fpurge(stdin);

    printf("reversed number: %s\n", num_reverse);


    // if the original value is negative, remember to add the negative


    return 0;
}