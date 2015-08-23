cmake_minimum_required(VERSION 2.4)

project(CE3D2)

set(CE3D2_VERSION_MAJOR 0)
set(CE3D2_VERSION_MINOR 1)
set(CE3D2_VERSION_MICRO dev)

find_package(Boost
             COMPONENTS unit_test_framework system
             REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/..")

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(SRC
    ${CMAKE_CURRENT_LIST_DIR}/Matrix
    ${CMAKE_CURRENT_LIST_DIR}/Precision
    ${CMAKE_CURRENT_LIST_DIR}/Vector)

add_library(${CMAKE_PROJECT_NAME}
            SHARED
            ${SRC})

if(TESTS_ENABLED)
    add_subdirectory("tests")
endif()
