file(GLOB SRC_FILES .c??)
file(GLOB HPP_FILES *.hpp)
file(GLOB H_FILES *.h)

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES} ${HPP_FILES} ${H_FILES})