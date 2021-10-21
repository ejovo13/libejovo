set(TP3_SRC_FILES

    ex1
    ex2
    ex3
    ex4
    ex5
    ex6
    ex7

)

set(TP3_SRC_LIBS

    ejovo

)

if (NOT WIN32)
    list(APPEND TP3_SRC_LIBS m)
endif()

# add_subdirectory(ex9)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN}/TP3)

foreach(FILE ${TP3_SRC_FILES})
    message(STATUS "Adding TP3_${FILE}")
    add_executable("TP3_${FILE}" "${FILE}.c")
    target_link_libraries(TP3_${FILE} ${TP3_SRC_LIBS})
    set_target_properties(TP3_${FILE} PROPERTIES OUTPUT_NAME ${FILE})
endforeach(FILE)
