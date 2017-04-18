//
// Created by Anna Siwik on 18.04.2017.
//

#include <gtest/gtest.h>
#include <problems/interface/IProblem.h>
#include <problems/header/HarmoniousGraph.h>
#include <accessors/header/LeastUsedValueGetter.h>

class LeastUsedValueGetterTestSuite : public ::testing::Test
{
    public:
        LeastUsedValueGetterTestSuite();
        ~LeastUsedValueGetterTestSuite();

    protected:
        const int width;
        IProblem* problem;
        IValueGetter* sut;
};

LeastUsedValueGetterTestSuite::LeastUsedValueGetterTestSuite() :
        width(3),
        problem(new HarmoniousGraph(width)),
        sut(new LeastUsedValueGetter(nullptr))
{}

LeastUsedValueGetterTestSuite::~LeastUsedValueGetterTestSuite()
{
    delete problem;
    delete sut;
}

TEST_F(LeastUsedValueGetterTestSuite, returnsFirstValueForTheFirstTime)
{
    sut->setVariable(problem->getVariable(0, 0));
    ASSERT_EQ(sut->getNext(), problem->getDomain()->getValue(0));
}

TEST_F(LeastUsedValueGetterTestSuite, returnsFirstLeastUsedValue)
{
    problem->getVariable(0, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 1)->setValue(problem->getDomain()->getValue(1));
    problem->getVariable(0, 2)->setValue(problem->getDomain()->getValue(5));

    problem->getVariable(1, 0)->setValue(problem->getDomain()->getValue(5));
    problem->getVariable(1, 1)->setValue(problem->getDomain()->getValue(2));

    sut->setVariable(problem->getVariable(1, 2));
    ASSERT_EQ(sut->getNext(), problem->getDomain()->getValue(3));
}

