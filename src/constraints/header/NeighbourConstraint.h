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

        const bool checkVariable(IVariable *variable) const override;
        const bool checkAllAndPutConstraints(bool limitDomains) override;

        void putConstraintsOnVariable(IVariable *variable, bool limitDomains) override;
        void putConstraintsOffVariable(IVariable *variable, bool limitDomains) override;

    const bool checkConnectionsWithNeighbours(IVariable *pVariable) const;

    void limitDomainsOnVariable(IVariable *pVariable);

    void limitDomainOnValue(IVariable *pVariable, const IValue *pValue);
};


#endif //SI_LAB_2_NEIGHBOURCONSTRAINT_H
