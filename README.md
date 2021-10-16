# TP4
***
![Ubuntu](https://github.com/ejovo13/informatique-TP4/actions/workflows/Ubuntu.yml/badge.svg)
![MacOs](https://github.com/ejovo13/informatique-TP4/actions/workflows/Mac.yml/badge.svg)
![Windows](https://github.com/ejovo13/informatique-TP4/actions/workflows/Windows.yml/badge.svg)

This repo contains my solutions to the exercises presented in TP4. All of the exercises can be made with CMake. Unfortunately, CMake will not successfully build on MacOs since `ejovo_rand.h` makes use of the `getrandom` function that is only defined on Linux systems. Hence, the build is passing for Ubuntu and builds just fine on my arch machine.

Todo:
- [ ] Add build support for Mac and Windows

### Build
Build with cmake. The executable files will be output in the `bin` directory.
```Bash
mkdir build && cd build
cmake ../        # Generate configuration and makefiles
cmake --build ./ # Build the project according to the configuration
ctest --output-on-failure
```

### Test

Tests can be run with `ctest` or `make test` while in the build directory. The tests verify that the functions declared in the `ejovo_*` are working properly.
### Docs
Documentation for all of the functions declared in the `ejovo` headers can be found [here](https://ejovo13.github.io/informatique-TP4/)

## Matrix
---
This TP4 includes a matrix framework that is declared in `/inc/ejovo_matrix.h`. Check out the wiki **here** for more information about how to use the `Matrix` structure and check out the **docs** for more details.

