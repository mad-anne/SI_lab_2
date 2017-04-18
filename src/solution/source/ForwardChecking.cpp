//
// Created by Anna Siwik on 2017-04-08.
//

#include <solution/header/Solution.h>
#include <accessors/header/NextValueGetter.h>
#include <iostream>
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
    recursiveFindAll();
    return & solutions;
}

ISolution* ForwardChecking::recursive()
{
    ISolution* solution = nullptr;
    IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
        return new Solution(problem);

    NextValueGetter valueGetter(variable);
     IValue* value;

    while ((value = valueGetter.getNext()) != nullptr)
    {
        variable->setValue(value);

        constraint->putConstraintsOn(variable, true);

        if ((solution = recursive()) == nullptr)
        {
            constraint->putConstraintsOff(variable, true);
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
        return;

    NextValueGetter valueGetter(variable);
    IValue* value;

    while ((value = valueGetter.getNext()) != nullptr)
    {
        variable->setValue(value);

        if (problem->isCompleted())
        {
            ++totalNumberOfSolutions;
            variable->setValue(nullptr);
            continue;
        }
        else
        {
            constraint->putConstraintsOn(variable, true);
            recursiveFindNumberOfAll();

            constraint->putConstraintsOff(variable, true);
            variable->setValue(nullptr);
        }
    }
}

void ForwardChecking::recursiveFindAll()
{
    IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
    {
        solutions.push_back(new Solution(problem));
        return;
    }

    NextValueGetter valueGetter(variable);
    IValue* value;

    while ((value = valueGetter.getNext()) != nullptr)
    {
        variable->setValue(value);

        constraint->putConstraintsOn(variable, true);
        recursiveFindAll();

        constraint->putConstraintsOff(variable, true);
        variable->setValue(nullptr);
    }
}