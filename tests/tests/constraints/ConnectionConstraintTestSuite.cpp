//
// Created by Anna Siwik on 2017-04-17.
//

#include <gtest/gtest.h>
#include <problems/interface/IProblem.h>
#include <constraints/header/ConnectionConstraint.h>
#include <problems/header/HarmoniousGraph.h>

class ConnectionConstraintTestSuite : public  ::testing::Test
{
    public:
        ConnectionConstraintTestSuite();
        ~ConnectionConstraintTestSuite();

    protected:
        const int width;
        IProblem* problem;
        IConstraint* sut;
};

ConnectionConstraintTestSuite::ConnectionConstraintTestSuite() :
    width(3),
    problem(new HarmoniousGraph(width)),
    sut(new ConnectionConstraint(problem))
{}

ConnectionConstraintTestSuite::~ConnectionConstraintTestSuite()
{
    delete problem;
    delete sut;
}

TEST_F(ConnectionConstraintTestSuite, checkVariableReturnsFalseIfConnectionExists)
{
    IVariable* var_0_0 = problem->getVariable(0, 0);
    IVariable* var_0_1 = problem->getVariable(0, 1);
    IVariable* var_0_2 = problem->getVariable(0, 2);

    var_0_0->setValue(problem->getDomain()->getValue(0));
    ASSERT_TRUE(sut->checkVariable(var_0_0));
    sut->putConstraintsOnVariable(var_0_0, false);

    var_0_1->setValue(problem->getDomain()->getValue(1));
    ASSERT_TRUE(sut->checkVariable(var_0_1));
    sut->putConstraintsOnVariable(var_0_1, false);

    var_0_2->setValue(problem->getDomain()->getValue(0));
    ASSERT_FALSE(sut->checkVariable(var_0_2));
}

TEST_F(ConnectionConstraintTestSuite, checkVariableReturnsTrueIfConnectionNotExists)
{
    IVariable* var_0_0 = problem->getVariable(0, 0);
    IVariable* var_0_1 = problem->getVariable(0, 1);
    IVariable* var_0_2 = problem->getVariable(0, 2);

    var_0_0->setValue(problem->getDomain()->getValue(0));
    ASSERT_TRUE(sut->checkVariable(var_0_0));
    sut->putConstraintsOnVariable(var_0_0, false);

    var_0_1->setValue(problem->getDomain()->getValue(1));
    ASSERT_TRUE(sut->checkVariable(var_0_1));
    sut->putConstraintsOnVariable(var_0_1, false);

    var_0_2->setValue(problem->getDomain()->getValue(2));
    ASSERT_TRUE(sut->checkVariable(var_0_2));
}

TEST_F(ConnectionConstraintTestSuite, checkAllReturnsFalseIfConnectionExists)
{
    IVariable* var_0_0 = problem->getVariable(0, 0);
    IVariable* var_0_1 = problem->getVariable(0, 1);
    IVariable* var_0_2 = problem->getVariable(0, 2);

    var_0_0->setValue(problem->getDomain()->getValue(0));
    var_0_1->setValue(problem->getDomain()->getValue(1));
    var_0_2->setValue(problem->getDomain()->getValue(0));

    ASSERT_FALSE(sut->checkAllAndPutConstraints(false));
}

TEST_F(ConnectionConstraintTestSuite, checkAllReturnsTrueIfConnectionNotExists)
{
    IVariable* var_0_0 = problem->getVariable(0, 0);
    IVariable* var_0_1 = problem->getVariable(0, 1);
    IVariable* var_0_2 = problem->getVariable(0, 2);

    var_0_0->setValue(problem->getDomain()->getValue(0));
    var_0_1->setValue(problem->getDomain()->getValue(1));
    var_0_2->setValue(problem->getDomain()->getValue(2));

    ASSERT_TRUE(sut->checkAllAndPutConstraints(false));
}

TEST_F(ConnectionConstraintTestSuite, checkVariableReturnsFalseIfConstraintsWherePutOff)
{
    IVariable* var_0_0 = problem->getVariable(0, 0);
    IVariable* var_0_1 = problem->getVariable(0, 1);
    IVariable* var_0_2 = problem->getVariable(0, 2);
    IVariable* var_1_0 = problem->getVariable(1, 0);

    var_0_0->setValue(problem->getDomain()->getValue(0));
    ASSERT_TRUE(sut->checkVariable(var_0_0));
    sut->putConstraintsOnVariable(var_0_0, false);

    var_0_1->setValue(problem->getDomain()->getValue(1));
    ASSERT_TRUE(sut->checkVariable(var_0_1));
    sut->putConstraintsOnVariable(var_0_1, false);

    var_0_2->setValue(problem->getDomain()->getValue(0));
    ASSERT_FALSE(sut->checkVariable(var_0_2));

    var_0_2->setValue(nullptr);

    sut->putConstraintsOffVariable(var_0_1, false);
    var_0_1->setValue(nullptr);

    var_1_0->setValue(problem->getDomain()->getValue(1));
    ASSERT_TRUE(sut->checkVariable(var_1_0));
}

TEST_F(ConnectionConstraintTestSuite, limitsDomainsBasedOnConnection)
{
    unsigned long int domainSize = problem->getDomain()->getSize();
    IVariable* var_0_0 = problem->getVariable(0, 0);
    IVariable* var_0_1 = problem->getVariable(0, 1);
    IVariable* var_0_2 = problem->getVariable(0, 2);

    var_0_0->setValue(problem->getDomain()->getValue(0));
    sut->putConstraintsOnVariable(var_0_0, true);

    ASSERT_EQ(domainSize, var_0_2->getDomain()->getSize());

    var_0_1->setValue(problem->getDomain()->getValue(1));
    sut->putConstraintsOnVariable(var_0_1, true);

    ASSERT_EQ(domainSize - 1, var_0_2->getDomain()->getSize());
}

TEST_F(ConnectionConstraintTestSuite, extendsDomainsBasedOnConnection)
{
    unsigned long int domainSize = problem->getDomain()->getSize();
    IVariable* var_0_0 = problem->getVariable(0, 0);
    IVariable* var_0_1 = problem->getVariable(0, 1);
    IVariable* var_0_2 = problem->getVariable(0, 2);

    var_0_0->setValue(problem->getDomain()->getValue(0));
    sut->putConstraintsOnVariable(var_0_0, true);

    var_0_1->setValue(problem->getDomain()->getValue(1));
    sut->putConstraintsOnVariable(var_0_1, true);

    sut->putConstraintsOffVariable(var_0_1, true);
    var_0_1->setValue(nullptr);

    ASSERT_EQ(domainSize, var_0_2->getDomain()->getSize());
}