//
// Created by Anna Siwik on 2017-04-17.
//

#ifndef SI_LAB_2_ICONSTRAINT_H
#define SI_LAB_2_ICONSTRAINT_H

#include <problems/interface/IProblem.h>
#include <constraints/header/Connection.h>

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
        virtual const bool checkAllAndPutConstraints(bool limitDomains) = 0;

        virtual void putConstraintsOnVariable(IVariable*, bool limitDomains) = 0;
        virtual void putConstraintsOffVariable(IVariable*, bool limitDomains) = 0;

        virtual IVariable* getLeftNeighbour(IVariable* variable) const
        {
            return  variable == nullptr ? nullptr
                    : problem->getVariable(variable->getRow(), variable->getColumn() - 1);
        }

        virtual IVariable* getUpNeighbour(IVariable* variable) const
        {
            return  variable == nullptr ? nullptr
                    : problem->getVariable(variable->getRow() - 1, variable->getColumn());

        }

        virtual IVariable* getRightNeighbour(IVariable* variable) const
        {
            return  variable == nullptr ? nullptr
                    : problem->getVariable(variable->getRow(), variable->getColumn() + 1);
        }

        virtual IVariable* getDownNeighbour(IVariable* variable) const
        {
            return  variable == nullptr ? nullptr
                    : problem->getVariable(variable->getRow() + 1, variable->getColumn());
        }

        virtual const IValue* getValueOfVariable(IVariable* variable) const
        {
            return variable == nullptr ? nullptr : variable->getValue();
        }
};

#endif //SI_LAB_2_ICONSTRAINT_H
