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

    addAllConnections(variable);

    if (limitDomains)
        limitDomainsOnVariable(variable);
}

// TODO: dla forward checking
void ConnectionConstraint::limitDomainsOnVariable(IVariable* variable)
{
    if (variable == nullptr || variable->getValue() == nullptr)
        return;
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

void ConnectionConstraint::addAllConnections(IVariable* variable)
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

void ConnectionConstraint::clearConnections()
{
    std::vector<Connection*>::const_iterator it = connections.begin();

    while (it != connections.end())
    {
        delete *it;
        it = connections.erase(it);
    }
}

