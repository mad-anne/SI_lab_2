//
// Created by Anna Siwik on 2017-04-13.
//

#ifndef SI_LAB_2_HARMONIOUSGRAPHCONSTRAINT_H
#define SI_LAB_2_HARMONIOUSGRAPHCONSTRAINT_H

#include <constraints/interface/IConstraint.h>
#include <components/header/Color.h>
#include <vector>
#include "Connection.h"


class HarmoniousGraphConstraint : public IConstraint
{
    std::vector<Connection*> connections;

    public:
        HarmoniousGraphConstraint(IProblem*);
        ~HarmoniousGraphConstraint();

        const bool updateConstraints(const IVariable*) override;
        void undoConstraints(const IVariable*) override;

        void setProblem(IProblem*) override;
        const IProblem* getProblem() const override;

    private:
        const bool checkConstraints(const IVariable*) const;
        const bool checkNeighbours(const IVariable*) const;
        const bool checkConnections(const IVariable*) const;

        const bool existsConnection(const IValue*, const IValue*) const;

        void addConnections(const IVariable*);
        void addConnection(const IValue*, const IValue*);

        void removeConnections(const IVariable*);
        void removeConnection(const IValue*, const IValue*);

        const IVariable* getUpNeighbour(const IVariable*) const;
        const IVariable* getRightNeighbour(const IVariable*) const;
        const IVariable* getDownNeighbour(const IVariable*) const;
        const IVariable* getLeftNeighbour(const IVariable*) const;

        const IValue* getValue(const IVariable*) const;
        void clearConnections();
};

#endif //SI_LAB_2_HARMONIOUSGRAPHCONSTRAINT_H
