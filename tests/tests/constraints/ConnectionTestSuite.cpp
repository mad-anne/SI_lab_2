//
// Created by Anna Siwik on 2017-04-17.
//

#include <gtest/gtest.h>
#include <constraints/header/Connection.h>
#include <components/header/Color.h>

class ConnectionTestSuite : public  ::testing::Test
{
    public:
        ConnectionTestSuite();
        ~ConnectionTestSuite();

    protected:
        IValue* first;
        IValue* second;
        Connection* sut;
};

ConnectionTestSuite::ConnectionTestSuite() :
    first(new Color(1)),
    second(new Color(2)),
    sut(new Connection(first, second))
{}

ConnectionTestSuite::~ConnectionTestSuite()
{
    delete first;
    delete second;
    delete sut;
}

TEST_F(ConnectionTestSuite, valuesAreTheSameAsSet)
{
    ASSERT_EQ(sut->getFirstValue(), first);
    ASSERT_EQ(sut->getSecondValue(), second);
}

TEST_F(ConnectionTestSuite, compareBetweenConnectionsWithTheSameValuesReturnsTrue)
{
    Connection compared1(first, second);
    Connection compared2(second, first);

    ASSERT_TRUE(*sut == compared1);
    ASSERT_TRUE(*sut == compared2);
}

TEST_F(ConnectionTestSuite, compareBetweenConnectionsWithDifferentValuesReturnsFalse)
{
    IValue* other = new Color(3);
    Connection compared(first, other);

    ASSERT_FALSE(*sut == compared);
}