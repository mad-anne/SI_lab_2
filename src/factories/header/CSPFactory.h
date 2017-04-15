//
// Created by Anna Siwik on 2017-04-14.
//

#ifndef SI_LAB_2_CSPFACTORY_H
#define SI_LAB_2_CSPFACTORY_H

#include <factories/interface/ICSPFactory.h>

class CSPFactory : public ICSPFactory
{
    public:
        CSPFactory();
        ~CSPFactory();

        const ISolution* getFirstSolutionByBacktracking(IProblemFactory*) const override;
        const ISolution* getFirstSolutionByForwardChecking(IProblemFactory*) const override;

        long long int getNumberOfSolutionsByBacktracking(IProblemFactory*) const override;
        long long int getNumberOfSolutionsByForwardChecking(IProblemFactory*) const override;

        std::vector<ISolution*>* getAllSolutionsByBacktracking(IProblemFactory*) const override;
        std::vector<ISolution*>* getAllSolutionsByForwardChecking(IProblemFactory*) const override;
};

#endif //SI_LAB_2_CSPFACTORY_H
