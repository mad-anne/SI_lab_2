//
// Created by Anna Siwik on 2017-04-08.
//

#include <iostream>
#include "../header/ForwardChecking.h"
#include "../header/Solution.h"

ForwardChecking::ForwardChecking()
{
    problem = nullptr;
}

ForwardChecking::~ForwardChecking()
{
    if (problem != nullptr)
        delete problem;
}

std::unique_ptr<ISolution> ForwardChecking::solveProblem(IProblem* problem)
{
    std::cout << "You have chosen to solve problem by forward checking." << std::endl;
    std::cout << "Here we're solving problem." << std::endl;
    std::cout << "..." << std::endl;
    std::cout << "THE END" << std::endl;

    return std::make_unique<Solution>();
}
