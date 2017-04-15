//
// Created by Anna Siwik on 2017-04-08.
//

#include <constraints/header/HarmoniousGraphConstraint.h>
#include <accessors/header/NextVariableGetter.h>
#include <accessors/header/NextValueGetter.h>
#include "../header/Backtracking.h"
#include "../header/Solution.h"

Backtracking::Backtracking() :
    IConstraintSatisfactionProblem()
{}

Backtracking::~Backtracking()
{}

void Backtracking::setAttributes(IProblemFactory* problemFactory)
{
    problem = problemFactory->getProblem();
    constraint = problemFactory->getConstraint();
    varGetter = problemFactory->getVariableGetter();
    valGetter = problemFactory->getValueGetter();
}

const ISolution* Backtracking::getFirstSolution(IProblemFactory* problemFactory)
{
    clearSolutions();
    setAttributes(problemFactory);
    return recursive();
}

long long int Backtracking::getNumberOfSolutions(IProblemFactory* problemFactory)
{
    clearSolutions();
    setAttributes(problemFactory);
    recursiveFindNumberOfAll();
    return totalNumberOfSolutions;
}

std::vector<ISolution*>* Backtracking::getAllSolutions(IProblemFactory* problemFactory)
{
    clearSolutions();
    setAttributes(problemFactory);
    recursiveFindAll();
    return & solutions;
}

ISolution* Backtracking::recursive()
{
    ISolution* solution = nullptr;
    const IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
        return new Solution(problem);

    NextValueGetter valueGetter(variable);
    const IValue* value;

    while ((value = valueGetter.getNext()) != nullptr)
    {
        problem->setVariableValue(variable, value);

        if (constraint->updateConstraints(variable))
        {
            if ((solution = recursive()) == nullptr)
            {
                constraint->undoConstraints(variable);
                problem->setVariableValue(variable, nullptr);
            }
            else
                break;
        }
        else
            problem->setVariableValue(variable, nullptr);
    }

    return solution;
}

void Backtracking::recursiveFindAll()
{
    const IVariable *variable = varGetter->getNext();

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

void Backtracking::recursiveFindNumberOfAll()
{
    const IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
    {
        ++totalNumberOfSolutions;
        return;
    }

    NextValueGetter valueGetter(variable);
    const IValue* value;

    while ((value = valueGetter.getNext()) != nullptr)
    {
        problem->setVariableValue(variable, value);

        if (constraint->updateConstraints(variable))
        {
            recursiveFindNumberOfAll();
            constraint->undoConstraints(variable);
            problem->setVariableValue(variable, nullptr);
        } else
            problem->setVariableValue(variable, nullptr);
    }
}