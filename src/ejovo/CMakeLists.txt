add_library(ejovo ejovo_print.c ejovo_rand.c ejovo_string.c)

target_link_libraries(ejovo m)
target_include_directories(ejovo PUBLIC "${CMAKE_SOURCE_DIR}/inc")

# message("Trying to include directory ${CMAKE_SOURCE_DIR}/inc/battleship")

# target_include_directories(ex9 PUBLIC "${CMAKE_SOURCE_DIR}/inc/battleship")
# target_include_directories(ex9 PUBLIC "${CMAKE_SOURCE_DIR}/inc")
# target_compile_options(ex9 PUBLIC -Wall)