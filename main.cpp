#include <iostream>
#include <memory>
#include <sstream>
#include "solution/header/ConstraintSatisfactionProblem.h"

void runMenu();

int getNumberFromInput(std::string choice);

void processChoice(std::shared_ptr<IConstraintSatisfactionProblem> shared_ptr, int choice);

int main()
{
    runMenu();
    return 0;
}

void runMenu()
{
    std::shared_ptr<IConstraintSatisfactionProblem> csp = std::make_shared<ConstraintSatisfactionProblem>();

    std::cout << "Hi! Welcome in program that solves Constraint Satisfaction Problem." << std::endl;
    std::cout << "It can solve Harmonious Graph Coloring and Binary Game." << std::endl;
    std::cout << "It implements backtracking and forward-checking methods." << std::endl;

    std::string choice = "";
    short int numberChoice = -2;
    do
    {
        if (numberChoice == -1)
            std::cout << "\nOoops! Number wasn't correct. Try again." << std::endl;

        std::cout << "\nWhat would you like to do? (choose correct number)" << std::endl;

        std::cout << "0. Exit Program." << std::endl;
        std::cout << "1. Solve Harmonious Graph Coloring." << std::endl;
        std::cout << "2. Solve Binary Game.\n" << std::endl;

        getline(std::cin, choice);
        numberChoice = getNumberFromInput(choice);
        processChoice(csp, numberChoice);
    } while (numberChoice);

    std::cout << "\nThank you for using my program!" << std::endl;
}

int getNumberFromInput(std::string choice)
{
    int numberChoice = 0;
    std::stringstream myStream(choice);

    return myStream >> numberChoice
           ? numberChoice
           : -1;
}

void processChoice(std::shared_ptr<IConstraintSatisfactionProblem> csp, int choice)
{
    switch (choice)
    {
        case 0:
            std::cout << "You chose to exit program." << std::endl;
            break;
        case 1:
            std::cout << "You chose to solve harmonious graph coloring." << std::endl;
            break;
        case 2:
            std::cout << "You chose to solve binary game." << std::endl;
            break;
        default:
            std::cout << "You chose option that doesn't exist." << std::endl;
            break;
    }
}