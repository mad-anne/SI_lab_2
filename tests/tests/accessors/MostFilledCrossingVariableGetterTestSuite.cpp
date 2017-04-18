//
// Created by Anna Siwik on 18.04.2017.
//

#include <lib/googletest/googletest/include/gtest/gtest.h>
#include <problems/interface/IProblem.h>
#include <accessors/interface/IVariableGetter.h>
#include <problems/header/BinaryGame.h>
#include <accessors/header/MostFilledCrossingVariableGetter.h>

class MostFilledCrossingVariableGetterTestSuite : public ::testing::Test
{
    public:
        MostFilledCrossingVariableGetterTestSuite();
        ~MostFilledCrossingVariableGetterTestSuite();

    protected:
        const int width;
        const int filledFields;
        IProblem* problem;
        IVariableGetter* sut;
};

MostFilledCrossingVariableGetterTestSuite::MostFilledCrossingVariableGetterTestSuite() :
    width(4),
    filledFields(0),
    problem(new BinaryGame(width, filledFields)),
    sut(new MostFilledCrossingVariableGetter(problem))
{}

MostFilledCrossingVariableGetterTestSuite::~MostFilledCrossingVariableGetterTestSuite()
{
    delete sut;
    delete problem;
}

TEST_F(MostFilledCrossingVariableGetterTestSuite, returnsFirstValueForTheFirstTime)
{
    ASSERT_EQ(sut->getNext(), problem->getVariable(0, 0));
}

TEST_F(MostFilledCrossingVariableGetterTestSuite, returnsFirstMostFilledOnCrossingVariable)
{
    problem->getVariable(0, 1)->setValue(problem->getDomain()->getValue(1));
    problem->getVariable(1, 1)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(3, 1)->setValue(problem->getDomain()->getValue(0));

    problem->getVariable(2, 0)->setValue(problem->getDomain()->getValue(0));

    ASSERT_EQ(sut->getNext(), problem->getVariable(2, 1));
}
