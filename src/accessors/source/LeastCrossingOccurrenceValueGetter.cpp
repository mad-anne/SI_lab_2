//
// Created by Anna Siwik on 18.04.2017.
//

#include <algorithm>
#include <constraints/header/Column.h>
#include <constraints/header/Row.h>
#include "accessors/header/LeastCrossingOccurrenceValueGetter.h"

LeastCrossingOccurrenceValueGetter::LeastCrossingOccurrenceValueGetter(const IVariable* variable, const IProblem* problem) :
        IValueGetter(variable),
        problem(problem)
{
    if (variable != nullptr)
        this->domain = variable->getDomain();
}

LeastCrossingOccurrenceValueGetter::~LeastCrossingOccurrenceValueGetter()
{}

IValue* LeastCrossingOccurrenceValueGetter::getNext()
{
    if (variable == nullptr || used.size() >= domain->getSize())
        return nullptr;

    int tempOccurrences = -1;
    int minOccurrences = -1;
    IValue* leastOccurrence = nullptr;

    for (int i = 0; i < domain->getSize(); ++i)
    {
        IValue* value = domain->getValue(i);

        if ( ! hasBeenUsed(value)
             && (minOccurrences == -1 || (tempOccurrences = countValueOnCrossing(value)) < minOccurrences))
        {
            leastOccurrence = value;
            minOccurrences = (tempOccurrences == -1 ? countValueOnCrossing(value) : tempOccurrences);
        }
    }

    return leastOccurrence;
}

void LeastCrossingOccurrenceValueGetter::setVariable(const IVariable* variable)
{
    this->variable = variable;

    if (variable != nullptr)
        this->domain = variable->getDomain();
}

const IVariable* LeastCrossingOccurrenceValueGetter::getVariable() const
{
    return variable;
}

bool LeastCrossingOccurrenceValueGetter::hasBeenUsed(IValue* value)
{
    return std::find(used.begin(), used.end(), value) != used.end();
}

int LeastCrossingOccurrenceValueGetter::countValueOnCrossing(IValue* value)
{
    Row r(problem, variable);
    Column c(problem, variable);

    return r.countValue(value) + c.countValue(value)
           + (variable->getValue() == value ? -1 : 0);
}

IValueGetter* LeastCrossingOccurrenceValueGetter::instantiate(const IVariable* variable) const
{
    return new LeastCrossingOccurrenceValueGetter(variable, problem);
}
