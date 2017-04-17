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
        void putConstraintsOffVariable(IVariable*, bool limitDomains) override ;

    private:
        const bool checkConnectionsWithNeighbours(IVariable*) const;

        void addConnectedConnections(IVariable*);
        const bool addConnection(const IValue*, const IValue*);

        void removeConnectedConnections(IVariable*);
        void removeConnection(const IValue*, const IValue*);

        void limitDomainsOnVariable(IVariable*);
        void limitDomainsOnConnection(const IValue*, const IValue*);
        void removeValueFromEmptyNeighbours(IVariable*, const IValue*);
        void removeValueFromDomainIfEmpty(IVariable*, const IValue*);

        void extendDomainsOnVariable(IVariable*);
        void extendDomainsOnConnection(const IValue*, const IValue*, IVariable* allowedNeighbour);
        void addValueToEmptyNeighbours(IVariable*, const IValue*, IVariable* allowedNeighbour);
        void addValueToDomainIfEmpty(IVariable*, const IValue*, IVariable* allowedNeighbour);

        const bool existsConnection(const IValue*, const IValue*) const;
        bool hasNeighbourWithValue(IVariable*, const IValue*, IVariable* allowedNeighbour);

        void clearConnections();
};


#endif //SI_LAB_2_CONNECTIONCONSTRAINT_H
