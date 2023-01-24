cmake_minimum_required(VERSION 3.10)

project(tsr VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT MSVC AND NOT WIN32)
    message(WARNING "Config with MSVC and WIN32 was only tested!")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_definitions(PROJECT_NAME="${CMAKE_PROJECT_NAME}")
add_compile_definitions(PROJECT_VERSION="${CMAKE_PROJECT_VERSION}")

set(QT_PATH CACHE STRING "QT path e.g. F:/qt/5.15.2/msvc2019_64")
if("${QT_PATH}" STREQUAL "")
    message(FATAL_ERROR "You need to first define QT_PATH")
endif()
list(APPEND CMAKE_PREFIX_PATH ${QT_PATH})
find_package(Qt5 REQUIRED COMPONENTS Core Quick Sql)

option(UNIT_TEST "Test the basic operation" ON)

add_subdirectory(src)
if(UNIT_TEST)
    enable_testing()
    add_subdirectory(external/googltest EXCLUDE_FROM_ALL)
    add_subdirectory(tests)
endif()