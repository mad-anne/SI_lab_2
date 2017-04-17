//
// Created by Dom on 2017-04-17.
//

#ifndef SI_LAB_2_CONNECTIONCONSTRAINT_H
#define SI_LAB_2_CONNECTIONCONSTRAINT_H


#include <constraints/interface/IConstraint.h>

class ConnectionConstraint : public IConstraint
{
    public:
        ConnectionConstraint(IProblem *problem);
        ~ConnectionConstraint() override;

        const bool checkVariable(IVariable*) const override;
        const bool checkAllAndPutConstraints(bool limitDomains) override;

        void putConstraintsOnVariable(IVariable*, bool limitDomains) override;

    private:
        const bool checkConnectionsWithNeighbours(IVariable*) const;

        const bool existsConnection(const IValue*, const IValue*) const;
        const bool addConnection(const IValue*, const IValue*);
        void addAllConnections(IVariable*);

        void limitDomainsOnVariable(IVariable*);

        void clearConnections();
};


#endif //SI_LAB_2_CONNECTIONCONSTRAINT_H
