# set(EJOVO_MATRIX_SRC

#     # matrix_d.c
#     # matrix_f.c
#     # matrix_i.c

# )

# set(EJOVO_MATRIX_SRC

#     # matrix_core.c
#     # matrix_foreach.c
#     # matrix_state.c
#     # matrix_vector.c
#     # matrix_linear.c
#     # matrix_getset.c
#     # matrix_compute.c
#     # matrix_iter.c
#     # matrix_special.c
#     # matrix_stats.c
#     # matrix_dist.c
#     # matrix_functional.c
#     # matrix_logical.c
#     # matrix_index.c
#     # matrix_stochastic.c
#     # matrix_getset.c

# )

file(MAKE_DIRECTORY ${INC}/matrix)
# add_library(ejovo_matrix_double OBJECT ${EJOVO_MATRIX_SRC})

add_library(ejovo_matrix_double OBJECT matrix_d.c)
add_library(ejovo_matrix_int OBJECT matrix_i.c)
add_library(ejovo_matrix_float OBJECT matrix_f.c)
add_library(ejovo_matrix_complex OBJECT matrix_c.c)

# Defining FIRST_COMPILATION_PASS allows me to add the definitions for M_PI and a few other 
# constants ONLY ONCE
target_compile_definitions(ejovo_matrix_double PUBLIC FIRST_COMPILATION_PASS) 
# target_compile_definitions(ejovo_matrix_int PUBLIC FIRST_COMPILATION_PASS)
# target_compile_definitions(ejovo_matrix_float PUBLIC FIRST_COMPILATION_PASS)

target_include_directories(ejovo_matrix_double PUBLIC ${INC}/matrix)
target_include_directories(ejovo_matrix_int PUBLIC ${INC}/matrix)
target_include_directories(ejovo_matrix_float PUBLIC ${INC}/matrix)
target_include_directories(ejovo_matrix_complex PUBLIC ${INC}/matrix)


# set_target_properties(ejovo_matrix PROPERTIES
#     HEADER_DIRS
#         ${INC}/matrix

# )