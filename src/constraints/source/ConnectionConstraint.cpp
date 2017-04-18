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

const bool ConnectionConstraint::checkVariable(const IVariable* variable) const
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

void ConnectionConstraint::putConstraintsOffVariable(IVariable* variable)
{
    removeConnectedConnections(variable);
}

void ConnectionConstraint::limitDomainsOnVariable(const IVariable* variable)
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return;

    for (int i = 0; i < connections.size(); ++i)
        limitDomainsOnConnection(connections[i]->getFirstValue(), connections[i]->getSecondValue());
}

const bool ConnectionConstraint::checkConnectionsWithNeighbours(const IVariable* variable) const
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return true;

    IValue* value = getValueOfVariable(variable);

    IValue* valLeft = getValueOfVariable(getLeftNeighbour(variable));
    IValue* valUp = getValueOfVariable(getUpNeighbour(variable));
    IValue* valRight = getValueOfVariable(getRightNeighbour(variable));
    IValue* valDown = getValueOfVariable(getDownNeighbour(variable));

    return (! existsConnection(value, valLeft)) && (! existsConnection(value, valUp))
            && (! existsConnection(value, valRight)) && (! existsConnection(value, valDown));
}

const bool ConnectionConstraint::existsConnection(IValue* valFirst, IValue* valSecond) const
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
    IValue* value = getValueOfVariable(variable);

    addConnection(value, getValueOfVariable(getLeftNeighbour(variable)));
    addConnection(value, getValueOfVariable(getUpNeighbour(variable)));
    addConnection(value, getValueOfVariable(getRightNeighbour(variable)));
    addConnection(value, getValueOfVariable(getDownNeighbour(variable)));
}

const bool ConnectionConstraint::addConnection(IValue* valFirst, IValue* valSecond)
{
    if (valFirst != nullptr && valSecond != nullptr && ! existsConnection(valFirst, valSecond))
    {
        connections.push_back(new Connection(valFirst, valSecond));
        valFirst->incrementConnectedConstraints();
        valSecond->incrementConnectedConstraints();
    }
}

void ConnectionConstraint::removeConnectedConnections(IVariable* variable)
{
    IValue* value = getValueOfVariable(variable);

    removeConnection(value, getValueOfVariable(getLeftNeighbour(variable)));
    removeConnection(value, getValueOfVariable(getUpNeighbour(variable)));
    removeConnection(value, getValueOfVariable(getRightNeighbour(variable)));
    removeConnection(value, getValueOfVariable(getDownNeighbour(variable)));
}

void ConnectionConstraint::removeConnection(IValue* valFirst, IValue* valSecond)
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
            (*it)->getFirstValue()->decrementConnectedConstraints();
            (*it)->getSecondValue()->decrementConnectedConstraints();
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

bool ConnectionConstraint::canAddValueToDomain(const IVariable* checked, IValue* value, const IVariable* reversed)
{
    return checkConnectedConnections(checked, value, reversed);
}

bool ConnectionConstraint::checkConnectedConnections(const IVariable* checked, IValue* value,
                                                     const IVariable* reversed)
{
    if (value == reversed->getValue())
        return true;

    const IVariable* varLeft = getLeftNeighbour(checked);
    const IVariable* varUp = getUpNeighbour(checked);
    const IVariable* varRight = getRightNeighbour(checked);
    const IVariable* varDown = getDownNeighbour(checked);

    return (varLeft == reversed || ! existsConnection(value, getValueOfVariable(varLeft)))
            && (varUp == reversed || ! existsConnection(value, getValueOfVariable(varUp)))
            && (varRight == reversed || ! existsConnection(value, getValueOfVariable(varRight)))
            && (varDown == reversed || ! existsConnection(value, getValueOfVariable(varDown)));
}

const IValue *ConnectionConstraint::getLeftValueInConnection(const IVariable* variable) const
{
    return getValueOfVariable(getLeftNeighbour(variable));
}

const IValue *ConnectionConstraint::getUpValueInConnection(const IVariable* variable) const
{
    return getValueOfVariable(getUpNeighbour(variable));
}

const IValue *ConnectionConstraint::getRightValueInConnection(const IVariable* variable) const
{
    return getValueOfVariable(getRightNeighbour(variable));
}

const IValue *ConnectionConstraint::getDownValueInConnection(const IVariable* variable) const
{
    return getValueOfVariable(getDownNeighbour(variable));
}
