//
// Created by Anna Siwik on 2017-04-08.
//

#include <iostream>
#include "../header/Backtracking.h"

Backtracking::Backtracking()
{
    problem = nullptr;
}

Backtracking::~Backtracking()
{
    if (problem != nullptr)
        delete problem;
}

void Backtracking::solveProblem(IProblem* problem)
{
    std::cout << "You have chosen to solve problem by backtracking." << std::endl;
    std::cout << "Here we're solving problem." << std::endl;
    std::cout << "..." << std::endl;
    std::cout << "THE END" << std::endl;
}
