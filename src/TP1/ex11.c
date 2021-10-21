#include "hw_printer.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

int get_rand_int(int max) {
// get random integer between 1 and max
    double x = ((double) rand()) / RAND_MAX;
    return (int) ceil(x * max);
}

void demo_rand() {
    for(int i = 0; i < 100; i++) {
        printf("%d\n", get_rand_int(100));
    }
}

int main() {

    ex(11, "Jeu de 'guess'");

    srand( time(NULL) );

    int rn = get_rand_int(100);

    int guess = 0;

    printf("Please enter a guess between 1 and 100\n\n");

    while(guess != rn) {

        scanf("%d", &guess);

        if (guess < rn) {
            printf("You guessed too low!\n");
            printf("Try again...\n\n");
        } else if (guess > rn) {
            printf("You guessed too high!\n");
            printf("Try again...\n\n");
        }
    }

    printf("Congratulations! You guessed correctly!!\n");

    printf("Secret number was: %d\n", rn);

    return 0;
}