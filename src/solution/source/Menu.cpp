//
// Created by Anna Siwik on 2017-04-15.
//

#include <factories/header/CSPFactory.h>
#include <iostream>
#include <sstream>
#include <factories/header/HarmoniousGraphFactory.h>
#include "solution/header/Menu.h"
#include <factories/header/BinaryGameFactory.h>
#include <accessors/header/MostConstrainedVariableGetter.h>
#include <accessors/header/LeastUsedValueGetter.h>
#include <accessors/header/LeastCrossingOccurrenceValueGetter.h>
#include <accessors/header/MostFilledCrossingVariableGetter.h>
#include <solution/header/Solution.h>

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

int Menu::getNumberFromRange(int min, int max) const
{
    int numberChoice = 0;
    bool isCorrect = false;

    while (!isCorrect)
    {
        std::string choice = "";
        getline(std::cin, choice);

        std::stringstream myStream(choice);

        if (myStream >> numberChoice && numberChoice >= min && numberChoice <= max)
            isCorrect = true;
        else
        {
            std::cout << "\nOoops! Number wasn't correct. Try again.";
            std::cout << " Choose between " << min << " and " << max << "." << std::endl << std::endl;
        }
    }

    return numberChoice;
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

    while ((size = getSizeFor("binary (6, 8, 10, 12 or 14)")) % 2 == 1
           && size != 6 && size != 8 && size != 10 && size != 12 && size != 14)
        std::cout << "\nBinary size must be one of the numbers: 6, 8, 10, 12, 14. Try again." << std::endl;

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
}

void Menu::printVariableGettersForHarmoniousGraph() const
{
    std::cout << "\nHow should be done getting next variable to evaluate?" << std::endl;

    std::cout << "1. Standard in-order." << std::endl;
    std::cout << "2. Get variable with neighbours with the most constraints." << std::endl;
}

void Menu::printValueGettersForHarmoniousGraph() const
{
    std::cout << "\nHow should be done getting next value to evaluate?" << std::endl;

    std::cout << "1. Standard in-order." << std::endl;
    std::cout << "2. Get value with the least occurrence." << std::endl;
}

void Menu::printVariableGettersForBinaryGame() const
{
    std::cout << "\nHow should be done getting next variable to evaluate?" << std::endl;

    std::cout << "1. Standard in-order." << std::endl;
    std::cout << "2. Get variable with the least nulls on crossing." << std::endl;
}

void Menu::printValueGettersForBinaryGame() const
{
    std::cout << "\nHow should be done getting next value to evaluate?" << std::endl;

    std::cout << "1. Standard in-order." << std::endl;
    std::cout << "2. Get value with the least occurrence on crossing." << std::endl;
}

int Menu::getSolvingMethod() const
{
    printSolvingOptions();
    return getNumberFromRange(1, 2);
}

int Menu::getResultTypeOptions() const
{
    printResultTypeOptions();
    return getNumberFromRange(1, 2);
}

IVariableGetter* Menu::getVariableGetterForHarmoniousGraph() const
{
    printVariableGettersForHarmoniousGraph();
    int varGetter = getNumberFromRange(1, 2);

    if (varGetter == 2)
        return new MostConstrainedVariableGetter(nullptr);

    return new NextVariableGetter(nullptr);
}

IValueGetter* Menu::getValueGetterForHarmoniousGraph() const
{
    printValueGettersForHarmoniousGraph();
    int valGetter = getNumberFromRange(1, 2);

    if (valGetter == 2)
        return new LeastUsedValueGetter(nullptr);

    return new NextValueGetter(nullptr);
}

IVariableGetter* Menu::getVariableGetterForBinaryGame() const
{
    printVariableGettersForBinaryGame();
    int varGetter = getNumberFromRange(1, 2);

    if (varGetter == 2)
        return new MostFilledCrossingVariableGetter(nullptr);

    return new NextVariableGetter(nullptr);
}

IValueGetter* Menu::getValueGetterForBinaryGame() const
{
    printValueGettersForBinaryGame();
    int valGetter = getNumberFromRange(1, 2);

    if (valGetter == 2)
        return new LeastCrossingOccurrenceValueGetter(nullptr, nullptr);

    return new NextValueGetter(nullptr);
}

void Menu::performHarmoniousGraphColoring(int method, int type) const
{
    clock_t startTime = 0;
    clock_t endTime = 0;
    IVariableGetter* varGetter = getVariableGetterForHarmoniousGraph();
    IValueGetter* valGetter = getValueGetterForHarmoniousGraph();

    IProblemFactory* hgFactory = new HarmoniousGraphFactory(getGraphSize(), varGetter, valGetter);

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

                    if (solution != nullptr)
                        solution->print();
                    else
                        std::cout << "\nSolution was not found." << std::endl;

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

                    if (solution != nullptr)
                        solution->print();
                    else
                        std::cout << "\nSolution was not found." << std::endl;

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

    std::cout<< "Time taken: " << (endTime - startTime) << " clocks per second"<< std::endl;

    delete hgFactory;
}

void Menu::performBinaryGameSolving(int method, int type) const
{
    clock_t startTime = 0;
    clock_t endTime = 0;

    IVariableGetter* varGetter = getVariableGetterForBinaryGame();
    IValueGetter* valGetter = getValueGetterForBinaryGame();

    int size = getBinarySize();
    int filledFields = getNumberOfFilledFields(size);

    IProblemFactory* bgFactory = new BinaryGameFactory(size, filledFields, varGetter, valGetter);
    valGetter->setProblem(bgFactory->getProblem());

    const ISolution* partialSolution = getSolutionFromPuzzles(size, filledFields);
    bgFactory->readPartialSolution(partialSolution, method == 2);

    std::cout << "Algorithm solves puzzles:" << std::endl;
    partialSolution->print();
    std::cout << std::endl;

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

                    if (solution != nullptr)
                        solution->print();
                    else
                        std::cout << "\nSolution was not found." << std::endl;

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

                    if (solution != nullptr)
                        solution->print();
                    else
                        std::cout << "\nSolution was not found." << std::endl;
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

    std::cout<< "Time taken: " << (endTime - startTime) << " clocks per second"<< std::endl;

    delete partialSolution;
    delete bgFactory;
}

const ISolution* Menu::getSolutionFromPuzzles(int size, int filledFields) const
{
    ISolution* solution;

    switch(size)
    {
        case 6:
            solution = getSolutionFromPuzzles_6_6();
            break;
        case 8:
            solution = getSolutionFromPuzzles_8_8();
            break;
        case 10:
            solution = getSolutionFromPuzzles_10_10();
            break;
        case 12:
            solution = getSolutionFromPuzzles_12_12();
            break;
        case 14:
            solution = getSolutionFromPuzzles_14_14();
            break;
        default: return nullptr;
    }

    int emptyFields = size * size - filledFields;
    solution->resetRandomValues(emptyFields);

    return solution;
}

ISolution* Menu::getSolutionFromPuzzles_6_6() const
{
    int size = 6;
    ISolution* solution = new Solution(size);

    for (int row = 0; row < size; ++row)
        for (int col = 0; col < size; ++col)
            solution->setValue(row, col, binaryPuzzles_6_6[row][col]);

    return solution;
}

ISolution* Menu::getSolutionFromPuzzles_8_8() const
{
    int size = 8;
    ISolution* solution = new Solution(size);

    for (int row = 0; row < size; ++row)
        for (int col = 0; col < size; ++col)
            solution->setValue(row, col, binaryPuzzles_8_8[row][col]);

    return solution;
}

ISolution* Menu::getSolutionFromPuzzles_10_10() const
{
    int size = 10;
    ISolution* solution = new Solution(size);

    for (int row = 0; row < size; ++row)
        for (int col = 0; col < size; ++col)
            solution->setValue(row, col, binaryPuzzles_10_10[row][col]);

    return solution;
}

ISolution* Menu::getSolutionFromPuzzles_12_12() const
{
    int size = 12;
    ISolution* solution = new Solution(size);

    for (int row = 0; row < size; ++row)
        for (int col = 0; col < size; ++col)
            solution->setValue(row, col, binaryPuzzles_12_12[row][col]);

    return solution;
}

ISolution* Menu::getSolutionFromPuzzles_14_14() const
{
    int size = 14;
    ISolution* solution = new Solution(size);

    for (int row = 0; row < size; ++row)
        for (int col = 0; col < size; ++col)
            solution->setValue(row, col, binaryPuzzles_14_14[row][col]);

    return solution;
}
