#include "ejovo_string.h"
#include <assert.h>

int main() {

    char test_str[] = "Hello my friends I am a fancy \n test: string that contains\t very 999012 strange characters";

    // Test for case
    assert(!is_substr(test_str, "hello"));
    assert(is_substr(test_str, "Hello"));

    // Test for whole string
    assert(is_substr(test_str, test_str));

    // Test for part of the string
    assert(is_substr(test_str, test_str + 10));

    // Test for wacky symbols
    assert(is_substr(test_str, " \n "));
    assert(is_substr(test_str, "\t"));
    assert(!is_substr(test_str, "\r"));
    assert(is_substr(test_str, "\0")); // Because the length is technically zero, a substring only composed of the null
                                       //character will

    // Test for numbers
    assert(is_substr(test_str, "999"));
    assert(is_substr(test_str, "999012"));
    assert(!is_substr(test_str, "9990122"));

    // Test for begining and ending sequences
    assert(is_substr(test_str, "Hello my friends"));
    assert(is_substr(test_str, " strange characters"));

    return 0;
}