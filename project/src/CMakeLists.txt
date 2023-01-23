project(${CMAKE_PROJECT_NAME}_lib)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(QT_PATH CACHE STRING "QT path e.g. F:/qt/5.15.2/msvc2019_64")
if("${QT_PATH}" STREQUAL "")
    message(FATAL_ERROR "You need to first define QT_PATH")
endif()
list(APPEND CMAKE_PREFIX_PATH ${QT_PATH})
find_package(Qt5 REQUIRED COMPONENTS Core Quick Sql)

file(GLOB_RECURSE SRC_FILES *.cpp)
file(GLOB_RECURSE H_FILES *.h)
file(GLOB_RECURSE HPP_FILES *.hpp)
file(GLOB_RECURSE QML_FILES *.qml)
list(REMOVE_ITEM ${SRC_FILES} main.cpp)
add_library(${PROJECT_NAME} ${SRC_FILES} ${H_FILES} ${HPP_FILES} ${QML_FILES} qml.qrc views/Database.js qtquickcontrols2.conf)

target_include_directories(${PROJECT_NAME} PRIVATE ${QT_PATH}/include/QtGui)
target_include_directories(${PROJECT_NAME} PRIVATE ${QT_PATH}/include/QtQuick)
target_include_directories(${PROJECT_NAME} PRIVATE .)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Sql)

add_executable(${CMAKE_PROJECT_NAME} main.cpp qml.qrc)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_NAME})

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/output/${CMAKE_BUILD_TYPE})
if(NOT EXISTS ${OUTPUT_DIR})
    file(MAKE_DIRECTORY ${OUTPUT_DIR})
endif()

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)
