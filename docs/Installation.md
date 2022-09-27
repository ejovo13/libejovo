# Installation
![MacOS](https://github.com/ejovo13/libejovo/actions/workflows/Mac.yml/badge.svg)
![Ubuntu](https://github.com/ejovo13/libejovo/actions/workflows/Ubuntu.yml/badge.svg)

## Building from source

Libejovo is build with CMake. If you don't have CMake installed on your system you can install it [here](https://cmake.org/install/).

### MacOS/Linux

To build libejovo, start off simply by cloning the [public repository](https://github.com/ejovo13/libejovo) using 

ssh:
```Bash
git clone git@github.com:ejovo13/libejovo.git
```
or https:
```Bash
git clone https://github.com/ejovo13/libejovo.git
```

We recommend that you create a new `build` directory and then evoke CMake:

```Bash
mkdir build && cd build          
cmake ../                   # configuration
```

If you would like to change the default install location (`/usr/local/`) replace the last line with:
```
cmake ../ -DCMAKE_INSTALL_PREFIX=<new_location>
```
then compile the project
```Bash
cmake --build ./  
```

Run `ctest` to make sure that things are working as expected. If there are no errors, go ahead and install libejovo with:
```Bash
sudo cmake --install ./
```

### Windows

Libejovo is not currently supported on Windows





