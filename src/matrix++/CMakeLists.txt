
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(libejovo++)

# find_library(matplot REQUIRED)
include(FindPNG)
include(FindGnuplot)


enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(matrix++ INTERFACE)

set(PROJ_INC ${PROJECT_SOURCE_DIR}/include)
set(PROJ_TEST ${PROJECT_SOURCE_DIR}/test)

target_include_directories(matrix++ INTERFACE ${PROJ_INC})
add_compile_options(-Wno-narrowing)
# add_subdirectory(sciplot)
# include_directories(sciplot)
# include_directories(matplotplusplus/source/matplot/util)
# include_directories(matplotlib-cpp)
# include_directories(/usr/include/python3.10)
# include_directories(/usr/lib/python3.10/site-packages/numpy/core/include/)

# add_library(pyth3 INTERFACE)
# target_link_libraries(pyth3 INTERFACE crypt dl m)

# add_subdirectory(matplotlib-cpp)
# add_subdirectory(matplotplusplus)
add_subdirectory(${PROJ_TEST})


# add_executable(t_abs_view t_AbsView.cpp)
# target_link_libraries(t_abs_view matrix++)
