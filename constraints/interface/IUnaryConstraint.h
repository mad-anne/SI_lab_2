//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_ISINGLEVARIABLECONSTRAINT_H
#define SI_LAB_2_ISINGLEVARIABLECONSTRAINT_H

#include <map>
#include "../../components/interface/IVariable.h"
#include "../../components/interface/IValue.h"

class ISingleVariableConstraint
{
    private:
        std::map<IVariable, IValue> constraints;

    public:
        virtual bool canHasValue(IVariable, IValue) = 0;
};

#endif //SI_LAB_2_ISINGLEVARIABLECONSTRAINT_H
