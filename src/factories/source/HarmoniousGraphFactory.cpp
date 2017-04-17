//
// Created by Anna Siwik on 2017-04-15.
//

#include <problems/header/HarmoniousGraph.h>
#include <constraints/header/HarmoniousGraphConstraintChecker.h>
#include <accessors/header/NextVariableGetter.h>
#include <accessors/header/NextValueGetter.h>
#include "factories/header/HarmoniousGraphFactory.h"

HarmoniousGraphFactory::HarmoniousGraphFactory(int width, IVariableGetter* variableGetter, IValueGetter* valueGetter)
{
    problem = new HarmoniousGraph(width);
    constraint = new HarmoniousGraphConstraintChecker(problem);

    if (variableGetter != nullptr)
    {
        variableGetter->setProblem(problem);
        varGetter = variableGetter;
    }
    else
        varGetter = new NextVariableGetter(problem);

    if (valGetter != nullptr)
        valGetter = valueGetter;
    else
        valGetter = new NextValueGetter(nullptr);
}

HarmoniousGraphFactory::~HarmoniousGraphFactory()
{
    clearValueGetter();
    clearVariableGetter();
    clearConstraint();
    clearProblem();
}

IProblem* HarmoniousGraphFactory::getProblem() const
{
    return problem;
}

IConstraintChecker* HarmoniousGraphFactory::getConstraint() const
{
    return constraint;
}

IVariableGetter* HarmoniousGraphFactory::getVariableGetter() const
{
    return varGetter;
}

IValueGetter* HarmoniousGraphFactory::getValueGetter() const
{
    return valGetter;
}

void HarmoniousGraphFactory::clearProblem()
{
    delete problem;
}

void HarmoniousGraphFactory::clearConstraint()
{
    delete constraint;
}

void HarmoniousGraphFactory::clearVariableGetter()
{
    delete varGetter;
}

void HarmoniousGraphFactory::clearValueGetter()
{
    delete valGetter;
}
