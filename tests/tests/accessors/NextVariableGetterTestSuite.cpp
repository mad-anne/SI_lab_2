//
// Created by Anna Siwik on 2017-04-14.
//

#include <gtest/gtest.h>
#include <accessors/header/NextVariableGetter.h>
#include <problems/header/HarmoniousGraph.h>

class NextVariableGetterTestSuite : public  ::testing::Test
{
    public:
        NextVariableGetterTestSuite();
        ~NextVariableGetterTestSuite();

        void completeProblem();
        void completeFirstRow();
    protected:
        int width;
        IProblem* problem;
        NextVariableGetter* sut;
};

NextVariableGetterTestSuite::NextVariableGetterTestSuite()
        : width(3),
          problem(new HarmoniousGraph(width)),
          sut(new NextVariableGetter(problem))
{}

NextVariableGetterTestSuite::~NextVariableGetterTestSuite()
{
    delete problem;
    delete sut;
}

void NextVariableGetterTestSuite::completeProblem()
{
    const IDomain* domain = problem->getDomain();

    problem->getVariable(0, 0)->setValue(domain->getValue(0));
    problem->getVariable(0, 1)->setValue(domain->getValue(1));
    problem->getVariable(0, 2)->setValue(domain->getValue(2));
    problem->getVariable(1, 0)->setValue(domain->getValue(3));
    problem->getVariable(1, 1)->setValue(domain->getValue(4));
    problem->getVariable(1, 2)->setValue(domain->getValue(5));
    problem->getVariable(2, 0)->setValue(domain->getValue(6));
    problem->getVariable(2, 1)->setValue(domain->getValue(2));
    problem->getVariable(2, 2)->setValue(domain->getValue(0));
}

void NextVariableGetterTestSuite::completeFirstRow()
{
    const IDomain* domain = problem->getDomain();

    problem->getVariable(0, 0)->setValue(domain->getValue(0));
    problem->getVariable(0, 1)->setValue(domain->getValue(1));
    problem->getVariable(0, 2)->setValue(domain->getValue(2));
}

TEST_F(NextVariableGetterTestSuite, canSetProblem)
{
    IProblem* other = new HarmoniousGraph(1);
    sut->setProblem(other);

    ASSERT_NE(sut->getProblem(), problem);
    ASSERT_EQ(sut->getProblem(), other);

    delete other;
}

TEST_F(NextVariableGetterTestSuite, returnsFirstVariableIfSolutionIsEmpty)
{
    ASSERT_EQ(sut->getNext(), problem->getVariable(0, 0));
}

TEST_F(NextVariableGetterTestSuite, returnsFirstVariableInSecondRowIfFirstRowIsCompleted)
{
    completeFirstRow();
    ASSERT_EQ(sut->getNext(), problem->getVariable(1, 0));
}

TEST_F(NextVariableGetterTestSuite, returnsNullptrIfProblemIsCompleted)
{
    completeProblem();
    ASSERT_EQ(sut->getNext(), nullptr);
}
