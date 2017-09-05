cmake_minimum_required(VERSION 2.4)

set(SRC
    ${CMAKE_CURRENT_LIST_DIR}/Matrix
    ${CMAKE_CURRENT_LIST_DIR}/Precision
    ${CMAKE_CURRENT_LIST_DIR}/Vector)
add_subdirectory("math")
add_subdirectory("models")
add_subdirectory("render")
add_subdirectory("strings")
add_subdirectory("transformation")

include_directories("${PROJECT_SOURCE_DIR}")

find_package(Boost
             COMPONENTS system filesystem
             REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_library(${CMAKE_PROJECT_NAME}
            SHARED
            ${SRC})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})
endif()

install(TARGETS ${CMAKE_PROJECT_NAME}
        LIBRARY DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/CE3D2
        DESTINATION include
        FILES_MATCHING
        REGEX "\\.(h|hpp)$"
        PATTERN "tests" EXCLUDE
        PATTERN "doc" EXCLUDE)

if(TESTS_ENABLED)
    find_package(Boost
                 COMPONENTS unit_test_framework
                 REQUIRED)
    add_subdirectory("tests")
endif()
