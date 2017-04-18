//
// Created by Anna Siwik on 18.04.2017.
//

#include <gtest/gtest.h>
#include <accessors/interface/IVariableGetter.h>
#include <problems/header/HarmoniousGraph.h>
#include <accessors/header/MostConstrainedVariableGetter.h>
#include <constraints/interface/IConstraintChecker.h>
#include <constraints/header/HarmoniousGraphConstraintChecker.h>

class MostConstrainedVariableGetterTestSuite : public ::testing::Test
{
    public:
        MostConstrainedVariableGetterTestSuite();
        ~MostConstrainedVariableGetterTestSuite();

    protected:
        const int width;
        IProblem* problem;
        IConstraintChecker* constraintChecker;
        IVariableGetter* sut;
};

MostConstrainedVariableGetterTestSuite::MostConstrainedVariableGetterTestSuite() :
    width(3),
    problem(new HarmoniousGraph(width)),
    constraintChecker(new HarmoniousGraphConstraintChecker(problem)),
    sut(new MostConstrainedVariableGetter(problem))
{}

MostConstrainedVariableGetterTestSuite::~MostConstrainedVariableGetterTestSuite()
{
    delete problem;
    delete constraintChecker;
    delete sut;
}

TEST_F(MostConstrainedVariableGetterTestSuite, returnsFirstVariableForTheFirstTime)
{
    ASSERT_EQ(sut->getNext(), problem->getVariable(0, 0));
}

TEST_F(MostConstrainedVariableGetterTestSuite, returnsNullptrWhenEveryVariableHasAssignedValue)
{
    IValue* value = problem->getDomain()->getValue(0);

    problem->getVariable(0, 0)->setValue(value);
    problem->getVariable(0, 1)->setValue(value);
    problem->getVariable(0, 2)->setValue(value);

    problem->getVariable(1, 0)->setValue(value);
    problem->getVariable(1, 1)->setValue(value);
    problem->getVariable(1, 2)->setValue(value);

    problem->getVariable(2, 0)->setValue(value);
    problem->getVariable(2, 1)->setValue(value);
    problem->getVariable(2, 2)->setValue(value);

    ASSERT_EQ(sut->getNext(), nullptr);
}

TEST_F(MostConstrainedVariableGetterTestSuite, returnsMostConstraintedVariableWithDomainLimits)
{
    IValue* value1 = problem->getDomain()->getValue(0);
    IValue* value2 = problem->getDomain()->getValue(1);
    IValue* value3 = problem->getDomain()->getValue(2);

    problem->getVariable(0, 0)->setValue(value1);
    constraintChecker->putConstraintsOn(problem->getVariable(0, 0), true);
    problem->getVariable(0, 1)->setValue(value2);
    constraintChecker->putConstraintsOn(problem->getVariable(0, 1), true);
    problem->getVariable(1, 0)->setValue(value3);
    constraintChecker->putConstraintsOn(problem->getVariable(1, 0), true);

    ASSERT_EQ(sut->getNext(), problem->getVariable(1, 1));
}

TEST_F(MostConstrainedVariableGetterTestSuite, returnsMostConstraintedVariable)
{
    IValue* value1 = problem->getDomain()->getValue(0);
    IValue* value2 = problem->getDomain()->getValue(1);
    IValue* value3 = problem->getDomain()->getValue(2);

    problem->getVariable(0, 0)->setValue(value1);
    constraintChecker->putConstraintsOn(problem->getVariable(0, 0), false);
    problem->getVariable(0, 1)->setValue(value2);
    constraintChecker->putConstraintsOn(problem->getVariable(0, 1), false);
    problem->getVariable(1, 0)->setValue(value3);
    constraintChecker->putConstraintsOn(problem->getVariable(1, 0), false);

    ASSERT_EQ(sut->getNext(), problem->getVariable(1, 1));
}