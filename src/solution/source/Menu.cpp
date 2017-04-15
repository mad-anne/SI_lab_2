//
// Created by Anna Siwik on 2017-04-15.
//

#include <factories/header/CSPFactory.h>
#include <iostream>
#include <sstream>
#include <factories/header/HarmoniousGraphFactory.h>
#include "solution/header/Menu.h"
#include <factories/header/BinaryGameFactory.h>

Menu::Menu()
    : cspFactory(std::make_shared<CSPFactory>())
{}

void Menu::start()
{
    printGreeting();
    bool exit = false;

    while (!exit)
    {
        printMainOptions();
        exit = processChoice(getPositiveNumberInput());
    }

    printFarewell();
}

void Menu::printGreeting() const
{
    std::cout << "Hi! Welcome in program that solves Constraint Satisfaction Problem." << std::endl;
    std::cout << "It can solve Harmonious Graph Coloring and Binary Game." << std::endl;
    std::cout << "It implements backtracking and forward-checking methods." << std::endl;
    std::cout << "Navigate menu by choosing correct numbers." << std::endl;
}

void Menu::printFarewell() const
{
    std::cout << "\nThank you for using my program!" << std::endl;
}

void Menu::printMainOptions() const
{
    std::cout << "\nWhat would you like to do?" << std::endl;

    std::cout << "0. Exit Program." << std::endl;
    std::cout << "1. Solve Harmonious Graph Coloring." << std::endl;
    std::cout << "2. Solve Binary Game.\n" << std::endl;
}

int Menu::getPositiveNumberInput() const
{
    int numberChoice = 0;
    std::string choice = "";
    getline(std::cin, choice);

    std::stringstream myStream(choice);

    return (myStream >> numberChoice) && (numberChoice >= 0)
           ? numberChoice
           : -1;
}

bool Menu::processChoice(int choice) const
{
    std::cout << std::endl;

    switch (choice)
    {
        case 0:
        {
            std::cout << "You have chosen to exit program." << std::endl;
            return true;
        }
        case 1:
        {
            processHarmoniousGraphColoring();
            break;
        }
        case 2:
        {

            processBinaryGameSolving();
            break;
        }
        default:
        {
            std::cout << "Ooops! Number wasn't correct. Try again." << std::endl;
            break;
        }
    }

    return false;
}

int Menu::getGraphSize() const
{
    return getSizeFor("graph");
}

int Menu::getBinarySize() const
{
    int size;

    while ((size = getSizeFor("binary")) % 2 == 1)
    {
        std::cout << "Binary size must be even number." << std::endl;
    }

    return size;
}

int Menu::getNumberOfFilledFields(int size) const
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

int Menu::getSizeFor(std::string whatFor) const
{
    std::string choice = "";
    int size;
    bool isCorrect = false;

    do
    {
        std::cout << "\nWhat should be the size of " << whatFor << "? (give number)" << std::endl;

        size = getPositiveNumberInput();

        if (size <= 0)
            std::cout << "\nOoops! Number wasn't correct - must be more than 0. Try again." << std::endl;
        else
            isCorrect = true;
    } while (! isCorrect);

    return size;
}

void Menu::printFirstTenSolutions(std::vector<ISolution*>* solutions) const
{
    for (int index = 0; index < 10 && index < solutions->size(); ++index)
        solutions->at(index)->print();
}

void Menu::processHarmoniousGraphColoring() const
{
    std::cout << "You have chosen to solve harmonious graph coloring." << std::endl;

    int method = getSolvingMethod();
    int resultType = getResultTypeOptions();

    performHarmoniousGraphColoring(method, resultType);
}

void Menu::processBinaryGameSolving() const
{
    std::cout << "You have chosen to solve binary game." << std::endl;

    int method = getSolvingMethod();
    int resultType = getResultTypeOptions();

    performBinaryGameSolving(method, resultType);
}

void Menu::printSolvingOptions() const
{
    std::cout << "\nHow would you like to solve problem?" << std::endl;

    std::cout << "1. Use backtracking." << std::endl;
    std::cout << "2. Use forward checking." << std::endl;
}

void Menu::printResultTypeOptions() const
{
    std::cout << "\nWhat should be the result of solving?" << std::endl;

    std::cout << "1. Print first found solution." << std::endl;
    std::cout << "2. Print number of all found solutions." << std::endl;
    std::cout << "3. Find all solutions and print first 10." << std::endl;
}

void Menu::printVariableGetters() const
{
    std::cout << "\nHow should be done getting next variable to evaluate?" << std::endl;

    std::cout << "1. Standard in-order." << std::endl;
    std::cout << "2. Get variable with most constraints." << std::endl;
}

void Menu::printValueGetters() const
{
    std::cout << "\nHow should be done getting next variable to evaluate?" << std::endl;

    std::cout << "1. Standard in-order." << std::endl;
    std::cout << "2. Get value with the least occurrence." << std::endl;
}

int Menu::getSolvingMethod() const
{
    std::string choice = "";
    int method;
    bool isCorrect = false;

    do
    {
        printSolvingOptions();

        method = getPositiveNumberInput();

        if (method <= 0 || method >= 3)
            std::cout << "\nOoops! Number wasn't correct. Try again." << std::endl;
        else
            isCorrect = true;
    } while (! isCorrect);

    return method;
}

int Menu::getResultTypeOptions() const
{
    std::string choice = "";
    int resultType;
    bool isCorrect = false;

    do
    {
        printResultTypeOptions();

        resultType = getPositiveNumberInput();

        if (resultType <= 0 || resultType >= 4)
            std::cout << "\nOoops! Number wasn't correct. Try again." << std::endl;
        else
            isCorrect = true;
    } while (! isCorrect);

    return resultType;
}

IVariableGetter* Menu::getVariableGetter() const
{
    std::string choice = "";
    int varGetter;
    bool isCorrect = false;

    do
    {
        printVariableGetters();

        varGetter = getPositiveNumberInput();

        if (varGetter <= 0 || varGetter >= 3)
            std::cout << "\nOoops! Number wasn't correct. Try again." << std::endl;
        else
            isCorrect = true;
    } while (! isCorrect);

    if (varGetter == 1)
        return new NextVariableGetter(nullptr);

    return nullptr;
}

IValueGetter* Menu::getValueGetter() const
{
    std::string choice = "";
    int valGetter;
    bool isCorrect = false;

    do
    {
        printValueGetters();

        valGetter = getPositiveNumberInput();

        if (valGetter <= 0 || valGetter >= 3)
            std::cout << "\nOoops! Number wasn't correct. Try again." << std::endl;
        else
            isCorrect = true;
    } while (! isCorrect);

    if (valGetter == 1)
        return new NextValueGetter(nullptr);

    return nullptr;
}

void Menu::performHarmoniousGraphColoring(int method, int type) const
{
    clock_t startTime = 0;
    clock_t endTime = 0;
    IProblemFactory* hgFactory = new HarmoniousGraphFactory(getGraphSize(), getVariableGetter(), getValueGetter());

    switch (method)
    {
        case 1:
        {
            switch (type)
            {
                case 1:
                {
                    startTime = clock();
                    const ISolution* solution = cspFactory->getFirstSolutionByBacktracking(hgFactory);
                    endTime = clock();
                    solution->print();
                    break;
                }
                case 2:
                {
                    startTime = clock();
                    long long int numberOfSolutions = cspFactory->getNumberOfSolutionsByBacktracking(hgFactory);
                    endTime = clock();
                    std::cout << "Number of solutions is " << numberOfSolutions << "." << std::endl;
                    break;
                }
                case 3:
                {
                    startTime = clock();
                    std::vector<ISolution*>* solutions = cspFactory->getAllSolutionsByBacktracking(hgFactory);
                    endTime = clock();
                    std::cout << "Printing first ten solutions:" << std::endl;
                    printFirstTenSolutions(solutions);
                    break;
                }
                default:
                {
                    std::cout << "Ooops! Something went wrong." << std::endl;
                    break;
                }

            }
            break;
        }

        case 2: {
            switch (type) {
                case 1:
                {
                    startTime = clock();
                    const ISolution* solution = cspFactory->getFirstSolutionByForwardChecking(hgFactory);
                    endTime = clock();
                    solution->print();
                    break;
                }
                case 2:
                {
                    startTime = clock();
                    long long int numberOfSolutions = cspFactory->getNumberOfSolutionsByForwardChecking(hgFactory);
                    endTime = clock();
                    std::cout << "Number of solutions is " << numberOfSolutions << "." << std::endl;
                    break;
                }
                case 3:
                {
                    startTime = clock();
                    std::vector<ISolution *> *solutions = cspFactory->getAllSolutionsByForwardChecking(hgFactory);
                    endTime = clock();
                    std::cout << "Printing first ten solutions:" << std::endl;
                    printFirstTenSolutions(solutions);
                    break;
                }
                default:
                {
                    std::cout << "Ooops! Something went wrong." << std::endl;
                    break;
                }
            }
            break;
        }

        default:
        {
            std::cout << "Ooops! Something went wrong." << std::endl;
            break;
        }
    }

    printf("Time taken: %.100fms\n", (double) (endTime - startTime));

    delete hgFactory;
}

void Menu::performBinaryGameSolving(int method, int type) const
{
    clock_t startTime = 0;
    clock_t endTime = 0;

    int size = getBinarySize();
    int filledFields = getNumberOfFilledFields(size);
    IProblemFactory* bgFactory = new BinaryGameFactory(size, filledFields, getVariableGetter(), getValueGetter());

    switch (method)
    {
        case 1:
        {
            switch (type)
            {
                case 1:
                {
                    startTime = clock();
                    const ISolution* solution = cspFactory->getFirstSolutionByBacktracking(bgFactory);
                    endTime = clock();
                    solution->print();
                    break;
                }
                case 2:
                {
                    startTime = clock();
                    long long int numberOfSolutions = cspFactory->getNumberOfSolutionsByBacktracking(bgFactory);
                    endTime = clock();
                    std::cout << "Number of solutions is " << numberOfSolutions << "." << std::endl;
                    break;
                }
                case 3:
                {
                    startTime = clock();
                    std::vector<ISolution*>* solutions = cspFactory->getAllSolutionsByBacktracking(bgFactory);
                    endTime = clock();
                    std::cout << "Printing first ten solutions:" << std::endl;
                    printFirstTenSolutions(solutions);
                    break;
                }
                default:
                {
                    std::cout << "Ooops! Something went wrong." << std::endl;
                    break;
                }

            }
            break;
        }

        case 2: {
            switch (type) {
                case 1:
                {
                    startTime = clock();
                    const ISolution* solution = cspFactory->getFirstSolutionByForwardChecking(bgFactory);
                    endTime = clock();
                    solution->print();
                    break;
                }
                case 2:
                {
                    startTime = clock();
                    long long int numberOfSolutions = cspFactory->getNumberOfSolutionsByForwardChecking(bgFactory);
                    endTime = clock();
                    std::cout << "Number of solutions is " << numberOfSolutions << "." << std::endl;
                    break;
                }
                case 3:
                {
                    startTime = clock();
                    std::vector<ISolution *> *solutions = cspFactory->getAllSolutionsByForwardChecking(bgFactory);
                    endTime = clock();
                    std::cout << "Printing first ten solutions:" << std::endl;
                    printFirstTenSolutions(solutions);
                    break;
                }
                default:
                {
                    std::cout << "Ooops! Something went wrong." << std::endl;
                    break;
                }
            }
            break;
        }

        default:
        {
            std::cout << "Ooops! Something went wrong." << std::endl;
            break;
        }
    }

    printf("Time taken: %.100fms\n", (double) (endTime - startTime));

    delete bgFactory;
}
