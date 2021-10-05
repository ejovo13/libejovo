#include "ejovo_string.h"
#include <assert.h>

int main() {

    char test_str[] = "Hello this is a test string";
    char substr1[] = "this";
    char substr2[] = "is";
    char repeat[] = "HiHiHiHiHiHiHiHiHiHihi";

    char test1[] = "Hello  is a test string";
    char test2[] = "Hello th  a test string";
    char test3[] = "hi";

    printf("Test string: '%s' - '%s' = '%s'\n", test_str, substr1, del_substr(test_str, substr1));
    printf("Test string: '%s' - '%s' = '%s'\n", test_str, substr2, del_substr(test_str, substr2));
    printf("Test string: '%s' - '%s' = '%s'\n", repeat, "Hi", del_substr(repeat, "Hi"));

    // Test removing 'this'
    assert(strcmp(test1, del_substr(test_str, substr1)) == 0);
    // Test removing 'is' twice
    assert(strcmp(test2, del_substr(test_str, substr2)) == 0);
    // Test removing the entire sub string
    assert(strcmp("", del_substr(test_str, test_str)) == 0);
    // Test a lot of repetition
    assert(strcmp(test3, del_substr(repeat, "Hi")) == 0);

    // TODO THIS SHIT IS FUCKED UP FIX IT

    return 0;
}