cmake_minimum_required(VERSION 3.7)
project(src)

set(SOURCE_FILES
        components/source/Color.cpp
        components/source/Domain.cpp
        components/source/Node.cpp

        problems/source/HarmoniousGraph.cpp

        solution/source/Backtracking.cpp
        solution/source/ForwardChecking.cpp
        solution/source/Solution.cpp components/header/MainDomain.h components/source/MainDomain.cpp constraints/interface/IConstraint.h constraints/header/HarmoniousGraphConstraint.h constraints/source/HarmoniousGraphConstraint.cpp constraints/interface/IConnection.h constraints/header/Connection.h constraints/source/Connection.cpp accessors/interface/IVariableGetter.h accessors/header/NextVariableGetter.h accessors/source/NextVariableGetter.cpp accessors/interface/IValueGetter.h accessors/source/NextValueGetter.cpp accessors/header/NextValueGetter.h factories/interface/ICSPFactory.h factories/header/CSPFactory.h factories/source/CSPFactory.cpp factories/interface/IProblemFactory.h factories/source/HarmoniousGraphFactory.cpp factories/header/HarmoniousGraphFactory.h solution/interface/IMenu.h solution/source/Menu.cpp solution/header/Menu.h)

add_library (sourcelib ${SOURCE_FILES})

add_executable(csp_run ../main.cpp)

target_link_libraries(csp_run sourcelib)