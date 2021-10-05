// Test cpy_str and cpy_n_str functions definied in "ejovo_string.h"
#include "ejovo_string.h"
#include "assert.h"

int main() {

    char test_str[] = "Hello this is the string that I am going to copy\n";
    size_t str_len = strlen(test_str);

    assert(strcmp(test_str, cpy_str(test_str)) == 0); // strcmp returns 0 if the strings are equal
    assert(strcmp(test_str, cpy_n_str(test_str, strlen(test_str))) == 0);
    assert(strcmp(test_str, cpy_n_str(test_str, str_len)) == 0);

    return 0;
}