//
// Created by Anna Siwik on 2017-04-14.
//

#include "accessors/header/NextValueGetter.h"

NextValueGetter::NextValueGetter(const IVariable* variable)
        : IValueGetter(variable),
          currentIndex(0)
{
    this->domain = variable->getDomain();
}

NextValueGetter::~NextValueGetter()
{}

const IValue* NextValueGetter::getNext()
{
    return currentIndex < domain->getSize()
           ? domain->getValue(currentIndex++)
           : nullptr;
}

void NextValueGetter::setVariable(const IVariable* variable)
{
    this->variable = variable;
    this->domain = variable->getDomain();
    currentIndex = 0;
}

const IVariable* NextValueGetter::getVariable() const
{
    return variable;
}
