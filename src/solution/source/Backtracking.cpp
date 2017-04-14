//
// Created by Anna Siwik on 2017-04-08.
//

#include <constraints/header/HarmoniousGraphConstraint.h>
#include <accessors/header/NextVariableGetter.h>
#include "../header/Backtracking.h"
#include "../header/Solution.h"

Backtracking::Backtracking() :
    IConstraintSatisfactionProblem(),
    getter(new NextVariableGetter(nullptr))
{}

Backtracking::~Backtracking()
{}

std::vector<ISolution*>* Backtracking::solveProblem(IProblem* problem)
{
    clearSolutions();

    getter->setProblem(problem);
    IConstraint* constraint = new HarmoniousGraphConstraint(problem);
    recursive(problem, constraint);
    delete constraint;
    return & solutions;
}

void Backtracking::recursive(IProblem* problem, IConstraint* constraint)
{
    if (problem->isComplete() && (HarmoniousGraphConstraint(problem).checkConstraints()))
    {
        solutions.push_back(new Solution(problem->deepCopy()));
        return;
    }

    const IVariable* variable = getter->getNext();

    if (variable == nullptr)
        return;

    const IDomain* domain = variable->getDomain();

    for (int i = 0; i < domain->getDomainSize(); ++i)
    {
        const IValue* value = domain->getValue(i);

        problem->setVariableValue(variable, value);
        // TODO: algorithm should go every path, check it
        // TODO: checking constraints should be done for variable, which has row and col
        // TODO: should be option to reverse adding constraints
        // TODO: checking constraints should NOT affect repetition from the past
//        if (constraint->checkConstraints(variable->getRow(), variable->getColumn()))
        if ((HarmoniousGraphConstraint(problem).checkConstraints()))
            recursive(problem, constraint);
        else
            problem->setVariableValue(variable, nullptr);
    }
}
