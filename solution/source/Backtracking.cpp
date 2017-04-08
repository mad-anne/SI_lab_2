//
// Created by Anna Siwik on 2017-04-08.
//

#include <iostream>
#include "../header/Backtracking.h"
<<<<<<< HEAD
#include "../header/Solution.h"
=======
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50

Backtracking::Backtracking()
{
    problem = nullptr;
}

Backtracking::~Backtracking()
{
    if (problem != nullptr)
        delete problem;
}

<<<<<<< HEAD
std::unique_ptr<ISolution> Backtracking::solveProblem(IProblem* problem)
=======
void Backtracking::solveProblem(IProblem* problem)
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
{
    std::cout << "You have chosen to solve problem by backtracking." << std::endl;
    std::cout << "Here we're solving problem." << std::endl;
    std::cout << "..." << std::endl;
<<<<<<< HEAD
    std::cout << "THE END\n\n";

    std::unique_ptr<ISolution> solution = std::make_unique<Solution>();
    return std::move(solution);
=======
    std::cout << "THE END" << std::endl;
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
}
