//
// Created by Anna Siwik on 2017-04-17.
//

#include <gtest/gtest.h>

#include <problems/interface/IProblem.h>
#include <constraints/interface/IConstraint.h>
#include <problems/header/HarmoniousGraph.h>
#include <constraints/header/NeighbourConstraint.h>

class NeighbourConstraintTestSuite : public ::testing::Test
{
    public:
        NeighbourConstraintTestSuite();
        ~NeighbourConstraintTestSuite();

    protected:
        const int width;
        IProblem* problem;
        IConstraint* sut;
};

NeighbourConstraintTestSuite::NeighbourConstraintTestSuite() :
        width(3),
        problem(new HarmoniousGraph(width)),
        sut(new NeighbourConstraint(problem))
{}

NeighbourConstraintTestSuite::~NeighbourConstraintTestSuite()
{
    delete problem;
    delete sut;
}

TEST_F(NeighbourConstraintTestSuite, checkVariableReturnsFalseIfNeighbourHasTheSameValue)
{
    IVariable* var_0_0 = problem->getVariable(0, 0);
    IVariable* var_0_1 = problem->getVariable(0, 1);

    var_0_0->setValue(problem->getDomain()->getValue(0));
    ASSERT_TRUE(sut->checkVariable(var_0_0));
    sut->putConstraintsOnVariable(var_0_0, false);

    var_0_1->setValue(problem->getDomain()->getValue(0));
    ASSERT_FALSE(sut->checkVariable(var_0_1));
}

TEST_F(NeighbourConstraintTestSuite, checkVariableReturnsTrueIfNeighboursHaveDifferentValues)
{
    IVariable* var_0_1 = problem->getVariable(0, 1);
    IVariable* var_1_0 = problem->getVariable(1, 0);
    IVariable* var_1_1 = problem->getVariable(1, 1);

    var_0_1->setValue(problem->getDomain()->getValue(0));
    ASSERT_TRUE(sut->checkVariable(var_0_1));
    sut->putConstraintsOnVariable(var_0_1, false);

    var_1_0->setValue(problem->getDomain()->getValue(1));
    ASSERT_TRUE(sut->checkVariable(var_1_0));
    sut->putConstraintsOnVariable(var_1_0, false);

    var_1_1->setValue(problem->getDomain()->getValue(2));
    ASSERT_TRUE(sut->checkVariable(var_1_1));
    sut->putConstraintsOnVariable(var_1_1, false);
}