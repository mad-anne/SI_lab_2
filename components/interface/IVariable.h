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
<<<<<<< HEAD
        virtual ~IVariable() {}

        virtual const IValue* getValue() const = 0;
        virtual const IDomain* getDomain() const = 0;
=======
        virtual const IValue* getValue() = 0;
        virtual const IDomain* getDomain() = 0;
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
};

#endif //SI_LAB_2_IVARIABLE_H
