//
// Created by Anna Siwik on 2017-04-08.
//

#include <iostream>
#include "../header/ForwardChecking.h"

ForwardChecking::ForwardChecking() :
    IConstraintSatisfactionProblem()
{}

ForwardChecking::~ForwardChecking()
{}

std::vector<ISolution*>* ForwardChecking::solveProblem(IProblem* problem)
{
    std::cout << "You have chosen to solve problem by forward checking." << std::endl;
    std::cout << "Here we're solving problem." << std::endl;
    std::cout << "..." << std::endl;
    std::cout << "THE END" << std::endl;

    return & solutions;
}
