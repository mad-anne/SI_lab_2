//
// Created by Anna Siwik on 2017-04-17.
//

#include <constraints/header/Row.h>
#include "constraints/header/PairConstraint.h"

PairConstraint::PairConstraint(IProblem *problem) :
        IConstraint(problem)
{}

PairConstraint::~PairConstraint()
{}

const bool PairConstraint::checkVariable(const IVariable* variable) const
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return true;

    return checkValueRepetitions(variable);
}

const bool PairConstraint::checkAllAndPutConstraints(bool limitDomains)
{
    return 0; // TODO
}

void PairConstraint::putConstraintsOnVariable(const IVariable* variable, bool limitDomains)
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return;

    if (limitDomains)
        limitDomainsOnVariable(variable);
}

void PairConstraint::putConstraintsOffVariable(const IVariable*)
{
    return;
}

bool PairConstraint::canAddValueToDomain(const IVariable* checked, const IValue* value, const IVariable* reversed)
{
    return canAddValueToRow(checked, value, reversed)
           && canAddValueToColumn(checked, value, reversed);
}

const bool PairConstraint::checkValueRepetitions(const IVariable* variable) const
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return true;

    return checkValuesInRow(variable) && checkValuesInColumn(variable);
}

const bool PairConstraint::checkValuesInRow(const IVariable* variable) const
{
    const IValue* value = getValueOfVariable(variable);

    const IValue* valLeft = getValueOfVariable(getLeftNeighbour(variable));
    const IValue* valRight = getValueOfVariable(getRightNeighbour(variable));

    return  ! (valLeft == value && value == valRight)
            && (valLeft == value ? getValueOfVariable(getLeftNeighbour(getLeftNeighbour(variable))) != value : true)
            && (valRight == value ? getValueOfVariable(getRightNeighbour(getRightNeighbour(variable))) != value : true);
}

bool PairConstraint::checkValuesInColumn(const IVariable* variable) const
{
    const IValue* value = getValueOfVariable(variable);

    const IValue* valUp = getValueOfVariable(getUpNeighbour(variable));
    const IValue* valDown = getValueOfVariable(getDownNeighbour(variable));

    return  ! (valUp == value && value == valDown)
            && (valUp == value ? getValueOfVariable(getUpNeighbour(getUpNeighbour(variable))) != value : true)
            && (valDown == value ? getValueOfVariable(getDownNeighbour(getDownNeighbour(variable))) != value : true);
}

void PairConstraint::limitDomainsOnVariable(const IVariable* variable)
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return;

    limitDomainsInRow(variable);
    limitDomainsInColumn(variable);
}

void PairConstraint::limitDomainsInRow(const IVariable* variable)
{
    const IValue* value = getValueOfVariable(variable);

    IVariable* varLeft = getLeftNeighbour(variable);
    IVariable* varRight = getRightNeighbour(variable);

    if (getValueOfVariable(varLeft) == value && varRight != nullptr && varRight->getValue() == nullptr)
        varRight->removeValueFromDomain(value);

    if (getValueOfVariable(varRight) == value && varLeft != nullptr && varLeft->getValue() == nullptr)
        varLeft->removeValueFromDomain(value);
}

void PairConstraint::limitDomainsInColumn(const IVariable* variable)
{
    const IValue* value = getValueOfVariable(variable);

    IVariable* varUp = getUpNeighbour(variable);
    IVariable* varDown = getDownNeighbour(variable);

    if (getValueOfVariable(varUp) == value && varDown != nullptr && varDown->getValue() == nullptr)
        varDown->removeValueFromDomain(value);

    if (getValueOfVariable(varDown) == value && varUp != nullptr && varUp->getValue() == nullptr)
        varUp->removeValueFromDomain(value);
}

bool PairConstraint::canAddValueToRow(const IVariable* checked, const IValue* value, const IVariable* reversed)
{
    IVariable* varLeft = getLeftNeighbour(checked);
    IVariable* varRight = getRightNeighbour(checked);

    return ! (getValueOfVariable(varLeft) == value && getValueOfVariable(varRight) == value)
           && ! (getValueOfVariable(varLeft) == value && getValueOfVariable(getLeftNeighbour(varLeft)) == value)
           && ! (getValueOfVariable(varRight) == value && getValueOfVariable(getRightNeighbour(varRight)) == value);
}

bool
PairConstraint::canAddValueToColumn(const IVariable* checked, const IValue* value, const IVariable* reversed)
{
    IVariable* varUp = getUpNeighbour(checked);
    IVariable* varDown = getDownNeighbour(checked);

    return ! (getValueOfVariable(varUp) == value && getValueOfVariable(varDown) == value)
           && ! (getValueOfVariable(varUp) == value && getValueOfVariable(getLeftNeighbour(varUp)) == value)
           && ! (getValueOfVariable(varDown) == value && getValueOfVariable(getRightNeighbour(varDown)) == value);
}
