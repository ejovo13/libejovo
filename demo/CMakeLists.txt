add_executable(d_vector d_vector.c)
add_executable(d_functional d_functional.c)

target_link_libraries(d_vector ejovo m)
target_link_libraries(d_functional ejovo m)
