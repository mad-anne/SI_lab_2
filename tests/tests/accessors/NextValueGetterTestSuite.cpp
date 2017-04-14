//
// Created by Anna Siwik on 2017-04-14.
//

#include <gtest/gtest.h>
#include <accessors/header/NextValueGetter.h>
#include <components/header/Node.h>
#include <components/header/Color.h>

class NextValueGetterTestSuite : public  ::testing::Test
{
    public:
        NextValueGetterTestSuite();
        ~NextValueGetterTestSuite();

    protected:
        int row;
        int col;
        IDomain* domain;
        IVariable* variable;
        IValueGetter* sut;
};

NextValueGetterTestSuite::NextValueGetterTestSuite()
        : row(0),
          col(0),
          domain(new Domain()),
          variable(new Node(row, col)),
          sut(new NextValueGetter(variable))
{
    domain->addValue(new Color(1));
    domain->addValue(new Color(2));
    domain->addValue(new Color(3));
    variable->addDomain(domain);
}

NextValueGetterTestSuite::~NextValueGetterTestSuite()
{
    delete sut;
    delete variable;
    delete domain;
}

TEST_F(NextValueGetterTestSuite, canSetVariable)
{
    IVariable* other = new Node(1, 1);
    sut->setVariable(other);

    ASSERT_NE(sut->getVariable(), variable);
    ASSERT_EQ(sut->getVariable(), other);

    delete other;
}


TEST_F(NextValueGetterTestSuite, returnsFirstValueIfNoneHasBeenChosenEarlier)
{
    ASSERT_EQ(sut->getNext(), domain->getValue(0));
}

TEST_F(NextValueGetterTestSuite, returnsValuesInOrderTheyAreInDomain)
{
    ASSERT_EQ(sut->getNext(), domain->getValue(0));
    ASSERT_EQ(sut->getNext(), domain->getValue(1));
    ASSERT_EQ(sut->getNext(), domain->getValue(2));
}

TEST_F(NextValueGetterTestSuite, returnsNullptrIfEveryValueHasBeenChosenEarlier)
{
    sut->getNext();
    sut->getNext();
    sut->getNext();

    ASSERT_EQ(sut->getNext(), nullptr);
}