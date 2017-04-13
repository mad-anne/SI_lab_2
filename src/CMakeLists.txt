cmake_minimum_required(VERSION 3.7)
project(src)

set(SOURCE_FILES ../main.cpp
        components/source/Color.cpp
        components/source/Domain.cpp
        components/source/Node.cpp

        constraints/source/BinaryConstraint.cpp
        constraints/source/UnaryConstraint.cpp

        problems/source/HarmoniousGraph.cpp

        solution/source/Backtracking.cpp
        solution/source/ForwardChecking.cpp
        solution/source/Solution.cpp)

add_executable(csp_run ${SOURCE_FILES})