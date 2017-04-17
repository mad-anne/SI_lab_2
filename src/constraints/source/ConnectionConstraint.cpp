//
// Created by Anna Siwik on 2017-04-17.
//

#include <constraints/header/Connection.h>
#include <problems/header/HarmoniousGraph.h>
#include "constraints/header/ConnectionConstraint.h"

ConnectionConstraint::ConnectionConstraint(IProblem* problem)
        : IConstraint(problem)
{}

ConnectionConstraint::~ConnectionConstraint()
{
    clearConnections();
}

const bool ConnectionConstraint::checkVariable(IVariable* variable) const
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return true;

    return checkConnectionsWithNeighbours(variable);
}

const bool ConnectionConstraint::checkAllAndPutConstraints(bool limitDomains)
{
    clearConnections();
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
                    {
                        isCorrect = false;
                        clearConnections();
                    }
                }
            }
        }
    }

    delete copy;

    return isCorrect;
}

void ConnectionConstraint::putConstraintsOnVariable(IVariable* variable, bool limitDomains)
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return;

    addConnectedConnections(variable);

    if (limitDomains)
        limitDomainsOnVariable(variable);
}

// TODO: uwzględnia fakt sąsiadowania - nie dodawaj w drugim constraints
void ConnectionConstraint::putConstraintsOffVariable(IVariable* variable, bool limitDomains)
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return;

    removeConnectedConnections(variable);

    if (limitDomains)
        extendDomainsOnVariable(variable);
}

void ConnectionConstraint::limitDomainsOnVariable(IVariable* variable)
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return;

    const IValue* value = getValueOfVariable(variable);

    limitDomainsOnConnection(value, getValueOfVariable(getLeftNeighbour(variable)));
    limitDomainsOnConnection(value, getValueOfVariable(getUpNeighbour(variable)));
    limitDomainsOnConnection(value, getValueOfVariable(getRightNeighbour(variable)));
    limitDomainsOnConnection(value, getValueOfVariable(getDownNeighbour(variable)));
}

const bool ConnectionConstraint::checkConnectionsWithNeighbours(IVariable* variable) const
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return true;

    const IValue* value = getValueOfVariable(variable);

    const IValue* valLeft = getValueOfVariable(getLeftNeighbour(variable));
    const IValue* valUp = getValueOfVariable(getUpNeighbour(variable));
    const IValue* valRight = getValueOfVariable(getRightNeighbour(variable));
    const IValue* valDown = getValueOfVariable(getDownNeighbour(variable));

    return (! existsConnection(value, valLeft)) && (! existsConnection(value, valUp))
            && (! existsConnection(value, valRight)) && (! existsConnection(value, valDown));
}

const bool ConnectionConstraint::existsConnection(const IValue* valFirst, const IValue* valSecond) const
{
    if (valFirst == nullptr || valSecond == nullptr)
        return false;

    Connection* connection = new Connection(valFirst, valSecond);
    std::vector<Connection*>::const_iterator it = connections.begin();
    bool exists = false;

    while (! exists && it != connections.end())
    {
        if (*(*it) == *connection)
            exists = true;

        ++it;
    }

    delete connection;
    return exists;
}

void ConnectionConstraint::addConnectedConnections(IVariable* variable)
{
    const IValue* value = getValueOfVariable(variable);

    addConnection(value, getValueOfVariable(getLeftNeighbour(variable)));
    addConnection(value, getValueOfVariable(getUpNeighbour(variable)));
    addConnection(value, getValueOfVariable(getRightNeighbour(variable)));
    addConnection(value, getValueOfVariable(getDownNeighbour(variable)));
}

const bool ConnectionConstraint::addConnection(const IValue* valFirst, const IValue* valSecond)
{
    if (valFirst != nullptr && valSecond != nullptr && ! existsConnection(valFirst, valSecond))
        connections.push_back(new Connection(valFirst, valSecond));
}

void ConnectionConstraint::removeConnectedConnections(IVariable* variable)
{
    const IValue* value = getValueOfVariable(variable);

    removeConnection(value, getValueOfVariable(getLeftNeighbour(variable)));
    removeConnection(value, getValueOfVariable(getUpNeighbour(variable)));
    removeConnection(value, getValueOfVariable(getRightNeighbour(variable)));
    removeConnection(value, getValueOfVariable(getDownNeighbour(variable)));
}

void ConnectionConstraint::removeConnection(const IValue* valFirst, const IValue* valSecond)
{
    if (valFirst == nullptr || valSecond == nullptr)
        return;

    Connection connection(valFirst, valSecond);

    bool found = false;
    std::vector<Connection*>::const_iterator it = connections.begin();

    while (!found && it != connections.end())
    {
        if ( *(*it) == connection)
        {
            found = true;
            delete *it;
            it = connections.erase(it);
        }
        ++it;
    }
}

void ConnectionConstraint::clearConnections()
{
    std::vector<Connection*>::const_iterator it = connections.begin();

    while (it != connections.end())
    {
        delete *it;
        it = connections.erase(it);
    }
}

void ConnectionConstraint::limitDomainsOnConnection(const IValue* valFirst, const IValue* valSecond)
{
    if (valFirst == nullptr || valSecond == nullptr)
        return;

    int width = problem->getWidth();
    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            IVariable* variable = problem->getVariable(row, col);

            if (variable->getValue() == valFirst)
            {
                removeValueFromEmptyNeighbours(variable, valSecond);
                continue;
            }

            if (variable->getValue() == valSecond)
                removeValueFromEmptyNeighbours(variable, valFirst);
        }
    }
}

void ConnectionConstraint::removeValueFromEmptyNeighbours(IVariable* variable, const IValue* value)
{
    removeValueFromDomainIfEmpty(getLeftNeighbour(variable), value);
    removeValueFromDomainIfEmpty(getUpNeighbour(variable), value);
    removeValueFromDomainIfEmpty(getRightNeighbour(variable), value);
    removeValueFromDomainIfEmpty(getDownNeighbour(variable), value);
}

void ConnectionConstraint::removeValueFromDomainIfEmpty(IVariable* variable, const IValue* value)
{
    if (variable != nullptr && variable->getValue() == nullptr)
        variable->removeValueFromDomain(value);
}

void ConnectionConstraint::extendDomainsOnVariable(IVariable* variable)
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return;

    const IValue* value = getValueOfVariable(variable);

    extendDomainsOnConnection(value, getValueOfVariable(getLeftNeighbour(variable)), variable);
    extendDomainsOnConnection(value, getValueOfVariable(getUpNeighbour(variable)), variable);
    extendDomainsOnConnection(value, getValueOfVariable(getRightNeighbour(variable)), variable);
    extendDomainsOnConnection(value, getValueOfVariable(getDownNeighbour(variable)), variable);
}

void ConnectionConstraint::extendDomainsOnConnection(const IValue* valFirst, const IValue* valSecond, IVariable* allowedNeighbour)
{
    if (valFirst == nullptr || valSecond == nullptr)
        return;

    int width = problem->getWidth();
    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            IVariable* variable = problem->getVariable(row, col);

            if (variable->getValue() == valFirst)
            {
                addValueToEmptyNeighbours(variable, valSecond, allowedNeighbour);
                continue;
            }

            if (variable->getValue() == valSecond)
                addValueToEmptyNeighbours(variable, valFirst, allowedNeighbour);
        }
    }
}

void ConnectionConstraint::addValueToEmptyNeighbours(IVariable* variable, const IValue* value, IVariable* allowedNeighbour)
{
    addValueToDomainIfEmpty(getLeftNeighbour(variable), value, allowedNeighbour);
    addValueToDomainIfEmpty(getUpNeighbour(variable), value, allowedNeighbour);
    addValueToDomainIfEmpty(getRightNeighbour(variable), value, allowedNeighbour);
    addValueToDomainIfEmpty(getDownNeighbour(variable), value, allowedNeighbour);
}

void ConnectionConstraint::addValueToDomainIfEmpty(IVariable* variable, const IValue* value, IVariable* allowedNeighbour)
{
    if (variable != nullptr && variable->getValue() == nullptr && ! hasNeighbourWithValue(variable, value, allowedNeighbour))
        variable->addValueToDomain(value);
}

bool ConnectionConstraint::hasNeighbourWithValue(IVariable* variable, const IValue* value, IVariable* allowedNeighbour)
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