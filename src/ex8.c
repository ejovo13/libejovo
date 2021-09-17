// Fizzbuzz with f = 3, b = 7

#include "hw_printer.h"

int main() {

    ex(8, "FizzBuzz(3, 7)");

    const int FIZZ = 3;
    const int BUZZ = 7;
    const int START = 1;
    const int END = 100;

    int FIZZBUZZ = FIZZ * BUZZ;

    for (int i = START; i <= END; i ++) {

        if (i % FIZZBUZZ == 0) {
            printf("FizzBuzz\n");
        } else if (i % FIZZ == 0 || i % 10 == FIZZ) {
            printf("Fizz\n");
        } else if (i % BUZZ == 0 || i % 10 == BUZZ) {
            printf("Buzz\n");
        } else {
            printf("%d\n", i);
        }
    }

    return 0;
}