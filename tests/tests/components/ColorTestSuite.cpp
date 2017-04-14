//
// Created by Anna Siwik on 2017-04-12.
//

#include <gtest/gtest.h>
#include <components/header/Color.h>

class ColorTestSuite : public ::testing::Test
{
    public:
        ColorTestSuite();
        ~ColorTestSuite();

    protected:
        IValue* sut;
};

ColorTestSuite::ColorTestSuite() :
    sut(new Color(0))
{ }

ColorTestSuite::~ColorTestSuite()
{
    delete sut;
}

TEST_F(ColorTestSuite, returnsDeepCopyObject)
{
    IValue* copy = sut->deepCopy();

    ASSERT_NE(copy, sut);
    ASSERT_EQ(copy->getValue(), sut->getValue());

    delete copy;
}