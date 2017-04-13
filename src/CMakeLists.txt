cmake_minimum_required(VERSION 3.7)
project(src)

set(SOURCE_FILES
        components/source/Color.cpp
        components/source/Domain.cpp
        components/source/Node.cpp

        problems/source/HarmoniousGraph.cpp

        solution/source/Backtracking.cpp
        solution/source/ForwardChecking.cpp
        solution/source/Solution.cpp components/header/MainDomain.h components/source/MainDomain.cpp constraints/interface/IConstraint.h constraints/header/HarmoniousGraphConstraint.h constraints/source/HarmoniousGraphConstraint.cpp)

add_library (sourcelib ${SOURCE_FILES})

add_executable(csp_run ../main.cpp)

target_link_libraries(csp_run sourcelib)