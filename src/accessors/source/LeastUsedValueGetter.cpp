//
// Created by Anna Siwik on 18.04.2017.
//

#include <algorithm>
#include <problems/interface/IProblem.h>
#include "accessors/header/LeastUsedValueGetter.h"

LeastUsedValueGetter::LeastUsedValueGetter(const IVariable* variable) :
        IValueGetter(variable)
{
    if (variable != nullptr)
        this->domain = variable->getDomain();
}

LeastUsedValueGetter::~LeastUsedValueGetter()
{}

IValue* LeastUsedValueGetter::getNext()
{
    if (variable == nullptr || used.size() >= domain->getSize())
        return nullptr;

    int index;
    int minUsages = -1;
    IValue* leastUsed = nullptr;

    for (int i = 0; i < domain->getSize(); ++i)
    {
        IValue* value = domain->getValue(i);

        if ( ! hasBeenUsed(value)
             && (minUsages == -1 || value->getNumberOfAssignments() < minUsages))
        {
            index = i;
            leastUsed = value;
            minUsages = value->getNumberOfAssignments();
        }
    }

    if (leastUsed != nullptr)
        used.push_back(domain->getValue(index));

    return leastUsed;
}

void LeastUsedValueGetter::setVariable(const IVariable* variable)
{
    this->variable = variable;

    if (variable != nullptr)
        this->domain = variable->getDomain();
}

const IVariable* LeastUsedValueGetter::getVariable() const
{
    return variable;
}

bool LeastUsedValueGetter::hasBeenUsed(IValue* value)
{
    return std::find(used.begin(), used.end(), value) != used.end();
}

IValueGetter* LeastUsedValueGetter::instantiate(const IVariable* variable) const
{
    return new LeastUsedValueGetter(variable);
}

void LeastUsedValueGetter::setProblem(const IProblem*)
{}
