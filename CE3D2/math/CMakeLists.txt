list(APPEND SRC ${CMAKE_CURRENT_LIST_DIR}/Box
                ${CMAKE_CURRENT_LIST_DIR}/LinearAffineFunction
                ${CMAKE_CURRENT_LIST_DIR}/math)

add_subdirectory("matrices")

set(SRC "${SRC}" PARENT_SCOPE)
