cmake_minimum_required(VERSION 2.4)

project(CE3D2)

set(CE3D2_VERSION_MAJOR 2)
set(CE3D2_VERSION_MINOR 2)
set(CE3D2_VERSION_MICRO dev)
set(CE3D2_VERSION
    ${CE3D2_VERSION_MAJOR}.${CE3D2_VERSION_MINOR}.${CE3D2_VERSION_MICRO})
set(PROJECT_VERSION_MAJOR ${CE3D2_VERSION_MAJOR})
set(PROJECT_VERSION_MINOR ${CE3D2_VERSION_MINOR})
set(PROJECT_VERSION_MICRO ${CE3D2_VERSION_MICRO})
set(PROJECT_VERSION ${CE3D2_VERSION})

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR
   CMAKE_BUILD_TYPE STREQUAL "Release")

    add_subdirectory("CE3D2")

    if(TESTS_ENABLED)
        find_package(Boost
                     COMPONENTS unit_test_framework
                     REQUIRED)
        add_subdirectory("tests")
    endif()

elseif(CMAKE_BUILD_TYPE STREQUAL "Documentation")
    find_package(Doxygen 1.8.8 REQUIRED)
    if (DOXYGEN_FOUND)
        add_subdirectory("CE3D2/doc")

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

        configure_file(${CMAKE_SOURCE_DIR}/CE3D2/doxyfile.in
                       ${CMAKE_BINARY_DIR}/doxyfile)
        configure_file(${CMAKE_SOURCE_DIR}/CE3D2/DoxygenLayout.xml
                       ${CMAKE_BINARY_DIR}/
                       COPYONLY)

        add_custom_target(doc
                          COMMAND
                              ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/doxyfile
                          DEPENDS ${CMAKE_SOURCE_DIR}/CE3D2/doxyfile.in
                          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                          COMMENT "Generating documentation with doxygen"
                          VERBATIM
                          SOURCES ${SRC})
    endif()
endif()
