# set (EJOVO_MODULES

#     "print"
#     "rand"
#     "string"
#     input
#     labyrinth
#     input
#     matrix
#     labyrinth
#     sort
#     comp
#     crypto
# )


set (EJOVO_LIB

    ejovo_print.c
    ejovo_rand.c
    ejovo_string.c
    ejovo_input.c
    # ejovo_labyrinth.c
    ejovo_sort.c
    ejovo_comp.c
    ejovo_crypto.c
    ejovo_list.c
    ejovo_bin.c
    ejovo_dataframe.c
    ejovo_color.c
    ejovo_time.c
    ejovo_img.c

)

# I don't remember why I have to do this weird shit...
set (EJOVO_LIB_HEADERS

    ${INC}/ejovo_print.h
    ${INC}/ejovo_rand.h
    ${INC}/ejovo_string.h
    ${INC}/ejovo_input.h
    ${INC}/ejovo_matrix.h
    # ${INC}/ejovo_labyrinth.h
    ${INC}/ejovo_list.h
    ${INC}/ejovo_sort.h
    ${INC}/ejovo_comp.h
    # ${INC}/ejovo_comp_matrix.h
    ${INC}/ejovo_crypto.h
    ${INC}/ejovo_bin.h
    ${INC}/ejovo_dataframe.h
    ${INC}/ejovo_color.h
    ${INC}/ejovo_time.h
    ${INC}/ejovo_img.h
    ${INC}/ejovo.h
    ${INC}/ejovo_assert.h
    ${INC}/ejovo_matrix_generic.h
    # ${INC}/ejovo_simulation.h
)

set (EJOVO_MATRIX_HEADERS

    ${INC}/matrix/matrix_compute.h
    ${INC}/matrix/matrix_core.h
    ${INC}/matrix/matrix_dist.h
    ${INC}/matrix/matrix_foreach.h
    ${INC}/matrix/matrix_functional.h
    ${INC}/matrix/matrix_getset.h
    ${INC}/matrix/matrix_iter.h
    ${INC}/matrix/matrix_linear.h
    ${INC}/matrix/matrix_special.h
    ${INC}/matrix/matrix_state.h
    ${INC}/matrix/matrix_stats.h
    ${INC}/matrix/matrix_vector.h
    ${INC}/matrix/matrix_logical.h
    ${INC}/matrix/matrix.h
    ${INC}/matrix/matrix_d.h
    ${INC}/matrix/matrix_f.h
    ${INC}/matrix/matrix_i.h
    ${INC}/matrix/matrix_c.h
    ${INC}/matrix/generic_macros.h
)

# set (PCG_HEADERS

#     ${INC}/pcg/





# )

message("Current source: ${CMAKE_CURRENT_SOURCE_DIR}")
message("Source: ${CMAKE_SOURCE_DIR}")
message("Project: ${PROJECT_SOURCE_DIR}")

add_subdirectory(matrix)

# add_library(ejovo STATIC ${EJOVO_LIB} $<TARGET_OBJECTS:ejovo_matrix_double>)
# add_library(ejovo STATIC ${EJOVO_LIB} $<TARGET_OBJECTS:ejovo_matrix_int>)
# add_library(ejovo STATIC ${EJOVO_LIB} $<TARGET_OBJECTS:ejovo_matrix_float>)
add_library(ejovo STATIC ${EJOVO_LIB} $<TARGET_OBJECTS:ejovo_matrix_double>
                                      $<TARGET_OBJECTS:ejovo_matrix_int>
                                      $<TARGET_OBJECTS:ejovo_matrix_float>
                                      $<TARGET_OBJECTS:ejovo_matrix_complex>)
# target_link_libraries(ejovo PUBLIC ${PCG_RANDOM_LIBRARY})
if (NOT WIN32)
    if (EXISTS ${PCG_RANDOM_LIBRARY})
        target_link_libraries(ejovo m ${PCG_RANDOM_LIBRARY})
    else()
        target_link_libraries(ejovo m)
    endif()
endif()
target_include_directories(ejovo PUBLIC "${INC}")
target_include_directories(ejovo PUBLIC "${INC}/matrix")

set_target_properties(ejovo PROPERTIES

    PUBLIC_HEADER "${EJOVO_LIB_HEADERS}"
    # MATRIX_HEADER "${EJOVO_MATRIX_HEADERS}"

)

include(GNUInstallDirs)
install(TARGETS ejovo
    PUBLIC_HEADER
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ejovo
    # MATRIX_HEADER ${CMAKE_INSTALL_INCLUDEDIR}/matrix
)

install(DIRECTORY ${INC}/matrix
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ejovo)
