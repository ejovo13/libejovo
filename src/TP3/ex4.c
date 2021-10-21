// Miroir

// prend chaine de caracteres chaine et l'inverser
// wtf we have already done this like 4 times

#include "ejovo_print.h"
#include "ejovo_rand.h"
#include "ejovo_string.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

void affiche_miroir(char * __chaine) {
// fonction recursive qui affiche le tableau

    // I can only thing of an algorithm that consumes the string, this is so so stupid in practice - maybe I need a better way then...
    // If the string has been consumed, bail
    if (__chaine[0] == '\0') { return; } else {
        // find the final character and print it
        char * pos = __chaine;
        while(pos[0] != '\0') {
            pos ++;
        }
        // print the final character (before '\0') of the string and set it equal to '\0'
        printf("%c", pos[-1]);
        pos[-1] = '\0';

    }
    affiche_miroir(__chaine);

}


int main() {

    char chaine[] = "Je suis stocke dans 'chaine'!";
    size_t chaine_len = strlen(chaine); // get length of string (NOT INCLUDING '\0')

    // 1. Donne chaine, ecrit dans le tableau miroir le miroir de chaine
    // char * mirroir = (char *) calloc(chaine_len + 1, sizeof(char));
    // for (size_t i = 0; i < chaine_len; i ++) {
    //     mirroir[chaine_len - 1 - i] = chaine[i];
    // }
    // printf("chaine de caracteres:\n %s\nreversed:\n %s\n", chaine, mirroir);


    // 2. Stocker le miroir dans le tableau CHAINE.

    printf("chaine de caracteres:\n  %s\n", chaine);

    char temp_c = '\0';

    for (size_t i = 0; i < chaine_len/2; i ++) { // Division euclidean couvre touts les deux possibilites; pair, impair

        temp_c = chaine[chaine_len - 1 - i];
        chaine[chaine_len - 1 -i] = chaine[i];
        chaine[i] = temp_c;

    }

    printf("reversed:\n  %s\n", chaine);
    printf("reversed again with 'affiche_miroir':\n  ");
    affiche_miroir(chaine);

    // GET USER INPUT!!!!
    printf("\n\nPlease enter a string to be reversed:\n  ");

    size_t buffer_size = 64;
    char * buffer = (char *) calloc(buffer_size, sizeof(char));
    if (!buffer) {
        perror("Error with malloc trying");
    }

    size_t num_chars_read = getline(&buffer, &buffer_size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    // char * chaine_input = (char *) calloc(num_chars_read, sizeof(char));
    // if (!chaine_input) {
    //     perror("Error with malloc trying");
    // }

    // strcpy(chaine_input, buffer);
    chaine_len = num_chars_read - 1;

    // reverse input string:
    for (size_t i = 0; i < chaine_len/2; i ++) { // Division euclidienne couvre touts les deux possibilites; pair, impair

        temp_c = buffer[chaine_len - 1 - i];
        buffer[chaine_len - 1 -i] = buffer[i];
        buffer[i] = temp_c;

    }

    printf("Input reversed:\n  %s\n", buffer);

    printf("Trying to afficher miroir:\n  ");
    affiche_miroir(buffer);
    printf("\n");

    return 0;
}