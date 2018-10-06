cmake_minimum_required(VERSION 2.8)
project(test)

#TODO: add option for C++03 

set(CMAKE_CXX_STANDARD 11)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(SOURCE_FILES main.cpp)

include_directories("${CMAKE_SOURCE_DIR}/../")

add_executable(test ${SOURCE_FILES})
