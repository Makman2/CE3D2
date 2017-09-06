find_package(Doxygen 1.8.6 REQUIRED)
if (DOXYGEN_FOUND)
    # Get the latest abbreviated commit hash of the working branch.
    execute_process(COMMAND git log -1 --format=%h
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                    OUTPUT_VARIABLE GIT_HEAD
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
    # Get the current working branch
    execute_process(COMMAND git rev-parse --abbrev-ref HEAD
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                    OUTPUT_VARIABLE GIT_BRANCH
                    OUTPUT_STRIP_TRAILING_WHITESPACE)

    configure_file(${CMAKE_CURRENT_LIST_DIR}/doxyfile.in
                   ${CMAKE_BINARY_DIR}/doxyfile)
    configure_file(${CMAKE_CURRENT_LIST_DIR}/DoxygenLayout.xml
                   ${CMAKE_BINARY_DIR}/
                   COPYONLY)

    add_custom_target(docs
                      COMMAND
                          ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/doxyfile
                      DEPENDS ${CMAKE_CURRENT_LIST_DIR}/doxyfile.in
                      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                      COMMENT "Generating documentation with doxygen"
                      VERBATIM
                      SOURCES ${SRC})
endif()
