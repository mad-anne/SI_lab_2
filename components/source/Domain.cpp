//
// Created by Anna Siwik on 2017-04-08.
//

#include "../header/Domain.h"

Domain::Domain()
<<<<<<< HEAD
{ }

Domain::~Domain()
{ }
=======
{}
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50

void Domain::addValue(IValue* value)
{
    values.push_back(value);
}

const IValue* Domain::getValue(int index)
{
    return index < values.size()
           ? values.at(index)
           : nullptr;
}

const int Domain::getDomainSize()
{
    return values.size();
}
