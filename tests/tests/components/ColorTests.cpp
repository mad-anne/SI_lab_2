//
// Created by Anna Siwik on 2017-04-12.
//

#include <gtest/gtest.h>
#include <components/header/Color.h>

class ColorTestSuite
{
    public:
        ColorTestSuite();

    private:
        Color sut;
};

ColorTestSuite::ColorTestSuite() :
    sut()
{ }


TEST(ColorTestSuite, classCreates)
{

}