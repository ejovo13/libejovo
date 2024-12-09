set(EXECUTABLES avi2mp4 hello_ejovo mandelbrot)

macro(add_ejovo_executable prog_name src_file)
  add_executable(${prog_name} ${src_file})
  target_link_directories(${prog_name} PUBLIC ${INC})
  target_link_libraries(${prog_name} ejovo)
endmacro()

foreach(PROG ${EXECUTABLES})
  add_ejovo_executable(${PROG} "${PROG}.c")
endforeach()

if(${FFMPEG_FOUND})

  # add_executable(avi2mp4 avi2mp4.c) add_executable(hello_ejovo hello_ejovo.c)
  # target_link_directories(avi2mp4 PUBLIC ${INC})
  # target_link_directories(hello_ejovo PUBLIC ${INC})
  # target_link_libraries(hello_ejovo ejovo) target_link_libraries(avi2mp4
  # ejovo)
  install(TARGETS ${EXECUTABLES} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

endif()

message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
