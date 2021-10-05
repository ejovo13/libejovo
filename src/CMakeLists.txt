list(APPEND SRC_FILES
    # test
    ex1
    ex2
    ex3
    ex4
    ex5
    ex6
    ex7
    # ex8
    # ex9
    # ex10
    # ex11
    # ex12
    # ex13
    # ex14
    # ex15
    # learn_pointers
)

# add_subdirectory(ex9)
add_subdirectory(ejovo)

foreach(FILE ${SRC_FILES})
    message(STATUS "Adding executable ${FILE}")
    add_executable(${FILE} "${FILE}.c")
    target_link_libraries(${FILE} m ejovo)
endforeach(FILE)
