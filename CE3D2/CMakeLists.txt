cmake_minimum_required(VERSION 2.4)

project(CE3D2)

set(CE3D2_VERSION_MAJOR 1)
set(CE3D2_VERSION_MINOR 0)
set(CE3D2_VERSION_MICRO dev)
set(CE3D2_VERSION
    ${CE3D2_VERSION_MAJOR}.${CE3D2_VERSION_MINOR}.${CE3D2_VERSION_MICRO})
set(PROJECT_VERSION_MAJOR ${CE3D2_VERSION_MAJOR})
set(PROJECT_VERSION_MINOR ${CE3D2_VERSION_MINOR})
set(PROJECT_VERSION_MICRO ${CE3D2_VERSION_MICRO})
set(PROJECT_VERSION ${CE3D2_VERSION})

set(SRC
    ${CMAKE_CURRENT_LIST_DIR}/Matrix
    ${CMAKE_CURRENT_LIST_DIR}/Precision
    ${CMAKE_CURRENT_LIST_DIR}/Vector)
add_subdirectory("math")
add_subdirectory("models")
add_subdirectory("render")
add_subdirectory("transformation")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR
   ${CMAKE_BUILD_TYPE} STREQUAL "Release")

    include_directories("${PROJECT_SOURCE_DIR}/..")

    find_package(Boost
                 COMPONENTS system
                 REQUIRED)

    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

    add_library(${CMAKE_PROJECT_NAME}
                SHARED
                ${SRC})

    install(TARGETS ${CMAKE_PROJECT_NAME}
            LIBRARY DESTINATION lib)
    install(DIRECTORY ${PROJECT_SOURCE_DIR}
            DESTINATION include
            FILES_MATCHING
            REGEX "\.(h|hpp)$"
            PATTERN "tests" EXCLUDE)

    if(TESTS_ENABLED)
        find_package(Boost
                     COMPONENTS unit_test_framework
                     REQUIRED)
        add_subdirectory("tests")
    endif()

elseif(${CMAKE_BUILD_TYPE} STREQUAL "Documentation")
    find_package(Doxygen REQUIRED)
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

        configure_file(${CMAKE_SOURCE_DIR}/doxyfile.in
                       ${CMAKE_BINARY_DIR}/doxyfile)
        add_custom_target(doc
                          COMMAND
                              ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/doxyfile
                          DEPENDS ${CMAKE_SOURCE_DIR}/doxyfile.in
                          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                          COMMENT "Generating documentation with doxygen"
                          VERBATIM
                          SOURCES ${SRC})
    endif()
endif()
