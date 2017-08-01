list(APPEND SRC ${CMAKE_CURRENT_LIST_DIR}/All
                ${CMAKE_CURRENT_LIST_DIR}/FileFormatException
                ${CMAKE_CURRENT_LIST_DIR}/InvalidFileException
                ${CMAKE_CURRENT_LIST_DIR}/WavefrontObj)

set(SRC "${SRC}" PARENT_SCOPE)
