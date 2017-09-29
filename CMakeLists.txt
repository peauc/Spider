cmake_minimum_required(VERSION 3.8)
project(cpp_spider)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE 1)
find_package(Boost REQUIRED COMPONENTS program_options regex)
include_directories( ${Boost_INCLUDE_DIRS} )

include_directories(include/server)

file(GLOB_RECURSE SOURCE_SRV
        src/server/*.cpp)
file(GLOB_RECURSE INCLUDE_SRV
        include/server/*.hpp)

add_executable(cpp_spider_server ${INCLUDE_SRV} ${SOURCE_SRV})
