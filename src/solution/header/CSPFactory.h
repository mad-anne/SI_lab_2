//
// Created by Anna Siwik on 2017-04-14.
//

#ifndef SI_LAB_2_CSPFACTORY_H
#define SI_LAB_2_CSPFACTORY_H

#include <solution/interface/ICSPFactory.h>

class CSPFactory : ICSPFactory
{
    public:
        CSPFactory();
        ~CSPFactory();

        ISolution* getFirstSolutionByBacktracking(IProblem*) const override;
        ISolution* getFirstSolutionByForwardChecking(IProblem*) const override;

        std::vector<ISolution*>* getAllSolutionsByBacktracking(IProblem*) const override;
        std::vector<ISolution*>* getAllSolutionsByForwardChecking(IProblem*) const override;

        void setVariableGetter(IVariableGetter* getter) override;
        void setValueGetter(IValueGetter* getter) override;

        void setDefaultVariableGetter() override;
        void setDefaultValueGetter() override;

};

#endif //SI_LAB_2_CSPFACTORY_H
