cmake_minimum_required(VERSION 3.7)
project(tests)

add_subdirectory(lib/googletest)

enable_testing()

include_directories(${gtest_SOURCE_DIR_}/include ${gtest_SOURCE_DIR_})

set(SOURCE_FILES
        gtest.cpp
        tests/components/ColorTests.cpp)

add_executable(tests_run ${SOURCE_FILES})

target_link_libraries(tests_run gtest gtest_main)