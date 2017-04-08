//
// Created by Anna Siwik on 2017-04-07.
//

#include "../interface/IValue.h"
#include "../interface/IDomain.h"
#include "../../constraints/interface/IUnaryConstraint.h"
#include "../header/Node.h"
<<<<<<< HEAD
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
=======

Node::Node()
{}

const IValue* Node::getValue()
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
{
    return value;
}

<<<<<<< HEAD
const IDomain* Node::getDomain() const
=======
const IDomain* Node::getDomain()
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
{
    return domain;
}
