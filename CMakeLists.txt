cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(example1)
add_executable(example1 "${CMAKE_CURRENT_LIST_DIR}/src/example1.cpp")
set_property(TARGET example1 PROPERTY CXX_STANDARD 23)
target_include_directories(example1 PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")