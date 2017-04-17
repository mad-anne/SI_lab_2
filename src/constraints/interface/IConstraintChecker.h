//
// Created by Anna Siwik on 2017-04-13.
//

#ifndef SI_LAB_2_ICONSTRAINTCHECKER_H
#define SI_LAB_2_ICONSTRAINTCHECKER_H

#include <problems/interface/IProblem.h>
#include "IConstraint.h"

class IConstraintChecker
{
    protected:
        IProblem* problem;

    public:
        IConstraintChecker(IProblem* problem) :
            problem(problem)
        {}

        virtual ~IConstraintChecker() = default;

        virtual bool isCorrectAssignment(const IVariable*) const = 0;

        virtual const void putConstraintsOn(const IVariable*, bool limitDomains) = 0;
        virtual const void putConstraintsOff(const IVariable*, bool limitDomains) = 0;

        // TODO - if limits domains && checking constraints is connected ?
};

#endif //SI_LAB_2_ICONSTRAINTCHECKER_H
