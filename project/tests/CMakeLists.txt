project(${CMAKE_PROJECT_NAME}_test)
add_executable(${PROJECT_NAME} tester.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${QT_PATH}/include/QtGui)
target_include_directories(${PROJECT_NAME} PRIVATE ${QT_PATH}/include/QtQuick)
target_include_directories(${PROJECT_NAME} PRIVATE .)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Sql)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${gtest_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE gtest_main)

add_test(DummyTest ${PROJECT_NAME} WORKING_DIRECTORY ${OUTPUT_DIR})
