set (EJOVO_LIB

    ejovo_print.c
    ejovo_rand.c
    ejovo_string.c
    ejovo_input.c
    ejovo_matrix.c
    ejovo_labyrinth.c
    ejovo_sort.c
    ejovo_comp.c

)

set (EJOVO_LIB_HEADERS

    ${INC}/ejovo_print.h
    ${INC}/ejovo_rand.h
    ${INC}/ejovo_string.h
    ${INC}/ejovo_input.h
    ${INC}/ejovo_matrix.h
    ${INC}/ejovo_labyrinth.h
    ${INC}/ejovo_sort.h
    ${INC}/ejovo_comp.h

)



add_library(ejovo STATIC ${EJOVO_LIB})
if (NOT WIN32)
    target_link_libraries(ejovo m)
endif()
target_include_directories(ejovo PRIVATE "${CMAKE_SOURCE_DIR}/inc")

set_target_properties(ejovo PROPERTIES

    PUBLIC_HEADER "${EJOVO_LIB_HEADERS}"

)

include(GNUInstallDirs)
install(TARGETS ejovo
    PUBLIC_HEADER
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ejovo
)

# message("Trying to include directory ${CMAKE_SOURCE_DIR}/inc/battleship")

# target_include_directories(ex9 PUBLIC "${CMAKE_SOURCE_DIR}/inc/battleship")
# target_include_directories(ex9 PUBLIC "${CMAKE_SOURCE_DIR}/inc")
# target_compile_options(ex9 PUBLIC -Wall)