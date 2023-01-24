project(${CMAKE_PROJECT_NAME}_lib)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Quick Sql)

file(GLOB_RECURSE SRC_FILES *.cpp)
file(GLOB_RECURSE H_FILES *.h)
file(GLOB_RECURSE HPP_FILES *.hpp)
file(GLOB_RECURSE QML_FILES *.qml)
list(REMOVE_ITEM ${SRC_FILES} main.cpp)
set(OTHER_FILES qml.qrc views/Database.js qtquickcontrols2.conf ${CMAKE_SOURCE_DIR}/CMakeLists.txt)
add_library(${PROJECT_NAME} ${SRC_FILES} ${H_FILES} ${HPP_FILES} ${QML_FILES} ${OTHER_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${QT_PATH}/include/QtGui
    ${QT_PATH}/include/QtQuick
    .
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core Qt::Quick Qt::Sql)

add_executable(${CMAKE_PROJECT_NAME} main.cpp qml.qrc)

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_NAME})

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/output/${CMAKE_BUILD_TYPE})
if(NOT EXISTS ${OUTPUT_DIR})
    file(MAKE_DIRECTORY ${OUTPUT_DIR})
endif()

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)
