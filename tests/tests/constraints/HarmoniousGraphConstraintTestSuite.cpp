//
// Created by Anna Siwik on 2017-04-13.
//

#include <gtest/gtest.h>
#include <constraints/interface/IConstraint.h>
#include <constraints/header/HarmoniousGraphConstraint.h>
#include <problems/header/HarmoniousGraph.h>
#include <components/header/Color.h>

class HarmoniousGraphConstraintTestSuite : public ::testing::Test
{
    public:
        HarmoniousGraphConstraintTestSuite();
        ~HarmoniousGraphConstraintTestSuite();

    protected:
        const int width;
        IProblem* problem;
        IConstraint* sut;
};

HarmoniousGraphConstraintTestSuite::HarmoniousGraphConstraintTestSuite()
        : width(3),
          problem(new HarmoniousGraph(width)),
          sut(new HarmoniousGraphConstraint(problem))
{}

HarmoniousGraphConstraintTestSuite::~HarmoniousGraphConstraintTestSuite()
{
    delete problem;
    delete sut;
}

TEST_F(HarmoniousGraphConstraintTestSuite, returnsTrueForNullptrVariable)
{
    ASSERT_TRUE(sut->updateConstraints(nullptr));
}

TEST_F(HarmoniousGraphConstraintTestSuite, returnsTrueWhenNeighboursHaveDifferentValue)
{
    IValue* value1 = new Color(1);
    IValue* value2 = new Color(2);

    problem->setVariableValue(0, 0, value1);
    ASSERT_TRUE(sut->updateConstraints(problem->getVariable(0, 0)));

    problem->setVariableValue(0, 1, value2);
    ASSERT_TRUE(sut->updateConstraints(problem->getVariable(0, 1)));

    delete value1;
    delete value2;
}

TEST_F(HarmoniousGraphConstraintTestSuite, returnsFalseIfNeighboursHaveTheSameValue)
{
    IValue* value = new Color(1);

    problem->setVariableValue(0, 0, value);
    ASSERT_TRUE(sut->updateConstraints(problem->getVariable(0, 0)));

    problem->setVariableValue(0, 1, value);
    ASSERT_FALSE(sut->updateConstraints(problem->getVariable(0, 1)));

    delete value;
}

TEST_F(HarmoniousGraphConstraintTestSuite, returnsFalseIfAlreadyExistsTheSameConnection)
{
    IValue* value1 = new Color(1);
    IValue* value2 = new Color(2);

    problem->setVariableValue(0, 0, value1);
    ASSERT_TRUE(sut->updateConstraints(problem->getVariable(0, 0)));

    problem->setVariableValue(0, 1, value2);
    ASSERT_TRUE(sut->updateConstraints(problem->getVariable(0, 1)));

    problem->setVariableValue(0, 2, value1);
    ASSERT_FALSE(sut->updateConstraints(problem->getVariable(0, 2)));

    delete value1;
    delete value2;
}

TEST_F(HarmoniousGraphConstraintTestSuite, returnsFalseIfAssigningAgainTheSameValueToVariable)
{
    IValue* value1 = new Color(1);
    IValue* value2 = new Color(2);

    problem->setVariableValue(0, 0, value1);
    ASSERT_TRUE(sut->updateConstraints(problem->getVariable(0, 0)));

    problem->setVariableValue(0, 1, value2);
    ASSERT_TRUE(sut->updateConstraints(problem->getVariable(0, 1)));

    problem->setVariableValue(0, 1, value2);
    ASSERT_FALSE(sut->updateConstraints(problem->getVariable(0, 1)));

    delete value1;
    delete value2;
}

TEST_F(HarmoniousGraphConstraintTestSuite, returnsTrueIfAssigningAgainTheSameValueToVariableWithUndo)
{
    IValue* value1 = new Color(1);
    IValue* value2 = new Color(2);

    problem->setVariableValue(0, 0, value1);
    ASSERT_TRUE(sut->updateConstraints(problem->getVariable(0, 0)));

    problem->setVariableValue(0, 1, value2);
    ASSERT_TRUE(sut->updateConstraints(problem->getVariable(0, 1)));

    sut->undoConstraints(problem->getVariable(0, 1));

    problem->setVariableValue(0, 1, value2);
    ASSERT_TRUE(sut->updateConstraints(problem->getVariable(0, 1)));

    delete value1;
    delete value2;
}