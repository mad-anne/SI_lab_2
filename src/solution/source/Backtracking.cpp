//
// Created by Anna Siwik on 2017-04-08.
//

#include <constraints/header/HarmoniousGraphConstraint.h>
#include <accessors/header/NextVariableGetter.h>
#include <accessors/header/NextValueGetter.h>
#include "../header/Backtracking.h"
#include "../header/Solution.h"

Backtracking::Backtracking() :
    IConstraintSatisfactionProblem(),
    getter(new NextVariableGetter(nullptr)),
    constraint(new HarmoniousGraphConstraint(nullptr))
{}

Backtracking::~Backtracking()
{
    delete getter;
    delete constraint;
}

std::vector<ISolution*>* Backtracking::solveProblem(IProblem* problem)
{
    clearSolutions();

    getter->setProblem(problem);
    constraint->setProblem(problem);
    recursive(problem);
    return & solutions;
}

void Backtracking::recursive(IProblem* problem)
{
    const IVariable* variable = getter->getNext();

    if (variable == nullptr)
    {
        solutions.push_back(new Solution(problem->deepCopy()));
        return;
    }

    NextValueGetter valueGetter(variable);
    const IValue* value;

    while ((value = valueGetter.getNext()) != nullptr)
    {
        problem->setVariableValue(variable, value);

        if (constraint->updateConstraints(variable))
        {
            recursive(problem);
            constraint->undoConstraints(variable);
            problem->setVariableValue(variable, nullptr);
        }
        else
            problem->setVariableValue(variable, nullptr);
    }
}
