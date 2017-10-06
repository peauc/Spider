cmake_minimum_required(VERSION 3.8)
project(cpp_spider)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE 1)
find_package(Boost REQUIRED COMPONENTS system thread filesystem regex)
include_directories( ${Boost_INCLUDE_DIRS} )

include_directories(include)

file(GLOB_RECURSE SOURCE_SRV
        src/server/*.cpp)
file(GLOB_RECURSE INCLUDE_SRV
        include/server/*.hpp)
file(GLOB_RECURSE SOURCE_CLI                          l
        src/client/*.cpp)
file(GLOB_RECURSE INCLUDE_CLI
        include/client/*.h*)

add_executable(cpp_spider_server ${INCLUDE_SRV} ${SOURCE_SRV})
add_executable(cpp_spider_client ${INCLUDE_CLI} ${SOURCE_CLI})
target_link_libraries(cpp_spider_server
        ${Boost_LOG_SETUP_LIBRARY}
        ${Boost_LOG_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_THREAD_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )
target_link_libraries(cpp_spider_client
        ${Boost_LOG_SETUP_LIBRARY}
        ${Boost_LOG_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_THREAD_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )
