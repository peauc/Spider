cmake_minimum_required(VERSION 3.8)
project(cpp_spider)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE 1)
if (WIN32)
set(BOOST_ROOT "C:\\boost_1_65_1")
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage/lib/)
endif (WIN32)
set(Boost_USE_STATIC_LIBS        ON)
find_package(Boost REQUIRED COMPONENTS system thread filesystem regex serialization)
include_directories( ${Boost_INCLUDE_DIRS} )

include_directories(include)

file(GLOB_RECURSE SOURCE_SRV
        src/server/*.cpp)
file(GLOB_RECURSE INCLUDE_SRV
        include/server/*.hpp)
file(GLOB_RECURSE SOURCE_CLI
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
        ${Boost_SERIALIZATION_LIBRARY}
        )

cmake_minimum_required(VERSION 3.9)
#project(KBHook)

include_directories(include/dll)
set(SOURCE_HKBHOOK_FILES src/dll/IziHook.cpp include/dll/IziHook.hh src/dll/launchDLL.cpp)
add_library(KBHook SHARED ${SOURCE_HKBHOOK_FILES})

#project(KeyboardListener)
set(SOURCE_KEYBOARDLISTENER_FILES src/dll/KeyboardListener.cpp include/dll/KeyboardListener.hh)
add_library(KeyboardListener SHARED ${SOURCE_KEYBOARDLISTENER_FILES})

#project(laucherDLL)
set(SOURCE_LAUNCHERDLL_FILES src/dll/launchDLL.cpp)
add_executable(launcherDLL ${SOURCE_LAUNCHERDLL_FILES})
