//
// Created by Anna Siwik on 2017-04-08.
//

#include <iostream>
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

    if (problem->isComplete())
    {
        solutions.push_back(new Solution(problem));
        return & solutions;
    }

    IVariable* variable = problem->getUnassignedVariable();
    const IDomain* domain = variable->getDomain();

    for (int i = 0; i < domain->getDomainSize(); ++i)
    {
        const IValue* value = domain->getValue(i);

        problem->setVariableValue(variable, value);
        // TODO: check constraints
        // TODO: if correct, solve problem again
        // TODO: if not correct, try to assign another value
        // TODO: if not correct and cannot assign another value, assign value -1 and return
    }

    std::cout << "You have chosen to solve problem by backtracking." << std::endl;
    std::cout << "Here we're solving problem." << std::endl;
    std::cout << "..." << std::endl;
    std::cout << "THE END\n\n";

    solutions.push_back(new Solution(problem));
    return & solutions;
}
