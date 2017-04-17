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
        std::vector<IConstraint*> constraints;

    public:
        IConstraintChecker(IProblem* problem) :
            problem(problem)
        {}

        virtual ~IConstraintChecker() = default;

        virtual const bool updateConstraints(const IVariable*) = 0;
        virtual void undoConstraints(const IVariable*) = 0;

        virtual const void putForwardConstraints(const IVariable*) = 0;
        virtual const void undoForwardConstraints(const IVariable*) = 0;

        virtual void setProblem(IProblem*) = 0;
        virtual const IProblem* getProblem() const = 0;
};

#endif //SI_LAB_2_ICONSTRAINTCHECKER_H
