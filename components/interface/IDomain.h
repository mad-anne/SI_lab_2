    //
// Created by Dom on 2017-04-08.
//

#ifndef SI_LAB_2_IDOMAIN_H
#define SI_LAB_2_IDOMAIN_H

#include <vector>
#include "IValue.h"

class IDomain
{
    protected:
        std::vector<IValue*> values;

    public:
        virtual ~IDomain() {}

        virtual void addValue(IValue*) = 0;
        virtual const IValue* getValue(int) = 0;
        virtual const int getDomainSize() = 0;
};

#endif //SI_LAB_2_IDOMAIN_H
