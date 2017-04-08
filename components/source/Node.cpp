//
// Created by Anna Siwik on 2017-04-07.
//

#include "../interface/IValue.h"
#include "../interface/IDomain.h"
#include "../../constraints/interface/IUnaryConstraint.h"
#include "../header/Node.h"

Node::Node()
{}

Node::~Node()
{}

const IValue* Node::getValue()
{
    return value;
}

const IDomain* Node::getDomain()
{
    return domain;
}
