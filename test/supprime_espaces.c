// test function supprime_espace
#include "ejovo_string.h"
#include <assert.h>

int main() {

    char test_str1[] = "This is test string 1";
    char test_str2[] = "This \n\ni \ns t e s\n t \n str i\nng \n  \n2";
    char test_str3[] = "Th\n \t \t \n i\t s    i s \tt \n e  s\n \nt \t string 3";

    char str1_stripped[] = "Thisisteststring1";
    char str2_stripped[] = "Thisisteststring2";
    char str3_stripped[] = "Thisisteststring3";

    // test removing spaces
    assert(strcmp(str1_stripped, supprime_espaces(test_str1)) == 0);
    // test removing new line characters
    assert(strcmp(str2_stripped, supprime_espaces(test_str2)) == 0);
    // test removing tabs
    assert(strcmp(str3_stripped, supprime_espaces(test_str3)) == 0);

    return 0;
}