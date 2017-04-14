//
// Created by Anna Siwik on 2017-04-08.
//

#ifndef SI_LAB_2_BACKTRACKING_H
#define SI_LAB_2_BACKTRACKING_H

#include "../interface/IConstraintSatisfactionProblem.h"
#include "../../constraints/interface/IConstraint.h"
#include "../../accessors/interface/IVariableGetter.h"

class Backtracking : public IConstraintSatisfactionProblem
{
    IVariableGetter* getter;

    public:
        Backtracking();
        ~Backtracking();

        std::vector<ISolution*>* solveProblem(IProblem*) override;

    private:
        void recursive(IProblem*, IConstraint*);
};

#endif //SI_LAB_2_BACKTRACKING_H
