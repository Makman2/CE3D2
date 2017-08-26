set(CE3D2_TEST_ROOT ${CMAKE_CURRENT_LIST_DIR})

# Adds a new test target. Only a single test file is supported.
# TestUtilities.h is automatically linked.
function(add_ce3d2_test test_file)
    get_filename_component(test_name ${test_file} NAME_WE)

    add_executable(${test_name}
                   EXCLUDE_FROM_ALL
                   # TestUtilities are embedded automatically into every test.
                   ${CE3D2_TEST_ROOT}/TestUtilities
                   ${test_file})

    target_link_libraries(${test_name}
                          ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                          CE3D2)

    add_test(${test_name} ${test_name})

    # Copy test files if existent.
    get_filename_component(test_file_directory ${test_file} DIRECTORY)
    set(test_data_directory "${test_name}Files")

    set(test_data_path "${test_file_directory}/${test_data_directory}")
    if(EXISTS ${test_data_path})
        file(GLOB test_files "${test_data_path}/*")

        foreach(test_data_file ${test_files})
            get_filename_component(name ${test_data_file} NAME)

            add_custom_command(OUTPUT ${test_data_directory}/${name}
                               COMMAND mkdir -p ${test_data_directory} && cp ${test_data_file} ${test_data_directory}/${name}
                               DEPENDS ${test_data_file}
                               COMMENT "Copying test file ${test_data_directory}/${name}..."
                               VERBATIM)

            list(APPEND test_file_targets ${CMAKE_CURRENT_BINARY_DIR}/${test_data_directory}/${name})
        endforeach()
    endif()

    add_custom_command(
        OUTPUT ${test_name}_execution_stamp
        DEPENDS ${test_name} ${test_file_targets}
        COMMAND ${test_name} --log_level=error --report_level=no
        COMMAND touch ${test_name}_execution_stamp
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Running ${test_name}..."
        VERBATIM)

    add_custom_target(
        ${test_name}_run
        ALL
        DEPENDS ${test_name}_execution_stamp)
endfunction()

# Tests in this directory.
add_ce3d2_test(${CMAKE_CURRENT_LIST_DIR}/MatrixTest)
add_ce3d2_test(${CMAKE_CURRENT_LIST_DIR}/VectorTest)

add_subdirectory("math")
add_subdirectory("models")
add_subdirectory("render")
add_subdirectory("strings")
add_subdirectory("transformation")
