//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_ICONSTRAINTSATISFACTIONPROBLEM_H
#define SI_LAB_2_ICONSTRAINTSATISFACTIONPROBLEM_H

#include <vector>
#include <memory>
#include "ISolution.h"
#include "../../problems/interface/IProblem.h"

class IConstraintSatisfactionProblem
{
    protected:
        IProblem* problem;
        std::vector<ISolution*> solutions;

    public:
        IConstraintSatisfactionProblem()
        {
            problem = nullptr;
        }

        virtual ~IConstraintSatisfactionProblem()
        {
            clearProblem();
            clearSolutions();
        }

        virtual std::vector<ISolution*>* solveProblem(IProblem*) = 0;

    protected:
        void clearSolutions()
        {
            for (int index = 0; index < solutions.size(); ++index)
                delete solutions[index];

            solutions.clear();
        }

        void clearProblem()
        {
            if (problem != nullptr)
                delete problem;

        }
};

#endif //SI_LAB_2_ICONSTRAINTSATISFACTIONPROBLEM_H
