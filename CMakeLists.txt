cmake_minimum_required(VERSION 3.15)
project(client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(MSVC)
    add_compile_options(/W3 /permissive-)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS _WIN32_WINNT=0x0601 WIN32_LEAN_AND_MEAN)
endif()

set(BOOST_ROOT "D:/cppsoft/boost_1_91_0" CACHE PATH "Boost root directory")
if(EXISTS "${BOOST_ROOT}")
    set(Boost_INCLUDE_DIRS "${BOOST_ROOT}")
    set(Boost_LIBRARY_DIRS "${BOOST_ROOT}/stage/lib")
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    message(STATUS "Found Boost at: ${BOOST_ROOT}")
else()
    message(STATUS "Boost not found at ${BOOST_ROOT}, searching via find_package...")
    find_package(Boost QUIET)
endif()

set(JSON_ROOT "D:/cppsoft/libjson" CACHE PATH "JsonCpp root directory")
if(EXISTS "${JSON_ROOT}")
    set(JSON_INCLUDE_DIR "${JSON_ROOT}/include")
    set(JSON_LIBRARY_DIR "${JSON_ROOT}/lib")
    include_directories(${JSON_INCLUDE_DIR})
    link_directories(${JSON_LIBRARY_DIR})
    message(STATUS "Found JsonCpp at: ${JSON_ROOT}")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(JSON_LIBRARY "json_vc71_libmtd")
    else()
        set(JSON_LIBRARY "json_vc71_libmt")
    endif()
else()
    message(WARNING "JsonCpp not found at ${JSON_ROOT}")
    set(JSON_LIBRARY "")
endif()

file(GLOB CLIENT_SOURCES CONFIGURE_DEPENDS
    "client/*.cpp"
    "client/*.h"
)

add_executable(server
    ${CLIENT_SOURCES}
    client/AsioIOServicePool.h
    client/AsioIOServicePool.cpp
)
target_include_directories(server PRIVATE ${CMAKE_SOURCE_DIR}/client)
if(WIN32)
    target_link_libraries(server PRIVATE ws2_32)
endif()
if(JSON_LIBRARY)
    target_link_libraries(server PRIVATE ${JSON_LIBRARY})
endif()