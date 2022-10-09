cmake_minimum_required(VERSION 3.10)

project(tsr VERSION 0.0.1)

if(NOT (WIN32 AND MINGW)) #Temporary
    message(FATAL_ERROR "${CMAKE_PROJECT_NAME} currently supports only Windows machines with MinGW compiler!")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(PROJECT_NAME="${CMAKE_PROJECT_NAME}")
add_compile_definitions(PROJECT_VERSION="${CMAKE_PROJECT_VERSION}")

option(UNIT_TEST "Test the basic operation" ON)

if(NOT DEFINED ${CMAKE_BUILD_TYPE})
    set(CMAKE_BUILD_TYPE "Debug")
endif()

add_compile_definitions("$<$<CONFIG:Debug>:_DEBUG>")
add_compile_options("$<$<CONFIG:DEBUG>:-O0;-g>")
add_compile_options("-Wextra;-Wall;-Werror;-Wfatal-errors")

add_subdirectory(./src)
if(UNIT_TEST)
    enable_testing()
    add_subdirectory(./external/googltest EXCLUDE_FROM_ALL)
    project(${CMAKE_PROJECT_NAME}_test)
    add_subdirectory(./tests)
endif()