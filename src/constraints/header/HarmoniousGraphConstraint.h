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

        const bool checkConstraints() override;
        const bool checkConstraints(int row, int col) override;
        void setProblem(IProblem *problem) override;

    private:
        const bool checkNeighbours(int row, int col) const;
        const bool checkConnection(int row, int col);
        const bool existsConnection(const IValue*, const IValue*) const;
};

#endif //SI_LAB_2_HARMONIOUSGRAPHCONSTRAINT_H
