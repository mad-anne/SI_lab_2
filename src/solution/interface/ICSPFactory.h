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
#include "IConstraintSatisfactionProblem.h"

class ICSPFactory
{
    protected:
        IConstraintSatisfactionProblem* backtracking;
        IConstraintSatisfactionProblem* forwardChecking;

        IVariableGetter* varGetter; //defaultowo powinien być nextVarGetter
        IValueGetter* valGetter; //defaultowo nextvalgetter

    public:
        ICSPFactory()
                : backtracking(new Backtracking()),
                  forwardChecking(new ForwardChecking()),
                  varGetter(new NextVariableGetter(nullptr)),
                  valGetter(new NextValueGetter(nullptr))
        {}

        virtual ~ICSPFactory()
        {
            if (varGetter != nullptr)
                delete varGetter;

            if (valGetter != nullptr)
                delete valGetter;

            delete backtracking;
            delete forwardChecking;
        };

        virtual ISolution* getFirstSolutionByBacktracking(IProblem*) const = 0;
        virtual ISolution* getFirstSolutionByForwardChecking(IProblem*) const = 0;

    //TODO: po każdym algorytmie należy usuwać dane!
        virtual std::vector<ISolution*>* getAllSolutionsByBacktracking(IProblem*) const = 0;
        virtual std::vector<ISolution*>* getAllSolutionsByForwardChecking(IProblem*) const = 0;

        virtual void setVariableGetter(IVariableGetter*) = 0;
        virtual void setValueGetter(IValueGetter*) = 0;

        virtual void setDefaultVariableGetter() = 0;
        virtual void setDefaultValueGetter() = 0;
};

#endif //SI_LAB_2_ICSPFACTORY_H
