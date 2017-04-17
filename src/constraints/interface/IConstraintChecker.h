//
// Created by Anna Siwik on 2017-04-13.
//

#ifndef SI_LAB_2_ICONSTRAINT_H
#define SI_LAB_2_ICONSTRAINT_H

#include <problems/interface/IProblem.h>

class IConstraintChecker
{
    protected:
        IProblem* problem;

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

#endif //SI_LAB_2_ICONSTRAINT_H
