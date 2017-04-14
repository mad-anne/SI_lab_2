//
// Created by Anna Siwik on 2017-04-08.
//

#include "../header/Domain.h"
#include <algorithm>

Domain::Domain()
{}

Domain::~Domain()
{}

void Domain::addValue(const IValue* value)
{
    if (! hasValue(value))
        values.push_back(value);
}

void Domain::removeValue(const IValue* value)
{
    values.erase(std::find(values.begin(), values.end(), value));
}

const IValue* Domain::getValue(int index) const
{
    return index < values.size()
           ? values[index]
           : nullptr;
}

const unsigned long int Domain::getSize() const
{
    return values.size();
}

bool Domain::hasValue(const IValue* value) const
{
    return std::find(values.begin(), values.end(), value) != values.end();
}

