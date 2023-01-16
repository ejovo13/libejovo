if (${FFMPEG_FOUND})

    add_executable(avi2mp4 avi2mp4.c)
    target_link_directories(avi2mp4 PUBLIC ${INC})
    target_link_libraries(avi2mp4 ejovo)
    install(
        TARGETS avi2mp4
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    )

endif()

message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
