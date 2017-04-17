//
// Created by Anna Siwik on 2017-04-17.
//

#ifndef SI_LAB_2_CONNECTIONCONSTRAINT_H
#define SI_LAB_2_CONNECTIONCONSTRAINT_H


#include <constraints/interface/IConstraint.h>

class ConnectionConstraint : public IConstraint
{
    std::vector<Connection*> connections;

    public:
        ConnectionConstraint(IProblem *problem);
        ~ConnectionConstraint() override;

        const bool checkVariable(const IVariable*) const override;
        const bool checkAllAndPutConstraints(bool limitDomains) override;

        void putConstraintsOnVariable(const IVariable*, bool limitDomains) override;
        void putConstraintsOffVariable(const IVariable*) override;

        bool canAddValueToDomain(const IVariable* checked, const IValue*, const IVariable* reversed);

        const IValue* getLeftValueInConnection(const IVariable*) const;
        const IValue* getUpValueInConnection(const IVariable*) const;
        const IValue* getRightValueInConnection(const IVariable*) const;
        const IValue* getDownValueInConnection(const IVariable*) const;

    private:
        const bool checkConnectionsWithNeighbours(const IVariable*) const;

        void addConnectedConnections(const IVariable*);
        const bool addConnection(const IValue*, const IValue*);

        void removeConnectedConnections(const IVariable*);
        void removeConnection(const IValue*, const IValue*);

        void limitDomainsOnVariable(const IVariable*);
        void limitDomainsOnConnection(const IValue*, const IValue*);
        void removeValueFromEmptyNeighbours(IVariable*, const IValue*);
        void removeValueFromDomainIfEmpty(IVariable*, const IValue*);

        const bool existsConnection(const IValue*, const IValue*) const;

        void clearConnections();

        bool checkConnectedConnections(const IVariable*, const IValue*, const IVariable*);
};


#endif //SI_LAB_2_CONNECTIONCONSTRAINT_H
