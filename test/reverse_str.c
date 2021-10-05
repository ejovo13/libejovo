// test reverse_string and reverse_string_n functions
#include "ejovo_string.h"
#include <assert.h>

int main() {

    char test_str[] = "This\n is a string that I will reverse";
    size_t num_chars = strlen(test_str);
    char test_str_reverse[] = "esrever lliw I taht gnirts a si \nsihT";

    // forward reversing
    assert(strcmp(reverse_string(test_str), test_str_reverse) == 0);
    // backward
    assert(strcmp(reverse_string(test_str_reverse), test_str) == 0);
    // check that the reverse of a reversed string is the starting string
    assert(strcmp( reverse_string(reverse_string(test_str)), test_str ) == 0);

    /*
    *   reverse_string_n
    *
    */

    // forward reversing
    assert(strcmp(reverse_string_n(test_str, num_chars), test_str_reverse) == 0);
    // backward
    assert(strcmp(reverse_string_n(test_str_reverse, num_chars), test_str) == 0);
    // check that the reverse of a reversed string is the starting string
    assert(strcmp( reverse_string_n(reverse_string_n(test_str, num_chars), num_chars), test_str ) == 0);

    return 0;
}