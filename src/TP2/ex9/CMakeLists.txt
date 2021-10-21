set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN}/TP2)

add_executable(ex9 ex9.c)
target_link_libraries(ex9 m ejovo)


message("Trying to include directory ${INC}/battleship")

target_include_directories(ex9 PUBLIC ${INC}/battleship)
target_include_directories(ex9 PUBLIC ${INC})
# target_compile_options(ex9 PUBLIC -Wall)