cmake_minimum_required(VERSION 3.2)

project(version VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

configure_file(version_def.h.in ${PROJECT_SOURCE_DIR}/version_def.h)

add_library(${PROJECT_NAME} version.cpp version.h version_def.h)

set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

