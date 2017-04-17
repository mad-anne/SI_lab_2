//
// Created by Anna Siwik on 2017-04-17.
//

#include <constraints/header/Connection.h>
#include "constraints/header/ConnectionConstraint.h"

ConnectionConstraint::ConnectionConstraint(IProblem* problem)
        : IConstraint(problem)
{}

ConnectionConstraint::~ConnectionConstraint()
{}

const bool ConnectionConstraint::checkVariable(IVariable* variable) const
{
    if (variable == nullptr)
        return true;

    return false;
}

const bool ConnectionConstraint::checkAll() const
{
    return 0;
}

void ConnectionConstraint::putConstraintsOnVariable(IVariable* variable, bool limitDomains)
{

}

void ConnectionConstraint::putConstraintsOnAll()
{

}

const bool ConnectionConstraint::existsConnection(IValue* valFirst, IValue* valSecond) const
{
    Connection* connection = new Connection(valFirst, valSecond);
    std::vector<Connection*>::const_iterator it = connections.begin();
    bool exists = false;


    while (! exists && it != connections.end())
    {
        if (*(*it) == *connection)
            exists = true;

        ++it;
    }

    return exists;
}
