//
// Created by Anna Siwik on 2017-04-17.
//

#include <gtest/gtest.h>
#include <problems/interface/IProblem.h>
#include <constraints/interface/IConstraint.h>
#include <problems/header/BinaryGame.h>
#include <constraints/header/EqualSplitConstraint.h>

class EqualSplitConstraintTestSuite : public ::testing::Test
{
    public:
        EqualSplitConstraintTestSuite();
        ~EqualSplitConstraintTestSuite();

    protected:
        const int width;
        const int filledFields;
        IProblem* problem;
        IConstraint* sut;

        const IValue* zero;
        const IValue* one;
};

EqualSplitConstraintTestSuite::EqualSplitConstraintTestSuite() :
        width(4),
        filledFields(0),
        problem(new BinaryGame(width, filledFields)),
        sut(new EqualSplitConstraint(problem)),
        zero(problem->getDomain()->getValue(0)),
        one(problem->getDomain()->getValue(1))
{}

EqualSplitConstraintTestSuite::~EqualSplitConstraintTestSuite()
{
    delete problem;
    delete sut;
}

TEST_F(EqualSplitConstraintTestSuite, checkVariableReturnsFalseIfItIsTooMuchZerosInRow)
{
    IVariable* var_0_0 = problem->getVariable(0, 0);
    IVariable* var_0_1 = problem->getVariable(0, 1);
    IVariable* var_0_2 = problem->getVariable(0, 2);

    var_0_0->setValue(zero);
    ASSERT_TRUE(sut->checkVariable(var_0_0));
    sut->putConstraintsOnVariable(var_0_0, false);

    var_0_1->setValue(zero);
    ASSERT_TRUE(sut->checkVariable(var_0_1));
    sut->putConstraintsOnVariable(var_0_1, false);

    var_0_2->setValue(zero);
    ASSERT_FALSE(sut->checkVariable(var_0_2));
    sut->putConstraintsOnVariable(var_0_2, false);
}

TEST_F(EqualSplitConstraintTestSuite, checkVariableReturnsFalseIfItIsTooMuchOnesInColumn)
{
    IVariable* var_0_0 = problem->getVariable(0, 0);
    IVariable* var_1_0 = problem->getVariable(1, 0);
    IVariable* var_2_0 = problem->getVariable(2, 0);

    var_0_0->setValue(one);
    ASSERT_TRUE(sut->checkVariable(var_0_0));
    sut->putConstraintsOnVariable(var_0_0, false);

    var_1_0->setValue(one);
    ASSERT_TRUE(sut->checkVariable(var_1_0));
    sut->putConstraintsOnVariable(var_1_0, false);

    var_2_0->setValue(one);
    ASSERT_FALSE(sut->checkVariable(var_2_0));
    sut->putConstraintsOnVariable(var_2_0, false);
}

TEST_F(EqualSplitConstraintTestSuite, canAddValueToDomainReturnsFalseWhenNotEqualSplit)
{
    IVariable* var_0_0 = problem->getVariable(0, 0);
    IVariable* var_0_1 = problem->getVariable(0, 1);
    IVariable* var_0_2 = problem->getVariable(0, 2);
    IVariable* var_0_3 = problem->getVariable(0, 3);

    var_0_0->setValue(one);
    sut->putConstraintsOnVariable(var_0_0, true);

    var_0_1->setValue(one);
    sut->putConstraintsOnVariable(var_0_1, true);

    var_0_2->setValue(zero);
    sut->putConstraintsOnVariable(var_0_2, true);

    sut->putConstraintsOffVariable(var_0_2);

    ASSERT_FALSE(sut->canAddValueToDomain(var_0_3, one, var_0_2));
}

TEST_F(EqualSplitConstraintTestSuite, canAddValueToDomainReturnsTrueIfEqualSplit)
{
    IVariable* var_0_0 = problem->getVariable(0, 0);
    IVariable* var_0_1 = problem->getVariable(0, 1);
    IVariable* var_0_2 = problem->getVariable(0, 2);
    IVariable* var_0_3 = problem->getVariable(0, 3);

    var_0_0->setValue(one);
    sut->putConstraintsOnVariable(var_0_0, true);

    var_0_1->setValue(one);
    sut->putConstraintsOnVariable(var_0_1, true);

    var_0_2->setValue(zero);
    sut->putConstraintsOnVariable(var_0_2, true);

    sut->putConstraintsOffVariable(var_0_2);
    var_0_2->setValue(nullptr);

    sut->putConstraintsOffVariable(var_0_1);

    ASSERT_TRUE(sut->canAddValueToDomain(var_0_3, one, var_0_1));
}

TEST_F(EqualSplitConstraintTestSuite, limitsDomainsBasedOnEqualSplit)
{
    IVariable* var_0_0 = problem->getVariable(0, 0);
    IVariable* var_0_1 = problem->getVariable(0, 1);
    IVariable* var_0_2 = problem->getVariable(0, 2);

    var_0_0->setValue(one);
    sut->putConstraintsOnVariable(var_0_0, true);

    ASSERT_EQ(var_0_2->getDomain()->getSize(), 2);

    var_0_1->setValue(one);
    sut->putConstraintsOnVariable(var_0_1, true);

    ASSERT_EQ(var_0_2->getDomain()->getSize(), 1);

    sut->putConstraintsOffVariable(var_0_1);
    var_0_1->setValue(nullptr);

    ASSERT_TRUE(sut->canAddValueToDomain(var_0_2, one, var_0_1));
}