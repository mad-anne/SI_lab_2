//
// Created by Anna Siwik on 2017-04-07.
//

#include "../interface/IValue.h"
#include "../interface/IDomain.h"
#include "../../constraints/interface/IUnaryConstraint.h"
#include "../header/Node.h"
#include "../header/Color.h"

Node::Node()
{
    value = new Color();
}

Node::~Node()
{
    delete value;
}

const IValue* Node::getValue() const
{
    return value;
}

const IDomain* Node::getDomain() const
{
    return domain;
}
