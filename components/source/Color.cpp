//
// Created by Anna Siwik on 2017-04-07.
//

#include <iostream>
#include "../header/Color.h"

Color::Color()
{
    value = -1;
}

Color::~Color()
{ }

const int Color::getValue() const
{
    return value;
}

const int Color::setValue(int value)
{
    return this->value = value;
}

const int Color::resetValue()
{
    return this->value = -1;
}
