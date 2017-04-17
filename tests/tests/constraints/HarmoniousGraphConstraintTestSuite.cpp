//
// Created by Anna Siwik on 2017-04-13.
//

#include <gtest/gtest.h>
#include <constraints/interface/IConstraintChecker.h>
#include <constraints/header/HarmoniousGraphConstraintChecker.h>
#include <problems/header/HarmoniousGraph.h>
#include <components/header/Color.h>

class HarmoniousGraphConstraintTestSuite : public ::testing::Test
{
    public:
        HarmoniousGraphConstraintTestSuite();
        ~HarmoniousGraphConstraintTestSuite();

    protected:
        const int width;
        IProblem* problem;
        IConstraintChecker* sut;

        const IValue* value1;
        const IValue* value2;
        const IValue* value3;

        IVariable* var_0_0;
        IVariable* var_0_1;
        IVariable* var_0_2;
};

HarmoniousGraphConstraintTestSuite::HarmoniousGraphConstraintTestSuite()
        : width(3),
          problem(new HarmoniousGraph(width)),
          sut(new HarmoniousGraphConstraintChecker(problem))
{
    const IDomain* domain = problem->getDomain();

    value1 = domain->getValue(0);
    value2 = domain->getValue(1);
    value3 = domain->getValue(2);

    var_0_0 = problem->getVariable(0, 0);
    var_0_1 = problem->getVariable(0, 1);
    var_0_2 = problem->getVariable(0, 2);
}

HarmoniousGraphConstraintTestSuite::~HarmoniousGraphConstraintTestSuite()
{
    delete problem;
    delete sut;
}

TEST_F(HarmoniousGraphConstraintTestSuite, returnsTrueForNullptrVariable)
{
    ASSERT_TRUE(sut->isCorrectAssignment(nullptr));
}

TEST_F(HarmoniousGraphConstraintTestSuite, returnsTrueWhenNeighboursHaveDifferentValues)
{
    var_0_0->setValue(value1);
    ASSERT_TRUE(sut->isCorrectAssignment(var_0_0));
    sut->putConstraintsOn(var_0_0, false);

    var_0_1->setValue(value2);
    ASSERT_TRUE(sut->isCorrectAssignment(var_0_1));
}

TEST_F(HarmoniousGraphConstraintTestSuite, returnsFalseIfNeighboursHaveTheSameValue)
{
    var_0_0->setValue(value1);
    ASSERT_TRUE(sut->isCorrectAssignment(var_0_0));
    sut->putConstraintsOn(var_0_0, false);

    var_0_1->setValue(value1);
    ASSERT_FALSE(sut->isCorrectAssignment(var_0_1));
}

TEST_F(HarmoniousGraphConstraintTestSuite, returnsFalseIfAlreadyExistsTheSameConnection)
{
    var_0_0->setValue(value1);
    ASSERT_TRUE(sut->isCorrectAssignment(var_0_0));
    sut->putConstraintsOn(var_0_0, false);

    var_0_1->setValue(value2);
    ASSERT_TRUE(sut->isCorrectAssignment(var_0_1));
    sut->putConstraintsOn(var_0_1, false);

    var_0_2->setValue(value1);
    ASSERT_FALSE(sut->isCorrectAssignment(var_0_2));
}

TEST_F(HarmoniousGraphConstraintTestSuite, notAffectsDomainSizeIfLimitDomainsSetToFalse)
{
    unsigned long int sizeBefore = problem->getVariable(1, 0)->getDomain()->getSize();

    var_0_0->setValue(value1);
    sut->putConstraintsOn(var_0_0, false);

    var_0_1->setValue(value2);
    sut->putConstraintsOn(var_0_1, false);

    unsigned long int sizeAfter = problem->getVariable(1, 0)->getDomain()->getSize();

    ASSERT_EQ(sizeBefore, sizeAfter);
}