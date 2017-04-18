//
// Created by Anna Siwik on 2017-04-08.
//

#include <solution/header/Solution.h>
#include <accessors/header/NextValueGetter.h>
#include <iostream>
#include "../header/ForwardChecking.h"

ForwardChecking::ForwardChecking() :
    IConstraintSatisfactionProblem()
{}

// TODO - jeśli którakolwiek domena jest pusta, przestań sprawdzać
ForwardChecking::~ForwardChecking()
{}

void ForwardChecking::setAttributes(IProblemFactory* problemFactory)
{
    problem = problemFactory->getProblem();
    constraint = problemFactory->getConstraint();
    varGetter = problemFactory->getVariableGetter();
    valGetter = problemFactory->getValueGetter();
}

const ISolution* ForwardChecking::getFirstSolution(IProblemFactory* problemFactory)
{
    clearSolutions();
    setAttributes(problemFactory);
    return recursive();
}

long long int ForwardChecking::getNumberOfSolutions(IProblemFactory* problemFactory)
{
    clearSolutions();
    setAttributes(problemFactory);
    recursiveFindNumberOfAll();
    return totalNumberOfSolutions;
}

std::vector<ISolution*>* ForwardChecking::getAllSolutions(IProblemFactory* problemFactory)
{
    clearSolutions();
    setAttributes(problemFactory);
    recursiveFindAll();
    return & solutions;
}

ISolution* ForwardChecking::recursive()
{
    ISolution* solution = nullptr;
    IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
        return new Solution(problem);

    NextValueGetter valueGetter(variable);
    const IValue* value;

    while ((value = valueGetter.getNext()) != nullptr)
    {
        variable->setValue(value);

        std::cout << "\nVARIABLE" << std::endl;
        std::cout << "row: " << variable->getRow() << " col: " << variable->getColumn() << std::endl;
        std::cout<< "assigned value: " << value->getValue() << std::endl;

        constraint->putConstraintsOn(variable, true);

        if ((solution = recursive()) == nullptr)
        {
            if (variable->getRow() == 1 && variable->getColumn() == 1 && variable->getValue()->getValue() == 0)
                std::cout << "COS" << std::endl;

            constraint->putConstraintsOff(variable, true);

            std::cout << "\nVARIABLE" << std::endl;
            std::cout << "row: " << variable->getRow() << " col: " << variable->getColumn() << std::endl;
            std::cout<< "REMOVED value: " << value->getValue() << std::endl;

            variable->setValue(nullptr);
        }
        else
            break;
    }

    return solution;
}


void ForwardChecking::recursiveFindNumberOfAll()
{
    IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
        return;

    NextValueGetter valueGetter(variable);
    const IValue* value;

    while ((value = valueGetter.getNext()) != nullptr)
    {
        variable->setValue(value);

        if (problem->isCompleted())
        {
            ++totalNumberOfSolutions;
            variable->setValue(nullptr);
            continue;
        }
        else
        {
            constraint->putConstraintsOn(variable, true);
            recursiveFindNumberOfAll();

            constraint->putConstraintsOff(variable, true);
            variable->setValue(nullptr);
        }
    }
}

void ForwardChecking::recursiveFindAll()
{
    IVariable* variable = varGetter->getNext();

    if (variable == nullptr)
    {
        solutions.push_back(new Solution(problem));
        return;
    }

    NextValueGetter valueGetter(variable);
    const IValue* value;

    while ((value = valueGetter.getNext()) != nullptr)
    {
        variable->setValue(value);

        constraint->putConstraintsOn(variable, true);
        recursiveFindAll();

        constraint->putConstraintsOff(variable, true);
        variable->setValue(nullptr);
    }
}