//
// Created by Anna Siwik on 2017-04-17.
//

#include <lib/googletest/googletest/include/gtest/gtest.h>
#include <problems/interface/IProblem.h>
#include <constraints/interface/IConstraint.h>
#include <problems/header/BinaryGame.h>
#include <constraints/header/ExistingRowConstraint.h>

class ExistingRowConstraintTestSuite : public ::testing::Test
{
    public:
        ExistingRowConstraintTestSuite();
        ~ExistingRowConstraintTestSuite();

    protected:
        const int width;
        const int filledFields;
        IProblem* problem;
        IConstraint* sut;

        const IValue* zero;
        const IValue* one;
};

ExistingRowConstraintTestSuite::ExistingRowConstraintTestSuite() :
        width(4),
        filledFields(0),
        problem(new BinaryGame(width, filledFields)),
        sut(new ExistingRowConstraint(problem)),
        zero(problem->getDomain()->getValue(0)),
        one(problem->getDomain()->getValue(1))
{}

ExistingRowConstraintTestSuite::~ExistingRowConstraintTestSuite()
{
    delete problem;
    delete sut;
}

TEST_F(ExistingRowConstraintTestSuite, checkVariableReturnsFalseIfRowAlreadyExists)
{
    IVariable* var_0_0 = problem->getVariable(0, 0);
    IVariable* var_0_1 = problem->getVariable(0, 1);
    IVariable* var_0_2 = problem->getVariable(0, 2);
    IVariable* var_0_3 = problem->getVariable(0, 3);

    IVariable* var_1_0 = problem->getVariable(1, 0);
    IVariable* var_1_1 = problem->getVariable(1, 1);
    IVariable* var_1_2 = problem->getVariable(1, 2);
    IVariable* var_1_3 = problem->getVariable(1, 3);

    var_0_0->setValue(zero);
    ASSERT_TRUE(sut->checkVariable(var_0_0));
    sut->putConstraintsOnVariable(var_0_0, false);

    var_0_1->setValue(zero);
    ASSERT_TRUE(sut->checkVariable(var_0_1));
    sut->putConstraintsOnVariable(var_0_1, false);

    var_0_2->setValue(one);
    ASSERT_TRUE(sut->checkVariable(var_0_2));
    sut->putConstraintsOnVariable(var_0_2, false);

    var_0_3->setValue(one);
    ASSERT_TRUE(sut->checkVariable(var_0_3));
    sut->putConstraintsOnVariable(var_0_3, false);

    var_1_0->setValue(zero);
    ASSERT_TRUE(sut->checkVariable(var_1_0));
    sut->putConstraintsOnVariable(var_1_0, false);

    var_1_1->setValue(zero);
    ASSERT_TRUE(sut->checkVariable(var_1_1));
    sut->putConstraintsOnVariable(var_1_1, false);

    var_1_2->setValue(one);
    ASSERT_TRUE(sut->checkVariable(var_1_2));
    sut->putConstraintsOnVariable(var_1_2, false);

    var_1_3->setValue(one);
    ASSERT_FALSE(sut->checkVariable(var_1_3));
    sut->putConstraintsOnVariable(var_1_3, false);
}

TEST_F(ExistingRowConstraintTestSuite, limitsDomainsBasedOnExistingRow)
{
    IVariable* var_0_0 = problem->getVariable(0, 0);
    IVariable* var_0_1 = problem->getVariable(0, 1);
    IVariable* var_0_2 = problem->getVariable(0, 2);
    IVariable* var_0_3 = problem->getVariable(0, 3);

    IVariable* var_1_0 = problem->getVariable(1, 0);
    IVariable* var_1_1 = problem->getVariable(1, 1);
    IVariable* var_1_2 = problem->getVariable(1, 2);
    IVariable* var_1_3 = problem->getVariable(1, 3);

    var_0_0->setValue(zero);
    sut->putConstraintsOnVariable(var_0_0, true);

    var_0_1->setValue(zero);
    sut->putConstraintsOnVariable(var_0_1, true);

    var_0_2->setValue(one);
    sut->putConstraintsOnVariable(var_0_2, true);

    var_0_3->setValue(one);
    sut->putConstraintsOnVariable(var_0_3, true);

    var_1_0->setValue(zero);
    sut->putConstraintsOnVariable(var_1_0, true);

    ASSERT_EQ(var_1_2->getDomain()->getSize(), 2);

    var_1_1->setValue(zero);
    sut->putConstraintsOnVariable(var_1_1, true);

    ASSERT_EQ(var_1_2->getDomain()->getSize(), 1);
    ASSERT_EQ(var_1_3->getDomain()->getSize(), 1);

    sut->putConstraintsOffVariable(var_1_1);
    var_1_1->setValue(nullptr);

    ASSERT_TRUE(sut->canAddValueToDomain(var_1_2, one, var_1_1));
}