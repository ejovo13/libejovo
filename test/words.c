#include "ejovo_string.h"
#include <assert.h>

int main() {


    char str[] = "This is a test string";
    char str1[] = "  This is a test string";
    char str2[] = "    This is a test string  ";
    char str3[] = "This is a test string  ";
    char str4[] = "This is a test string 1 2 3 4 ";

    printf("Performing 5 tests\n");

    assert(count_words(str) == 5);
    assert(count_words(str1) == 5);
    assert(count_words(str2) == 5);
    assert(count_words(str3) == 5);
    assert(count_words(str4) == 9);


    return 0;
}