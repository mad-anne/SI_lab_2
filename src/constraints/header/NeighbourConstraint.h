//
// Created by Anna Siwik on 2017-04-17.
//

#ifndef SI_LAB_2_NEIGHBOURCONSTRAINT_H
#define SI_LAB_2_NEIGHBOURCONSTRAINT_H


#include <constraints/interface/IConstraint.h>

class NeighbourConstraint : public IConstraint
{
    public:
        NeighbourConstraint(IProblem *problem);
        ~NeighbourConstraint() override;

        const bool checkVariable(const IVariable*) const override;
        const bool checkAllAndPutConstraints(bool limitDomains) override;

        void putConstraintsOnVariable(const IVariable*, bool limitDomains) override;
        void putConstraintsOffVariable(const IVariable*, bool limitDomains) override;

    private:
        const bool checkConnectionsWithNeighbours(const IVariable*) const;

        void limitDomainsOnVariable(const IVariable*);
        void limitDomainOnValue(IVariable*, const IValue*);
};


#endif //SI_LAB_2_NEIGHBOURCONSTRAINT_H
