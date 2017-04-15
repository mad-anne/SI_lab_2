//
// Created by Anna Siwik on 2017-04-15.
//

#include "components/header/Number.h"

Number::Number() :
        IValue(-1)
{}

Number::Number(int value) :
    IValue(value)
{}

Number::~Number()
{}

IValue* Number::deepCopy() const
{
    return new Number(value);
}

const int Number::getValue() const
{
    return value;
}
