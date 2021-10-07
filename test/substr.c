// Test functions to get substr from a larger string, slice as well

#include "ejovo_string.h"

int main() {

    char str[] = "Hello this is a large string!";
    size_t str_len = strlen(str);

    printf("substr(str, 0, 1): '%s'\n", substr(str, 0, 1));
    printf("substr(str, 5, 10): '%s'\n", substr(str, 5, 10));
    printf("substr(str, 0, 5): '%s'\n", substr(str, 0, 5));
    printf("substr(str, 10, -2): '%s'\n", substr(str, 10, -2));
    printf("substr(str, 1, 0): '%s'\n", substr(str, 1, 0));

    printf("slice(str, 0, 4): '%s'\n", slice(str, 0, 4));
    printf("slice(str, 0, 0): '%s'\n", slice(str, 0, 0));
    printf("slice(str, 5, -1): '%s'\n", slice(str, 5, -1));
    printf("slice(str, -25, 15): '%s'\n", slice(str, -25, 15));


    return 0;
}