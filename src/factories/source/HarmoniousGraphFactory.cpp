//
// Created by Dom on 2017-04-15.
//

#include <problems/header/HarmoniousGraph.h>
#include <constraints/header/HarmoniousGraphConstraint.h>
#include <accessors/header/NextVariableGetter.h>
#include <accessors/header/NextValueGetter.h>
#include "factories/header/HarmoniousGraphFactory.h"

HarmoniousGraphFactory::HarmoniousGraphFactory(int width)

{
    problem = new HarmoniousGraph(width);
    constraint = new HarmoniousGraphConstraint(problem);
    varGetter = new NextVariableGetter(problem);
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

IConstraint* HarmoniousGraphFactory::getConstraint() const
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
