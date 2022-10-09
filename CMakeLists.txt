cmake_minimum_required(VERSION 3.10)

project(tsr VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SRC_FILES src/*.c??)
file(GLOB HPP_FILES src/*.hpp)
file(GLOB H_FILES src/*.h)

add_compile_definitions(PROJECT_NAME="${CMAKE_PROJECT_NAME}")
add_compile_definitions(PROJECT_VERSION="${CMAKE_PROJECT_VERSION}")

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES} ${HPP_FILES} ${H_FILES})
