set(CE3D2_TEST_ROOT ${CMAKE_CURRENT_LIST_DIR})

# Adds a new test target
function(add_ce3d2_test target)
    # TestUtilities are embedded automatically into every test.
    list(APPEND ARGN ${CE3D2_TEST_ROOT}/TestUtilities)

    add_executable(${target} ${ARGN})

    target_link_libraries(${target}
                          ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                          CE3D2)

    add_test(${target} ${target})

    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${target}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Running ${target}..."
        VERBATIM)

endfunction()

# Tests in this directory.
add_ce3d2_test(VectorTest ${CMAKE_CURRENT_LIST_DIR}/VectorTest)
add_ce3d2_test(MatrixTest ${CMAKE_CURRENT_LIST_DIR}/MatrixTest)

add_subdirectory("models")
add_subdirectory("transformation")
