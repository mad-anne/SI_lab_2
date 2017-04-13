//
// Created by Anna Siwik on 2017-04-08.
//

#include <constraints/header/HarmoniousGraphConstraint.h>
#include "../header/Backtracking.h"
#include "../header/Solution.h"

Backtracking::Backtracking() :
    IConstraintSatisfactionProblem()
{}

Backtracking::~Backtracking()
{}

std::vector<ISolution*>* Backtracking::solveProblem(IProblem* problem)
{
    clearSolutions();

    IConstraint* constraint = new HarmoniousGraphConstraint(problem);
    std::vector<ISolution*>* solutions = recursive(problem, constraint);
    delete constraint;
    return solutions;
}

std::vector<ISolution*>* Backtracking::recursive(IProblem* problem, IConstraint* constraint)
{
    if (problem->isComplete() && (HarmoniousGraphConstraint(problem).checkConstraints()))
    {
        solutions.push_back(new Solution(problem->deepCopy()));
        return & solutions;
    }

    IVariable* variable = problem->getUnassignedVariable();

    if (variable == nullptr)
        return & solutions;

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

    return & solutions;
}
