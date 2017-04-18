//
// Created by Anna Siwik on 2017-04-14.
//

#include "accessors/header/NextValueGetter.h"
#include <algorithm>

NextValueGetter::NextValueGetter(const IVariable* variable)
        : IValueGetter(variable)
{
    if (variable != nullptr)
        this->domain = variable->getDomain();
}

NextValueGetter::~NextValueGetter()
{}

const IValue* NextValueGetter::getNext()
{
    if (used.size() >= domain->getSize())
        return nullptr;

    for (int i = 0; i < domain->getSize(); ++i)
    {
        if ( ! hasBeenUsed(domain->getValue(i)))
        {
            used.push_back(domain->getValue(i));
            return domain->getValue(i);
        }
    }
}

void NextValueGetter::setVariable(const IVariable* variable)
{
    this->variable = variable;
    this->domain = variable->getDomain();
}

const IVariable* NextValueGetter::getVariable() const
{
    return variable;
}

bool NextValueGetter::hasBeenUsed(const IValue* value)
{
    return std::find(used.begin(), used.end(), value) != used.end();
}
