# TP3
![Ubuntu](https://github.com/ejovo13/informatique-TP3/actions/workflows/Ubuntu.yml/badge.svg)

This repo contains my solutions to the exercises presented in TP3. All of the exercises can be made with CMake. Unfortunately, CMake will not successfully build on MacOs since `ejovo_rand.h` makes use of the `getrandom` function that is only defined on Linux systems. Hence, the build is passing for Ubuntu and builds just fine on my arch machine.

## SRC

Contains the programs that exhibit behavior prescribed by the exercises.

## INC

Inc contains the super important header files `ejovo_*` that declare many of the functions written to complete the TP exercises. Their corresponding definitions can be found in `./src/ejovo`

## TEST

Tests can be run with `ctest` or `make test` while in the build directory. The tests verify that the functions declared in `ejovo_string` are working properly.

# Exercise 1
The function `reverse` recursively prints the last digit of a passed integer to stdout. If the number is negative the negative sign will only be printed once.

The program `ex1` asks for the user's input as an integer and then prints the number in reverse order.

# Exercise 2
In `ex2.c` 5 new functions are declared and defined:
- `nb_chiffres`
- `extrait_nombre`
- `est_pair`
- `somme_des_chiffres`
- `est_coucable`

The main program generates a uniform random integer in the range [0, 5000], and then prints to stdout the results of
`extrait_nombre`, `somme_des_chiffres`, and `est_coucable`.

# Exercise 3
Call the function `supprime_espaces` that is declared in `ejovo_string.h`.

# Exercise 4
Complete subsections 1, 2, and 3. The function `afficher_miroir` is called in the main executable ex3
alongside the reversing function created in parts 1 and 2.

The main program reverses a sample string and then asks the user for a string to reverse.

# Exercise 5
Define a new function `is_palindrome` and then test out the function in `main` with various test strings. The function `is_palindrome` ignores case.

# Exercise 6
The main function of exercise 6 calls the function `del_substr` that is declared in `ejovo_string.h`. This function deletes a substring (recursively ;) ) if it exists in a full string.

# Exercise 7
2. -- ()(()) correct
   -- ()))   incorrect - way too many ')'
   -- ())(() incorrect - ) not matched with anything

3. Function `est_bien_parenthesee` declared in `ejovo_string.h`
4. Function `plus_longue_expr` declared in `ejovo_string.h`

The executable ex7 tests if several expressions are properly parenthesized and then also calls `plus_longue_expression`.