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

        void putConstraintsOnVariable(IVariable*, bool limitDomains) override;
        void putConstraintsOffVariable(IVariable*) override;

        bool canAddValueToDomain(const IVariable* checked, IValue*, const IVariable* reversed) override;

    private:
        const bool checkConnectionsWithNeighbours(const IVariable*) const;

        void limitDomainsOnVariable(const IVariable*);
        void limitDomainOnValue(IVariable*, const IValue*);

        bool hasNeighbourWithValue(const IVariable* variable, const IValue*, const IVariable* allowedNeighbour) const;
};


#endif //SI_LAB_2_NEIGHBOURCONSTRAINT_H
