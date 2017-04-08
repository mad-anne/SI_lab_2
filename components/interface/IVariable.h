//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_IVARIABLE_H
#define SI_LAB_2_IVARIABLE_H

#include "IValue.h"
#include "IDomain.h"
#include "../../constraints/interface/IUnaryConstraint.h"
#include "../../constraints/interface/IBinaryConstraint.h"

class IVariable
{
    protected:
        IValue* value;
        IDomain* domain;

    public:
        virtual const IValue* getValue() = 0;
        virtual const IDomain* getDomain() = 0;
};

#endif //SI_LAB_2_IVARIABLE_H
