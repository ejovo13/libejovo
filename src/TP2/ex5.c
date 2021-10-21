// Repeter Suppression des doublons avec le tableau genere en ex4.
#include "ejovo_print.h"
#include "ejovo_rand.h"

#define N 50
#define P 3

int main() {

    ex(5, "Refaire la suppressions de doublons avec le tableau du ex4");

    srand( time( NULL ) );

    int T[N] = {0}; // stripped array
    int T_og[N] = {0}; // original array
    int init_value = get_rand_int(10);
    T[0] = init_value;
    T_og[0] = init_value;
    int r = 0;

    for (int i = 1; i < N; i ++) {

        r = get_rand_int(P+1) - 1;
        T[i] = T[i-1] + r;
        T_og[i] = T[i-1] + r;

    }

    printf("Generating array...\n");
    printf("Filtering duplicate values...\n\n");

    int diff = 0;
    int potential_duplicate = init_value;

    for (int i = 1; i < N; i ++) {
        diff = T[i] - potential_duplicate;
        if (diff == 0) {
            T[i] = 0; // duplicate value
        } else {
            potential_duplicate = T[i]; // not a duplicate, store it for next test
        }
    }

    printf("Original array: \n");
    print_int_array(T_og, N);


    printf("Stripped array: \n");
    print_int_array(T, N);


    return 0;
}