[[_TOC_]]

# TP3
![Ubuntu](https://github.com/ejovo13/informatique-TP3/actions/workflows/Ubuntu.yml/badge.svg)

This repo contains my solutions to the exercises presented in TP3. All of the exercises can be made with CMake. Unfortunately, CMake will not successfully build on MacOs since `ejovo_rand.h` makes use of the `getrandom` function that is only defined on Linux systems. Hence, the build is passing for Ubuntu and builds just fine on my arch machine.

## SRC

Contaions the programs that exhibit prper behavior as prescribed by the exercises.

## INC

Inc contains the super important header files `ejovo_*` that declare many of the functions written to complete the TP exercises. Their corresponding definitions can be found in `./src/ejovo`

## TEST

Tests can be run with `ctest` or `make test` while in the build directory.

# Exercice 1

