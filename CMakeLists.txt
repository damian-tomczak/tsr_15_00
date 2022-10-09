cmake_minimum_required(VERSION 3.10)

project(tsr VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(PROJECT_NAME="${CMAKE_PROJECT_NAME}")
add_compile_definitions(PROJECT_VERSION="${CMAKE_PROJECT_VERSION}")

option(UNIT_TEST "Test the basic operation" ON)

add_subdirectory(src)
if(UNIT_TEST)
    add_subdirectory(tests)
endif()