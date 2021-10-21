set(TP5_SRC_FILES

    ex1
    ex2
    ex3
    ex4
    ex5
    ex6
    ex7

)

set(TP5_SRC_LIBS

    ejovo

)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN}/TP5)

if (NOT WIN32)
    list(APPEND TP5_SRC_LIBS m)
endif()


foreach(FILE ${TP5_SRC_FILES})
    message(STATUS "Adding TP5_${FILE}")
    add_executable("TP5_${FILE}" "${FILE}.c")
    target_link_libraries("TP5_${FILE}" ${TP5_SRC_LIBS})
    set_target_properties(TP5_${FILE} PROPERTIES OUTPUT_NAME ${FILE})
endforeach(FILE)
