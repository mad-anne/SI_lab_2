//
// Created by Anna Siwik on 2017-04-07.
//

#include "../header/Color.h"

Color::Color(int value) :
    IValue(value)
{}

Color::~Color()
{}

IValue* Color::deepCopy() const
{
    return new Color(value);
}

const int Color::getValue() const
{
    return value;
}
