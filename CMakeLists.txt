#cmake_minimum_required(VERSION 3.8)
#project(cpp_spider)
#project(KBHook)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_VERBOSE_MAKEFILE 1)
#find_package(Boost REQUIRED COMPONENTS system thread filesystem regex)
#include_directories( ${Boost_INCLUDE_DIRS} )

#include_directories(include)

#file(GLOB_RECURSE SOURCE_SRV
#        src/server/*.cpp)
#file(GLOB_RECURSE INCLUDE_SRV
#        include/server/*.hpp)
#file(GLOB_RECURSE SOURCE_CLI                          l
#        src/client/*.cpp)
#file(GLOB_RECURSE INCLUDE_CLI
#        include/client/*.h*)

#file(GLOB_RECURSE SOURCE_DLLHOOK                         l
 #       src/client/dll/IziHook.cpp)
#file(GLOB_RECURSE INCLUDE_DLLHOOK
  #      include/client/dll/IziHook.hh)

#add_executable(cpp_spider_server ${INCLUDE_SRV} ${SOURCE_SRV})
#add_executable(cpp_spider_client ${INCLUDE_CLI} ${SOURCE_CLI})
#add_library(KBHook SHARED ${INCLUDE_DLLHOOK} ${SOURCE_DLLHOOK})

#target_link_libraries(cpp_spider_server
#        ${Boost_LOG_SETUP_LIBRARY}
#        ${Boost_LOG_LIBRARY}
#        ${Boost_FILESYSTEM_LIBRARY}
#        ${Boost_THREAD_LIBRARY}
#        ${Boost_SYSTEM_LIBRARY}
#        )
#target_link_libraries(cpp_spider_client
#        ${Boost_LOG_SETUP_LIBRARY}
#        ${Boost_LOG_LIBRARY}
#        ${Boost_FILESYSTEM_LIBRARY}
#        ${Boost_THREAD_LIBRARY}
#        ${Boost_SYSTEM_LIBRARY}
#        )

cmake_minimum_required(VERSION 3.9)
project(KBHook)

set(CMAKE_CXX_STANDARD 14)

include_directories(include/dll)
set(SOURCE_HKBHOOK_FILES src/dll/IziHook.cpp include/dll/IziHook.hh)
add_library(KBHook SHARED ${SOURCE_HKBHOOK_FILES})

cmake_minimum_required(VERSION 3.9)
project(KeyboardListener)
set(CMAKE_CXX_STANDARD 14)
include_directories(include/dll)
set(SOURCE_KEYBOARDLISTENER_FILES src/dll/KeyboardListener.cpp include/dll/KeyboardListener.hh)
add_library(KeyboardListener SHARED ${SOURCE_KEYBOARDLISTENER_FILES})

