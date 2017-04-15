//
// Created by Anna Siwik on 2017-04-07.
//

#ifndef SI_LAB_2_ICONSTRAINTSATISFACTIONPROBLEM_H
#define SI_LAB_2_ICONSTRAINTSATISFACTIONPROBLEM_H

#include <vector>
#include <memory>
#include "ISolution.h"
#include "../../problems/interface/IProblem.h"
#include "../../factories/interface/IProblemFactory.h"

class IConstraintSatisfactionProblem
{
    protected:
        IProblem* problem;
        IConstraint* constraint;
        IVariableGetter* varGetter;
        IValueGetter* valGetter;

        std::vector<ISolution*> solutions;

    public:
        IConstraintSatisfactionProblem() :
            problem(nullptr),
            constraint(nullptr),
            varGetter(nullptr),
            valGetter(nullptr)
        {}
        virtual ~IConstraintSatisfactionProblem()
        {
            clearSolutions();
        }

        virtual const ISolution* getFirstSolution(IProblemFactory*) = 0;
        virtual int getNumberOfSolutions(IProblemFactory*) = 0;
        virtual std::vector<ISolution*>* getAllSolutions(IProblemFactory*) = 0;

    protected:
        void clearSolutions()
        {
            std::vector<ISolution*>::const_iterator it = solutions.begin();

            while (it != solutions.end())
            {
                delete *it;
                it = solutions.erase(it);
            }
        }
};

#endif //SI_LAB_2_ICONSTRAINTSATISFACTIONPROBLEM_H
