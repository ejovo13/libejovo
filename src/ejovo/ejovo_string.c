#include "ejovo_string.h"

// copy a NULL TERMINATED STRING into another one, without being given the length of the string
char * cpy_str(char * __input) {
    size_t len = strlen(__input);
    printf("Size __input: %ld\n", len);
    char * new_str = (char *) calloc(len + 1, sizeof(char));
    strcpy(new_str, __input);
    return new_str;
}

// copy a NULL TERMINATED STRING into another one, specifiying ahead of time the length of the string to copy
// We follow the convention established by string.h where strlen() returns the number of characters not including the null string;
char * cpy_n_str(char * __input, size_t n) {
    char * new_str = (char *) calloc(n + 1, sizeof(char));
    strcpy(new_str, __input);
    return new_str;
}

// take an input string and return a copy that has been reversed.
char * reverse_string(const char * __string) {

    size_t __string_length = strlen(__string);
    char * duplicate = (char *) malloc (sizeof(char) * (__string_length + 1));

    for (size_t i = 0; i < __string_length; i ++) {
        duplicate[__string_length - 1 - i] = __string[i];
    }
    duplicate[__string_length] = '\0';

    return duplicate;

}

// Tell me how long the string is (without null-terminating character) and then reverse the string
char * reverse_string_n(const char * __string, size_t __string_length) {

    char * duplicate = (char *) malloc (sizeof(char) * (__string_length + 1));

    for (size_t i = 0; i < __string_length; i ++) {
        duplicate[__string_length - 1 - i] = __string[i];
    }
    duplicate[__string_length] = '\0';
    return duplicate;

}

// Delete spaces from a string and return a new string who has no spaces, also save the number of spaces removed
char * supprime_espaces(const char * __input) {

    // return the number of spaces deleted,
    size_t len = strlen(__input);

    size_t num_spaces = 0;
    // count number of spaces
    for (size_t i = 0; i < len; i ++) {
        if(__input[i] == ' ' || __input[i] == '\n' || __input[i] == '\t') { num_spaces ++; }
    }

    // initialize a new string whose length is len - num_spaces
    size_t new_str_capacity = len - num_spaces + 1;
    char * new_str = (char *) malloc(sizeof(char) * new_str_capacity);

    // Fill new string
    new_str[new_str_capacity-1] = '\0';

    size_t i_new = 0; // index of new string
    for (size_t i = 0; i < len; i ++) {
        if(__input[i] != ' ' && __input[i] != '\n'&& __input[i] != '\t') {
            new_str[i_new] = __input[i];
            i_new ++;
        }
    }

    return new_str;
}

// Delete spaces from a string and return a new string who has no spaces, also save the number of spaces removed
char * supprime_espaces_n(const char * __input, size_t * __nb_esp_supp) {

    // return the number of spaces deleted,
    size_t len = strlen(__input);

    size_t num_spaces = 0;
    // count number of spaces
    for (size_t i = 0; i < len; i ++) {
        if(__input[i] == ' ' || __input[i] == '\n' || __input[i] == '\t') { num_spaces ++; }
    }

    // initialize a new string whose length is len - num_spaces
    size_t new_str_capacity = len - num_spaces + 1;
    char * new_str = (char *) malloc(sizeof(char) * new_str_capacity);

    // Fill new string
    new_str[new_str_capacity-1] = '\0';

    size_t i_new = 0; // index of new string
    for (size_t i = 0; i < len; i ++) {
        if(__input[i] != ' ' && __input[i] != '\n'&& __input[i] != '\t') {
            new_str[i_new] = __input[i];
            i_new ++;
        }
    }

    *__nb_esp_supp = num_spaces;

    return new_str;
}

bool is_substr(const char * __s1, const char * __s2) {
// How to determine if __s2 is entirely contained in __s1?

    size_t i1 = 0; // index of string 1
    size_t i2 = 0; // index of string 2
    size_t s2_chars_in_s1 = 0;

    while (__s1[i1] != '\0') { // While we haven't reached the null character, scan for string 2

        // printf("Comparing s1[%lu]: %c, s2[%lu]: %c\t", i1, __s1[i1], i2, __s2[i2]);

        if (__s2[i2] == '\0') { // then we have finished scanning through s2, return whether or not s2 is contained
            // printf("Reached end of string2\n");
            // printf("s2_chars_in_s1 = %lu\n", s2_chars_in_s1);
            // printf("i1: %lu, i2: %lu\n", i1, i2);
            break;
        }

        if(__s1[i1] == __s2[i2]) { // While the current __s1 character is equal to the current

            // printf("Matched character: %c\n", __s2[i2]);
            s2_chars_in_s1 ++;
            i2 ++;

        } else {

            // printf("Unmatched character: %c\n", __s2[i2]);
            if(__s1[i1] == __s2[0]) {
                // If this new unmatched character is also the same character of our substring, we want to match it
                // printf("Matched character: %c\n", __s2[0]);
                s2_chars_in_s1 = 1;
                i2 = 1;
            } else {

                s2_chars_in_s1 = 0;
                i2 = 0; // reset str2 index to it's initial position
                // i1 --; // This is crazy, we want to go back in time
            }
        }

        i1 ++;
    }

    return s2_chars_in_s1 == strlen(__s2);
}

char * del_substr(const char * const __s1, const char * const __substr) {

    // this sounds like a job for RECURSION!!!!!!!!!!
    size_t len_substr = strlen(__substr);
    size_t len_s1 = strlen(__s1);
    char * reduced_str = __s1;
    char * substr_pos = NULL; // pointer to where the __substr appears in __s1

    size_t first_index = 0; // First index of __s1 that matches __substr

    // While the substr is contained in __s1, go ahead and remove it
    if ( is_substr(__s1, __substr) ) {

        // printf("Substring '%s' found in '%s'\n", __substr, __s1);
        substr_pos = strstr(__s1, __substr); // strstr returns a pointer to the first instance of __substr in __s1
        first_index = substr_pos - __s1;
        // printf("First index = %lu\n", first_index);
        reduced_str = (char *) malloc(sizeof(char) * (len_s1 - len_substr + 1)); // Allocate a new string that is length of __s1 minus length of __substr

        // fill the first part of the string
        for (size_t i = 0; i < first_index; i++) {

            reduced_str[i] = __s1[i];

        }

        // fill the second part of the string
        for (size_t i = first_index; i <= len_s1 - len_substr; i ++) {

            reduced_str[i] = __s1[i + len_substr];

        }

        // printf("Reduced string: %s\n", reduced_str);

        reduced_str = del_substr(reduced_str, __substr);
        return reduced_str;

    } else {
        // printf("Returning '%s'\n", __s1);
        return __s1;
    }
}

// ecrire une fonction qui prend une expression algebrique en entree et
// renvoi un tableau de caracteres ne contenant que les parentheses
char * extract_parentheses(const char * const __expr_alg) {

    uint32_t num_parenthesis = 0;
    size_t str_len = strlen(__expr_alg);
    // First thing to do is count the number of parenthesis
    for( size_t i = 0; i < str_len; i ++) {
        if ( __expr_alg[i] == '(' || __expr_alg[i] == ')' ) {
            num_parenthesis ++;
        }
    }

    char * parenthesis = (char *) malloc(sizeof(char) * (num_parenthesis + 1));
    parenthesis[num_parenthesis] = '\0';
    size_t p_index = 0; // index of parenthesis string

    for( size_t i = 0; i < str_len; i ++) {
        if ( __expr_alg[i] == '(' || __expr_alg[i] == ')' ) {
            parenthesis[p_index] = __expr_alg[i];
            p_index ++;
        }
    }
    return parenthesis;
}

bool est_bien_parenthesee(const char * const __expr) {

    int status = 0; // status of parenthesis. +1 for '(' -1 for ')'
                    // if the status drops below zero, return false
                    // only return true if status == 0 at the end of reading the string

    for(char * p = __expr; *p != '\0'; p ++) {

        if ( *p == '(' ) {
            status ++;
        } else if ( *p == ')') {
            status --;
        }

        if ( status < 0 ) {
            return false;
        }
    }

    return status == 0;
}