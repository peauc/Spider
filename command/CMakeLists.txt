cmake_minimum_required(VERSION 3.6)
project(test)

set(CMAKE_CXX_STANDARD 14)
include_directories(include)
set(SOURCE_FILES src/)
add_executable(test ${SOURCE_FILES})