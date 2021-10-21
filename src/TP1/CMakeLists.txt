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

foreach(FILE ${TP1_SRC_FILES})
    message(STATUS "Adding ${FILE}")
    add_executable(${FILE} "${FILE}.c")
endforeach(FILE)

add_library(hello_dep autre.c encore_une_autre.c)
target_link_libraries(hello hello_dep)

target_link_libraries(ex7 m)
target_link_libraries(ex11 m)
target_link_libraries(ex12 m)
target_link_libraries(ex13 m)
target_link_libraries(ex15 m)
