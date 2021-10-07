// Parentheses
#include "ejovo_string.h"

// Return the longest string that is bien parenthesee
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

int main() {

    char exp_alg[] = "(a + x - 2)*(e^x - (2 * 2))+(3)";
    char test[] = "())))";

    printf("Expression: '%s', reduced: '%s'\n", exp_alg, extract_parentheses(exp_alg)); // extract_parenthesis defined in "ejovo_string.c"
    printf("est_bien_parenthese(exp_alg) = %d\n", est_bien_parenthesee(exp_alg)); // est_bien_parenthesee defined in "ejovo_string.c"
    printf("est_bien_parenthese(exp_alg) = %d\n", est_bien_parenthesee(test)); // est_bien_parenthesee defined in "ejovo_string.c"
    printf("est_bien_parenthese(exp_alg) = %d\n", est_bien_parenthesee("()(())")); // est_bien_parenthesee defined in "ejovo_string.c"
    printf("est_bien_parenthese(exp_alg) = %d\n", est_bien_parenthesee("()")); // est_bien_parenthesee defined in "ejovo_string.c"
    printf("est_bien_parenthese(exp_alg) = %d\n", est_bien_parenthesee_n(test, 3)); // est_bien_parenthesee defined in "ejovo_string.c"

    printf("Longest section of '%s': '%s'\n", test, plus_longue_expr(test));
    printf("Longest section of '%s': '%s'\n", exp_alg, plus_longue_expr(exp_alg));

    return 0;
}