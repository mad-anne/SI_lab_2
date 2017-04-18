//
// Created by Anna Siwik on 18.04.2017.
//

#include <gtest/gtest.h>
#include <problems/interface/IProblem.h>
#include <accessors/interface/IValueGetter.h>
#include <problems/header/BinaryGame.h>
#include <accessors/header/LeastCrossingOccurrenceValueGetter.h>

class LeastCrossingOccurrenceValueGetterTestSuite : public ::testing::Test
{
    public:
        LeastCrossingOccurrenceValueGetterTestSuite();
        ~LeastCrossingOccurrenceValueGetterTestSuite();

    protected:
        const int width;
        const int filledFields;
        IProblem* problem;
        IValueGetter* sut;
};

LeastCrossingOccurrenceValueGetterTestSuite::LeastCrossingOccurrenceValueGetterTestSuite() :
    width(4),
    filledFields(0),
    problem(new BinaryGame(width, filledFields)),
    sut(new LeastCrossingOccurrenceValueGetter(nullptr, problem))
{}

LeastCrossingOccurrenceValueGetterTestSuite::~LeastCrossingOccurrenceValueGetterTestSuite()
{
    delete sut;
    delete problem;
}

TEST_F(LeastCrossingOccurrenceValueGetterTestSuite, returnsFirstValueForTheFirstTime)
{
    sut->setVariable(problem->getVariable(0, 0));
    ASSERT_EQ(sut->getNext(), problem->getDomain()->getValue(0));
}

TEST_F(LeastCrossingOccurrenceValueGetterTestSuite, returnsLeastOccurrenceOnCrossingValue)
{
    problem->getVariable(0, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 1)->setValue(problem->getDomain()->getValue(1));
    problem->getVariable(0, 2)->setValue(problem->getDomain()->getValue(0));

    problem->getVariable(2, 1)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(3, 1)->setValue(problem->getDomain()->getValue(1));

    sut->setVariable(problem->getVariable(1, 1));
    ASSERT_EQ(sut->getNext(), problem->getDomain()->getValue(0));
}


