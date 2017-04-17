//
// Created by Anna Siwik on 2017-04-15.
//

#include <problems/header/BinaryGame.h>
#include <accessors/header/NextVariableGetter.h>
#include <accessors/header/NextValueGetter.h>
#include <constraints/header/BinaryGameConstraintChecker.h>
#include "BinaryGameFactory.h"

BinaryGameFactory::BinaryGameFactory(int width, int emptyFields, IVariableGetter* variableGetter, IValueGetter* valueGetter)
{
    problem = new BinaryGame(width, emptyFields);

    constraint = new BinaryGameConstraintChecker(problem);

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

BinaryGameFactory::~BinaryGameFactory()
{
    clearValueGetter();
    clearVariableGetter();
    clearConstraint();
    clearProblem();
}

IProblem* BinaryGameFactory::getProblem() const
{
    return problem;
}

IConstraintChecker* BinaryGameFactory::getConstraint() const
{
    return constraint;
}

IVariableGetter* BinaryGameFactory::getVariableGetter() const
{
    return varGetter;
}

IValueGetter* BinaryGameFactory::getValueGetter() const
{
    return valGetter;
}

void BinaryGameFactory::clearProblem()
{
    delete problem;
}

void BinaryGameFactory::clearConstraint()
{
    delete constraint;
}

void BinaryGameFactory::clearVariableGetter()
{
    delete varGetter;
}

void BinaryGameFactory::clearValueGetter()
{
    delete valGetter;
}
