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
    recursive();
    return solutions.size() > 0
           ? solutions[0]
           : nullptr;
}

long long int ForwardChecking::getNumberOfSolutions(IProblemFactory* problemFactory)
{
    return 0;
}

std::vector<ISolution*>* ForwardChecking::getAllSolutions(IProblemFactory* problemFactory)
{
    clearSolutions();
    setAttributes(problemFactory);
    recursive();
    return & solutions;
}

void ForwardChecking::recursive()
{
    const IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
    {
        solutions.push_back(new Solution(problem));
        return;
    }

    NextValueGetter valueGetter(variable);
    const IValue* value;

    while ((value = valueGetter.getNext()) != nullptr)
    {
        problem->setVariableValue(variable, value);

        if (constraint->updateConstraints(variable))
        {
            recursive();
            constraint->undoConstraints(variable);
            problem->setVariableValue(variable, nullptr);
        }
        else
            problem->setVariableValue(variable, nullptr);
    }
}