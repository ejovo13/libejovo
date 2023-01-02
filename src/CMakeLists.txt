add_executable(avi2mp4 avi2mp4.c)
target_link_directories(avi2mp4 PUBLIC ${INC})
target_link_libraries(avi2mp4 ejovo)