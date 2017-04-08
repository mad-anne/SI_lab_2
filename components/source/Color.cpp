//
// Created by Anna Siwik on 2017-04-07.
//

#include "../header/Color.h"

Color::Color()
{
    value = -1;
}

Color::~Color()
{ }

int Color::getValue()
{
    return value;
}

int Color::setValue(int value)
{
    return this->value = value;
}

int Color::resetValue()
{
    return this->value = -1;
}
