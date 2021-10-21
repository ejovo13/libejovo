set(TP2_SRC_FILES

    test
    ex1
    ex2
    ex3
    ex4
    ex5
    ex7
    ex8
    ex10
    ex11
    learn_pointers

)

set(TP2_SRC_LIBS

    ejovo

)

if (NOT WIN32)
    list(APPEND TP2_SRC_LIBS m)
endif()

add_subdirectory(ex9)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN}/TP2)

foreach(FILE ${TP2_SRC_FILES})
    message(STATUS "Adding TP2_${FILE}")
    add_executable("TP2_${FILE}" "${FILE}.c")
    target_link_libraries("TP2_${FILE}" ${TP2_SRC_LIBS})
    set_target_properties("TP2_${FILE}" PROPERTIES OUTPUT_NAME ${FILE})
endforeach(FILE)
