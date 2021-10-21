set (EJOVO_LIB

    ejovo_print.c
    ejovo_rand.c
    ejovo_string.c
    ejovo_input.c
    ejovo_matrix.c
    ejovo_labyrinth.c
    ejovo_sort.c

)




add_library(ejovo ${EJOVO_LIB})
if (NOT WIN32)
    target_link_libraries(ejovo m)
endif()
target_include_directories(ejovo PRIVATE "${CMAKE_SOURCE_DIR}/inc")

# message("Trying to include directory ${CMAKE_SOURCE_DIR}/inc/battleship")

# target_include_directories(ex9 PUBLIC "${CMAKE_SOURCE_DIR}/inc/battleship")
# target_include_directories(ex9 PUBLIC "${CMAKE_SOURCE_DIR}/inc")
# target_compile_options(ex9 PUBLIC -Wall)