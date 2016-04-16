list(APPEND SRC ${CMAKE_CURRENT_LIST_DIR}/Box
                ${CMAKE_CURRENT_LIST_DIR}/LinearAffineFunction)

add_subdirectory("matrices")

set(SRC "${SRC}" PARENT_SCOPE)
