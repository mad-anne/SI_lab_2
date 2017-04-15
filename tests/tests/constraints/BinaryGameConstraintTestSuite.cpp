//
// Created by Anna Siwik on 2017-04-15.
//

#include <problems/interface/IProblem.h>
#include <constraints/interface/IConstraint.h>
#include <problems/header/BinaryGame.h>
#include <constraints/header/BinaryGameConstraint.h>
#include <gtest/gtest.h>

class BinaryGameConstraintTestSuite : public ::testing::Test
{
    public:
        BinaryGameConstraintTestSuite();
        ~BinaryGameConstraintTestSuite();

    protected:
        int width;
        int filledFields;
        IProblem* problem;
        IConstraint* sut;
};

BinaryGameConstraintTestSuite::BinaryGameConstraintTestSuite() :
    width(4),
    filledFields(0),
    problem(new BinaryGame(width, filledFields)),
    sut(new BinaryGameConstraint(problem))
{}

BinaryGameConstraintTestSuite::~BinaryGameConstraintTestSuite()
{
    delete problem;
    delete sut;
}

TEST_F(BinaryGameConstraintTestSuite, returnsTrueForNullptrVariable)
{
    ASSERT_TRUE(sut->updateConstraints(nullptr));
}

TEST_F(BinaryGameConstraintTestSuite, returnsTrueWhenFilledRowIsCorrect)
{
    problem->getVariable(0, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 1)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 2)->setValue(problem->getDomain()->getValue(1));
    problem->getVariable(0, 3)->setValue(problem->getDomain()->getValue(1));

    ASSERT_TRUE(sut->updateConstraints(problem->getVariable(0, 3)));
}

TEST_F(BinaryGameConstraintTestSuite, returnsFalseWhenAssigningThreeTheSameValuesAfterEachOther)
{
    problem->getVariable(0, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 1)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 2)->setValue(problem->getDomain()->getValue(0));

    ASSERT_FALSE(sut->updateConstraints(problem->getVariable(0, 2)));
}

TEST_F(BinaryGameConstraintTestSuite, returnsFalseWhenAssigningMoreZerosThanOnesInRow)
{
    problem->getVariable(0, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 1)->setValue(problem->getDomain()->getValue(1));
    problem->getVariable(0, 2)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 3)->setValue(problem->getDomain()->getValue(0));

    ASSERT_FALSE(sut->updateConstraints(problem->getVariable(0, 3)));
}

TEST_F(BinaryGameConstraintTestSuite, returnsFalseWhenRowAlreadyExists)
{
    problem->getVariable(0, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 1)->setValue(problem->getDomain()->getValue(1));
    problem->getVariable(0, 2)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 3)->setValue(problem->getDomain()->getValue(1));

    sut->updateConstraints(problem->getVariable(0, 3));

    problem->getVariable(1, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(1, 1)->setValue(problem->getDomain()->getValue(1));
    problem->getVariable(1, 2)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(1, 3)->setValue(problem->getDomain()->getValue(1));

    ASSERT_FALSE(sut->updateConstraints(problem->getVariable(1, 3)));
}

TEST_F(BinaryGameConstraintTestSuite, removesRowsFromAlreadyExisting)
{
    problem->getVariable(0, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 1)->setValue(problem->getDomain()->getValue(1));
    problem->getVariable(0, 2)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 3)->setValue(problem->getDomain()->getValue(1));

    sut->updateConstraints(problem->getVariable(0, 3));

    problem->getVariable(1, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(1, 1)->setValue(problem->getDomain()->getValue(1));
    problem->getVariable(1, 2)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(1, 3)->setValue(problem->getDomain()->getValue(1));

    sut->undoConstraints(problem->getVariable(0, 3));

    ASSERT_TRUE(sut->updateConstraints(problem->getVariable(1, 3)));
}