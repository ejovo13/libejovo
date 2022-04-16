# add_executable(t_AbsView t_AbsView.cpp)
# add_executable(t_Matrix t_Matrix.cpp)
# add_executable(t_DiffEq t_DiffEq.cpp)
# add_executable(t_Plot t_Plot.cpp)
# add_executable(t_Quad t_Quad.cpp)
add_executable(t_Grid t_Grid.cpp)

# target_link_libraries(t_AbsView PUBLIC matrix++)
# target_link_libraries(t_Matrix PUBLIC matrix++)
# target_link_libraries(t_DiffEq PUBLIC matrix++)
# target_link_libraries(t_Plot PUBLIC matrix++)
# target_link_libraries(t_Quad PUBLIC matrix++)
target_link_libraries(t_Grid PUBLIC matrix++)




# target_link_libraries(t_Matrix INTERFACE matplot)
# target_link_libraries(t_Matrix INTERFACE pyth3)
# target_include_directories()
# target_link_libraries(t_Matrix matplot)