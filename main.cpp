#include <iostream>
#include <memory>
#include <sstream>
#include "problems/interface/IProblem.h"
#include "solution/header/Backtracking.h"
#include "solution/header/ForwardChecking.h"
#include "problems/header/HarmoniousGraph.h"

void runMenu();
int getNumberFromInput(std::string choice);
void processChoice(std::shared_ptr<IConstraintSatisfactionProblem> backtracking,
                   std::shared_ptr<IConstraintSatisfactionProblem> forwardChecking,
                   int choice);

int getGraphSize();
int getBinarySize();
int getNumberOfFilledFields(int size);
int getSizeFor(std::string);

int main()
{
    runMenu();
    return 0;
}

void runMenu()
{
    std::shared_ptr<IConstraintSatisfactionProblem> backtracking = std::make_shared<Backtracking>();
    std::shared_ptr<IConstraintSatisfactionProblem> forwardChecking = std::make_shared<ForwardChecking>();

    std::cout << "Hi! Welcome in program that solves Constraint Satisfaction Problem." << std::endl;
    std::cout << "It can solve Harmonious Graph Coloring and Binary Game." << std::endl;
    std::cout << "It implements backtracking and forward-checking methods." << std::endl;

    std::string choice = "";
    int numberChoice;

    do
    {
        std::cout << "\nWhat would you like to do? (choose correct number)" << std::endl;

        std::cout << "0. Exit Program." << std::endl;
        std::cout << "1. Solve Harmonious Graph Coloring." << std::endl;
        std::cout << "2. Solve Binary Game.\n" << std::endl;

        getline(std::cin, choice);
        numberChoice = getNumberFromInput(choice);
        processChoice(backtracking, forwardChecking, numberChoice);
    } while (numberChoice);

    std::cout << "\nThank you for using my program!" << std::endl;
}

int getNumberFromInput(std::string choice)
{
    int numberChoice = 0;
    std::stringstream myStream(choice);

    return (myStream >> numberChoice) && (numberChoice >= 0)
           ? numberChoice
           : -1;
}

void processChoice(std::shared_ptr<IConstraintSatisfactionProblem> backtracking,
                   std::shared_ptr<IConstraintSatisfactionProblem> forwardChecking,
                   int choice)
{
    std::cout << std::endl;

    switch (choice)
    {
        case 0:
        {
            std::cout << "You have chosen to exit program." << std::endl;
            break;
        }
        case 1:
        {
            std::cout << "You have chosen to solve harmonious graph coloring." << std::endl;
            int size = getGraphSize();
            IProblem* graph = new HarmoniousGraph(size);

            std::unique_ptr<ISolution> backtrackingSolution = backtracking->solveProblem(graph);
            std::unique_ptr<ISolution> forwardCheckingSolution = forwardChecking->solveProblem(graph);

            backtrackingSolution->printHarmoniousGraph();
            forwardCheckingSolution->printHarmoniousGraph();

            delete graph;
            break;
        }
        case 2:
        {
            std::cout << "You have chosen to solve binary game." << std::endl;
            int size = getBinarySize();
            int filledFields = getNumberOfFilledFields(size);
            break;
        }
        default:
        {
            std::cout << "Ooops! Number wasn't correct. Try again." << std::endl;
            break;
        }
    }
}

int getGraphSize()
{
    int binarySize = getSizeFor("graph");
    return binarySize;
}

int getBinarySize()
{
    int binarySize = getSizeFor("binary");
    return binarySize;
}

int getNumberOfFilledFields(int size)
{
    int fields = size * size;
    int filledFields;
    bool isCorrect = false;

    do
    {
        filledFields = getSizeFor("filled fields");

        if (filledFields > fields)
            std::cout << "\nFilled fields size can not be greater than number of fields, which is " << fields << "." << std::endl;
        else
            isCorrect = true;

    } while (! isCorrect);

    return filledFields;
}

int getSizeFor(std::string whatFor)
{
    std::string choice = "";
    int size;
    bool isCorrect = false;

    do
    {
        std::cout << "\nWhat should be the size of " << whatFor << "? (give number)" << std::endl;

        getline(std::cin, choice);
        size = getNumberFromInput(choice);

        if (size <= 0)
            std::cout << "\nOoops! Number wasn't correct. Try again." << std::endl;
        else
            isCorrect = true;
    } while (! isCorrect);

    return size;
}