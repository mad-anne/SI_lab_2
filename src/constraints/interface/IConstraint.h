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

    public:
        IConstraint(IProblem* problem)
                : problem(problem)
        {}
        virtual ~IConstraint() = default;

        virtual const bool checkVariable(const IVariable*) const = 0;
        virtual const bool checkAllAndPutConstraints(bool limitDomains) = 0;

        virtual void putConstraintsOnVariable(const IVariable*, bool limitDomains) = 0;
        virtual void putConstraintsOffVariable(const IVariable*) = 0;

        virtual bool canAddValueToDomain(const IVariable* checked, const IValue*, const IVariable* reversed) = 0;

    protected:
        virtual IVariable* getLeftNeighbour(const IVariable* variable) const
        {
            return  variable == nullptr ? nullptr
                    : problem->getVariable(variable->getRow(), variable->getColumn() - 1);
        }

        virtual IVariable* getUpNeighbour(const IVariable* variable) const
        {
            return  variable == nullptr ? nullptr
                    : problem->getVariable(variable->getRow() - 1, variable->getColumn());

        }

        virtual IVariable* getRightNeighbour(const IVariable* variable) const
        {
            return  variable == nullptr ? nullptr
                    : problem->getVariable(variable->getRow(), variable->getColumn() + 1);
        }

        virtual IVariable* getDownNeighbour(const IVariable* variable) const
        {
            return  variable == nullptr ? nullptr
                    : problem->getVariable(variable->getRow() + 1, variable->getColumn());
        }

        virtual const IValue* getValueOfVariable(const IVariable* variable) const
        {
            return variable == nullptr ? nullptr : variable->getValue();
        }
};

#endif //SI_LAB_2_ICONSTRAINT_H
