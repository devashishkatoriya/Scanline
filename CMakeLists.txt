cmake_minimum_required(VERSION 3.7)
project(Scanline)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(Scanline ${SOURCE_FILES})
target_link_libraries(Scanline graph)