//
// Created by Anna Siwik on 2017-04-07.
//

#include <iostream>
#include "../interface/IValue.h"
#include "../interface/IDomain.h"
#include "../header/Node.h"

Node::Node(int row, int col) :
    IVariable(row, col)
{}

Node::~Node()
{}

void Node::setValue(const IValue* value)
{
    this->value = value;
}

const IValue* Node::getValue() const
{
    return value;
}

void Node::resetValue()
{
    this->value = nullptr;
}

const IDomain* Node::getDomain() const
{
    return domain;
}

void Node::addDomain(const IDomain* domain)
{
    for (int i = 0; i < domain->getSize(); ++i)
        this->domain->addValue(domain->getValue(i));
}

void Node::addValueToDomain(const IValue* value)
{
    domain->addValue(value);
}

void Node::removeValueFromDomain(const IValue* value)
{
    domain->removeValue(value);
}

const int Node::getRow() const
{
    return row;
}

const int Node::getColumn() const
{
    return col;
}