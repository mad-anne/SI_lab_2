//
// Created by Anna Siwik on 2017-04-08.
//

#include <iostream>
#include <solution/header/Solution.h>
#include <accessors/header/NextValueGetter.h>
#include "../header/ForwardChecking.h"

ForwardChecking::ForwardChecking() :
    IConstraintSatisfactionProblem()
{}

ForwardChecking::~ForwardChecking()
{}

void ForwardChecking::setAttributes(IProblemFactory* problemFactory)
{
    problem = problemFactory->getProblem();
    constraint = problemFactory->getConstraint();
    varGetter = problemFactory->getVariableGetter();
    valGetter = problemFactory->getValueGetter();
}

const ISolution* ForwardChecking::getFirstSolution(IProblemFactory* problemFactory)
{
    clearSolutions();
    setAttributes(problemFactory);
    return recursive();
}

long long int ForwardChecking::getNumberOfSolutions(IProblemFactory* problemFactory)
{
    clearSolutions();
    setAttributes(problemFactory);
    recursiveFindNumberOfAll();
    return totalNumberOfSolutions;
}

std::vector<ISolution*>* ForwardChecking::getAllSolutions(IProblemFactory* problemFactory)
{
    clearSolutions();
    setAttributes(problemFactory);
    recursive();
    return & solutions;
}

ISolution* ForwardChecking::recursive()
{
    ISolution* solution = nullptr;
    IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
        return new Solution(problem);

    NextValueGetter valueGetter(variable);
    const IValue* value;

    while ((value = valueGetter.getNext()) != nullptr)
    {
        variable->setValue(value);

        constraint->putForwardConstraints(variable);

        if ((solution = recursive()) == nullptr)
        {
            constraint->undoForwardConstraints(variable);
            variable->setValue(nullptr);
        }
        else
            break;
    }

    return solution;
}


void ForwardChecking::recursiveFindNumberOfAll()
{
    IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
    {
        ++totalNumberOfSolutions;
        return;
    }

    NextValueGetter valueGetter(variable);
    const IValue* value;

    while ((value = valueGetter.getNext()) != nullptr)
    {
        variable->setValue(value);

        constraint->putForwardConstraints(variable);
        recursiveFindNumberOfAll();

        constraint->undoForwardConstraints(variable);
        variable->setValue(nullptr);
    }
}