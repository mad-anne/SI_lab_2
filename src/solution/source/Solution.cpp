//
// Created by Anna Siwik on 2017-04-08.
//

#include <iostream>
#include "../header/Solution.h"
#include "../../problems/header/HarmoniousGraph.h"

Solution::Solution(IProblem* solution)
{
    readProblem(solution);
}

Solution::~Solution()
{}

void Solution::print() const
{
    if (solution == nullptr)
        std::cout << "Solution is empty." << std::endl;

    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
            printf( "| %3d ", solution[row][col]);

        std::cout << "|" << std::endl;
    }

    std::cout << std::endl << std::endl;

}

void Solution::readProblem(IProblem* problem)
{
    width = problem->getWidth();
    solution = new int*[width];

    for (int row = 0; row < width; ++row)
    {
        solution[row] = new int[width];

        for (int col = 0; col < width; ++col)
        {
            int value = problem->getVariable(row, col)->getValue()->getValue();
            solution[row][col] = value;
        }
    }
}