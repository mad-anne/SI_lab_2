//
// Created by Anna Siwik on 2017-04-07.
//

#include "../interface/IValue.h"
#include "../interface/IDomain.h"
#include "../header/Node.h"

Node::Node(int row, int col) :
    IVariable(),
    row(row),
    col(col)
{
}

Node::~Node()
{
    delete domain;
}

const IValue* Node::getValue() const
{
    return value;
}

const IDomain* Node::getDomain() const
{
    return domain;
}

void Node::setValue(const IValue* value)
{
    this->value = value;
}

void Node::addValueToDomain(const IValue* value)
{
    domain->addValue(value);
}

void Node::resetValue()
{
    this->value = nullptr;
}

void Node::addDomain(const IDomain* domain)
{
    for (int i = 0; i < domain->getDomainSize(); ++i)
        this->domain->addValue(domain->getValue(i));
}

const int Node::getRow() const
{
    return row;
}

const int Node::getColumn() const
{
    return col;
}