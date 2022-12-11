project(${CMAKE_PROJECT_NAME}_test)
add_executable(${PROJECT_NAME} tester.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${gtest_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE gtest_main)

add_test(DummyTest ${PROJECT_NAME} WORKING_DIRECTORY ${OUTPUT_DIR})
