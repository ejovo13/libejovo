set(TP6_SRC_FILES

    ex1
    ex2
    # ex3
    # ex4
    ex5
    # ex6
    # ex7

)

set(TP6_SRC_LIBS

    ejovo

)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN}/TP6)

if (NOT WIN32)
    list(APPEND TP6_SRC_LIBS m)
endif()


foreach(FILE ${TP6_SRC_FILES})
    message(STATUS "Adding TP6_${FILE}")
    add_executable("TP6_${FILE}" "${FILE}.c")
    target_link_libraries("TP6_${FILE}" ${TP6_SRC_LIBS})
    set_target_properties(TP6_${FILE} PROPERTIES OUTPUT_NAME ${FILE})
endforeach(FILE)
