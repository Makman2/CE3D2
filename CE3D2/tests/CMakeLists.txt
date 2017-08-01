set(CE3D2_TEST_ROOT ${CMAKE_CURRENT_LIST_DIR})

# Adds a new test target
function(add_ce3d2_test target)
    add_executable(${target}
                   # TestUtilities are embedded automatically into every test.
                   ${CE3D2_TEST_ROOT}/TestUtilities
                   ${ARGN})

    target_link_libraries(${target}
                          ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                          CE3D2)

    add_test(${target} ${target})

    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${target} --log_level=error --report_level=no
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Running ${target}..."
        VERBATIM)

    # Copy test files if existent.
    foreach(file ${ARGN})
        get_filename_component(test_file_directory ${file} DIRECTORY)
        get_filename_component(test_data_directory ${file} NAME_WE)
        set(test_data_directory "${test_data_directory}Files")

        set(test_data_path "${test_file_directory}/${test_data_directory}")
        if(EXISTS ${test_data_path})
            file(GLOB test_files "${test_data_path}/*")

            foreach(test_file ${test_files})
                get_filename_component(name ${test_file} NAME)

                add_custom_command(OUTPUT ${test_data_directory}/${name}
                                   COMMAND mkdir -p ${test_data_directory} && cp ${test_file} ${test_data_directory}/${name}
                                   DEPENDS ${test_file}
                                   COMMENT "Copying test file ${test_data_directory}/${name}..."
                                   VERBATIM)

                list(APPEND test_file_targets ${test_data_directory}/${name})
            endforeach()

            set(test_files_dependency_target "${target}Files")

            add_custom_target(${test_files_dependency_target}
                              DEPENDS ${test_file_targets})

            add_dependencies(${target} ${test_files_dependency_target})
        endif()
    endforeach()
endfunction()

# Tests in this directory.
add_ce3d2_test(MatrixTest ${CMAKE_CURRENT_LIST_DIR}/MatrixTest)
add_ce3d2_test(VectorTest ${CMAKE_CURRENT_LIST_DIR}/VectorTest)

add_subdirectory("math")
add_subdirectory("models")
add_subdirectory("render")
add_subdirectory("transformation")
