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
    std::cout << "You have chosen to solve problem by backtracking." << std::endl;
    std::cout << "Here we're solving problem." << std::endl;
    std::cout << "..." << std::endl;
    std::cout << "THE END\n\n";

    solutions.push_back(new Solution(problem));
    return & solutions;
}
