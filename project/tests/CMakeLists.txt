add_executable(${CMAKE_PROJECT_NAME} tester.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${gtest_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE gtest_main)

add_test(DummyTest ${CMAKE_PROJECT_NAME} WORKING_DIRECTORY ${OUTPUT_DIR})
