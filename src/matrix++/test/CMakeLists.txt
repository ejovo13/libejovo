add_executable(t_AbsView t_AbsView.cpp)
add_executable(t_Matrix t_Matrix.cpp)

target_link_libraries(t_AbsView PUBLIC matrix++)
target_link_libraries(t_Matrix PUBLIC matrix++)
# target_link_libraries(t_Matrix INTERFACE matplot)
# target_link_libraries(t_Matrix INTERFACE pyth3)
# target_include_directories()
# target_link_libraries(t_Matrix matplot)