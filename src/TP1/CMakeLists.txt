set(TP1_SRC_FILES
    # autre
    # encore_une_autre
    increment
    hello
    ex3
    ex5
    ex6
    ex7
    ex8
    ex9
    ex10
    ex11
    ex12
    ex13
    ex14
    ex15
)

set(TP1_LIB
    autre
    encore_une_autre
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN}/TP1)

foreach(FILE ${TP1_SRC_FILES})
    message(STATUS "Adding TP1_${FILE}")
    add_executable("TP1_${FILE}" "${FILE}.c")
    set_target_properties("TP1_${FILE}" PROPERTIES OUTPUT_NAME ${FILE})
endforeach(FILE)

add_library(hello_dep autre.c encore_une_autre.c)
target_link_libraries(TP1_hello hello_dep)

if(NOT WIN32)

    target_link_libraries(TP1_ex7 m)
    target_link_libraries(TP1_ex11 m)
    target_link_libraries(TP1_ex12 m)
    target_link_libraries(TP1_ex13 m)
    target_link_libraries(TP1_ex15 m)

endif()

