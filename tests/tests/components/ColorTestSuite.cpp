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
    sut(new Color())
{ }

ColorTestSuite::~ColorTestSuite()
{
    delete sut;
}

TEST_F(ColorTestSuite, setsValueToMinusOneAsDefault)
{
    ASSERT_EQ(sut->getValue(), -1);
}

TEST_F(ColorTestSuite, returnsValueThatHasBeenSet)
{
    int value = 6;
    sut->setValue(value);

    ASSERT_EQ(sut->getValue(), 6);
}

TEST_F(ColorTestSuite, resetsValueToMinusOneAsDefault)
{
    int value = 6;
    sut->setValue(value);
    sut->resetValue();

    ASSERT_EQ(sut->getValue(), -1);
}

TEST_F(ColorTestSuite, returnsDeepCopyObject)
{
    int value = 6;
    sut->setValue(value);
    IValue* copy = sut->deepCopy();

    ASSERT_NE(copy, sut);
    ASSERT_EQ(copy->getValue(), sut->getValue());

    delete copy;
}