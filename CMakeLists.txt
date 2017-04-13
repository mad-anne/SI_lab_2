cmake_minimum_required(VERSION 3.7)
project(SI_lab_2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")

include_directories(src)
include_directories(tests)

add_subdirectory(src)
add_subdirectory(tests)
