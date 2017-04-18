//
// Created by Anna Siwik on 2017-04-15.
//

#include <problems/interface/IProblem.h>
#include <constraints/interface/IConstraintChecker.h>
#include <problems/header/BinaryGame.h>
#include <constraints/header/BinaryGameConstraintChecker.h>
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
        IConstraintChecker* sut;
};

BinaryGameConstraintTestSuite::BinaryGameConstraintTestSuite() :
    width(4),
    filledFields(0),
    problem(new BinaryGame(width, filledFields)),
    sut(new BinaryGameConstraintChecker(problem))
{}

BinaryGameConstraintTestSuite::~BinaryGameConstraintTestSuite()
{
    delete problem;
    delete sut;
}

TEST_F(BinaryGameConstraintTestSuite, returnsTrueForNullptrVariable)
{
    ASSERT_TRUE(sut->isCorrectAssignment(nullptr));
}

TEST_F(BinaryGameConstraintTestSuite, returnsTrueWhenFilledRowIsCorrect)
{
    problem->getVariable(0, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 1)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 2)->setValue(problem->getDomain()->getValue(1));
    problem->getVariable(0, 3)->setValue(problem->getDomain()->getValue(1));

    ASSERT_TRUE(sut->isCorrectAssignment(problem->getVariable(0, 3)));
}

TEST_F(BinaryGameConstraintTestSuite, returnsFalseWhenAssigningThreeTheSameValuesAfterEachOther)
{
    problem->getVariable(0, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 1)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 2)->setValue(problem->getDomain()->getValue(0));

    ASSERT_FALSE(sut->isCorrectAssignment(problem->getVariable(0, 2)));
}

TEST_F(BinaryGameConstraintTestSuite, returnsFalseWhenAssigningMoreZerosThanOnesInRow)
{
    problem->getVariable(0, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 1)->setValue(problem->getDomain()->getValue(1));
    problem->getVariable(0, 2)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 3)->setValue(problem->getDomain()->getValue(0));

    ASSERT_FALSE(sut->isCorrectAssignment(problem->getVariable(0, 3)));
}

TEST_F(BinaryGameConstraintTestSuite, returnsFalseWhenRowAlreadyExists)
{
    problem->getVariable(0, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 1)->setValue(problem->getDomain()->getValue(1));
    problem->getVariable(0, 2)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 3)->setValue(problem->getDomain()->getValue(1));

    sut->putConstraintsOn(problem->getVariable(0, 3), false);

    problem->getVariable(1, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(1, 1)->setValue(problem->getDomain()->getValue(1));
    problem->getVariable(1, 2)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(1, 3)->setValue(problem->getDomain()->getValue(1));

    ASSERT_FALSE(sut->isCorrectAssignment(problem->getVariable(1, 3)));
}

TEST_F(BinaryGameConstraintTestSuite, removesRowsFromAlreadyExisting)
{
    problem->getVariable(0, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 1)->setValue(problem->getDomain()->getValue(1));
    problem->getVariable(0, 2)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(0, 3)->setValue(problem->getDomain()->getValue(1));

    ASSERT_TRUE(sut->isCorrectAssignment(problem->getVariable(0, 3)));
    sut->putConstraintsOn(problem->getVariable(0, 3), true);

    problem->getVariable(1, 0)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(1, 1)->setValue(problem->getDomain()->getValue(1));
    problem->getVariable(1, 2)->setValue(problem->getDomain()->getValue(0));
    problem->getVariable(1, 3)->setValue(problem->getDomain()->getValue(1));

    ASSERT_FALSE(sut->isCorrectAssignment(problem->getVariable(1, 3)));
    problem->getVariable(1, 3)->setValue(nullptr);

    sut->putConstraintsOff(problem->getVariable(0, 3), true);
    problem->getVariable(0, 3)->setValue(nullptr);

    ASSERT_TRUE(sut->isCorrectAssignment(problem->getVariable(1, 3)));
}

TEST_F(BinaryGameConstraintTestSuite, limitsDomainsCorrectlyWhenFirstFilled)
{
    problem->getVariable(0, 0)->setValue(problem->getDomain()->getValue(0));
    sut->putConstraintsOn(problem->getVariable(0, 0), true);

    problem->getVariable(0, 1)->setValue(problem->getDomain()->getValue(0));
    sut->putConstraintsOn(problem->getVariable(0, 1), true);

    problem->getVariable(0, 2)->setValue(problem->getDomain()->getValue(1));
    sut->putConstraintsOn(problem->getVariable(0, 2), true);

    problem->getVariable(0, 3)->setValue(problem->getDomain()->getValue(1));
    sut->putConstraintsOn(problem->getVariable(0, 3), true);

    ASSERT_EQ(problem->getVariable(1, 0)->getDomain()->getSize(), 2);
    ASSERT_EQ(problem->getVariable(1, 2)->getDomain()->getSize(), 2);

    problem->getVariable(1, 0)->setValue(problem->getDomain()->getValue(0));
    sut->putConstraintsOn(problem->getVariable(1, 0), true);

    problem->getVariable(1, 1)->setValue(problem->getDomain()->getValue(0));
    sut->putConstraintsOn(problem->getVariable(1, 1), true);

    ASSERT_EQ(problem->getVariable(1, 2)->getDomain()->getSize(), 0);

    sut->putConstraintsOff(problem->getVariable(1, 1), true);
    problem->getVariable(1, 1)->setValue(nullptr);

    ASSERT_EQ(problem->getVariable(1, 2)->getDomain()->getSize(), 2);
}