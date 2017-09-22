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

function(add_docs doxyfile)  # TODO Accepts doxyfile only (optinally defaults to ${CMAKE_CURRENT_LIST_DIR/doxyfile) (And optionally a target name that defaults to "docs")
    find_package(Doxygen 1.8.6 REQUIRED)
    if (DOXYGEN_FOUND)
    # TODO Scan for implicit dependencies by scanning for variables that accept paths and add
    # TODO    according targets and commands.

    # TODO Problem: For implicit dependency scanning I need the finally processed file somehow.
    # TODO   So either allow to use CMake variables inside a doxyfile.in or find a solution
    # TODO   when doing "configure_file" that the same file produced doesn't retrigger a rebuild.

    # TODO The macro could be extended to a second version accepting all the doxyfile variables and putting them into
    # TODO   a doxyfile automatically.

    # TODO Also support could be added for simple DoxygenLayout.xml tasks, like renaming tabs.

    endif()
endfunction()
# TODO Actually this function could be put into a separate repository!
# TODO Maybe there are already existing functions?


add_custom_target(docs
                  COMMAND
                      ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/doxyfile
                  DEPENDS
                      ${CMAKE_CURRENT_LIST_DIR}/doxyfile.in
                      ${SRC}
                      # TODO Use a dependency scanning script that uses doxyfile.in / doxyfile
                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                  COMMENT "Generating documentation with doxygen"
                  VERBATIM
                  SOURCES ${SRC})  # TODO What is "SOURCES"?
