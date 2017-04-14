//
// Created by Anna Siwik on 2017-04-13.
//

#include <gtest/gtest.h>
#include <components/header/Node.h>
#include <components/header/Color.h>

class NodeTestSuite : public  ::testing::Test
{
    public:
        NodeTestSuite();
        ~NodeTestSuite();

    protected:
        IVariable* sut;
};

NodeTestSuite::NodeTestSuite() :
    sut(new Node(-1, -1))
{ }

NodeTestSuite::~NodeTestSuite()
{
    delete sut;
}

TEST_F(NodeTestSuite, returnsNullptrIfValueHasNotBeenSet)
{
    ASSERT_EQ(sut->getValue(), nullptr);
}

TEST_F(NodeTestSuite, returnsNullptrIfValueHasBeenReset)
{
    IValue* value = new Color(1);
    sut->setValue(value);
    sut->resetValue();

    ASSERT_EQ(sut->getValue(), nullptr);

    delete value;
}

TEST_F(NodeTestSuite, returnsValueThatHasBeenSet)
{
    IValue* value = new Color(1);
    sut->setValue(value);

    ASSERT_EQ(sut->getValue(), value);

    delete value;
}

TEST_F(NodeTestSuite, domainIsEmptyAsDefault)
{
    ASSERT_EQ(sut->getDomain()->getSize(), 0);
}

TEST_F(NodeTestSuite, domainConsistsOfValuesThatHasBeenAdded)
{
    IValue* value1 = new Color(1);
    IValue* value2 = new Color(2);

    sut->addValueToDomain(value1);
    sut->addValueToDomain(value2);

    const IDomain* domain = sut->getDomain();

    ASSERT_EQ(domain->getSize(), 2);
    ASSERT_EQ(domain->getValue(0), value1);
    ASSERT_EQ(domain->getValue(1), value2);

    delete value1;
    delete value2;
}

TEST_F(NodeTestSuite, copyValuesFromOtherDomain)
{
    IValue* value1 = new Color(1);
    IValue* value2 = new Color(2);

    IDomain* domain = new Domain();
    domain->addValue(value1);
    domain->addValue(value2);

    sut->addDomain(domain);

    const IDomain* sutDomain = sut->getDomain();

    ASSERT_NE(sut->getDomain(), domain);

    ASSERT_EQ(domain->getSize(), 2);
    ASSERT_EQ(sutDomain->getValue(0), value1);
    ASSERT_EQ(sutDomain->getValue(1), value2);

    delete domain;
    delete value1;
    delete value2;
}