//
// Created by Anna Siwik on 2017-04-13.
//

#ifndef SI_LAB_2_ICONSTRAINT_H
#define SI_LAB_2_ICONSTRAINT_H

#include <problems/interface/IProblem.h>

class IConstraint
{
    protected:
        IProblem* problem;

    public:
        IConstraint(IProblem* problem) :
            problem(problem)
        {}

        virtual ~IConstraint() = default;

        virtual const bool checkConstraints() const = 0;
        virtual void setProblem(IProblem*) = 0;
};

#endif //SI_LAB_2_ICONSTRAINT_H
