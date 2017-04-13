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
        const int width = 3;
        IProblem* problem;
        IConstraint* sut;
};

HarmoniousGraphConstraintTestSuite::HarmoniousGraphConstraintTestSuite()
        : problem(new HarmoniousGraph(3)),
          sut(new HarmoniousGraphConstraint(problem))
{}

HarmoniousGraphConstraintTestSuite::~HarmoniousGraphConstraintTestSuite()
{
    delete problem;
    delete sut;
}

TEST_F(HarmoniousGraphConstraintTestSuite, returnsTrueForUnsolvedProblem)
{
    ASSERT_TRUE(sut->checkConstraints());
}

TEST_F(HarmoniousGraphConstraintTestSuite, returnsTrueWhenNeighboursHaveDifferentColors)
{
    IValue* value1 = new Color(1);
    IValue* value2 = new Color(2);

    problem->setVariableValue(0, 0, value1);
    problem->setVariableValue(0, 1, value2);

    ASSERT_TRUE(sut->checkConstraints());

    delete value1;
    delete value2;
}

TEST_F(HarmoniousGraphConstraintTestSuite, returnsFalseIfNeighboursHaveTheSameColor)
{
    IValue* value = new Color(1);

    problem->setVariableValue(0, 0, value);
    problem->setVariableValue(0, 1, value);

    ASSERT_FALSE(sut->checkConstraints());

    delete value;
}

TEST_F(HarmoniousGraphConstraintTestSuite, returnsFalseIfExistsTheSameConnection)
{
    IValue* value1 = new Color(1);
    IValue* value2 = new Color(2);

    problem->setVariableValue(0, 0, value1);
    problem->setVariableValue(0, 1, value2);
    problem->setVariableValue(0, 2, value1);

    ASSERT_FALSE(sut->checkConstraints());

    delete value1;
    delete value2;
}

TEST_F(HarmoniousGraphConstraintTestSuite, returnsTrueIfSolutionIsCorrect)
{
    IValue* value1 = new Color(1);
    IValue* value2 = new Color(2);
    IValue* value3 = new Color(3);
    IValue* value4 = new Color(4);
    IValue* value5 = new Color(5);
    IValue* value6 = new Color(6);
    IValue* value7 = new Color(7);

    problem->setVariableValue(0, 0, value1);
    problem->setVariableValue(0, 1, value2);
    problem->setVariableValue(0, 2, value3);
    problem->setVariableValue(1, 0, value4);
    problem->setVariableValue(1, 1, value5);
    problem->setVariableValue(1, 2, value6);
    problem->setVariableValue(2, 0, value7);
    problem->setVariableValue(2, 1, value3);
    problem->setVariableValue(2, 2, value1);

    ASSERT_TRUE(sut->checkConstraints());

    delete value1;
    delete value2;
    delete value3;
    delete value4;
    delete value5;
    delete value6;
    delete value7;
}