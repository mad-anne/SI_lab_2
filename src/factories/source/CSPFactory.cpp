//
// Created by Anna Siwik on 2017-04-14.
//

#include <vector>
#include <problems/interface/IProblem.h>
#include <accessors/interface/IVariableGetter.h>
#include <accessors/interface/IValueGetter.h>
#include <factories/header/CSPFactory.h>

CSPFactory::CSPFactory()
        : ICSPFactory()
{}

CSPFactory::~CSPFactory()
{}

const ISolution* CSPFactory::getFirstSolutionByBacktracking(IProblemFactory* problemFactory) const
{
    return backtracking->getFirstSolution(problemFactory);
}

const ISolution* CSPFactory::getFirstSolutionByForwardChecking(IProblemFactory* problemFactory) const
{
    return forwardChecking->getFirstSolution(problemFactory);
}

long long int CSPFactory::getNumberOfSolutionsByBacktracking(IProblemFactory* problemFactory) const
{
    return backtracking->getNumberOfSolutions(problemFactory);
}

long long int CSPFactory::getNumberOfSolutionsByForwardChecking(IProblemFactory* problemFactory) const
{
    return forwardChecking->getNumberOfSolutions(problemFactory);
}

std::vector<ISolution*>* CSPFactory::getAllSolutionsByBacktracking(IProblemFactory* problemFactory) const
{
    return backtracking->getAllSolutions(problemFactory);
}

std::vector<ISolution*>* CSPFactory::getAllSolutionsByForwardChecking(IProblemFactory* problemFactory) const
{
    return forwardChecking->getAllSolutions(problemFactory);
}