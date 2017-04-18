//
// Created by Anna Siwik on 2017-04-08.
//

#include <constraints/header/HarmoniousGraphConstraintChecker.h>
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
    IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
        return new Solution(problem);

    IValueGetter* tempValGetter = valGetter->instantiate(variable);
    IValue* value;

    while ((value = tempValGetter->getNext()) != nullptr)
    {
        variable->setValue(value);

        if (constraint->isCorrectAssignment(variable))
        {
            constraint->putConstraintsOn(variable, false);

            if ((solution = recursive()) == nullptr)
            {
                constraint->putConstraintsOff(variable, false);
                variable->setValue(nullptr);
            }
            else
                break;
        }
        else
            variable->setValue(nullptr);
    }

    delete tempValGetter;

    return solution;
}

void Backtracking::recursiveFindAll()
{
    IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
    {
        solutions.push_back(new Solution(problem));
        return;
    }

    IValueGetter* tempValGetter = valGetter->instantiate(variable);
    IValue* value;

    while ((value = tempValGetter->getNext()) != nullptr)
    {
        variable->setValue(value);

        if (constraint->isCorrectAssignment(variable))
        {
            constraint->putConstraintsOn(variable, false);
            recursiveFindAll();
            constraint->putConstraintsOff(variable, false);
            variable->setValue(nullptr);
        }
        else
            variable->setValue(nullptr);
    }

    delete tempValGetter;
}

void Backtracking::recursiveFindNumberOfAll()
{
    IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
    {
        ++totalNumberOfSolutions;
        return;
    }

    IValueGetter* tempValGetter = valGetter->instantiate(variable);
    IValue* value;

    while ((value = tempValGetter->getNext()) != nullptr)
    {
        variable->setValue(value);

        if (constraint->isCorrectAssignment(variable))
        {
            constraint->putConstraintsOn(variable, false);
            recursiveFindNumberOfAll();
            constraint->putConstraintsOff(variable, false);
            variable->setValue(nullptr);
        }
        else
            variable->setValue(nullptr);
    }

    delete tempValGetter;
}

