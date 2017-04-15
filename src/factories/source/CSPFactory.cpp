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
//   TODO: forwardChecking->getSolution(problem, varGetter, valGetter);
    return nullptr;
}

int CSPFactory::getNumberOfSolutionsByBacktracking(IProblemFactory* problemFactory) const
{
    return 0;
}

int CSPFactory::getNumberOfSolutionsByForwardChecking(IProblemFactory* problemFactory) const
{
    return 0;
}

std::vector<ISolution*>* CSPFactory::getAllSolutionsByBacktracking(IProblemFactory* problemFactory) const
{
//   TODO: backtracking->getAllSolutions(problem, varGetter, valGetter);
    return nullptr;
}

std::vector<ISolution*>* CSPFactory::getAllSolutionsByForwardChecking(IProblemFactory* problemFactory) const
{
//   TODO: forwardChecking->getAllSolutions(problem, varGetter, valGetter);
    return nullptr;
}

void CSPFactory::setVariableGetter(IVariableGetter* getter)
{
    if (varGetter != nullptr)
        delete varGetter;
    varGetter = getter;
}

void CSPFactory::setValueGetter(IValueGetter* getter)
{
    if (valGetter != nullptr)
        delete valGetter;
    valGetter = getter;
}

void CSPFactory::setDefaultVariableGetter()
{
    if (varGetter != nullptr)
        delete varGetter;
    varGetter = new NextVariableGetter(nullptr);
}

void CSPFactory::setDefaultValueGetter()
{
    if (valGetter != nullptr)
        delete valGetter;
    valGetter = new NextValueGetter(nullptr);
}
