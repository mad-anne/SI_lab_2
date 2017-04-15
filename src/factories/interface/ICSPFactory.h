//
// Created by Anna Siwik on 2017-04-14.
//

#ifndef SI_LAB_2_ICSPFACTORY_H
#define SI_LAB_2_ICSPFACTORY_H

#include <accessors/interface/IVariableGetter.h>
#include <accessors/interface/IValueGetter.h>
#include <solution/header/Backtracking.h>
#include <solution/header/ForwardChecking.h>
#include <accessors/header/NextVariableGetter.h>
#include <accessors/header/NextValueGetter.h>
#include "solution/interface/IConstraintSatisfactionProblem.h"

class ICSPFactory
{
    protected:
        IConstraintSatisfactionProblem* backtracking;
        IConstraintSatisfactionProblem* forwardChecking;

    public:
        ICSPFactory()
                : backtracking(new Backtracking()),
                  forwardChecking(new ForwardChecking())
        {}

        virtual ~ICSPFactory()
        {
            delete backtracking;
            delete forwardChecking;
        };

        virtual const ISolution* getFirstSolutionByBacktracking(IProblemFactory*) const = 0;
        virtual const ISolution* getFirstSolutionByForwardChecking(IProblemFactory*) const = 0;

        virtual long long int getNumberOfSolutionsByBacktracking(IProblemFactory*) const = 0;
        virtual long long int getNumberOfSolutionsByForwardChecking(IProblemFactory*) const = 0;

        virtual std::vector<ISolution*>* getAllSolutionsByBacktracking(IProblemFactory*) const = 0;
        virtual std::vector<ISolution*>* getAllSolutionsByForwardChecking(IProblemFactory*) const = 0;
};

#endif //SI_LAB_2_ICSPFACTORY_H
