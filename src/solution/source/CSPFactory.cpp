//
// Created by Anna Siwik on 2017-04-14.
//

#include <vector>
#include <problems/interface/IProblem.h>
#include <accessors/interface/IVariableGetter.h>
#include <accessors/interface/IValueGetter.h>
#include <solution/header/CSPFactory.h>

CSPFactory::CSPFactory()
        : ICSPFactory()
{}

CSPFactory::~CSPFactory()
{}

ISolution* CSPFactory::getFirstSolutionByBacktracking(IProblem* problem) const
{
//    TODO: backtracking->getSolution(problem, varGetter, valGetter);
    return nullptr;
}

ISolution* CSPFactory::getFirstSolutionByForwardChecking(IProblem* problem) const
{
//   TODO: forwardChecking->getSolution(problem, varGetter, valGetter);
    return nullptr;
}

std::vector<ISolution*>* CSPFactory::getAllSolutionsByBacktracking(IProblem* problem) const
{
//   TODO: backtracking->getAllSolutions(problem, varGetter, valGetter);
    return nullptr;
}

std::vector<ISolution*>* CSPFactory::getAllSolutionsByForwardChecking(IProblem* problem) const
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
