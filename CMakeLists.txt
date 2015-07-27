cmake_minimum_required(VERSION 2.8.4)
project(camrem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/camrem.cpp)
add_executable(camrem ${SOURCE_FILES})