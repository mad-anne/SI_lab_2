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

    IValueGetter* tempValGetter = valGetter->instantiate(variable);
    IValue* value;

    while ((value = tempValGetter->getNext()) != nullptr)
    {
        variable->setValue(value);

        constraint->putConstraintsOn(variable, true);

        if (!isNullVariableWithEmptyDomain() && (solution = recursive()) == nullptr)
        {
            constraint->putConstraintsOff(variable, true);
            variable->setValue(nullptr);
        }
        else
            break;
    }

    delete tempValGetter;

    return solution;
}


void ForwardChecking::recursiveFindNumberOfAll()
{
    IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
        return;

    IValueGetter* tempValGetter = valGetter->instantiate(variable);
    IValue* value;

    while ((value = tempValGetter->getNext()) != nullptr)
    {
        variable->setValue(value);

        if (problem->isCompleted())
        {
            ++totalNumberOfSolutions;
            variable->setValue(nullptr);
            continue;
        }

        constraint->putConstraintsOn(variable, true);

        if (! isNullVariableWithEmptyDomain())
            recursiveFindNumberOfAll();

        constraint->putConstraintsOff(variable, true);
        variable->setValue(nullptr);
    }

    delete tempValGetter;
}

void ForwardChecking::recursiveFindAll()
{
    IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
        return;

    IValueGetter* tempValGetter = valGetter->instantiate(variable);
    IValue* value;

    while ((value = tempValGetter->getNext()) != nullptr)
    {
        variable->setValue(value);

        if (problem->isCompleted())
        {
            solutions.push_back(new Solution(problem));
            variable->setValue(nullptr);
            continue;
        }

        constraint->putConstraintsOn(variable, true);

        if (! isNullVariableWithEmptyDomain())
            recursiveFindAll();

        constraint->putConstraintsOff(variable, true);
        variable->setValue(nullptr);
    }

    delete tempValGetter;
}

bool ForwardChecking::isNullVariableWithEmptyDomain()
{
    int width = problem->getWidth();

    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            IVariable* tempVar = problem->getVariable(row, col);

            if (tempVar->getValue() == nullptr && tempVar->getDomain()->getSize() == 0)
                return true;
        }
    }

    return false;
}