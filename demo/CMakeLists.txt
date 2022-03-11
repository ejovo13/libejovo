add_executable(d_vector d_vector.c)
add_executable(d_functional d_functional.c)
add_executable(d_stochastic d_stochastic.c)

target_link_libraries(d_vector ejovo m)
target_link_libraries(d_functional ejovo m)
target_link_libraries(d_stochastic ejovo m)
