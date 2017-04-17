//
// Created by Anna Siwik on 2017-04-17.
//

#include "constraints/header/NeighbourConstraint.h"

NeighbourConstraint::NeighbourConstraint(IProblem* problem) :
        IConstraint(problem)
{}

NeighbourConstraint::~NeighbourConstraint()
{}

const bool NeighbourConstraint::checkVariable(const IVariable* variable) const
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return true;

    return checkConnectionsWithNeighbours(variable);
}

const bool NeighbourConstraint::checkAllAndPutConstraints(bool limitDomains)
{
    bool isCorrect = true;

    IProblem* copy = problem->deepCopy();
    const IDomain* domain = problem->getDomain();

    problem->resetAllVariables();

    int width = problem->getWidth();
    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (copy->getVariable(row, col)->getValue() != nullptr)
            {
                int index = copy->getVariable(row, col)->getValue()->getValue();
                IVariable* variable = problem->getVariable(row, col);
                variable->setValue(domain->getValue(index));

                if (isCorrect)
                {
                    if (checkVariable(variable))
                        putConstraintsOnVariable(variable, limitDomains);
                    else
                        isCorrect = false;
                }
            }
        }
    }

    delete copy;

    return isCorrect;
}

void NeighbourConstraint::putConstraintsOnVariable(const IVariable* variable, bool limitDomains)
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return;

    if (limitDomains)
        limitDomainsOnVariable(variable);
}

void NeighbourConstraint::putConstraintsOffVariable(const IVariable*)
{
    return;
}

bool NeighbourConstraint::canAddValueToDomain(const IVariable* checked, const IValue* value, const IVariable* reversed)
{
    return ! hasNeighbourWithValue(checked, value, reversed);
}

const bool NeighbourConstraint::checkConnectionsWithNeighbours(const IVariable* variable) const
{
    const IValue* value = variable->getValue();

    return  (getValueOfVariable(getLeftNeighbour(variable)) != value)
            && (getValueOfVariable(getUpNeighbour(variable)) != value)
            && (getValueOfVariable(getRightNeighbour(variable)) != value)
            && (getValueOfVariable(getDownNeighbour(variable)) != value);
}

void NeighbourConstraint::limitDomainsOnVariable(const IVariable* variable)
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return;

    const IValue* value = getValueOfVariable(variable);

    limitDomainOnValue(getLeftNeighbour(variable), value);
    limitDomainOnValue(getUpNeighbour(variable), value);
    limitDomainOnValue(getRightNeighbour(variable), value);
    limitDomainOnValue(getDownNeighbour(variable), value);
}

void NeighbourConstraint::limitDomainOnValue(IVariable* variable, const IValue* value)
{
    if (variable != nullptr)
        variable->removeValueFromDomain(value);
}

bool NeighbourConstraint::hasNeighbourWithValue(const IVariable* variable, const IValue* value, const IVariable* allowedNeighbour) const
{
    IVariable* varLeft = getLeftNeighbour(variable);
    IVariable* varUp = getUpNeighbour(variable);
    IVariable* varRight = getRightNeighbour(variable);
    IVariable* varDown = getDownNeighbour(variable);

    return  (getValueOfVariable(varLeft) == value && varLeft != allowedNeighbour)
            || (getValueOfVariable(varUp) == value && varUp != allowedNeighbour)
            || (getValueOfVariable(varRight) == value && varRight != allowedNeighbour)
            || (getValueOfVariable(varDown) == value && varDown != allowedNeighbour);
}
