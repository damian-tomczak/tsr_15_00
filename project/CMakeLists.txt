cmake_minimum_required(VERSION 3.10)

set(QT_PATH CACHE STRING "QT path e.g. F:/qt/5.15.2/msvc2019_64")
if("${QT_PATH}" STREQUAL "")
    message(FATAL_ERROR "You need to first define QT_PATH")
endif()
list(APPEND CMAKE_PREFIX_PATH ${QT_PATH})

project(tsr VERSION 0.0.1 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    enable_testing()
    add_subdirectory(external/googltest EXCLUDE_FROM_ALL)
    add_subdirectory(tests)
endif()