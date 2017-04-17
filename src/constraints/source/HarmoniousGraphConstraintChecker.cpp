//
// Created by Anna Siwik on 2017-04-13.
//

#include <problems/interface/IProblem.h>
#include <constraints/header/HarmoniousGraphConstraintChecker.h>

HarmoniousGraphConstraintChecker::HarmoniousGraphConstraintChecker(IProblem* problem)
        : IConstraintChecker(problem)
{}

HarmoniousGraphConstraintChecker::~HarmoniousGraphConstraintChecker()
{
    clearConnections();
}

const bool HarmoniousGraphConstraintChecker::updateConstraints(const IVariable* variable)
{
    if (checkConstraints(variable))
    {
        addConnections(variable);
        return true;
    }

    return false;
}

void HarmoniousGraphConstraintChecker::undoConstraints(const IVariable* variable)
{
    removeConnections(variable);
}

void HarmoniousGraphConstraintChecker::setProblem(IProblem* problem)
{
    this->problem = problem;
}

const IProblem* HarmoniousGraphConstraintChecker::getProblem() const
{
    return problem;
}

const bool HarmoniousGraphConstraintChecker::checkConstraints(const IVariable* variable) const
{
    if (variable == nullptr)
        return true;

    return checkNeighbours(variable) && checkConnections(variable);
}

const bool HarmoniousGraphConstraintChecker::checkNeighbours(const IVariable* variable) const
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

const bool HarmoniousGraphConstraintChecker::checkConnections(const IVariable* variable) const
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

const bool HarmoniousGraphConstraintChecker::existsConnection(const IValue* value, const IValue* neighbour) const
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

void HarmoniousGraphConstraintChecker::addConnections(const IVariable* variable)
{
    if (variable == nullptr)
        return;

    const IValue* value = getValue(variable);

    addConnection(value, getValue(getUpNeighbour(variable)));
    addConnection(value, getValue(getRightNeighbour(variable)));
    addConnection(value, getValue(getDownNeighbour(variable)));
    addConnection(value, getValue(getLeftNeighbour(variable)));
}

void HarmoniousGraphConstraintChecker::addConnection(const IValue* value1, const IValue* value2)
{
    if (value1 == nullptr || value2 == nullptr)
        return;

    connections.push_back(new Connection(value1, value2));
    connections.push_back(new Connection(value2, value1));
}

void HarmoniousGraphConstraintChecker::removeConnections(const IVariable* variable)
{
    const IValue* value = getValue(variable);

    removeConnection(value, getValue(getUpNeighbour(variable)));
    removeConnection(value, getValue(getRightNeighbour(variable)));
    removeConnection(value, getValue(getDownNeighbour(variable)));
    removeConnection(value, getValue(getLeftNeighbour(variable)));
}

void HarmoniousGraphConstraintChecker::removeConnection(const IValue* value, const IValue* neighbour)
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

IVariable* HarmoniousGraphConstraintChecker::getUpNeighbour(const IVariable* variable) const
{
    return variable != nullptr
           ? problem->getVariable(variable->getRow() - 1, variable->getColumn())
           : nullptr;
}

IVariable* HarmoniousGraphConstraintChecker::getRightNeighbour(const IVariable* variable) const
{
    return variable != nullptr
           ? problem->getVariable(variable->getRow(), variable->getColumn() + 1)
           : nullptr;
}

IVariable* HarmoniousGraphConstraintChecker::getDownNeighbour(const IVariable* variable) const
{
    return variable != nullptr
           ? problem->getVariable(variable->getRow() + 1, variable->getColumn())
           : nullptr;
}

IVariable* HarmoniousGraphConstraintChecker::getLeftNeighbour(const IVariable* variable) const
{
    return variable != nullptr
           ? problem->getVariable(variable->getRow(), variable->getColumn() - 1)
           : nullptr;
}

const IValue *HarmoniousGraphConstraintChecker::getValue(const IVariable* variable) const
{
    return  variable == nullptr
            ? nullptr
            : variable->getValue();
}

void HarmoniousGraphConstraintChecker::clearConnections()
{
    for (int i = 0; i < connections.size(); ++i)
        delete connections[i];

    connections.clear();
}

const void HarmoniousGraphConstraintChecker::putForwardConstraints(const IVariable* variable)
{
    removeValueFromEmptyNeighbours(variable, variable->getValue());
    limitDomainsOnConnections(variable);
}

const void HarmoniousGraphConstraintChecker::undoForwardConstraints(const IVariable* variable)
{
    addValueToEmptyNeighbours(variable, variable->getValue());
    removeLimitsOnConnections(variable);
}

void HarmoniousGraphConstraintChecker::removeValueFromEmptyNeighbours(const IVariable* variable, const IValue* value)
{
    IVariable* varLeft = getLeftNeighbour(variable);
    IVariable* varRight = getRightNeighbour(variable);
    IVariable* varUp = getUpNeighbour(variable);
    IVariable* varDown = getDownNeighbour(variable);

    if (varLeft != nullptr && varLeft->getValue() == nullptr)
        varLeft->removeValueFromDomain(value);

    if (varRight != nullptr && varRight->getValue() == nullptr)
        varRight->removeValueFromDomain(value);

    if (varUp != nullptr && varUp->getValue() == nullptr)
        varUp->removeValueFromDomain(value);

    if (varDown != nullptr && varDown->getValue() == nullptr)
        varDown->removeValueFromDomain(value);
}

void HarmoniousGraphConstraintChecker::limitDomainsOnConnections(const IVariable* variable)
{
    std::vector<Connection*> cons;

    const IValue* value = variable->getValue();

    IVariable* varLeft = getLeftNeighbour(variable);
    IVariable* varRight = getRightNeighbour(variable);
    IVariable* varUp = getUpNeighbour(variable);
    IVariable* varDown = getDownNeighbour(variable);

    if (varLeft != nullptr && varLeft->getValue() != nullptr)
        cons.push_back(new Connection(value, varLeft->getValue()));

    if (varRight != nullptr && varRight->getValue() != nullptr)
        cons.push_back(new Connection(value, varRight->getValue()));

    if (varUp != nullptr && varUp->getValue() != nullptr)
        cons.push_back(new Connection(value, varUp->getValue()));

    if (varDown != nullptr && varDown->getValue() != nullptr)
        cons.push_back(new Connection(value, varDown->getValue()));

    std::vector<Connection*>::iterator it;

    for (it = cons.begin(); it != cons.end(); ++it)
    {
        limitDomainsOnConnection(*it);
        connections.push_back(*it);
    }

    const IDomain* domain = problem->getDomain();
    for (int i = 0; i < domain->getSize(); ++i)
    {
        if (existsConnection(domain->getValue(i), value))
        {
            if (varLeft != nullptr && varLeft->getValue() == nullptr)
                varLeft->removeValueFromDomain(domain->getValue(i));

            if (varRight != nullptr && varRight->getValue() == nullptr)
                varRight->removeValueFromDomain(domain->getValue(i));

            if (varUp != nullptr && varUp->getValue() == nullptr)
                varUp->removeValueFromDomain(domain->getValue(i));

            if (varDown != nullptr && varDown->getValue() == nullptr)
                varDown->removeValueFromDomain(domain->getValue(i));
        }
    }
}

void HarmoniousGraphConstraintChecker::limitDomainsOnConnection(const Connection* connection)
{
    int width = problem->getWidth();
    IVariable* variable;
    const IValue* first = connection->getFirstValue();
    const IValue* second = connection->getSecondValue();

    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            variable = problem->getVariable(row, col);
            const IValue* value = variable->getValue();

            if (value == first)
                removeValueFromEmptyNeighbours(variable, second);
            else if (value == second)
                removeValueFromEmptyNeighbours(variable, first);
        }
    }
}

void HarmoniousGraphConstraintChecker::addValueToEmptyNeighbours(const IVariable* variable, const IValue* value)
{
    IVariable* varLeft = getLeftNeighbour(variable);
    IVariable* varRight = getRightNeighbour(variable);
    IVariable* varUp = getUpNeighbour(variable);
    IVariable* varDown = getDownNeighbour(variable);

    if (varLeft != nullptr && varLeft->getValue() == nullptr)
        varLeft->addValueToDomain(value);

    if (varRight != nullptr && varRight->getValue() == nullptr)
        varRight->addValueToDomain(value);

    if (varUp != nullptr && varUp->getValue() == nullptr)
        varUp->addValueToDomain(value);

    if (varDown != nullptr && varDown->getValue() == nullptr)
        varDown->addValueToDomain(value);
}

void HarmoniousGraphConstraintChecker::removeLimitsOnConnections(const IVariable* variable)
{
    std::vector<Connection*> cons;

    const IValue* value = variable->getValue();

    IVariable* varLeft = getLeftNeighbour(variable);
    IVariable* varRight = getRightNeighbour(variable);
    IVariable* varUp = getUpNeighbour(variable);
    IVariable* varDown = getDownNeighbour(variable);

    if (varLeft != nullptr && varLeft->getValue() != nullptr)
        cons.push_back(new Connection(value, varLeft->getValue()));

    if (varRight != nullptr && varRight->getValue() != nullptr)
        cons.push_back(new Connection(value, varRight->getValue()));

    if (varUp != nullptr && varUp->getValue() != nullptr)
        cons.push_back(new Connection(value, varUp->getValue()));

    if (varDown != nullptr && varDown->getValue() != nullptr)
        cons.push_back(new Connection(value, varDown->getValue()));


    std::vector<Connection*>::iterator it = cons.begin();

    while (it != cons.end())
    {
        removeFromConnections(*it);
        removeLimitsOnConnection(variable, *it);
        delete *it;
        it = cons.erase(it);
    }
}

void HarmoniousGraphConstraintChecker::removeLimitsOnConnection(const IVariable* variable, Connection* connection)
{
    int width = problem->getWidth();
    IVariable* tempVariable;

    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            tempVariable = problem->getVariable(row, col);

            if (tempVariable == nullptr)
                addValueToDomainIfPossible(tempVariable, variable, connection);
        }
    }
}

void HarmoniousGraphConstraintChecker::removeFromConnections(Connection* connection)
{
    std::vector<Connection*>::const_iterator it;

    for (it = connections.begin(); it != connections.end(); ++it)
    {
        if ((*it)->getFirstValue() == connection->getFirstValue()
            && (*it)->getSecondValue() == connection->getSecondValue()
            ||( (*it)->getFirstValue() == connection->getSecondValue()
               && (*it)->getSecondValue() == connection->getFirstValue()))
        {
            it = connections.erase(it);
            return;
        }
    }
}

void HarmoniousGraphConstraintChecker::addValueToDomainIfPossible(IVariable* variable, const IVariable* removed,
                                                           Connection* connection)
{
    if (notExistsConstraintOnValues(getLeftNeighbour(variable), variable, removed)
        && notExistsConstraintOnValues(getRightNeighbour(variable), variable, removed)
        && notExistsConstraintOnValues(getUpNeighbour(variable), variable, removed)
        && notExistsConstraintOnValues(getDownNeighbour(variable), variable, removed))
    {
        variable->addValueToDomain(removed->getValue());
    }
}

bool HarmoniousGraphConstraintChecker::notExistsConstraintOnValues(IVariable* neighbour, IVariable* variable,
                                                         const IVariable* removed)
{
    return (neighbour == nullptr || neighbour->getValue() != removed->getValue() || neighbour == removed)
            && (neighbour == nullptr || neighbour == removed || ! existsConnection(neighbour->getValue(), removed->getValue()));
}

