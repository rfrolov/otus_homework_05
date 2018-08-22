cmake_minimum_required(VERSION 3.2)

project(tests VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

add_subdirectory(googletest EXCLUDE_FROM_ALL)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(${PROJECT_NAME} test_main.cpp)

set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

target_link_libraries(${PROJECT_NAME} gtest pthread version)

add_test(tests ${PROJECT_NAME})
enable_testing()