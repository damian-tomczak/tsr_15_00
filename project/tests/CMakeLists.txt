project(${CMAKE_PROJECT_NAME}_test)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Quick Sql)

add_executable(${PROJECT_NAME} tester.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${gtest_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${QT_PATH}/include/QtGui
    ${QT_PATH}/include/QtQuick
)


target_link_libraries(${PROJECT_NAME} PRIVATE
    gtest_main
    ${CMAKE_PROJECT_NAME}_lib
    Qt::Core
    Qt::Quick
    Qt::Sql
)

add_test(DummyTests ${PROJECT_NAME} WORKING_DIRECTORY ${OUTPUT_DIR})
add_test(Basic ${PROJECT_NAME} WORKING_DIRECTORY ${OUTPUT_DIR})
