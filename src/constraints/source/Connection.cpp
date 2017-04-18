//
// Created by Anna Siwik on 2017-04-13.
//


#include <constraints/header/Connection.h>

Connection::Connection(IValue* first, IValue* second)
        : first(first),
          second(second)
{}

Connection::Connection(const Connection& connection)
    : Connection(connection.getFirstValue(), connection.getSecondValue())
{}

Connection::~Connection()
{}

IValue* Connection::getFirstValue() const
{
    return first;
}

IValue* Connection::getSecondValue() const
{
    return second;
}

bool Connection::operator==(const Connection& con)
{
    return (first == con.getFirstValue() && second == con.getSecondValue())
           || (first == con.getSecondValue() && second == con.getFirstValue());
}
