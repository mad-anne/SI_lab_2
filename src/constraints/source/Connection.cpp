//
// Created by Anna Siwik on 2017-04-13.
//


#include <constraints/header/Connection.h>

Connection::Connection(const IValue *first, const IValue *second)
        : IConnection(first, second)
{}

Connection::~Connection()
{}

const IValue* Connection::getFirstValue() const
{
    return first;
}

const IValue *Connection::getSecondValue() const
{
    return second;
}
