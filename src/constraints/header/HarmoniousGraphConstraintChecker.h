//
// Created by Anna Siwik on 2017-04-13.
//

#ifndef SI_LAB_2_HARMONIOUSGRAPHCONSTRAINT_H
#define SI_LAB_2_HARMONIOUSGRAPHCONSTRAINT_H

#include <constraints/interface/IConstraintChecker.h>
#include <constraints/interface/IConstraint.h>
#include <components/header/Color.h>
#include <vector>
#include "Connection.h"


class HarmoniousGraphConstraintChecker : public IConstraintChecker
{
    IConstraint* connectionConstraint;
    IConstraint* neighbourConstraint;

    public:
        HarmoniousGraphConstraintChecker(IProblem*);
        ~HarmoniousGraphConstraintChecker();

        bool isCorrectAssignment(const IVariable* variable) const override;

        const void putConstraintsOn(IVariable* variable, bool limitDomains) override;
        const void putConstraintsOff(IVariable* variable, bool limitDomains) override;
};

#endif //SI_LAB_2_HARMONIOUSGRAPHCONSTRAINT_H
