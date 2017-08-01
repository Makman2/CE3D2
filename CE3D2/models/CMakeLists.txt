list(APPEND SRC ${CMAKE_CURRENT_LIST_DIR}/IndexPair
                ${CMAKE_CURRENT_LIST_DIR}/LineModel
                ${CMAKE_CURRENT_LIST_DIR}/Model
                ${CMAKE_CURRENT_LIST_DIR}/StorageType)

add_subdirectory("loaders")

set(SRC "${SRC}" PARENT_SCOPE)
