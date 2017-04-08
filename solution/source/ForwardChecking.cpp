//
// Created by Anna Siwik on 2017-04-08.
//

#include <iostream>
#include "../header/ForwardChecking.h"
<<<<<<< HEAD
#include "../header/Solution.h"
=======
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50

ForwardChecking::ForwardChecking()
{
    problem = nullptr;
}

ForwardChecking::~ForwardChecking()
{
    if (problem != nullptr)
        delete problem;
}

<<<<<<< HEAD
std::unique_ptr<ISolution> ForwardChecking::solveProblem(IProblem* problem)
=======
void ForwardChecking::solveProblem(IProblem* problem)
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
{
    std::cout << "You have chosen to solve problem by forward checking." << std::endl;
    std::cout << "Here we're solving problem." << std::endl;
    std::cout << "..." << std::endl;
    std::cout << "THE END" << std::endl;
<<<<<<< HEAD

    return std::make_unique<Solution>();
=======
>>>>>>> 8e927268749581ebfa7dbdd3c68afe7a0c154d50
}
