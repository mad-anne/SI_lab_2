cmake_minimum_required(VERSION 3.7)
project(src)

set(SOURCE_FILES
        components/source/Color.cpp
        components/source/Domain.cpp
        components/source/Node.cpp

        problems/source/HarmoniousGraph.cpp

        solution/source/Backtracking.cpp
        solution/source/ForwardChecking.cpp
        solution/source/Solution.cpp components/header/MainDomain.h components/source/MainDomain.cpp constraints/interface/IConstraintChecker.h constraints/header/HarmoniousGraphConstraintChecker.h constraints/source/HarmoniousGraphConstraintChecker.cpp constraints/header/Connection.h constraints/source/Connection.cpp accessors/interface/IVariableGetter.h accessors/header/NextVariableGetter.h accessors/source/NextVariableGetter.cpp accessors/interface/IValueGetter.h accessors/source/NextValueGetter.cpp accessors/header/NextValueGetter.h factories/interface/ICSPFactory.h factories/header/CSPFactory.h factories/source/CSPFactory.cpp factories/interface/IProblemFactory.h factories/source/HarmoniousGraphFactory.cpp factories/header/HarmoniousGraphFactory.h solution/interface/IMenu.h solution/source/Menu.cpp solution/header/Menu.h problems/source/BinaryGame.cpp problems/header/BinaryGame.h components/source/Number.cpp components/header/Number.h factories/header/BinaryGameFactory.cpp factories/header/BinaryGameFactory.h constraints/source/BinaryGameConstraintChecker.cpp constraints/header/BinaryGameConstraintChecker.h constraints/interface/IRow.h constraints/source/Row.cpp constraints/header/Row.h constraints/source/Column.cpp constraints/header/Column.h constraints/interface/IConstraint.h constraints/source/ConnectionConstraint.cpp constraints/header/ConnectionConstraint.h constraints/source/NeighbourConstraint.cpp constraints/header/NeighbourConstraint.h constraints/source/PairConstraint.cpp constraints/header/PairConstraint.h constraints/source/EqualSplitConstraint.cpp constraints/header/EqualSplitConstraint.h constraints/source/ExistingRowConstraint.cpp constraints/header/ExistingRowConstraint.h accessors/source/MostConstrainedVariableGetter.cpp accessors/header/MostConstrainedVariableGetter.h accessors/source/LeastUsedValueGetter.cpp accessors/header/LeastUsedValueGetter.h accessors/source/MostFilledCrossingVariableGetter.cpp accessors/header/MostFilledCrossingVariableGetter.h accessors/source/LeastCrossingOccurrenceValueGetter.cpp accessors/header/LeastCrossingOccurrenceValueGetter.h)

add_library (sourcelib ${SOURCE_FILES})

add_executable(csp_run ../main.cpp)

target_link_libraries(csp_run sourcelib)