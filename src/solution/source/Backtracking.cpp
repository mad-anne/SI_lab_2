//
// Created by Anna Siwik on 2017-04-08.
//

#include <iostream>
#include "../header/Backtracking.h"
#include "../header/Solution.h"
#include "../../components/header/Color.h"

Backtracking::Backtracking() :
    IConstraintSatisfactionProblem()
{}

Backtracking::~Backtracking()
{}

std::vector<ISolution*>* Backtracking::solveProblem(IProblem* problem)
{
    clearSolutions();

    std::cout << "You have chosen to solve problem by backtracking." << std::endl;
    std::cout << "Here we're solving problem." << std::endl;
    std::cout << "..." << std::endl;

    return recursive(problem);
}

std::vector<ISolution*>* Backtracking::recursive(IProblem* problem)
{
    if (problem->isComplete())
    {
        solutions.push_back(new Solution(problem));
        return & solutions;
    }

    IVariable* variable = problem->getUnassignedVariable();

    if (variable == nullptr)
        return & solutions;

//    const IDomain* domain = variable->getDomain();
//
//    for (int i = 0; i < domain->getDomainSize(); ++i)
//    {
//        const IValue* value = domain->getValue(i);
//
//        problem->setVariableValue(variable, value);
//
//        if (problem->checkConstraints()) // TODO: check constraints
//            recursive(problem); // TODO: if correct, solve problem again
//        else
//            problem->setVariableValue(variable, new Color(-1)); // TODO: if not correct, try to assign another value
//    }

    return & solutions;
    // TODO: if not correct and cannot assign another value, assign value -1 and return
}
