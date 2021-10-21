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

if (NOT WIN32)
    list(APPEND TP4_SRC_LIBS m)
endif()


foreach(FILE ${SRC_FILES})
    message(STATUS "Adding executable ${FILE}")
    add_executable(${FILE} "${FILE}.c")
    target_link_libraries(${FILE} ${TP4_SRC_LIBS})
endforeach(FILE)
