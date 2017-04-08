//
// Created by Anna Siwik on 2017-04-08.
//

#include <iostream>
#include "../header/Solution.h"
#include "../../problems/header/HarmoniousGraph.h"

Solution::Solution()
{
    solution = nullptr;
}

Solution::Solution(IProblem* solution)
{
    this->solution = solution;
}

Solution::~Solution()
{
    if (solution != nullptr)
        delete solution;
}

void Solution::printHarmoniousGraph()
{
    if (solution == nullptr)
        return;

    std::cout << "Hi! I'm printing harmonious graph solution." << std::endl;

    int width = solution->getWidth();

    std::cout << "It's size: " << width << std::endl;

    for (int row = 0; row < width; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            const IValue* val = solution->getVariable(row, col)->getValue();
            printf( "| %3d ", val->getValue());
        }
        std::cout << "|" << std::endl;
    }

    std::cout << std::endl << std::endl;

}

void Solution::printBinaryGame()
{
    std::cout << "Hi! I'm printing binary game solution." << std::endl;
}

void Solution::setSolution(IProblem* problem)
{
    solution = problem;
}

