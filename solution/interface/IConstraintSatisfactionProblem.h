//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_ICONSTRAINTSATISFACTIONPROBLEM_H
#define SI_LAB_2_ICONSTRAINTSATISFACTIONPROBLEM_H

#include <vector>
#include "ISolution.h"
#include "../../problems/interface/IProblem.h"

class IConstraintSatisfactionProblem
{
    protected:
        IProblem* problem;

    public:
        virtual void solveProblem(IProblem*) = 0;
};

#endif //SI_LAB_2_ICONSTRAINTSATISFACTIONPROBLEM_H
