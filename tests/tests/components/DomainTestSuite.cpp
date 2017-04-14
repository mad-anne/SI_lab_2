//
// Created by Anna Siwik on 2017-04-13.
//

#include <gtest/gtest.h>
#include <components/interface/IDomain.h>
#include <components/header/Domain.h>
#include <components/header/Color.h>

class DomainTestSuite : public  ::testing::Test
{
    public:
        DomainTestSuite();
        ~DomainTestSuite();

    protected:
        IDomain* sut;
};

DomainTestSuite::DomainTestSuite() :
    sut(new Domain())
{ }

DomainTestSuite::~DomainTestSuite()
{
    delete sut;
}

TEST_F(DomainTestSuite, returnsNullptrIfValueDoesNotExist)
{
    ASSERT_EQ(sut->getValue(0), nullptr);
}

TEST_F(DomainTestSuite, addsValueCorrectly)
{
    IValue* value = new Color(5);
    sut->addValue(value);

    ASSERT_EQ(value, sut->getValue(0));

    delete value;
}

TEST_F(DomainTestSuite, returnsDomainSizeCorrectly)
{
    IValue* value1 = new Color(1);
    IValue* value2 = new Color(2);

    sut->addValue(value1);
    sut->addValue(value2);

    ASSERT_EQ(sut->getSize(), 2);

    delete value1;
    delete value2;
}

TEST_F(DomainTestSuite, cannotAddTwoTheSameValues)
{
    IValue* value1 = new Color(1);
    IValue* value2 = new Color(2);
    IValue* value3 = new Color(3);

    sut->addValue(value1);
    sut->addValue(value1);
    sut->addValue(value2);
    sut->addValue(value3);
    sut->addValue(value2);

    ASSERT_EQ(sut->getSize(), 3);

    delete value1;
    delete value2;
    delete value3;
}
