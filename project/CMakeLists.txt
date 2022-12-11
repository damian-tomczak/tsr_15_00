cmake_minimum_required(VERSION 3.10)

project(tsr VERSION 0.0.1 LANGUAGES CXX)

if(NOT MSVC AND NOT WIN32)
    message(WARNING "Config with MSVC and WIN32 was only tested!")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_definitions(PROJECT_NAME="${CMAKE_PROJECT_NAME}")
add_compile_definitions(PROJECT_VERSION="${CMAKE_PROJECT_VERSION}")

option(UNIT_TEST "Test the basic operation" ON)

add_subdirectory(src)
if(UNIT_TEST)
    enable_testing()
    add_subdirectory(external/googltest EXCLUDE_FROM_ALL)
    add_subdirectory(tests)
endif()