set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../../)
add_executable(t_cuda cuda_test.cu)

set_property(TARGET t_cuda
             PROPERTY CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(t_cuda INTERFACE matrix++)
target_include_directories(t_cuda PUBLIC ${PROJ_INC})
