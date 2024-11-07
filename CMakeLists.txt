cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 23)
include_directories("${CMAKE_CURRENT_LIST_DIR}/include")

project(example1)
add_executable(example1 "${CMAKE_CURRENT_LIST_DIR}/src/example1.cpp")

project(example2)
add_executable(example2 "${CMAKE_CURRENT_LIST_DIR}/src/example2.cpp")

project(example3)
add_executable(example3 "${CMAKE_CURRENT_LIST_DIR}/src/example3.cpp")

enable_testing()
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/tests")