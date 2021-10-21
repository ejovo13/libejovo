// Dans cet exercise il s'agit d'ecrire un programme de histogramm
// 0 - 20

#include "ejovo_rand.h"
#include "ejovo_print.h"


// Function pointer that will allow me to fill a histogram with different random number generators
typedef int (*RNG)(int, int);

// Naive rng uses the modulo operator - very nooby and not very secure
int naive_rng(int a, int b) {

    int x = rand() % (b - a + 1);
    return (x + a);

}

// Fill a histogram (__obervations) and count each observation (__counts) with scores int [0, __highest_score]
void fill_histogram(int __n_observations, int __highest_score, RNG __rng, int * __observations, int * __counts) {

    // Zero out __counts
    for (int i = 0; i <= __highest_score; i ++) {
        __counts[i] = 0;
    }

    for (int i = 0; i < __n_observations; i ++) {
        __observations[i] = __rng(0, __highest_score);
    }

    // count the each score
    for (int i = 0; i <= __n_observations; i ++) {
        for (int j = 0; j <= __highest_score; j ++) {
            if ( __observations[i] == j ) {
                __counts[j] ++;
                // printf("scores[%d] = %d\n", i, j);
                j = __highest_score + 10;
            }
        }
    }
}

void print_histogram(int __n_observations, int __highest_score, int * __counts) {

    // get maximum value in counts
    int max_count = __counts[0];
    for (int s = 1; s <= __highest_score; s ++) {
        if (__counts[s] > max_count) max_count = __counts[s];
    }

    double num_characters = 40.0;

    double scaling_factor;
    if ( max_count > num_characters ) {
        scaling_factor =  max_count / num_characters;
    } else {
        scaling_factor = 1.0;
    }

    for (int i = 0; i <= __highest_score; i ++) {

        printf("%2d | ", i);

        // let's try and print about 80 characters

        for (int n = 0; n < (__counts[i])/scaling_factor; n ++) {

            printf("*");

        }

        printf("\n");

    }
}

#define MAX_SCORE 20 // maximum score that you can get on an exam
#define CLASS_SIZE 50000

int main() {


    srand( time( NULL ) );

    ejovo_seed();

    int scores[CLASS_SIZE] = {0};
    int histogram_counts[MAX_SCORE + 1] = {0};

    // NAIVE RNG Generation using MODULE operator!!!
    fill_histogram(CLASS_SIZE, MAX_SCORE, naive_rng, scores, histogram_counts);
    print_histogram(CLASS_SIZE, MAX_SCORE, histogram_counts);
    // print_int_array(scores, CLASS_SIZE);

    printf("\n\n");

    // RNG Generation using (rand() / RAND_MAX) * [a, b]. function 'get_rand_int_range' defined in "ejovo_rand.c"
    fill_histogram(CLASS_SIZE, MAX_SCORE, get_rand_int_range, scores, histogram_counts);
    print_histogram(CLASS_SIZE, MAX_SCORE, histogram_counts);
    // print_int_array(scores, CLASS_SIZE);

    printf("\n\n");

    // XOROSHIFT2566** GENERATION! Using function 'unif' defined in "ejovo_rand.c"j
    fill_histogram(CLASS_SIZE, MAX_SCORE, unif, scores, histogram_counts);
    print_histogram(CLASS_SIZE, MAX_SCORE, histogram_counts);

    printf("\n\n");


}