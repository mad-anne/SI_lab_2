//
// Created by Anna Siwik on 2017-04-13.
//

#include <problems/interface/IProblem.h>
#include <constraints/header/HarmoniousGraphConstraint.h>

HarmoniousGraphConstraint::HarmoniousGraphConstraint(IProblem* problem)
        : IConstraint(problem)
{}

HarmoniousGraphConstraint::~HarmoniousGraphConstraint()
{
    clearConnections();
}

const bool HarmoniousGraphConstraint::updateConstraints(const IVariable* variable)
{
    if (checkConstraints(variable))
    {
        addConnections(variable);
        return true;
    }

    return false;
}

void HarmoniousGraphConstraint::undoConstraints(const IVariable* variable)
{
    removeConnections(variable);
}

void HarmoniousGraphConstraint::setProblem(IProblem* problem)
{
    this->problem = problem;
}

const IProblem* HarmoniousGraphConstraint::getProblem() const
{
    return problem;
}

const bool HarmoniousGraphConstraint::checkConstraints(const IVariable* variable) const
{
    if (variable == nullptr)
        return true;

    return checkNeighbours(variable) && checkConnections(variable);
}

const bool HarmoniousGraphConstraint::checkNeighbours(const IVariable* variable) const
{
    const IValue* value = getValue(variable);

    const IValue* valueUp = getValue(getUpNeighbour(variable));
    const IValue* valueRight = getValue(getRightNeighbour(variable));
    const IValue* valueDown = getValue(getDownNeighbour(variable));
    const IValue* valueLeft = getValue(getLeftNeighbour(variable));

    return  value != valueUp
            && value != valueRight
            && value != valueDown
            && value != valueLeft;
}

const bool HarmoniousGraphConstraint::checkConnections(const IVariable* variable) const
{
    const IValue* value = getValue(variable);

    const IValue* valueUp = getValue(getUpNeighbour(variable));
    const IValue* valueRight = getValue(getRightNeighbour(variable));
    const IValue* valueDown = getValue(getDownNeighbour(variable));
    const IValue* valueLeft = getValue(getLeftNeighbour(variable));

    return  ! existsConnection(value, valueUp)
            && ! existsConnection(value, valueRight)
            && ! existsConnection(value, valueDown)
            && ! existsConnection(value, valueLeft);
}

const bool HarmoniousGraphConstraint::existsConnection(const IValue* value, const IValue* neighbour) const
{
    if (value == nullptr || neighbour == nullptr)
        return false;

    bool exists = false;

    for (unsigned long int i = 0; ! exists && i < connections.size(); ++i)
    {
        const IValue* first = connections[i]->getFirstValue();
        const IValue* second = connections[i]->getSecondValue();

        if ((value == first && neighbour == second) || (value == second && neighbour == first))
            exists = true;
    }

    return exists;
}

void HarmoniousGraphConstraint::addConnections(const IVariable* variable)
{
    if (variable == nullptr)
        return;

    const IValue* value = getValue(variable);

    addConnection(value, getValue(getUpNeighbour(variable)));
    addConnection(value, getValue(getRightNeighbour(variable)));
    addConnection(value, getValue(getDownNeighbour(variable)));
    addConnection(value, getValue(getLeftNeighbour(variable)));
}

void HarmoniousGraphConstraint::addConnection(const IValue* value1, const IValue* value2)
{
    if (value1 == nullptr || value2 == nullptr)
        return;

    connections.push_back(new Connection(value1, value2));
    connections.push_back(new Connection(value2, value1));
}

void HarmoniousGraphConstraint::removeConnections(const IVariable* variable)
{
    const IValue* value = getValue(variable);

    removeConnection(value, getValue(getUpNeighbour(variable)));
    removeConnection(value, getValue(getRightNeighbour(variable)));
    removeConnection(value, getValue(getDownNeighbour(variable)));
    removeConnection(value, getValue(getLeftNeighbour(variable)));
}

void HarmoniousGraphConstraint::removeConnection(const IValue* value, const IValue* neighbour)
{
    if (value == nullptr || neighbour == nullptr)
        return;

    unsigned long int index = 0;
    while (index < connections.size())
    {
        const IValue* first = connections[index]->getFirstValue();
        const IValue* second = connections[index]->getSecondValue();

        if ((value == first && neighbour == second) || (value == second && neighbour == first))
        {
            delete connections[index];
            connections.erase(connections.begin() + index);
        }
        else
            ++index;
    }
}

const IVariable* HarmoniousGraphConstraint::getUpNeighbour(const IVariable* variable) const
{
    return (variable != nullptr && variable->getRow() > 0)
           ? problem->getVariable(variable->getRow() - 1, variable->getColumn())
           : nullptr;
}

const IVariable* HarmoniousGraphConstraint::getRightNeighbour(const IVariable* variable) const
{
    return (variable != nullptr && variable->getColumn() < problem->getWidth() - 1)
           ? problem->getVariable(variable->getRow(), variable->getColumn() + 1)
           : nullptr;
}

const IVariable* HarmoniousGraphConstraint::getDownNeighbour(const IVariable* variable) const
{
    return (variable != nullptr && variable->getRow() < problem->getWidth() - 1)
           ? problem->getVariable(variable->getRow() + 1, variable->getColumn())
           : nullptr;
}

const IVariable* HarmoniousGraphConstraint::getLeftNeighbour(const IVariable* variable) const
{
    return (variable != nullptr && variable->getColumn() > 0)
           ? problem->getVariable(variable->getRow(), variable->getColumn() - 1)
           : nullptr;
}

const IValue *HarmoniousGraphConstraint::getValue(const IVariable* variable) const
{
    return  variable == nullptr
            ? nullptr
            : variable->getValue();
}

void HarmoniousGraphConstraint::clearConnections()
{
    for (int i = 0; i < connections.size(); ++i)
        delete connections[i];

    connections.clear();
}
