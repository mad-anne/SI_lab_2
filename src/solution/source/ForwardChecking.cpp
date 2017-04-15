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
    IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
    {
        solutions.push_back(new Solution(problem));
        return;
    }

    NextValueGetter valueGetter(variable);
    const IValue* value;

    while ((value = valueGetter.getNext()) != nullptr)
    {
        variable->setValue(value);
        // TODO: EVERY assign should be correct (?), cause domains are corrrect
        // TODO: after assigning a value, delete from neighbours domains this value, also watching on constraints (delete value if it causes to exists wrong connection)
        // TODO: must implements inversing putting constraints OMG
        if (constraint->updateConstraints(variable))
        {
            recursive();
            constraint->undoConstraints(variable);
            variable->setValue(nullptr);
        }
        else
            variable->setValue(nullptr);
    }
}