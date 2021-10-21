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
    for (size_t i = 0; i < n; i++) {
        new_str[i] = __input[i];
    }
    return new_str;
}

// Get a substr starting at position __start_index (INCLUSIVE) and ending at __end_index (INCLUSIVE) because fuck python
/* RANT
*
*   Every mathematical programming language/toolbox (FORTRAN, MATLAB, even NUMPY) use the syntax
*   of start:stop. Thus, I will not use Python's bullshit string slicing and have decided
*   to include the __end_index in the substring
*
*   substr(__s1, 0, 1) returns a substring containing the characters at both 0 and 1
*/
// Doesn't check if the bounds are even legit, so make sure you are passing positive bounds and don't extend
// byond the original string's length
char * substr(const char * __s1, const size_t __start_index, const size_t __end_index) {

    size_t size_char = sizeof(char);
    size_t len_substr = __end_index - __start_index + 1;
    size_t num_bytes = size_char * len_substr;

    char * str = (char *) malloc(size_char * (len_substr + 1));

    if(str) {
        memcpy((void *) str, (void *) (__s1 + __start_index), size_char * (len_substr));
        str[len_substr] = 0;
    }

    return str;

}

// This function attempts to replicate the python slice. Thus, __end_index_py is NOT INCLUDED in the resulting slice
// Thus, slice(__s1, x, x) returns a string with length 0 (a character pointer to the null character)
char * slice(const char * __s1, const int __start_index_py, const int __end_index_py) {

    size_t size_char = sizeof(char);
    size_t start_index = 0;
    size_t end_index = 0;
    size_t str_len = 0;

    // Determine the appropriate bounds
    if (__start_index_py < 0) {

        str_len = strlen(__s1);
        start_index = str_len - (size_t) abs(__start_index_py);

        if (__end_index_py < 0) {

            end_index = str_len - (size_t) abs(__end_index_py);

        } else {
            end_index = (size_t) __end_index_py;
        }

    } else  {

        str_len = strlen(__s1);
        start_index = (size_t) __start_index_py;

        if (__end_index_py < 0) {

            end_index = str_len - (size_t) abs(__end_index_py);

        } else {
            end_index = (size_t) __end_index_py;
        }
    }

    size_t len_substr = 0;

    if (end_index >= start_index) {
        len_substr = end_index - start_index;
    } else {
        return NULL;
    }

    char * str = (char *) malloc(size_char * (len_substr + 1));

    if (str) {

        for (size_t i = start_index; i < end_index; i++) {
            str[i - start_index] = __s1[i];
        }
    } else {
        return NULL;
    }

    str[len_substr] = 0;

    return str;

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

    if(strlen(__expr) < 2) {
        return false;
    }

    int status = 0; // status of parenthesis. +1 for '(' -1 for ')'
                    // if the status drops below zero, return false
                    // only return true if status == 0 at the end of reading the string

    for(char * p = __expr; *p != '\0'; p ++) {

        if ( *p == '(' ) {
            status ++;
        } else if ( *p == ')') {
            status --;
        }

        if (status < 0) {
            return false;
        }
    }

    return status == 0;
}

bool est_bien_parenthesee_n(const char * const __expr, size_t __n) {

    if (__n < 2) {
        return false;
    }

    int status = 0; // status of parenthesis. +1 for '(' -1 for ')'
                    // if the status drops below zero, return false
                    // only return true if status == 0 at the end of reading the string

    for (size_t i = 0; i < __n; i++) {

        if ( __expr[i] == '(' ) {
            status ++;
        } else if ( __expr[i] == ')') {
            status --;
        }

        if ( status < 0 ) {
            return false;
        }
    }

    return status == 0;
}


// Find the longest string that is properly parenthesized
char * plus_longue_expr(const char * const __expr_alg)
{

    char * expr_reduced = extract_parentheses(__expr_alg);
    char * longue_expr = NULL;
    size_t str_len = strlen(expr_reduced);
    char * sub_str = NULL;
    // now that we have a copy, we can start changing the end points to test shorter string sections
    bool expr_found = false;

    size_t i = 0;
    size_t j = 0;
    // start with the longest string section (the whole string)
    for (i = 0; i < str_len - 1; i++) {

        for (j = 0; j < str_len - i - 1; j++) {// remove segments from the end

            sub_str = substr(expr_reduced, i, str_len - j - 1);
            if (est_bien_parenthesee(sub_str)) {
                expr_found = true;
                goto fuck_up;
            }


        }
    }
    fuck_up: // This label is called fuck up because I made a mistake and thought that the break statement will
            // break you out of all loops. That's pretty stupid. Instead it only breaks you out of the inner loop
            // and I should have known better.

    if (expr_found) {
        longue_expr = sub_str;
    }

    return longue_expr; // Will be null if expression was not found

}

// count the number of space, tab, or newline delimited words
size_t count_words(const char * __string) {

    // decompose a string that is separated by spaces
    size_t len = strlen(__string); // we can avoid this

    // count the words that exist in a string

    // a word can be separated by any number of spaces or tabs

    size_t n_words = 0;

    while (*__string != '\0') {

        if (__string[0] != ' ' && __string[0] != '\n' && __string[0] != '\t') { // If the current character is not a space
            // and next character is a space of null character
            if(__string[1] == ' ' || __string[1] == '\n' || __string[1] == '\t' || __string[1] == '\0') {
                n_words ++;
            }
        }

        __string++;

    }

    return n_words;
}

char * int_to_string(int __x) {
// Take an integer and return a null terminated string of that integer.
// if the number is negative, take that into account and return a string that
// includes the negative sign

    int n_digits = nb_chiffres_(__x);
    int str_length = 0;
    char * num_str = NULL;

    if ( __x > 0 ) {

        str_length = n_digits + 1;

    } else {

        str_length = n_digits + 2; // Allocate space for the digits, a negative sign, and a null-terminated string

    }

    num_str = (char *) malloc(sizeof(char) * (str_length));
    num_str[str_length - 1] = '\0';

    sprintf(num_str, "%d", __x);

    return num_str;

}

static int nb_chiffres_(long x) {
// Return the number of digits for an integer
// nb_chiffres(-10) returns 2
// nb_chiffres(100) returns 3
    return (int) log10((double) labs(x) ) + 1;
}