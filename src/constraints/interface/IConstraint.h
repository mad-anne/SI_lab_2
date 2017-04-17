//
// Created by Anna Siwik on 2017-04-17.
//

#ifndef SI_LAB_2_ICONSTRAINT_H
#define SI_LAB_2_ICONSTRAINT_H

#include <problems/interface/IProblem.h>

class IConstraint
{
    protected:
        IProblem* problem;
        std::vector<Connection*> connections;

    public:
        IConstraint(IProblem* problem)
                : problem(problem)
        {}
        virtual ~IConstraint() = default;

        virtual const bool checkVariable(IVariable*) const = 0;
        virtual const bool checkAll() const = 0;

        virtual void putConstraintsOnVariable(IVariable*, bool limitDomains) = 0;
        virtual void putConstraintsOnAll() = 0;
};

#endif //SI_LAB_2_ICONSTRAINT_H
