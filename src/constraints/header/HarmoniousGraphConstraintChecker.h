//
// Created by Anna Siwik on 2017-04-13.
//

#ifndef SI_LAB_2_HARMONIOUSGRAPHCONSTRAINT_H
#define SI_LAB_2_HARMONIOUSGRAPHCONSTRAINT_H

#include <constraints/interface/IConstraintChecker.h>
#include <constraints/interface/IConstraint.h>
#include <components/header/Color.h>
#include <vector>
#include "Connection.h"


class HarmoniousGraphConstraintChecker : public IConstraintChecker
{
    std::vector<Connection*> connections;

    public:
        HarmoniousGraphConstraintChecker(IProblem*);
        ~HarmoniousGraphConstraintChecker();

        const bool updateConstraints(const IVariable*) override;
        void undoConstraints(const IVariable*) override;

        void setProblem(IProblem*) override;
        const IProblem* getProblem() const override;

        const void putForwardConstraints(const IVariable *variable) override;
        const void undoForwardConstraints(const IVariable *variable) override;

private:
        const bool checkConstraints(const IVariable*) const;
        const bool checkNeighbours(const IVariable*) const;
        const bool checkConnections(const IVariable*) const;

        const bool existsConnection(const IValue*, const IValue*) const;

        void addConnections(const IVariable*);
        void addConnection(const IValue*, const IValue*);

        void removeConnections(const IVariable*);
        void removeConnection(const IValue*, const IValue*);

        IVariable* getUpNeighbour(const IVariable*) const;
        IVariable* getRightNeighbour(const IVariable*) const;
        IVariable* getDownNeighbour(const IVariable*) const;
        IVariable* getLeftNeighbour(const IVariable*) const;

        const IValue* getValue(const IVariable*) const;
        void clearConnections();

    void removeValueFromEmptyNeighbours(const IVariable*, const IValue*);
    void limitDomainsOnConnection(const Connection*);
    void limitDomainsOnConnections(const IVariable*);
    void addValueToEmptyNeighbours(const IVariable*, const IValue*);

    void removeLimitsOnConnections(const IVariable*);
    void removeLimitsOnConnection(const IVariable* variable, Connection*);
    void removeFromConnections(Connection*);

    void addValueToDomainIfPossible(IVariable *pVariable, const IVariable *pIVariable, Connection *pConnection);

    bool notExistsConstraintOnValues(IVariable *neighbour, IVariable *variable, const IVariable *removed);
};

#endif //SI_LAB_2_HARMONIOUSGRAPHCONSTRAINT_H
