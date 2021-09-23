add_executable(ex9 ex9.c)

target_link_libraries(ex9 m)

message("Trying to include directory ${CMAKE_SOURCE_DIR}/inc/battleship")

target_include_directories(ex9 PUBLIC "${CMAKE_SOURCE_DIR}/inc/battleship")
target_include_directories(ex9 PUBLIC "${CMAKE_SOURCE_DIR}/inc")
target_compile_options(ex9 PUBLIC -Wall)