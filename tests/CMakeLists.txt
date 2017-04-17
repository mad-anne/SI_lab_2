cmake_minimum_required(VERSION 3.7)
project(tests)

add_subdirectory(lib/googletest)

enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES
        gtest.cpp
        tests/components/ColorTestSuite.cpp tests/components/DomainTestSuite.cpp tests/components/NodeTestSuite.cpp tests/constraints/HarmoniousGraphConstraintTestSuite.cpp tests/accessors/NextVariableGetterTestSuite.cpp tests/accessors/NextValueGetterTestSuite.cpp tests/constraints/BinaryGameConstraintTestSuite.cpp tests/constraints/ConnectionTestSuite.cpp tests/constraints/ConnectionConstraintTestSuite.cpp)

add_executable(tests_run ${SOURCE_FILES})

target_link_libraries(tests_run gtest gtest_main sourcelib)