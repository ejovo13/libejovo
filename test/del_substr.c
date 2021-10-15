#include "ejovo_string.h"
#include <assert.h>

int main() {

    char test_str[] = "Hello this is a test string";
    char repeat[] = "HiHiHiHiHiHiHiHiHiHihi";

    // substrings
    char substr1[] = "this";
    char substr2[] = "is";
    char hello[] = "hello";
    char Hello[] = "Hello";

    // expected test results
    char test1[] = "Hello  is a test string";
    char test2[] = "Hello th  a test string";
    char test3[] = "hi";
    char test4[] = "HiHiHiHiHiHiHiHiHiHi";
    char test_hello[] = "Hello this is a test string";
    char test_Hello[] = " this is a test string";

    // Tests
    assert(strcmp(test1, del_substr(test_str, substr1)) == 0); // Test removing 'this'
    assert(strcmp(test2, del_substr(test_str, substr2)) == 0); // Test removing 'is' twice
    assert(strcmp(test3, del_substr(repeat, "Hi")) == 0);  // Test a lot of repetition and case
    assert(strcmp(test4, del_substr(repeat, "hi")) == 0);

    assert(strcmp(test_Hello, del_substr(test_str, Hello)) == 0);
    assert(strcmp(test_hello, del_substr(test_str, hello)) == 0);
    assert(strcmp("", del_substr(test_str, test_str)) == 0);  // Test removing the entire sub string

    return 0;
}