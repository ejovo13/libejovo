list(APPEND SRC
    ex1
    ex2
    ex3
    ex4
    ex5
    # ex6
    # ex7
    # ex8
    # ex9
    # ex10
    # ex11
    # ex12
    # ex13
    # ex14
    # ex15
)

foreach(FILE ${SRC})
    message(STATUS "Adding ${FILE}")
    add_executable(${FILE} "${FILE}.c")
endforeach(FILE)

target_link_libraries(ex1 m)
target_link_libraries(ex2 m)
target_link_libraries(ex3 m)
target_link_libraries(ex4 m)
target_link_libraries(ex5 m)