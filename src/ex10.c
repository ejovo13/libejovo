// Dans cet exercise il s'agit d'ecrire un programme de histogramm
// 0 - 20

#include "ejovo_rand.h"
#include "ejovo_print.h"

#define MAX_SCORE 20 // maximum score that you can get on an exam
#define CLASS_SIZE 500


int main() {

    srand( time( NULL ) );

    int scores[CLASS_SIZE] = {0};
    int histogram_counts[MAX_SCORE + 1] = {0};

    // generate a bunch of scores
    for (int i = 0; i < CLASS_SIZE; i ++) {
        scores[i] = get_rand_int_range(0, MAX_SCORE);
    }

    // count the each score
    for (int i = 0; i <= CLASS_SIZE; i ++) {
        for (int j = 0; j <= MAX_SCORE; j ++) {
            if ( scores[i] == j ) {
                histogram_counts[j] ++;
                // printf("scores[%d] = %d\n", i, j);
                j = MAX_SCORE + 10;
            }
        }

    }

    // print the histogram
    // print_int_array(histogram_counts, MAX_SCORE + 1);
    // print_int_array(scores, CLASS_SIZE);

    for (int i = 0; i <= MAX_SCORE; i ++) {

        printf("%2d | ", i);

        for (int n = 0; n < histogram_counts[i]; n ++) {

            printf("*");

        }

        printf("\n");


    }

}