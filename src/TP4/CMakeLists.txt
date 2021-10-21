set(TP4_SRC_FILES

    ex1
    ex2
    ex3
    ex4
    ex5
    ex6
    ex7

)

set(TP4_SRC_LIBS

    ejovo

)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN}/TP4)

if (NOT WIN32)
    list(APPEND TP4_SRC_LIBS m)
endif()


foreach(FILE ${TP4_SRC_FILES})
    message(STATUS "Adding TP4_${FILE}")
    add_executable("TP4_${FILE}" "${FILE}.c")
    target_link_libraries("TP4_${FILE}" ${TP4_SRC_LIBS})
    set_target_properties(TP4_${FILE} PROPERTIES OUTPUT_NAME ${FILE})
endforeach(FILE)
